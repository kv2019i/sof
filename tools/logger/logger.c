// SPDX-License-Identifier: BSD-3-Clause
//
// Copyright(c) 2018 Intel Corporation. All rights reserved.
//
// Author: Bartosz Kokoszko	<bartoszx.kokoszko@linux.intel.com>
//	   Artur Kloniecki	<arturx.kloniecki@linux.intel.com>

#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <stdbool.h>
#include <termios.h>

#include <sys/types.h>
#include <dirent.h>

#include "config.h"

#if HAS_INOTIFY
#include <poll.h>
#include <sys/inotify.h>
#include <sys/stat.h>
#endif

#include "convert.h"
#include "misc.h"

#define APP_NAME "sof-logger"

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))
#endif

static const char *debugfs[] = {
	"dmac0", "dmac1", "ssp0", "ssp1",
	"ssp2", "iram", "dram", "shim",
	"mbox", "etrace",
	"hda", "pp", "dsp",
};

/** See PLATFORM_DEFAULT_CLOCK in the firmware code. */
static const float DEFAULT_CLOCK_MHZ = 19.2;

static void usage(void)
{
	fprintf(stdout, "Usage %s <option(s)> <file(s)>\n", APP_NAME);
	fprintf(stdout, "%s:\t \t\t\tDisplay mailbox or DMA trace contents\n", APP_NAME);
	fprintf(stdout, "%s:\t -i infile -o outfile\tDump infile contents "
		"to outfile\n", APP_NAME);
	fprintf(stdout, "%s:\t -l *.ldc_file\t\t.ldc input file generated by smex\n",
		APP_NAME);
	fprintf(stdout, "%s:\t -p \t\t\tInput from stdin\n", APP_NAME);
	fprintf(stdout, "%s:\t -v ver_file\t\tUse ver_file instead of "
		"/sys/kernel/debug/sof/fw_version\n", APP_NAME);
	fprintf(stdout, "%s:\t -n\t\t\tDo not compare dictionary checksums\n",
		APP_NAME);
	fprintf(stdout, "%s:\t -c clock\t\tSet timestamp clock in MHz, %.2f MHz by default\n",
		APP_NAME, DEFAULT_CLOCK_MHZ);
	fprintf(stdout, "%s:\t -s state_name\t\tTake a snapshot of state\n",
		APP_NAME);
	fprintf(stdout, "%s:\t -t\t\t\tDMA 'trace' stream instead of 'etrace' error mailbox\n",
		APP_NAME);
	fprintf(stdout, "%s:\t -u baud\t\tInput data from a UART\n", APP_NAME);
	fprintf(stdout, "%s:\t -r\t\t\tLess formatted output for "
		"chained log processors\n",
		APP_NAME);
	fprintf(stdout, "%s:\t -L\t\t\tHide log location in source code\n",
		APP_NAME);
	fprintf(stdout,
		"%s:\t -e 0/1\t\t\tTimestamps relative to first entry seen. Defaults to\n",
		APP_NAME);
	fprintf(stdout, "%s:\t\t\t\tabsolute when -r(aw), relative otherwise.\n",
		APP_NAME);
	fprintf(stdout, "%s:\t -f precision\t\tSet timestamp precision\n",
		APP_NAME);
	fprintf(stdout, "%s:\t -g\t\t\tHide timestamp\n",
		APP_NAME);
	fprintf(stdout, "%s:\t -d *.ldc_file \t\tDump ldc_file information\n",
		APP_NAME);
	fprintf(stdout, "%s:\t -F filter\t\tUpdate trace filter, format: "
		"<level>=<comp1>[, <comp2>]\n",
		APP_NAME);
	exit(0);
}

