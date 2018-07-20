#pragma once
#include "stdlib.h"
#include "sgx.h"
#include "sgx_urts.h"
#include "trust_definitions.h"

class TimeBasedDRM
{
public:
    TimeBasedDRM(void);
    ~TimeBasedDRM(void);
        uint32_t init(uint8_t*  stored_time_based_policy, uint32_t lease_duration);
    uint32_t init(uint32_t lease_duration);
    
    uint32_t perform_function();
    uint32_t perform_function(uint8_t* stored_time_based_policy);

    uint32_t get_time_based_policy(uint8_t* stored_time_based_policy);
    uint32_t get_left_time(uint8_t* stored_time_based_policy, uint64_t *left_time);
    uint32_t get_left_time(uint64_t *left_time);

    static const uint32_t time_based_policy_length = TIME_BASED_PAY_LOAD_SIZE;
private:
    uint8_t  time_based_policy[time_based_policy_length];
    sgx_enclave_id_t enclave_id;
    const char *token_name = "DrmEnclave.token";
    const char *enclave_name = "DrmEnclave.signed.so";
};
