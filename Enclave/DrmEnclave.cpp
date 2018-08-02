#include "DrmEnclave.h"
#include <stdio.h>
void printf(const char *fmt, ...)
{
	char buf[BUFSIZ] = {'\0'};
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(buf, BUFSIZ, fmt, ap);
	va_end(ap);
	ocall_print_string(buf);
}

static int verify_mc(replay_protected_pay_load* data2verify)
{
    int ret = 0;
    uint32_t mc_value;
    ret = sgx_read_monotonic_counter(&data2verify->mc,&mc_value);
    //printf("verify_mc:%d\n", ret);
    if(ret != SGX_SUCCESS)
    {
        switch(ret)
        {
        case SGX_ERROR_SERVICE_UNAVAILABLE:
            /* Architecture Enclave Service Manager is not installed or not
            working properly.*/
                break;
        case SGX_ERROR_SERVICE_TIMEOUT:
            /* retry the operation later*/
                break;
        case SGX_ERROR_BUSY:
            /* retry the operation later*/
                break;
        case SGX_ERROR_MC_NOT_FOUND:
            /* the the Monotonic Counter ID is invalid.*/
                break;
        default:
            /*other errors*/
            break;
        }
    }
    else if(mc_value!=data2verify->mc_value)
    {
        ret = REPLAY_DETECTED;
    }
    return ret;
}

static int verify_sealed_data(
    const sgx_sealed_data_t* data2unseal,
    replay_protected_pay_load* data_unsealed)
{
    int ret = 0;    
    replay_protected_pay_load temp_unseal;
    uint32_t unseal_length = sizeof(replay_protected_pay_load);

    ret = sgx_unseal_data(data2unseal, NULL, 0,
        (uint8_t*)&temp_unseal, &unseal_length);
    if(ret != SGX_SUCCESS)
    {
        switch(ret)
        {
        case SGX_ERROR_MAC_MISMATCH:
            /* MAC of the sealed data is incorrect.
            The sealed data has been tampered.*/
            break;
        case SGX_ERROR_INVALID_ATTRIBUTE:
            /*Indicates attribute field of the sealed data is incorrect.*/
            break;
        case SGX_ERROR_INVALID_ISVSVN:
            /* Indicates isv_svn field of the sealed data is greater than
            the enclave's ISVSVN. This is a downgraded enclave.*/
            break;
        case SGX_ERROR_INVALID_CPUSVN:
            /* Indicates cpu_svn field of the sealed data is greater than
            the platform's cpu_svn. enclave is  on a downgraded platform.*/
            break;
        case SGX_ERROR_INVALID_KEYNAME:
            /*Indicates key_name field of the sealed data is incorrect.*/
            break;
        default:
            /*other errors*/
            break;
        }
        return ret;
    }
    ret = verify_mc(&temp_unseal);
    if (ret == SGX_SUCCESS)
        memcpy(data_unsealed,&temp_unseal,sizeof(replay_protected_pay_load));
    /* remember to clear secret data after been used by memset_s */
    memset_s(&temp_unseal, sizeof(replay_protected_pay_load), 0,
        sizeof(replay_protected_pay_load));
    return ret;
}





