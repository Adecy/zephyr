/*
 * Copyright (c) 2020 Markus Fuchs <markus.fuchs@de.sauter-bc.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#ifndef ZEPHYR_DRIVERS_CRYPTO_CRYPTO_STM32_PRIV_H_
#define ZEPHYR_DRIVERS_CRYPTO_CRYPTO_STM32_PRIV_H_

#if DT_HAS_COMPAT_STATUS_OKAY(st_stm32_cryp) || DT_HAS_COMPAT_STATUS_OKAY(st_stm32_aes)
#define STM32_CRYPTO_CONFIG_TYPEDEF            CRYP_ConfigTypeDef
#elif DT_HAS_COMPAT_STATUS_OKAY(st_stm32l4_aes)
#define STM32_CRYPTO_CONFIG_TYPEDEF            CRYP_InitTypeDef
#else
#error No STM32 HW Crypto Accelerator in device tree
#endif

/* Maximum supported key length is 256 bits */
#define CRYPTO_STM32_AES_MAX_KEY_LEN (256 / 8)

struct crypto_stm32_config {
	const struct reset_dt_spec reset;
	struct stm32_pclken pclken;
};

struct crypto_stm32_data {
	CRYP_HandleTypeDef hcryp;
	struct k_sem device_sem;
	struct k_sem session_sem;
};

struct crypto_stm32_session {
	STM32_CRYPTO_CONFIG_TYPEDEF config;
	uint32_t key[CRYPTO_STM32_AES_MAX_KEY_LEN / sizeof(uint32_t)];
	bool in_use;
#if DT_HAS_COMPAT_STATUS_OKAY(st_stm32l4_aes)
	enum cipher_mode mode;
#endif
};

#define CRYPTO_STM32_CFG(dev) \
	((const struct crypto_stm32_config *const)(dev)->config)

#define CRYPTO_STM32_DATA(dev) \
	((struct crypto_stm32_data *const)(dev)->data)

#define CRYPTO_STM32_SESSN(ctx) \
	((struct crypto_stm32_session *const)(ctx)->drv_sessn_state)

static inline void session_set_algorithm(struct crypto_stm32_session *session, uint32_t algorithm)
{
#if !DT_HAS_COMPAT_STATUS_OKAY(st_stm32l4_aes)
	session->config.Algorithm = algorithm;
#endif
}

#endif /* ZEPHYR_DRIVERS_CRYPTO_CRYPTO_STM32_PRIV_H_ */
