#ifndef _TRUST_ECALLS_H_
#define _TRUST_ECALLS_H_
#include <stdint.h>
#include <string>
#include <sgx_eid.h>
#include <sgx_uae_service.h>
#include "definitions.h"
/* define ECALLs here. */

void ecalls_say_hello(sgx_enclave_id_t eid, std::string name);

#endif