int ecall_create_sealed_policy(uint8_t* sealed_log, size_t sealed_log_size, uint32_t max_release)
{
    int ret = 0;
    int busy_retry_times = 2;
    replay_protected_pay_load data2seal;
    memset(&data2seal, 0, sizeof(data2seal));
    int size = sgx_calc_sealed_data_size(0,
        sizeof(replay_protected_pay_load));
    if(sealed_log_size != size) 
        return SGX_ERROR_INVALID_PARAMETER;
    do{
        ret = sgx_create_pse_session();
    }while (ret == SGX_ERROR_BUSY && busy_retry_times--);
    if (ret != SGX_SUCCESS)
        return ret;
    do
    {
        ret = sgx_create_monotonic_counter(&data2seal.mc,&data2seal.mc_value);
        if(ret != SGX_SUCCESS)
        {
            switch(ret)
            {
            case SGX_ERROR_SERVICE_UNAVAILABLE:
                /* Architecture Enclave Service Manager is not installed or not
                working properly.*/
                break;
            case SGX_ERROR_SERVICE_TIMEOUT:
                /* retry the operation later*/
                break;
            case SGX_ERROR_BUSY:
                /* retry the operation later*/
                break;
            case SGX_ERROR_MC_OVER_QUOTA:
                /* SGX Platform Service enforces a quota scheme on the Monotonic
                Counters a SGX app can maintain. the enclave has reached the
                quota.*/
                break;
            case SGX_ERROR_MC_USED_UP:
                /* the Monotonic Counter has been used up and cannot create
                Monotonic Counter anymore.*/
                break;
            default:
                /*other errors*/
                break;
            }
            break;
        }

        /* secret should be provisioned into enclave after the enclave attests to
        the secret owner.
        For example, the server that delivers the encrypted DRM content.
        In this sample code, a random number is used to represent the secret */ 
        ret = sgx_read_rand(data2seal.secret, REPLAY_PROTECTED_SECRET_SIZE);
        if(ret != SGX_SUCCESS)
            break;
        data2seal.log.release_version = 0;
        /* the secret can be updated for 5 times */
        data2seal.log.max_release_version = 
            max_release;

        /*sealing the plaintext to ciphertext. The ciphertext can be delivered
        outside of enclave.*/
        ret = sgx_seal_data(0, NULL,sizeof(data2seal),(uint8_t*)&data2seal,
            sealed_log_size, (sgx_sealed_data_t*)sealed_log);
    } while (0);
    
    /* remember to clear secret data after been used by memset_s */
    memset_s(&data2seal, sizeof(replay_protected_pay_load), 0,
        sizeof(replay_protected_pay_load));
    sgx_close_pse_session();
    return ret;
}

int ecall_perform_sealed_policy(const uint8_t* sealed_log,
                               size_t sealed_log_size)
{
    int ret = 0;
    int busy_retry_times = 2;
    replay_protected_pay_load data_unsealed;
    if(sealed_log_size != sgx_calc_sealed_data_size(0,
        sizeof(replay_protected_pay_load))) 
        return SGX_ERROR_INVALID_PARAMETER;
    do{
        ret = sgx_create_pse_session();
    }while (ret == SGX_ERROR_BUSY && busy_retry_times--);
    if (ret != SGX_SUCCESS)
        return ret;
    ret = verify_sealed_data((const sgx_sealed_data_t*) sealed_log,
        &data_unsealed);
    if (SGX_SUCCESS == ret)
    {
      /* release the secret to perform the requested functions,
      for example, decrypt the DRM content*/
    }
    else
    {
      /* activity log update fail to verify activity log,
      refuse to release the secret */
    }
    sgx_close_pse_session();

    /* remember to clear secret data after been used by memset_s */
    memset_s(&data_unsealed, sizeof(data_unsealed),
        0, sizeof(replay_protected_pay_load) );
    return ret;

}


