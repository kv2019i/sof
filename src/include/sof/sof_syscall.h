/* SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 2025, Intel Corporation.
 */

#ifndef SOF_SYSCALL
#define SOF_SYSCALL

#include <zephyr/drivers/dma.h>
#include <zephyr/toolchain.h>

#include <stdint.h>

__syscall uint32_t sof_local_lock(void);
__syscall void sof_local_unlock(uint32_t flags);

__syscall struct sof_dma *sof_dma_get(uint32_t dir, uint32_t caps, uint32_t dev, uint32_t flags);
__syscall void sof_dma_put(struct sof_dma *dma);

__syscall int sof_dma_get_attribute(struct sof_dma *dma, uint32_t type, uint32_t *value);

__syscall int sof_dma_request_channel(struct sof_dma *dma, uint32_t stream_tag);

__syscall void sof_dma_release_channel(struct sof_dma *dma,
				       uint32_t channel);

__syscall int sof_dma_config(struct sof_dma *dma, uint32_t channel,
			     struct dma_config *config);

__syscall int sof_dma_start(struct sof_dma *dma, uint32_t channel);

__syscall int sof_dma_stop(struct sof_dma *dma, uint32_t channel);

__syscall int sof_dma_get_status(struct sof_dma *dma, uint32_t channel, struct dma_status *stat);

__syscall int sof_dma_reload(struct sof_dma *dma, uint32_t channel, size_t size);

/*
 * TODO:
 * - add reload
 */

#include <zephyr/syscalls/sof_syscall.h>

#endif
