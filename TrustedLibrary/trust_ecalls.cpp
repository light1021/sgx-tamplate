#include "DrmEnclave_u.h"
#include "trust_ecalls.h"
#include <iostream>
using namespace std;


int trust_sgx_create_sealed_policy(sgx_enclave_id_t eid, uint8_t* sealed_log, size_t sealed_log_size, uint32_t max_release){
    int ret = 0;

    sgx_status_t sgx_ret = SGX_ERROR_UNEXPECTED;
    sgx_ps_cap_t ps_cap;
    memset(&ps_cap, 0, sizeof(sgx_ps_cap_t));
    sgx_ret = sgx_get_ps_cap(&ps_cap);
    if (sgx_ret)
    {
        cerr<<"cannot get platform service capability, error code = 0x"<< hex
            << sgx_ret <<endl;
        return sgx_ret;
    }
    if (!SGX_IS_MONOTONIC_COUNTER_AVAILABLE(ps_cap))
    {
        cerr<<"monotonic counter is not supported"<<endl;
        return SGX_ERROR_SERVICE_UNAVAILABLE;
    }
    
    sgx_ret = ecall_create_sealed_policy(eid, &ret, sealed_log, sealed_log_size, max_release);
    if (sgx_ret)
    {
        cerr<<"call create_sealed_policy fail, error code = 0x"<< hex<< sgx_ret
            <<endl;
        return sgx_ret;
    } 
    if (ret)
    {
        cerr<<"cannot create_sealed_policy, function return fail, error code ="
            "0x"<< hex<< ret <<endl;
        return ret;
    }

    return ret;
}

int trust_sgx_perform_sealed_policy(sgx_enclave_id_t eid, uint8_t* sealed_log, size_t sealed_log_size){
    int ret = 0;

    sgx_status_t sgx_ret = SGX_ERROR_UNEXPECTED;
    sgx_ret = ecall_perform_sealed_policy(eid, &ret, sealed_log, sealed_log_size);
    if (sgx_ret)
    {
        cerr<<"call perform_sealed_policy fail, error code = 0x"<< hex<< sgx_ret
            <<endl;
        return sgx_ret;
    } 
    if (ret)
    {
        cerr<<"cannot perform_sealed_policy, function return fail, error code ="
            "0x"<< hex<< ret <<endl;
        return ret;
    }

    return ret;
}

int trust_sgx_update_sealed_policy(sgx_enclave_id_t eid, uint8_t* sealed_log, size_t sealed_log_size){
    int ret = 0;

    sgx_status_t sgx_ret = SGX_ERROR_UNEXPECTED;

    sgx_ret = ecall_update_sealed_policy(eid, &ret, sealed_log, sealed_log_size);
    if (sgx_ret)
    {
        cerr<<"call update_sealed_policy fail, error code = 0x"<< hex<< sgx_ret
            <<endl;
        return sgx_ret;
    } 
    if (ret)
    {
        cerr<<"cannot update_sealed_policy, function return fail, error code ="
            "0x"<< hex<< ret <<endl;
        return ret;
    }

    return ret;
}

int trust_sgx_delete_sealed_policy(sgx_enclave_id_t eid, uint8_t* sealed_log, size_t sealed_log_size){
    int ret = 0;

    sgx_status_t sgx_ret = SGX_ERROR_UNEXPECTED;


    sgx_ret = ecall_delete_sealed_policy(eid, &ret, sealed_log, sealed_log_size);
    if (sgx_ret)
    {
        cerr<<"call delete_sealed_policy fail, error code = 0x"<< hex<< sgx_ret 
            <<endl;
        return sgx_ret;
    } 
    if (ret)
    {
        cerr<<"cannot delete_sealed_policy, function return fail, error code ="
            "0x"<< hex<< ret <<endl;
        return ret;
    }

    return ret;
}

int trust_sgx_create_time_based_policy(sgx_enclave_id_t eid, uint8_t* sealed_log, size_t sealed_log_size, uint32_t lease_duration){
    int ret = 0;

    sgx_status_t sgx_ret = SGX_ERROR_UNEXPECTED;
    sgx_ps_cap_t ps_cap;
    memset(&ps_cap, 0, sizeof(sgx_ps_cap_t));
    sgx_ret = sgx_get_ps_cap(&ps_cap);
    if (sgx_ret)
    {
        cerr<<"cannot get platform service capability, error code = 0x"<< hex<<
            sgx_ret <<endl;
        return sgx_ret;
    }
    if (!SGX_IS_TRUSTED_TIME_AVAILABLE(ps_cap))
    {
        cerr<<"trusted time is not supported"<<endl;
        return SGX_ERROR_SERVICE_UNAVAILABLE;
    }
    uint32_t enclave_ret = 0;
    sgx_ret = ecall_create_time_based_policy(eid, &ret, sealed_log, sealed_log_size, lease_duration);
    if (sgx_ret)
    {
        cerr<<"call create_time_based_policy fail, error code = 0x"<< hex<<
            sgx_ret <<endl;
        return sgx_ret;
    } 
    if (ret)
    {
        cerr<<"cannot create_time_based_policy, function return fail, error code = 0x"
            << hex<< ret <<endl;
        return ret;
    }

    return ret;
}

int trust_sgx_perform_time_based_policy(sgx_enclave_id_t eid, const uint8_t* sealed_log, size_t sealed_log_size ){
    int ret = 0;

    sgx_status_t sgx_ret = SGX_ERROR_UNEXPECTED;
    uint32_t enclave_ret = 0;
    sgx_ret = ecall_perform_time_based_policy(eid, &ret, sealed_log, sealed_log_size);
    if (sgx_ret)
    {
        cerr<<"call perform_time_based_policy fail, error code = 0x"<< hex<<
            sgx_ret <<endl;
        return sgx_ret;
    }
    if (ret)
    {
        cerr<<"cannot perform_time_based_policy, function return fail, error code = 0x"
            << hex<< ret <<endl;
        return ret;
    }

    return ret;
}
