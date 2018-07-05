#include "ReplayProtectedDRM.h"
#include "TimeBasedDRM.h"
#include <iostream>
#include <string.h>
#include <unistd.h>

using namespace std;
#define memcpy_s(dst,dst_size,src,max_count)  memcpy(dst,src,max_count)
#define Sleep(n) usleep((n)*1000)


uint32_t test_replay_protected_drm_update_limitation()
{
    cout<<endl<<"--------> Replay Protected DRM update limitation:"<<endl;
    uint32_t result = 0;
    ReplayProtectedDRM DRM;
    result = DRM.init(3);
    if(result)
    {
        cerr<<"Initialization the DRM failed."<<endl;
        return result;
    }
    else 
        cout<<"Successfully initialized the DRM."<<endl;
    do{
        for (int i = 0; i <= REPLAY_PROTECTED_PAY_LOAD_MAX_RELEASE_VERSION; i++)
        {
            result = DRM.update_secret();
            if(result == MAX_RELEASE_REACHED)
            {
                cout<<"\tExpected failure."<<endl
                    <<"\tThe DRM secret update limitation reached."<<endl;
                result = 0;
                return result;
            }
            else if(result)
            {
                cerr<<"Updating the DRM secret failed."<<endl;
                break;
            }
            else 
                cout<<"Successfully updated the DRM secret."<<endl;
        }
        if(!result)
        {
            result = 1;
            cerr<<"\tUnexpected success."<<endl
                <<"\tFailed to catch update limitation."<<endl;
        }
    }while(0);
    return result;
}


uint32_t test_time_based_policy_operation()
{
    cout<<endl<<"--------> Time based policy operation:"<<endl;
    TimeBasedDRM DRM;
    uint32_t result = 0;
    result = DRM.init(3);
    if(result)
    {
        cerr<<"Initialization the time based policy failed."<<endl;
        return result;
    }
    else
        cout<<"Successfully initialized the time based policy."<<endl;

    result = DRM.perform_function();
    if(result)
    {
        cerr<<"Performing the time based policy functions failed."<<endl;
        return result;
    }
    else
        cout<<"Successfully performed the time based policy functions."<<endl;
    return 0;
}

uint32_t test_time_based_policy_expiration()
{
    cout<<endl<<"--------> Time based policy expiration:"<<endl;
    TimeBasedDRM DRM;
    uint32_t result = 0;
    result = DRM.init(3);
    if(result)
    {
        cerr<<"Initialization the time based policy failed."<<endl;
        return result;
    }
    else
        cout<<"Successfully initialized the time based policy."<<endl;

    /* wait for time based DRM expiring */
    Sleep((TIME_BASED_LEASE_DURATION_SECOND+1)*1000);
    result = DRM.perform_function();

    if(result== LEASE_EXPIRED)
    {
        cout<<"\tExpected failure."<<endl
            <<"\tTime based policy has expired."<<endl;
        return 0;
    }
    else
    {
        cerr<<"\tUnexpected success."<<endl
            <<"\tTime based policy failed to catch expiration."<<endl;
        return 1;
    }
}

/* Application entry */
int SGX_CDECL main(int argc, char *argv[])
{
    (void)(argc);
    (void)(argv);
    uint32_t result;

    /* trigger update limitation */
    result = test_replay_protected_drm_update_limitation();


    /* normal operation */
    result = test_time_based_policy_operation();
    /* trigger expiration */
    result = test_time_based_policy_expiration();
    
    printf("Enter a character before exit ...\n");
    getchar();
    return 0;
}