int ecall_update_sealed_policy(uint8_t* sealed_log, size_t sealed_log_size)
{
    int ret = 0;
    int busy_retry_times = 2;
    replay_protected_pay_load data_unsealed;
    replay_protected_pay_load data2seal;
    if(sealed_log_size != sgx_calc_sealed_data_size(0,
        sizeof(replay_protected_pay_load))) 
        return SGX_ERROR_INVALID_PARAMETER;
    do{
        ret = sgx_create_pse_session();
    }while (ret == SGX_ERROR_BUSY && busy_retry_times--);
    if (ret != SGX_SUCCESS)
        return ret;
    do
    {
        ret = verify_sealed_data((sgx_sealed_data_t*) sealed_log,
            &data_unsealed);
        if(ret != SGX_SUCCESS)
            break;

        memcpy(&data2seal,&data_unsealed, sizeof(replay_protected_pay_load));

        ret = sgx_increment_monotonic_counter(&data2seal.mc,
            &data2seal.mc_value);
        if(ret != SGX_SUCCESS)
        {
            switch(ret)
            {
            case SGX_ERROR_SERVICE_UNAVAILABLE:
                /* Architecture Enclave Service Manager is not installed or not
                working properly.*/
                break;
            case SGX_ERROR_SERVICE_TIMEOUT:
                /* retry the operation*/
                break;
            case SGX_ERROR_BUSY:
                /* retry the operation later*/
                break;
            case SGX_ERROR_MC_NOT_FOUND:
                /* The Monotonic Counter was deleted or invalidated.
                This might happen under certain conditions.
                For example, the Monotonic Counter has been deleted, the SGX
                Platform Service lost its data or the system is under attack. */
                break;
            case SGX_ERROR_MC_NO_ACCESS_RIGHT:
                /* The Monotonic Counter is not accessible by this enclave.
                This might happen under certain conditions.
                For example, the SGX Platform Service lost its data or the
                system is under attack. */
                break;
            default:
                /*other errors*/
                break;
            }
            break;
        }

        /* If the counter value returns doesn't match the expected value,
        some other entity has updated the counter, for example, another instance
        of this enclave. The system might be under attack */
        if(data2seal.mc_value!= data_unsealed.mc_value+1)
        {
            ret = REPLAY_DETECTED;
            break;
        }

        if(data2seal.log.release_version >= data2seal.log.max_release_version)
        {
            /* the max release version has reached, cannot update. Delete the
            monotonic_counter, whether the deleting is successful or not. */
            (void)sgx_destroy_monotonic_counter(&data2seal.mc);
            ret= MAX_RELEASE_REACHED;
            break;
        }

        /* next release versiona */
        data2seal.log.release_version++;
        /* release next data2seal.secret, here is a sample */
        for(int i = 0; i< REPLAY_PROTECTED_SECRET_SIZE; i++)
            data2seal.secret[i]++;

        /* seal the new log */
        ret = sgx_seal_data(0, NULL, sizeof(data2seal), (uint8_t*)&data2seal,
            sealed_log_size, (sgx_sealed_data_t*)sealed_log);
    } while (0);

    /* remember to clear secret data after been used by memset_s */
    memset_s(&data_unsealed, sizeof(replay_protected_pay_load), 0,
        sizeof(replay_protected_pay_load));

    /* remember to clear secret data after been used by memset_s */
    memset_s(&data2seal, sizeof(replay_protected_pay_load), 0,
        sizeof(replay_protected_pay_load));
    sgx_close_pse_session();
    return ret;
}

int ecall_get_left_times(uint8_t* sealed_log, size_t sealed_log_size, uint64_t *left_times){
    int ret = 0;
    int busy_retry_times = 2;
    replay_protected_pay_load data_unsealed;
    replay_protected_pay_load data2seal;
    if(sealed_log_size != sgx_calc_sealed_data_size(0,
        sizeof(replay_protected_pay_load))) 
        return SGX_ERROR_INVALID_PARAMETER;
    do{
        ret = sgx_create_pse_session();
    }while (ret == SGX_ERROR_BUSY && busy_retry_times--);
    if (ret != SGX_SUCCESS)
        return ret;

    do
    {
        ret = verify_sealed_data((sgx_sealed_data_t*) sealed_log,
            &data_unsealed);
        if(ret != SGX_SUCCESS)
            break;

        memcpy(&data2seal,&data_unsealed, sizeof(replay_protected_pay_load));


        uint64_t tmp = (data2seal.log.max_release_version > data2seal.log.release_version)? 
        data2seal.log.max_release_version - data2seal.log.release_version : 0;
        memcpy(left_times, &tmp, sizeof(uint64_t));

        /* seal the new log */
        sgx_seal_data(0, NULL, sizeof(data2seal), (uint8_t*)&data2seal,
            sealed_log_size, (sgx_sealed_data_t*)sealed_log);
    } while (0);

    /* remember to clear secret data after been used by memset_s */
    memset_s(&data_unsealed, sizeof(replay_protected_pay_load), 0,
        sizeof(replay_protected_pay_load));

    /* remember to clear secret data after been used by memset_s */
    memset_s(&data2seal, sizeof(replay_protected_pay_load), 0,
        sizeof(replay_protected_pay_load));
    sgx_close_pse_session();
    return ret;
}

