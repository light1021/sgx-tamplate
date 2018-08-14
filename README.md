# sgx-template

Make it easier to start a new sgx project with CMake.

## start 

change path to suit your enviroment

```CMakeLists
SET(SGX_LIBRARY_PATH ${SGX_SDK}/lib64)
SET(SGX_SSL_LIB_PATH ${SGX_SSL}/lib64/debug)
SET(SGX_EDGER8R ${SGX_SDK}/bin/x64/sgx_edger8r)
SET(SGX_ENCLAVE_SIGNER ${SGX_SDK}/bin/x64/sgx_sign) 
```

## Usage

```bash
mkdir build
cmake ..
make
```
## Notice

This sample Enclave uses [intel-sgx-ssl](https://github.com/intel/intel-sgx-ssl), you can set up it or delete relation functions.
