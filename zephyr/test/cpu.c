// SPDX-License-Identifier: BSD-3-Clause
/*
 * Copyright(c) 2024 Intel Corporation. All rights reserved.
 *
 * Author: Kai Vehmanen <kai.vehmanen@linux.intel.com>
 */

#include <errno.h>
#include <stdbool.h>

#include <sof/boot_test.h>
#include <sof/lib/cpu.h>

#include <zephyr/logging/log.h>
#include <zephyr/ztest.h>

LOG_MODULE_DECLARE(sof_boot_test, CONFIG_SOF_LOG_LEVEL);

#define T2_STACK_SIZE (2048 + CONFIG_TEST_EXTRA_STACK_SIZE)
struct k_thread t2;
K_THREAD_STACK_DEFINE(t2_stack, T2_STACK_SIZE);

volatile int t2_count;

static void t2_fn(void *a, void *b, void *c)
{
	ARG_UNUSED(a);
	ARG_UNUSED(b);
	ARG_UNUSED(c);

	t2_count = 0;

	while (1) {
		k_sleep(K_USEC(5));
		t2_count++;
	}
}

static int cpu_test(int cpu)
{
	int res = 0;
	int res2;
	int n, m;

	k_tid_t thread = k_thread_create(&t2, t2_stack, T2_STACK_SIZE, t2_fn,
				NULL, NULL, NULL,
				-CONFIG_NUM_COOP_PRIORITIES, 0, K_FOREVER);

	k_thread_cpu_mask_clear(thread);
	k_thread_cpu_mask_enable(thread, cpu);

	for (n = 0; n < 500000; n++) {
		if (!(n & 0xff))
			printk("Test#%d, enable core %d!\n", n, cpu);
		cpu_enable_core(cpu);
		k_thread_start(thread);

		for (m = 0; m < 50000; m++) {
			k_sleep(K_USEC(6));
			if (t2_count) {
				k_thread_abort(thread);
				break;
			}
		}

		if (!t2_count) {
			res = -1;
			goto out;
		}

		cpu_disable_core(cpu);
		k_sleep(K_USEC(10));
	}

out:
	k_thread_abort(thread);
	res2 = k_thread_join(thread, K_MSEC(10));
	if (res2)
		res = res2;

	return res;
}

ZTEST(sof_boot, cpu_boot)
{
	int ret = cpu_test(1);
	int ret2 = cpu_test(2);

	TEST_CHECK_RET(ret + ret2, "cpu_boot2");
}
