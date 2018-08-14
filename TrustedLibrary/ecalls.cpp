#include "ecalls.h"
#include <iostream>
#include "common.h"
#include "Enclave_u.h"
using namespace std;

void ecalls_say_hello(sgx_enclave_id_t eid, string name){
    const char *tmpname = name.c_str();
    size_t size = name.size();
    sgx_status_t sgx_ret = ecall_say_hello(eid, tmpname, size);
    if (sgx_ret)
    {
        print_error_message(sgx_ret);
        cerr<<"call say hello fail, error code = 0x"<< hex << sgx_ret <<endl;
    } 
}