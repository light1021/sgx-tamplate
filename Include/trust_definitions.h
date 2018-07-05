#ifndef _TRUST_DEFINITIONS_H
#define _TRUST_DEFINITIONS_H
#include "sgx_error.h"
#define MAX_DATA_LEN 1024 * 1024 * 10
#define IV_SIZE 12

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

#define TIME_BASED_LOG_SIZE 1024
#define COUNT_BASED_LOG_SIZE 1024

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



#define PLATFORM_SERVICE_DOWNGRADED 0xF001

#define REPLAY_DETECTED             0xF002
#define MAX_RELEASE_REACHED         0xF003

/* equal to sgx_calc_sealed_data_size(0,sizeof(replay_protected_pay_load))) */ 
#define SEALED_REPLAY_PROTECTED_PAY_LOAD_SIZE 620
#define REPLAY_PROTECTED_PAY_LOAD_MAX_RELEASE_VERSION 5

#define TIMESOURCE_CHANGED          0xF004
#define TIMESTAMP_UNEXPECTED        0xF005
#define LEASE_EXPIRED               0xF006

/* equal tosgx_calc_sealed_data_size(0,sizeof(time_based_pay_load))) */ 
#define TIME_BASED_PAY_LOAD_SIZE 624
#define TIME_BASED_LEASE_DURATION_SECOND 3

#endif