static int snapshot(const char *name)
{
	const char *path = "/sys/kernel/debug/sof";
	uint32_t val, addr;
	char pinname[64], poutname[64], buffer[128];
	FILE *in_fd, *out_fd;
	int i, count;

	if (!name) {
		fprintf(stderr, "error: need snapshot name\n");
		return -EINVAL;
	}

	for (i = 0; i < ARRAY_SIZE(debugfs); i++) {

		sprintf(pinname, "%s/%s", path, debugfs[i]);
		sprintf(poutname, "%s.%s.txt", name, debugfs[i]);

		/* open debugfs for reading */
		in_fd = fopen(pinname, "rb");
		if (!in_fd) {
			fprintf(stderr, "error: unable to open %s for reading: %s\n",
				pinname, strerror(errno));
			continue;
		}

		/* open outfile for writing */
		out_fd = fopen(poutname, "wb");
		if (!out_fd) {
			fprintf(stderr, "error: unable to open %s for writing: %s\n",
				poutname, strerror(errno));
			fclose(in_fd);
			continue;
		}

		fprintf(stdout, "processing %s...\n", pinname);
		addr = 0;

		while (1) {
			count = fread(&val, 1, 4, in_fd);
			if (count != 4)
				break;

			sprintf(buffer, "0x%6.6x: 0x%8.8x\n", addr, val);

			count = fwrite(buffer, 1, strlen(buffer), out_fd);

			addr += 4;
		}

		fclose(in_fd);
		fclose(out_fd);
	}

	return 0;
}

static int configure_uart(const char *file, unsigned int baud)
{
	struct termios tio = {};
	int ret, fd = open(file, O_RDWR | O_NOCTTY);
	if (fd < 0)
		return -errno;

	cfsetspeed(&tio, 115200);
	cfmakeraw(&tio);

	tio.c_iflag |= IGNBRK;

	tio.c_cflag |= CLOCAL | CREAD | HUPCL;

	tio.c_cc[VTIME] = 1;
	tio.c_cc[VMIN] = 1;

	ret = tcsetattr(fd, TCSANOW, &tio);
	return ret < 0 ? -errno : fd;
}

/* Concantenate `config->filter_config` with `input` + `\n` */
static int append_filter_config(struct convert_config *config, const char *input)
{
	char *old_config = config->filter_config;

	/* filer_config can't be NULL for following steps */
	if (!old_config)
		old_config = log_asprintf("%s", "");

	config->filter_config = log_asprintf("%s%s\n", old_config, input);
	free(old_config);
	if (!config->filter_config)
		return -ENOMEM;
	return 0;
}

#if !HAS_INOTIFY
static void *wait_open(const char *watched_dir, const char *expected_file)
{
	assert(HAS_INOTIFY); /* Should never be called */
}
#else
/*
 * This 5 minutes timeout is for "backward compatible safety" in case
 * any user/script of an earlier, pre-inotify version of sof-logger
 * (accidentally?) _expected_ the tool to quit when the driver was not
 * loaded. This expectation was always wrong but an infinite wait is too
 * severe of a punishment. This timeout cannot be too small otherwise it
 * would defeat the new feature.
 */
#ifndef SOF_LOGGER_WAIT_OPEN_TIMEOUT_SECS
#define SOF_LOGGER_WAIT_OPEN_TIMEOUT_SECS (5 * 60)
#endif

/*
 * Using inotify, wait up to 5 minutes for 'expected_name' to appear in
 * 'watched_dir'.  Then return opendir/fopen(expected_name). fopen() and
 * opendir() failures are NOT handled; e.g. NULL from fopen() is just
 * passed through.
 *
 * Returns a FILE * or DIR *
 */
