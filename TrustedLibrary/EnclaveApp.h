#pragma once
#include "stdlib.h"
#include "sgx.h"
#include "sgx_urts.h"
#include "definitions.h"
#include <string>

class EnclaveApp
{
public:
    EnclaveApp(void);
    ~EnclaveApp(void);
    void sayhello(std::string name);

private:
    sgx_enclave_id_t enclave_id;
    const char *token_name = "enclave.token";
    const char *enclave_name = "Enclave.signed.so";
};
