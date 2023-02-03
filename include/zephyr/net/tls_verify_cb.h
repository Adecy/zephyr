/*
 * Copyright (c) 2023 Lucas Dietrich <ld.adecy@gmail.com
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/** @file
 * @brief TLS verify callback
 *
 * An structure to register a verify callback for TLS handshake
 */

#ifndef ZEPHYR_INCLUDE_NET_TLS_VERIFY_CB_H_
#define ZEPHYR_INCLUDE_NET_TLS_VERIFY_CB_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Forward declaration of x509 certificate structure from <mbedtls/x509_crt.h>
 */
struct mbedtls_x509_crt;

struct tls_verify_cb {
	/**
	 * @brief Callback function to verify peer certificate
	 *
	 * @param user_data User data passed to the callback via tls_verify_cb
	 * @param crt mbedtls peer certificate structure
	 * @param depth The depth of the certificate in the chain for n to 1, where n is the root
	 * certificate in the chain and 1 is the leaf certificate
	 * @param flags mbedtls verification flags
	 *
	 * @return 0 if the certificate is valid, negative value otherwise
	 */
	int (*callback)(void *user_data, struct mbedtls_x509_crt *crt, int depth, uint32_t *flags);

	/**
	 * @brief User data to be passed to the callback
	 */
	void *user_data;
};

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* ZEPHYR_INCLUDE_NET_TLS_VERIFY_CB_H_ */
