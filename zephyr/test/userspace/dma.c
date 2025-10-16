// SPDX-License-Identifier: BSD-3-Clause
/*
 * Copyright(c) 2025 Intel Corporation.
 */

#include <sof/boot_test.h>

#include <zephyr/kernel.h>
#include <zephyr/ztest.h>
#include <zephyr/logging/log.h>
#include <sof/lib/dma.h>
#include <sof/sof_syscall.h>

LOG_MODULE_DECLARE(sof_boot_test, LOG_LEVEL_DBG);

#define USER_STACKSIZE	2048

static struct k_thread user_thread;
static K_THREAD_STACK_DEFINE(user_stack, USER_STACKSIZE);

static void user_function(void *p1, void *p2, void *p3)
{
	uint32_t addr_align = 0xdeadabba;
	struct sof_dma *dma;
	struct dma_config config;
	struct dma_block_config dma_block_cfg;
	struct dma_status stat;
	uint32_t data_buf[64];
	int err, channel;

	__ASSERT(k_is_user_context(), "isn't user");

	LOG_INF("SOF thread %s (%s)",
		k_is_user_context() ? "UserSpace!" : "privileged mode.",
		CONFIG_BOARD_TARGET);

	/*
	 * note: this gets a pointer to kernel memory this thread
	 * cannot access
	 */
	dma = sof_dma_get(SOF_DMA_DIR_LMEM_TO_HMEM, 0, SOF_DMA_DEV_HOST, SOF_DMA_ACCESS_SHARED);

#if NEEDS_FAULT_HANDLING
	/* test passing a invalid kernel handle */
	channel = sof_dma_request_channel(dma + 0x4000, 0);
	LOG_INF("sof_dma_request_channel/invalid: ret %d", channel);
	__ASSERT(channel == -ENOENT, "sof-dma-request-channel with invalid DMA handle");
#endif

	channel = sof_dma_request_channel(dma, 0);
	LOG_INF("sof_dma_request_channel: ret %d", channel);

	err = sof_dma_get_attribute(dma, DMA_ATTR_BUFFER_ADDRESS_ALIGNMENT,
				    &addr_align);
	__ASSERT(!err, "dma-attr-alignment error");
	__ASSERT(addr_align != 0xdeadabba, "dma-attr-alignment not reported");
	LOG_INF("DMA attr: addr alignment %u", addr_align);

	/* set up a DMA transfer */
	memset(&dma_block_cfg, 0, sizeof(dma_block_cfg));
	dma_block_cfg.dest_address = 0; /* host fifo */
	dma_block_cfg.source_address = data_buf;
	dma_block_cfg.block_size = sizeof(data_buf);

	memset(&config, 0, sizeof(config));
	config.channel_direction = MEMORY_TO_HOST;
	config.block_count = 1;
	config.head_block = &dma_block_cfg;

	err = sof_dma_config(dma, channel, &config);
	__ASSERT(!err, "dma-config error");
	LOG_INF("sof_dma_config: success");

	err = sof_dma_start(dma, channel);
	LOG_INF("sof_dma_start: ret %d", err);

	err = sof_dma_reload(dma, channel, sizeof(data_buf) >> 1);
	LOG_INF("sof_dma_reload: ret %d", err);

	err = sof_dma_get_status(dma, channel, &stat);
	LOG_INF("sof_dma_get_status 1: ret %d pend %u free %u", err,
		stat.pending_length, stat.free);

	k_sleep(K_MSEC(10));
	err = sof_dma_get_status(dma, channel, &stat);
	LOG_INF("sof_dma_get_status 2: ret %d pend %u free %u", err,
		stat.pending_length, stat.free);
	err = sof_dma_reload(dma, channel, 1);
	LOG_INF("sof_dma_reload: ret %d", err);

	err = sof_dma_get_status(dma, channel, &stat);
	LOG_INF("sof_dma_get_status 3: ret %d pend %u free %u", err,
		stat.pending_length, stat.free);

	err = sof_dma_stop(dma, channel);
	LOG_INF("sof_dma_stop: ret %d", err);

	sof_dma_release_channel(dma, channel);
	LOG_INF("sof_dma_release_channel: success");

	sof_dma_put(dma);
	LOG_INF("sof_dma_put: success");
}

static void test_user_thread_dma(void)
{
	const struct device *dma;

	k_thread_create(&user_thread, user_stack, USER_STACKSIZE,
			user_function, NULL, NULL, NULL,
			-1, K_USER, K_FOREVER);

	dma = DEVICE_DT_GET(DT_NODELABEL(hda_host_in));
	k_thread_access_grant(&user_thread, dma);

	k_thread_start(&user_thread);
	k_thread_join(&user_thread, K_FOREVER);
}

ZTEST(sof_boot, user_space_dma)
{
	test_user_thread_dma();

	ztest_test_pass();
}
