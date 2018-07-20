#include <iostream>
#include "sgx.h"
#include "sgx_urts.h"
#include "sgx_uae_service.h"
#include "DrmEnclave_u.h"
#include "ReplayProtectedDRM.h"
#include "trust_ecalls.h"
#include "sgx_tseal.h"
#include "common.h"

using namespace std;

#define ENCLAVE_NAME    "DRM_enclave.signed.so"


ReplayProtectedDRM::ReplayProtectedDRM(): enclave_id(0)
{
    int ret = 0;
    ret = initialize_enclave(&enclave_id, enclave_name, token_name);
    if(ret){
        cout << "failed to initialize enclave" << endl;
    }
}


ReplayProtectedDRM::~ReplayProtectedDRM(void)
{   
    destroy_enclave(enclave_id);
}

uint32_t ReplayProtectedDRM:: init(uint8_t*  stored_sealed_activity_log, uint32_t max_release)
{
    int ret = 0;

    ret = trust_sgx_create_sealed_policy(enclave_id, (uint8_t *)stored_sealed_activity_log, sealed_activity_log_length, max_release);

    return ret;
}


uint32_t ReplayProtectedDRM:: init(uint32_t max_release)
{
    return init(sealed_activity_log, max_release);
}



// uint32_t ReplayProtectedDRM:: perform_function(
//     uint8_t* stored_sealed_activity_log)
// {
//     int ret = 0;

//     ret = trust_sgx_perform_sealed_policy(enclave_id, (uint8_t *)stored_sealed_activity_log, sealed_activity_log_length);

//     return ret;
// }

// uint32_t ReplayProtectedDRM:: perform_function()
// {
//     return perform_function(sealed_activity_log);
// }

uint32_t ReplayProtectedDRM:: update_secret(uint8_t* stored_sealed_activity_log)
{
    int ret = 0;
    ret = trust_sgx_update_sealed_policy(enclave_id, (uint8_t *)stored_sealed_activity_log, sealed_activity_log_length);
    return ret;
}


uint32_t ReplayProtectedDRM::update_secret()
{
    return update_secret(sealed_activity_log); 
}

// uint32_t ReplayProtectedDRM:: delete_secret(uint8_t* stored_sealed_activity_log)
// {
//     int ret = 0;

//     ret = trust_sgx_delete_sealed_policy(enclave_id, (uint8_t *)stored_sealed_activity_log, sealed_activity_log_length);

//     return 0;
// }

// uint32_t ReplayProtectedDRM::delete_secret()
// {
//     return delete_secret(sealed_activity_log);
// }

uint32_t ReplayProtectedDRM::get_left_times(uint8_t* stored_sealed_activity_log, uint64_t *left_times){
    int ret = 0;
    ret = trust_sgx_get_left_times(enclave_id, (uint8_t *)stored_sealed_activity_log, sealed_activity_log_length, left_times);
    return ret;
}

uint32_t ReplayProtectedDRM::get_left_times(uint64_t *left_times){
    return get_left_times(sealed_activity_log, left_times);
}