#include "EnclaveApp.h"
#include "sgx_urts.h"
#include "sgx_uae_service.h"
#include "ecalls.h"
#include "common.h"
#include <iostream>
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP
using namespace std;

#define ENCLAVE_NAME    "enclave.signed.so"

EnclaveApp::EnclaveApp(void): enclave_id(0)
{
    int ret = 0;
    ret = initialize_enclave(&enclave_id, enclave_name, token_name);
    if(ret){
        cout << "failed to initialize enclave" << endl;
    }
}


EnclaveApp::~EnclaveApp(void)
{
    destroy_enclave(enclave_id);
}


void EnclaveApp::sayhello(std::string name){
    ecalls_say_hello(enclave_id, name);
}