int ecall_delete_sealed_policy(const uint8_t* sealed_log,
                              size_t sealed_log_size)
{
    int ret = 0;
    int busy_retry_times = 2;
    replay_protected_pay_load data_unsealed;
    if(sealed_log_size != sgx_calc_sealed_data_size(0,
        sizeof(replay_protected_pay_load))) 
        return SGX_ERROR_INVALID_PARAMETER;
    do{
        ret = sgx_create_pse_session();
    }while (ret == SGX_ERROR_BUSY && busy_retry_times--);
    if (ret != SGX_SUCCESS)
        return ret;
    do
    {
        ret = verify_sealed_data((const sgx_sealed_data_t*) sealed_log,
            &data_unsealed);
        if(ret != SGX_SUCCESS)
            break;
        ret = sgx_destroy_monotonic_counter(&data_unsealed.mc);
        if(ret != SGX_SUCCESS)
        {
            switch(ret)
            {
            case SGX_ERROR_SERVICE_UNAVAILABLE:
                /* Architecture Enclave Service Manager is not installed or not
                working properly.*/
                break;
            case SGX_ERROR_SERVICE_TIMEOUT:
                /* retry the operation later*/
                break;
            case SGX_ERROR_BUSY:
                /* retry the operation later*/
                break;
            case SGX_ERROR_MC_NOT_FOUND:
                /* the the Monotonic Counter ID is invalid.*/
                break;
            case SGX_ERROR_MC_NO_ACCESS_RIGHT:
                /* the Monotonic Counter is not accessible by this enclave.
                This might happen under certain conditions.
                For example, the SGX Platform Service lost its data or
                the system is under attack. */
                break;
            default:
                /*other errors*/
                break;
            }
        }
    } while (0);
    /* remember to clear secret data after been used by memset_s */
    memset_s(&data_unsealed, sizeof(replay_protected_pay_load), 0,
        sizeof(replay_protected_pay_load));
    sgx_close_pse_session();
    return ret;
}

/* The secret required to render service is stored together with the time based
policy.If an attack tampered with or destroyed the time based policy data, the
service won't be rendered */ 
#define TIME_BASED_SECRET_SIZE 16
typedef struct _time_based_pay_load
{
    sgx_time_source_nonce_t nonce;
    sgx_time_t timestamp_base;
    uint8_t secret[TIME_BASED_SECRET_SIZE];
    sgx_time_t lease_duration;
}time_based_pay_load;


int ecall_create_time_based_policy(uint8_t* sealed_log,
                                  size_t sealed_log_size, uint32_t lease_duration)
{
    int ret = 0;
    int busy_retry_times = 2;
    time_based_pay_load payload2seal;
    memset(&payload2seal, 0, sizeof(time_based_pay_load));
    int size = sgx_calc_sealed_data_size(0,sizeof(payload2seal));
    if(sealed_log_size != size) 
        return SGX_ERROR_INVALID_PARAMETER;
    do{
        ret = sgx_create_pse_session();
    }while (ret == SGX_ERROR_BUSY && busy_retry_times--);
    if (ret != SGX_SUCCESS)
        return ret;
    do
    {
        ret = sgx_get_trusted_time(&payload2seal.timestamp_base, 
            &payload2seal.nonce);
        if(ret != SGX_SUCCESS)
        {
            switch(ret)
            {
            case SGX_ERROR_SERVICE_UNAVAILABLE:
                /* Architecture Enclave Service Manager is not installed or not
                working properly.*/
                break;
            case SGX_ERROR_SERVICE_TIMEOUT:
                /* retry the operation*/
                break;
            case SGX_ERROR_BUSY:
                /* retry the operation later*/
                break;
            default:
                /*other errors*/
                break;
            }
            break;
        }
        /*secret should be provisioned into enclave after the enclave attests to
        the secret owner, for example, the server that delivers the encrypted
        DRM content.
        In this sample code, a random number is used to represent the secret*/ 
        ret = sgx_read_rand(payload2seal.secret, TIME_BASED_SECRET_SIZE);
        if(ret != SGX_SUCCESS)
            break;
        payload2seal.lease_duration = lease_duration;
        /* sead the pay load */
        ret = sgx_seal_data(0, NULL, 
            sizeof(payload2seal), (uint8_t*)&payload2seal,
            sealed_log_size, (sgx_sealed_data_t*)sealed_log);
    }while(0);
    /* clear the plaintext secret after used */
    memset_s(&payload2seal, sizeof(payload2seal), 0,
        sizeof(time_based_pay_load));
    sgx_close_pse_session();
    return ret;
}

