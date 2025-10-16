// SPDX-License-Identifier: BSD-3-Clause
//
// Copyright(c) 2025 Intel Corporation.

#include <sof/lib/dma.h>
#include <sof/sof_syscall.h>
#include <zephyr/kernel.h>
#include <zephyr/internal/syscall_handler.h>

#define SOF_MAX_USERSPACE_DMA_HANDLES		16

#ifdef CONFIG_USERSPACE

struct sof_dma *__sof_dma_objs[SOF_MAX_USERSPACE_DMA_HANDLES];

static inline struct sof_dma *__register_dma(struct sof_dma *dma)
{
	for (int n = 0; n < SOF_MAX_USERSPACE_DMA_HANDLES; n++) {
		if (!__sof_dma_objs[n]) {
			__sof_dma_objs[n] = dma;
			return dma;
		}
	}

	return NULL;
}

static inline int __unregister_dma(struct sof_dma *dma)
{
	for (int n = 0; n < SOF_MAX_USERSPACE_DMA_HANDLES; n++) {
		if (__sof_dma_objs[n] == dma) {
			__sof_dma_objs[n] = NULL;
			return 0;
		}
	}

	return -1;
}

static inline bool __is_valid(struct sof_dma *dma)
{
	struct sof_dma *dma_ko = NULL;

	for (int n = 0; n < SOF_MAX_USERSPACE_DMA_HANDLES; n++) {
		if (__sof_dma_objs[n] == dma)
			dma_ko = dma;
	}

	/*
	 * use the Zephyr dma.h device handle to check calling
	 * thread has access to it
	 */
	if (dma_ko && k_object_is_valid(dma_ko->z_dev, K_OBJ_ANY))
		return true;

	return false;
}

static inline struct sof_dma *z_vrfy_sof_dma_get(uint32_t dir, uint32_t cap,
						 uint32_t dev, uint32_t flags)
{
	/*
	 * TODO:
	 * - check whether caller has access to underlying
	 *   dma->z_dev?
	 */
	struct sof_dma *dma = z_impl_sof_dma_get(dir, cap, dev, flags);

	return __register_dma(dma);
}
#include <zephyr/syscalls/sof_dma_get_mrsh.c>

static inline void z_vrfy_sof_dma_put(struct sof_dma *dma)
{
	K_OOPS(!__is_valid(dma));

	if (!__unregister_dma(dma))
		z_impl_sof_dma_put(dma);
}
#include <zephyr/syscalls/sof_dma_put_mrsh.c>

static inline int z_vrfy_sof_dma_get_attribute(struct sof_dma *dma, uint32_t type, uint32_t *value)
{
	K_OOPS(!__is_valid(dma));
	K_OOPS(K_SYSCALL_MEMORY_WRITE(value, sizeof(*value)));

	return z_impl_sof_dma_get_attribute(dma, type, value);
}
#include <zephyr/syscalls/sof_dma_get_attribute_mrsh.c>

static inline int z_vrfy_sof_dma_request_channel(struct sof_dma *dma, uint32_t stream_tag)
{
	K_OOPS(!__is_valid(dma));

	return z_impl_sof_dma_request_channel(dma, stream_tag);
}
#include <zephyr/syscalls/sof_dma_request_channel_mrsh.c>

static inline void z_vrfy_sof_dma_release_channel(struct sof_dma *dma,
				    uint32_t channel)
{
	K_OOPS(!__is_valid(dma));

	return z_impl_sof_dma_release_channel(dma, channel);
}
#include <zephyr/syscalls/sof_dma_release_channel_mrsh.c>

static inline int z_vrfy_sof_dma_config(struct sof_dma *dma, uint32_t channel,
					struct dma_config *config)
{
	struct dma_block_config blk_cfg;

	/*
	 * TODO:
	 *  - complete verification of the pointers in config
	 */
	K_OOPS(!__is_valid(dma));
	K_OOPS(K_SYSCALL_MEMORY_READ(config, sizeof(*config)));
	K_OOPS(K_SYSCALL_MEMORY_READ(config->head_block, sizeof(blk_cfg)));
	K_OOPS(k_usermode_from_copy(&blk_cfg, config->head_block, sizeof(blk_cfg)));

	/* TODO: add support for multiple blocks */
	K_OOPS(config->block_count != 1);
	K_OOPS(blk_cfg.next_block != NULL);

	if (blk_cfg.dest_address)
		K_OOPS(K_SYSCALL_MEMORY_WRITE((void *)blk_cfg.dest_address, blk_cfg.block_size));

	if (blk_cfg.source_address)
		K_OOPS(K_SYSCALL_MEMORY_READ((void *)blk_cfg.source_address, blk_cfg.block_size));

	return z_impl_sof_dma_config(dma, channel, config);
}
#include <zephyr/syscalls/sof_dma_config_mrsh.c>

static inline int z_vrfy_sof_dma_start(struct sof_dma *dma, uint32_t channel)
{
	K_OOPS(!__is_valid(dma));

	return z_impl_sof_dma_start(dma, channel);
}
#include <zephyr/syscalls/sof_dma_start_mrsh.c>

static inline int z_vrfy_sof_dma_stop(struct sof_dma *dma, uint32_t channel)
{
	K_OOPS(!__is_valid(dma));

	return z_impl_sof_dma_stop(dma, channel);
}
#include <zephyr/syscalls/sof_dma_stop_mrsh.c>

static inline int z_vrfy_sof_dma_get_status(struct sof_dma *dma, uint32_t channel,
					     struct dma_status *stat)
{
	K_OOPS(!__is_valid(dma));
	K_OOPS(K_SYSCALL_MEMORY_WRITE(stat, sizeof(*stat)));

	return z_impl_sof_dma_get_status(dma, channel, stat);
}
#include <zephyr/syscalls/sof_dma_get_status_mrsh.c>

static inline int z_vrfy_sof_dma_reload(struct sof_dma *dma, uint32_t channel, size_t size)
{
	K_OOPS(!__is_valid(dma));

	return z_impl_sof_dma_reload(dma, channel, size);
}
#include <zephyr/syscalls/sof_dma_reload_mrsh.c>

#endif /* CONFIG_USERSPACE */
