#ifndef _TRUST_ECALLS_H_
#define _TRUST_ECALLS_H_
#include <stdint.h>
#include <string>
#include <sgx_eid.h>
#include <sgx_uae_service.h>
#include "trust_definitions.h"
/* define ECALLs here. */
int trust_sgx_create_sealed_policy(sgx_enclave_id_t eid, uint8_t* sealed_log, size_t sealed_log_size, uint32_t max_release);
int trust_sgx_perform_sealed_policy(sgx_enclave_id_t eid, uint8_t* sealed_log, size_t sealed_log_size);
int trust_sgx_update_sealed_policy(sgx_enclave_id_t eid, uint8_t* sealed_log, size_t sealed_log_size);
int trust_sgx_delete_sealed_policy(sgx_enclave_id_t eid, uint8_t* sealed_log, size_t sealed_log_size);
int trust_sgx_create_time_based_policy(sgx_enclave_id_t eid, uint8_t* sealed_log, size_t sealed_log_size, uint32_t lease_duration);
int trust_sgx_perform_time_based_policy(sgx_enclave_id_t eid, const uint8_t* sealed_log, size_t sealed_log_size );

#endif