int ecall_perform_time_based_policy(const uint8_t* sealed_log,
                                   size_t sealed_log_size )
{
    int ret = 0;
    int busy_retry_times = 2;
    time_based_pay_load unsealed_data;
    uint32_t data2seal_length = sizeof(time_based_pay_load);

    int size = sgx_calc_sealed_data_size(0,sizeof(time_based_pay_load));
    if(sealed_log_size != size) 
        return SGX_ERROR_INVALID_PARAMETER;


    ret = sgx_unseal_data((const sgx_sealed_data_t*)sealed_log, NULL, 0,
        (uint8_t*)&unsealed_data, &data2seal_length);
    if(ret != SGX_SUCCESS)
    {
        switch(ret)
        {
        case SGX_ERROR_MAC_MISMATCH:
            /* MAC of the sealed data is incorrect. the sealed data has been
            tampered.*/
            break;
        case SGX_ERROR_INVALID_ATTRIBUTE:
            /*Indicates attribute field of the sealed data is incorrect.*/
            break;
        case SGX_ERROR_INVALID_ISVSVN:
            /* Indicates isv_svn field of the sealed data is greater than the
            enclave's ISVSVN. This is a downgraded enclave.*/
            break;
        case SGX_ERROR_INVALID_CPUSVN:
            /* Indicates cpu_svn field of the sealed data is greater than the
            platform's cpu_svn. enclave is  on a downgraded platform.*/
            break;
        case SGX_ERROR_INVALID_KEYNAME:
            /*Indicates key_name field of the sealed data is incorrect.*/
            break;
        default:
            /*other errors*/
            break;
        }
        return ret;
    }
    do{
        ret = sgx_create_pse_session();
    }while (ret == SGX_ERROR_BUSY && busy_retry_times--);
    if (ret != SGX_SUCCESS)
    {
        memset_s(&unsealed_data, sizeof(unsealed_data), 0, 
            sizeof(time_based_pay_load));
        return ret;
    }
    do
    {
        sgx_time_source_nonce_t nonce = {0};
        sgx_time_t current_timestamp;
        ret = sgx_get_trusted_time(&current_timestamp, &nonce);
        if(ret != SGX_SUCCESS)
        {
            switch(ret)
            {
            case SGX_ERROR_SERVICE_UNAVAILABLE:
                /* Architecture Enclave Service Manager is not installed or not
                working properly.*/
                break;
            case SGX_ERROR_SERVICE_TIMEOUT:
                /* retry the operation*/
                break;
            case SGX_ERROR_BUSY:
                /* retry the operation later*/
                break;
            default:
                /*other errors*/
                break;
            }
            break;
        }
        /*source nonce must be the same, otherwise time source is changed and
        the two timestamps are not comparable.*/
        if (memcmp(&nonce,&unsealed_data.nonce,
            sizeof(sgx_time_source_nonce_t)))
        {
            ret  = TIMESOURCE_CHANGED;
            break;
        }

        /* This should not happen. 
        SGX Platform service guarantees that the time stamp reading moves
        forward, unless the time source is changed.*/
        if(current_timestamp < unsealed_data.timestamp_base)
        {
            ret = TIMESTAMP_UNEXPECTED;
            break;
        }
        /*compare lease_duration and timestamp_diff
        if lease_duration is less than difference of current time and base time,
        lease tern has expired.*/
        if(current_timestamp - unsealed_data.timestamp_base >
            unsealed_data.lease_duration)
        {
            ret = LEASE_EXPIRED;
            break;
        }
    }while(0);
    if (SGX_SUCCESS == ret)
    {
      /* release the secret to render service, for example, decrypt the DRM
      content*/
    }
    else
    {
      /* The secret is not released. the service won't be rendered and the DRM
      content can be deleted.*/ 
    }
    /* clear the plaintext secret after used */
    memset_s(&unsealed_data, sizeof(unsealed_data), 0,
        sizeof(time_based_pay_load));
    sgx_close_pse_session();
    return ret;
}