static void *wait_open(const char *watched_dir, const char *expected_file)
{
	if (access(watched_dir, R_OK)) {
		fprintf(stderr, "error: %s() cannot read %s\n", __func__, watched_dir);
		return NULL;
	}

	const int iqueue = inotify_init();
	const int dwatch = inotify_add_watch(iqueue, watched_dir, IN_CREATE);
	struct stat expected_stat;
	void *ret_stream = NULL;

	char * const fpath = malloc(strlen(watched_dir) + 1 + strlen(expected_file) + 1);

	strcpy(fpath, watched_dir);
	strcat(fpath, "/");
	strcat(fpath, expected_file);

	/* Not racy because the inotify watch was set first. */
	if (!access(fpath, F_OK))
		goto fopenit;

	fprintf(stdout, "%s: waiting in %s/ for %s\n", APP_NAME, watched_dir, expected_file);
	fflush(stdout);

	while (1) {
		char evlist[1 * sizeof(struct inotify_event)];
		struct pollfd pfd[1] = {{ .fd = iqueue, .events = POLLIN, .revents = 0 }};
		int pret = poll(pfd, sizeof(pfd) / sizeof(struct pollfd),
				SOF_LOGGER_WAIT_OPEN_TIMEOUT_SECS * 1000);

		if (pret == 0) {
			fprintf(stderr, "error: no %s after waiting %d seconds\n",
				expected_file, SOF_LOGGER_WAIT_OPEN_TIMEOUT_SECS);
			goto cleanup;
		}

		if (pret < 0 || pfd[0].revents != POLLIN) {
			fprintf(stderr, "error: in %s, poll(%s) returned %d, %d\n",
				__func__, watched_dir, pret, pfd[0].revents);
			goto cleanup;
		}

		/* Silence __attribute__((warn_unused_result)) which is
		 * enabled by some Linux distros even when broken in gcc:
		 * https://gcc.gnu.org/bugzilla/show_bug.cgi?id=66425
		 */
		(void)!read(iqueue, evlist, sizeof(evlist));

		if (!access(fpath, F_OK))
			goto fopenit;
	}

fopenit:
	stat(fpath, &expected_stat);
	if ((expected_stat.st_mode & S_IFMT) == S_IFDIR)
		ret_stream = opendir(fpath);
	else
		ret_stream = fopen(fpath, "rb");

cleanup:
	free(fpath);
	inotify_rm_watch(iqueue, dwatch);

	return ret_stream;
}
#endif // HAS_INOTIFY


