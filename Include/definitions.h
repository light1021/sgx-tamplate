#ifndef _DEFINITIONS_H
#define _DEFINITIONS_H
#include "sgx_error.h"

#define SEALED_ECC_KEY_LENGTH 592

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#if defined(__GNUC__)
#define TOKEN_FILENAME "enclave.token"
#define ENCLAVE_FILENAME "enclave.signed.so"
#endif


typedef struct sealed_ecc_private_key
{
  uint8_t r[SEALED_ECC_KEY_LENGTH];
} sealed_ecc_private_key_t;

typedef struct sealed_ecc_public_key
{
  uint8_t gx[SEALED_ECC_KEY_LENGTH];
  uint8_t gy[SEALED_ECC_KEY_LENGTH];
} sealed_ecc_public_key_t;

enum status
{
  STATUS_OK,
  STATUS_PARAM_ERROR,
  STATUS_UNKNOW
};


#endif