int ecall_get_left_time(const uint8_t* sealed_log,
                                   size_t sealed_log_size,
                                   uint64_t *left_time)
{
    int ret = 0;
    int busy_retry_times = 2;
    time_based_pay_load unsealed_data;
    uint32_t data2seal_length = sizeof(time_based_pay_load);

    int size = sgx_calc_sealed_data_size(0,sizeof(time_based_pay_load));
    if(sealed_log_size != size) 
        return SGX_ERROR_INVALID_PARAMETER;


    ret = sgx_unseal_data((const sgx_sealed_data_t*)sealed_log, NULL, 0,
        (uint8_t*)&unsealed_data, &data2seal_length);
    if(ret != SGX_SUCCESS)
    {
        switch(ret)
        {
        case SGX_ERROR_MAC_MISMATCH:
            /* MAC of the sealed data is incorrect. the sealed data has been
            tampered.*/
            break;
        case SGX_ERROR_INVALID_ATTRIBUTE:
            /*Indicates attribute field of the sealed data is incorrect.*/
            break;
        case SGX_ERROR_INVALID_ISVSVN:
            /* Indicates isv_svn field of the sealed data is greater than the
            enclave's ISVSVN. This is a downgraded enclave.*/
            break;
        case SGX_ERROR_INVALID_CPUSVN:
            /* Indicates cpu_svn field of the sealed data is greater than the
            platform's cpu_svn. enclave is  on a downgraded platform.*/
            break;
        case SGX_ERROR_INVALID_KEYNAME:
            /*Indicates key_name field of the sealed data is incorrect.*/
            break;
        default:
            /*other errors*/
            break;
        }
        return ret;
    }
    do{
        ret = sgx_create_pse_session();
    }while (ret == SGX_ERROR_BUSY && busy_retry_times--);
    if (ret != SGX_SUCCESS)
    {
        memset_s(&unsealed_data, sizeof(unsealed_data), 0, 
            sizeof(time_based_pay_load));
        return ret;
    }
    do
    {
        sgx_time_source_nonce_t nonce = {0};
        sgx_time_t current_timestamp;
        ret = sgx_get_trusted_time(&current_timestamp, &nonce);
        if(ret != SGX_SUCCESS)
        {
            switch(ret)
            {
            case SGX_ERROR_SERVICE_UNAVAILABLE:
                /* Architecture Enclave Service Manager is not installed or not
                working properly.*/
                break;
            case SGX_ERROR_SERVICE_TIMEOUT:
                /* retry the operation*/
                break;
            case SGX_ERROR_BUSY:
                /* retry the operation later*/
                break;
            default:
                /*other errors*/
                break;
            }
            break;
        }
        /*source nonce must be the same, otherwise time source is changed and
        the two timestamps are not comparable.*/
        if (memcmp(&nonce,&unsealed_data.nonce,
            sizeof(sgx_time_source_nonce_t)))
        {
            ret  = TIMESOURCE_CHANGED;
            break;
        }

        /* This should not happen. 
        SGX Platform service guarantees that the time stamp reading moves
        forward, unless the time source is changed.*/
        if(current_timestamp < unsealed_data.timestamp_base)
        {
            ret = TIMESTAMP_UNEXPECTED;
            break;
        }
        /*compare lease_duration and timestamp_diff
        if lease_duration is less than difference of current time and base time,
        lease tern has expired.*/
        uint64_t tmp = (unsealed_data.timestamp_base + unsealed_data.lease_duration > current_timestamp)
         ? unsealed_data.timestamp_base + unsealed_data.lease_duration - current_timestamp : 0;
        //printf("get left time: --> current_timestap: %d\n", current_timestamp);
        memcpy(left_time, &tmp, sizeof(uint64_t));
    }while(0);
    if (SGX_SUCCESS == ret)
    {
      /* release the secret to render service, for example, decrypt the DRM
      content*/
    }
    else
    {
      /* The secret is not released. the service won't be rendered and the DRM
      content can be deleted.*/ 
    }
    /* clear the plaintext secret after used */
    memset_s(&unsealed_data, sizeof(unsealed_data), 0,
        sizeof(time_based_pay_load));
    sgx_close_pse_session();
    return ret;
}