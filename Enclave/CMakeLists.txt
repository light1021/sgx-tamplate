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

ADD_CUSTOM_COMMAND(OUTPUT DrmEnclave_t.h DrmEnclave_t.c
    COMMAND ${SGX_EDGER8R} --trusted ${PROJECT_SOURCE_DIR}/Enclave/DrmEnclave.edl --search-path ${PROJECT_SOURCE_DIR}/Enclave --search-path ${SGX_SDK}/include
    COMMENT "make tcode"
)
ADD_CUSTOM_TARGET(
    tcode ALL
    DEPENDS DrmEnclave_t.h DrmEnclave_t.c
)

SET(Crypto_Library_Name sgx_tcrypto)
FILE(GLOB_RECURSE Enclave_Cpp_Files "*.cpp")
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/Include ${PROJECT_SOURCE_DIR}/build/Enclave ${PROJECT_SOURCE_DIR}/Enclave ${PROJECT_SOURCE_DIR}/TrustedLibrary ${PROJECT_SOURCE_DIR}/Enclave/TrustedLibrary ${SGX_SDK}/include ${SGX_SDK}/include/tlibc ${SGX_SDK}/include/libcxx)
SET(Enclave_C_Flags "${SGX_COMMON_CFLAGS} -nostdinc -fvisibility=hidden -fpie -ffunction-sections -fdata-sections -fstack-protector")
SET(Enclave_Cpp_Flags "${Enclave_C_Flags} -std=c++11 -nostdinc++")
SET(Enclave_Link_Flags "${SGX_COMMON_CFLAGS} -Wl,--no-undefined -nostdlib -nodefaultlibs -nostartfiles -L${SGX_LIBRARY_PATH} -Wl,--whole-archive -l${Trts_Library_Name} -Wl,--no-whole-archive -Wl,--start-group -lsgx_tstdc -lsgx_tcxx -lsgx_tkey_exchange -l${Crypto_Library_Name} -l${Service_Library_Name} -Wl,--end-group -Wl,-Bstatic -Wl,-Bsymbolic -Wl,--no-undefined -Wl,-pie,-eenclave_entry -Wl,--export-dynamic -Wl,--defsym,__ImageBase=0 -Wl,--gc-sections -Wl,--version-script=${PROJECT_SOURCE_DIR}/Enclave/Enclave.lds")
#设置产生so文件的链接选项注意一下-Wl,--whole-archive -l${Trts_Library_Name} -Wl,--no-whole-archive 
#-Wl,--start-group -lsgx_tstdc -lsgx_tcxx -l${Crypto_Library_Name} -l${Service_Library_Name} 
#-Wl,--end-group 这些部分，连接的时候要把sgx_trts库所有相关的都要连接上，不然会报上一大堆错误，
#后面的不需要全部链接相关的库，只需要链接对应的库即可在makefile中的原文如下：
# To generate a proper enclave, it is recommended to follow below guideline to link the trusted libraries:
#    1. Link sgx_trts with the `--whole-archive' and `--no-whole-archive' options,
#       so that the whole content of trts is included in the enclave.
#    2. For other libraries, you just need to pull the required symbols.
#       Use `--start-group' and `--end-group' to link these libraries.
# Do NOT move the libraries linked with `--start-group' and `--end-group' within `--whole-archive' and `--no-whole-archive' options.
# Otherwise, you may get some undesirable errors.
SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_C_FLAGS ${Enclave_C_Flags})#设置Cmake编译C文件的编译选项
SET(CMAKE_CXX_FLAGS ${Enclave_Cpp_Flags})#设置CMake编译Cpp文件的编译选项
SET(CMAKE_SHARED_LINKER_FLAGS ${Enclave_Link_Flags})#设置共享库的链接选项
LINK_DIRECTORIES(${SGX_LIBRARY_PATH})#共享库链接其他库的时候的搜索路径，此处是SDK中提供的静态库
ADD_LIBRARY(DrmEnclave SHARED ${Enclave_Cpp_Files} ${PROJECT_SOURCE_DIR}/build/Enclave/DrmEnclave_t.c)#生成libenclave.so
#ADD_LIBRARY(enclave SHARED Enclave.cpp TrustedLibrary/Libcxx.cpp TrustedLibrary/seal.cpp ../build/Enclave_t.c)#生成libenclave.so

TARGET_LINK_LIBRARIES(DrmEnclave sgx_trts)#链接libenclave.so需要的库
TARGET_LINK_LIBRARIES(DrmEnclave sgx_tkey_exchange sgx_tservice sgx_tcrypto sgx_tcxx sgx_tstdc)#链接libenclave.so需要的库

########################################################################
#同样的问题，使用手动签名
ADD_CUSTOM_COMMAND(OUTPUT DrmEnclave.signed.so
    COMMAND ${SGX_ENCLAVE_SIGNER} sign -key ${PROJECT_SOURCE_DIR}/Enclave/Enclave_private.pem -enclave ${PROJECT_SOURCE_DIR}/build/Enclave/libDrmEnclave.so -out ${PROJECT_SOURCE_DIR}/build/TrustedLibrary/DrmEnclave.signed.so -config ${PROJECT_SOURCE_DIR}/Enclave/Enclave.config.xml
    DEPENDS DrmEnclave
    COMMENT "sign"
)

ADD_CUSTOM_TARGET(
    sign ALL
    DEPENDS DrmEnclave.signed.so
)