int main(int argc, char *argv[])
{
	static const char optstring[] = "ho:i:l:ps:c:u:tv:rd:Le:f:gF:n";
	struct convert_config config;
	unsigned int baud = 0;
	const char *snapshot_file = 0;
	int opt, ret = 0;

	config.trace = 0;
	config.clock = DEFAULT_CLOCK_MHZ;
	config.in_file = NULL;
	config.out_file = NULL;
	config.out_fd = NULL;
	config.in_fd = NULL;
	config.ldc_file = NULL;
	config.ldc_fd = NULL;
	config.input_std = 0;
	/* checking fw version is disabled by default */
	config.version_file = "/sys/kernel/debug/sof/fw_version";
	config.version_fd = NULL;
	config.version_fw = 1;
	config.use_colors = 1;
	config.serial_fd = -EINVAL;
	config.raw_output = 0;
	config.dump_ldc = 0;
	config.hide_location = 0;
	config.time_precision = 6;
	config.relative_timestamps = INT_MAX; /* unspecified */
	config.filter_config = NULL;

	while ((opt = getopt(argc, argv, optstring)) != -1) {
		switch (opt) {
		case 'o':
			config.out_file = optarg;
			break;
		case 'i':
			config.in_file = optarg;
			break;
		case 't':
			config.trace = 1;
			break;
		case 'c':
			config.clock = atof(optarg);
			break;
		case 's':
			snapshot_file = optarg;
			break;
		case 'l':
			if (config.ldc_file) {
				fprintf(stderr, "error: Multiple ldc files\n");
				usage();
			}
			config.ldc_file = optarg;
			break;
		case 'p':
			config.input_std = 1;
			break;
		case 'u':
			baud = atoi(optarg);
			break;
		case 'r':
			config.raw_output = 1;
			break;
		case 'v':
			/* enabling checking fw version with ver_file file */
			config.version_file = optarg;
			break;
		case 'n':
			config.version_fw = 0;
			break;
		case 'L':
			config.hide_location = 1;
			break;
		case 'e': {
			int i = atoi(optarg);

			if (i < 0 || 1 < i) {
				fprintf(stderr, "%s: invalid option: -e %s\n",
					APP_NAME, optarg);
				return -EINVAL;
			}
			config.relative_timestamps = i;
			break;
		}
		case 'f':
			config.time_precision = atoi(optarg);
			if (config.time_precision < 0) {
				usage();
				return -EINVAL;
			}
			break;
		case 'g':
			config.time_precision = -1;
			break;
		case 'd':
			if (config.ldc_file) {
				fprintf(stderr, "error: Multiple ldc files\n");
				usage();
			}
			config.dump_ldc = 1;
			config.ldc_file = optarg;
			break;
		case 'F':
			ret = append_filter_config(&config, optarg);
			if (ret < 0)
				return ret;
			break;
		case 'h':
		default: /* '?' */
			usage();
		}
	}

	if (argc != optind) {
		fprintf(stderr, "error: Unused parameter '%s'\n", argv[optind]);
		usage();
	}

	if (snapshot_file)
		return baud ? EINVAL : -snapshot(snapshot_file);

	if (!config.ldc_file) {
		fprintf(stderr, "error: Missing ldc file\n");
		usage();
	}

	config.ldc_fd = fopen(config.ldc_file, "rb");
	if (!config.ldc_fd) {
		ret = errno;
		fprintf(stderr, "error: Unable to open ldc file %s: %s\n",
			config.ldc_file, strerror(ret));
		goto out;
	}

	if (config.out_file) {
		config.out_fd = fopen(config.out_file, "w");
		if (!config.out_fd) {
			ret = errno;
			fprintf(stderr, "error: Unable to open out file %s: %s\n",
				config.out_file, strerror(ret));
			goto out;
		}
	} else {
		config.out_fd = stdout;
	}

	/* trace requested ? */
	if (config.trace)
		config.in_file = "/sys/kernel/debug/sof/trace";

	/* Default value when -e is not specified */
	if (config.relative_timestamps == INT_MAX)
		config.relative_timestamps = config.raw_output ? 0 : 1;

	/* default option with no infile is to dump errors/debug data */
	if (!config.in_file && !config.dump_ldc)
		config.in_file = "/sys/kernel/debug/sof/etrace";

	if (!config.in_file && baud) {
		fprintf(stderr, "error: No UART device specified\n");
		usage();
	}

	if (config.input_std) {
		config.in_fd = stdin;
	} else if (baud) {
		config.serial_fd = configure_uart(config.in_file, baud);
		if (config.serial_fd < 0) {
			ret = -config.serial_fd;
			goto out;
		}
	} else if (config.in_file) {
		static const char sys_debug[] = "/sys/kernel/debug";
		static const char sys_debug_sof[] = "/sys/kernel/debug/sof";
		/* In the future we could add an option to force waiting
		 * for _any_ input file, not just for /sys/kernel/debug/sof/[e]trace
		 */
		config.in_fd = NULL;
		if (!HAS_INOTIFY ||
		    strncmp(config.in_file, sys_debug, strlen(sys_debug))) {
			config.in_fd = fopen(config.in_file, "rb");
		} else { // both inotify and /sys/kernel/debug/
			DIR *dbg_sof = (DIR *)wait_open(sys_debug, "sof");

			if (dbg_sof) {
				closedir(dbg_sof);
				config.in_fd =
					(FILE *)wait_open(sys_debug_sof,
							  config.in_file +
							  strlen(sys_debug_sof) + 1);
			}
		}

		if (!config.in_fd) {
			ret = errno;
			fprintf(stderr,
				"error: Unable to open in file %s: %s\n",
				config.in_file, strerror(ret));
			goto out;
		}
	}
	if (isatty(fileno(config.out_fd)) != 1)
		config.use_colors = 0;

	if (config.version_fw) {
		config.version_fd = fopen(config.version_file, "rb");
		if (!config.version_fd && !config.dump_ldc) {
			ret = errno;
			fprintf(stderr,
				"error: Unable to open version file %s: %s\n",
				config.version_file, strerror(ret));
			goto out;
		}
	}

	ret = -convert(&config);

out:
	/* free memory */
	if (config.filter_config)
		free(config.filter_config);

	/* close files */
	if (config.out_fd)
		fclose(config.out_fd);

	if (config.in_fd)
		fclose(config.in_fd);

	if (config.ldc_fd)
		fclose(config.ldc_fd);

	if (config.version_fd)
		fclose(config.version_fd);

	return ret;
}
