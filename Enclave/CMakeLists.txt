#set link librarys
IF (${SGX_MODE} STREQUAL "SIM")
    SET(Trts_Library_Name sgx_trts_sim)
ELSEIF(${SGX_MODE} STREQUAL "HW")
    SET(Trts_Library_Name sgx_trts)
ENDIF(${SGX_MODE} STREQUAL "SIM")

IF (${SGX_MODE} STREQUAL "SIM")
    SET(Service_Library_Name sgx_tservice_sim)
ELSEIF(${SGX_MODE} STREQUAL "HW")
    SET(Service_Library_Name sgx_tservice)
ENDIF(${SGX_MODE} STREQUAL "SIM")

ADD_CUSTOM_COMMAND(OUTPUT Enclave_t.h Enclave_t.c
    COMMAND ${SGX_EDGER8R} --trusted ${PROJECT_SOURCE_DIR}/Enclave/Enclave.edl --search-path ${PROJECT_SOURCE_DIR}/Enclave --search-path ${SGX_SSL}/include --search-path ${SGX_SDK}/include 
    COMMENT "make tcode"
)
ADD_CUSTOM_TARGET(
    tcode ALL
    DEPENDS Enclave_t.h Enclave_t.c
)

SET(Crypto_Library_Name sgx_tcrypto)
FILE(GLOB_RECURSE Enclave_Cpp_Files "*.cpp")
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/Include ${PROJECT_SOURCE_DIR}/build/Enclave 
    ${PROJECT_SOURCE_DIR}/Enclave ${PROJECT_SOURCE_DIR}/TrustedLibrary 
    ${PROJECT_SOURCE_DIR}/Enclave/TrustedLibrary ${SGX_SDK}/include ${SGX_SDK}/include/tlibc 
    ${SGX_SDK}/include/libcxx ${SGX_SSL}/include ${SGX_SSL}/include/openssl)
SET(Enclave_C_Flags "${SGX_COMMON_CFLAGS} -nostdinc -fvisibility=hidden -fpie -ffunction-sections -fdata-sections -fstack-protector")
SET(Enclave_Cpp_Flags "${Enclave_C_Flags} -std=c++11 -nostdinc++")
SET(Enclave_Link_Flags "${SGX_COMMON_CFLAGS} -Wl,--no-undefined -nostdlib -nodefaultlibs -nostartfiles -L${SGX_LIBRARY_PATH} -L${SGX_SSL_LIB_PATH} \
    -Wl,--whole-archive -lsgx_tsgxssl -Wl,--no-whole-archive -lsgx_tsgxssl_crypto \
    -Wl,--whole-archive -l${Trts_Library_Name} \
    -Wl,--no-whole-archive -Wl,--start-group -lsgx_tstdc -lsgx_tcxx -lsgx_tkey_exchange \
    -l${Crypto_Library_Name} -l${Service_Library_Name} -Wl,--end-group \
    -Wl,-Bstatic -Wl,-Bsymbolic -Wl,--no-undefined \
    -Wl,-pie,-eenclave_entry -Wl,--export-dynamic -Wl,--defsym,__ImageBase=0 \
    -Wl,--gc-sections -Wl,--version-script=${PROJECT_SOURCE_DIR}/Enclave/Enclave.lds")

SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_C_FLAGS ${Enclave_C_Flags})#设置Cmake编译C文件的编译选项
SET(CMAKE_CXX_FLAGS ${Enclave_Cpp_Flags})#设置CMake编译Cpp文件的编译选项
SET(CMAKE_SHARED_LINKER_FLAGS ${Enclave_Link_Flags})#设置共享库的链接选项
LINK_DIRECTORIES(${SGX_LIBRARY_PATH} ${SGX_SSL_LIB_PATH})#共享库链接其他库的时候的搜索路径，此处是SDK中提供的静态库
ADD_LIBRARY(Enclave SHARED ${Enclave_Cpp_Files} ${PROJECT_SOURCE_DIR}/build/Enclave/Enclave_t.c)#生成libenclave.so
#ADD_LIBRARY(enclave SHARED Enclave.cpp TrustedLibrary/Libcxx.cpp TrustedLibrary/seal.cpp ../build/Enclave_t.c)#生成libenclave.so

TARGET_LINK_LIBRARIES(Enclave sgx_tsgxssl sgx_tsgxssl_crypto sgx_trts)#链接libenclave.so需要的库
TARGET_LINK_LIBRARIES(Enclave sgx_tkey_exchange sgx_tservice sgx_tcrypto sgx_tcxx sgx_tstdc)#链接libenclave.so需要的库


ADD_CUSTOM_COMMAND(OUTPUT Enclave.signed.so
    COMMAND ${SGX_ENCLAVE_SIGNER} sign -key ${PROJECT_SOURCE_DIR}/Enclave/Enclave_private.pem -enclave ${PROJECT_SOURCE_DIR}/build/Enclave/libEnclave.so -out ${PROJECT_SOURCE_DIR}/build/TrustedLibrary/Enclave.signed.so -config ${PROJECT_SOURCE_DIR}/Enclave/Enclave.config.xml
    DEPENDS Enclave
    COMMENT "sign"
)

ADD_CUSTOM_TARGET(
    sign ALL
    DEPENDS Enclave.signed.so
)
