#pragma once
#include "stdlib.h"
#include "sgx.h"
#include "sgx_urts.h"
#include "trust_definitions.h"


class ReplayProtectedDRM
{
public:
    ReplayProtectedDRM();
    ~ReplayProtectedDRM(void);
    
    uint32_t init(uint8_t*  stored_sealed_activity_log, uint32_t max_release);
    uint32_t init(uint32_t max_release);
    // uint32_t perform_function();
    // uint32_t perform_function(uint8_t* stored_sealed_activity_log);
    uint32_t update_secret();
    uint32_t update_secret(uint8_t* stored_sealed_activity_log);
    uint32_t get_left_times(uint64_t *left_times);
    uint32_t get_left_times(uint8_t* stored_sealed_activity_log, uint64_t *left_times);

    // uint32_t delete_secret();
    // uint32_t delete_secret(uint8_t* stored_sealed_activity_log);

    // uint32_t get_activity_log(uint8_t* stored_sealed_activity_log);

    
    static const uint32_t sealed_activity_log_length = SEALED_REPLAY_PROTECTED_PAY_LOAD_SIZE;
private:
    uint8_t  sealed_activity_log[sealed_activity_log_length];
    sgx_enclave_id_t enclave_id;
    const char *token_name = "DrmEnclave.token";
    const char *enclave_name = "DrmEnclave.signed.so";

};