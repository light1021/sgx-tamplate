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
/*!
*   Gets the required sealed buffer size given plain text size
*   @return size_t - size in bytes required for seal buffer
*   @param enclave_id - target enclave handle
*   @param add - add info size
*   @param plain_len - plain text buffer size
*/
size_t get_sealed_data_len(sgx_enclave_id_t enclave_id, size_t add, size_t plain_len);
/*!
*   Gets the required add info size given sealed buffer size
*   @return size_t - size in bytes required for add info
*   @param enclave_id - target enclave handle
*   @param[in] sealed_buf_ptr - sealed buffer of interst
*   @param sealed_len - size of sealed_len
*/
size_t get_add_mac_len(sgx_enclave_id_t enclave_id, uint8_t* sealed_buf_ptr, uint32_t sealed_len);
/*!
*   Gets the required plain text size given sealed buffer
*   @return size_t - size in bytes required for plain text
*   @param enclave_id - target enclave handle
*   @param[in] sealed_buf_ptr - sealed buffer of interst
*   @param sealed_len - size of sealed_len
*/
size_t get_encrypted_len(sgx_enclave_id_t enclave_id, uint8_t* sealed_buf_ptr, uint32_t sealed_len);
#if defined(__cplusplus)
}
#endif

#endif