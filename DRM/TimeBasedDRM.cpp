#include "TimeBasedDRM.h"
#include "sgx_urts.h"
#include "sgx_uae_service.h"
#include "trust_ecalls.h"
#include "common.h"
#include <iostream>
using namespace std;

#define ENCLAVE_NAME    "DRM_enclave.signed.so"

TimeBasedDRM::TimeBasedDRM(void): enclave_id(0)
{
    int ret = 0;
    ret = initialize_enclave(&enclave_id, enclave_name, token_name);
    if(ret){
        cout << "failed to initialize enclave" << endl;
    }
}


TimeBasedDRM::~TimeBasedDRM(void)
{
    destroy_enclave(enclave_id);
}

uint32_t TimeBasedDRM:: init(uint8_t*  stored_time_based_policy, uint32_t lease_duration)
{
    int ret = 0;

    ret = trust_sgx_create_time_based_policy(enclave_id, (uint8_t *)stored_time_based_policy, time_based_policy_length, lease_duration);

    return ret;
}


uint32_t TimeBasedDRM:: init(uint32_t lease_duration)
{
    return init(time_based_policy, lease_duration);
}



uint32_t TimeBasedDRM::perform_function(uint8_t* stored_time_based_policy)
{
    int ret = 0;

    ret = trust_sgx_perform_time_based_policy(enclave_id, (uint8_t *)time_based_policy, time_based_policy_length);
    
    return ret;
}

uint32_t TimeBasedDRM::perform_function()
{
    return perform_function(time_based_policy);
}


uint32_t TimeBasedDRM::get_left_time(uint8_t* stored_time_based_policy, uint64_t *left_time){
    int ret = 0;

    ret = trust_sgx_get_left_time(enclave_id, stored_time_based_policy, time_based_policy_length, left_time);
    
    return ret;
}
uint32_t TimeBasedDRM::get_left_time(uint64_t *left_time){
    return get_left_time(time_based_policy, left_time);
}