#ifndef _B_COMMON_H_
#define _B_COMMON_H_

#if defined(__cplusplus)
extern "C" {
#endif
/*!
*   Create the enclave
*   @return sgx_status_t - SGX_SUCCESS on success, error code otherwise
*   @param[out] enclave_id - target enclave handle
*/
int initialize_enclave(sgx_enclave_id_t *enclave_id, const char *enclave_name, const char *token_name);
/*!
*   Destroy the Barbican enclave
*   @param enclave_id - target enclave handle
*/
void destroy_enclave(sgx_enclave_id_t enclave_id);

#if defined(__cplusplus)
}
#endif

#endif
