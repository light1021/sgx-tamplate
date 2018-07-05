IF (${SGX_MODE} STREQUAL "SIM")
    SET(Urts_Library_Name sgx_urts_sim)
ELSEIF(${SGX_MODE} STREQUAL "HW")
    SET(Urts_Library_Name sgx_urts)
ENDIF(${SGX_MODE} STREQUAL "SIM")

IF (${SGX_MODE} STREQUAL "SIM")
    SET(Uservice_Library_Name sgx_uae_service_sim)
ELSEIF(${SGX_MODE} STREQUAL "HW")
    SET(Uservice_Library_Name sgx_uae_service)
ENDIF(${SGX_MODE} STREQUAL "SIM")

SET(Trust_Enclave "trustenclave")

FILE(GLOB_RECURSE App_Cpp_Files "*.cpp")   #将App文件夹中的cpp文件列表赋值给APP_CPP_FILES
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/Include ${PROJECT_SOURCE_DIR}/DRM ${PROJECT_SOURCE_DIR}/Test ${PROJECT_SOURCE_DIR}/TrustedLibrary ${SGX_SDK}/include ${PROJECT_SOURCE_DIR}/build/Test)  #包含所需要的头文件，后面记得链接,相当于Makefile文件中“-L”选项
SET(App_C_Flags "${SGX_COMMON_CFLAGS} -fPIC -Wno-attributescmake")#设置编译App文件夹中C文件的文件选项
SET(App_C_Flags "${App_C_Flags} -DDEBUG -UNDEBUG -UEDEBUG")   #设置编译App文件夹中C文件的文件选项
SET(App_Cpp_Flags "${App_C_Flags}")                         #设置编译App文件夹中的CPP文件编译选项行
SET(App_Link_Flags "${SGX_COMMON_CFLAGS} -L/usr/lib -L${SGX_SDK}/lib64 -l${Urts_Library_Name} -lpthread -l${Uservice_Library_Name}")    #设置生成应用程序的链接选项，因为要用到SDK中带有的库
SET(CMAKE_CXX_FLAGS ${App_Cpp_Flags})         #将CMake中编译CPP文件中的编译选项设置成我们自己的选项
SET(CMAKE_C_FLAGS ${App_C_Flags})            #将将CMake中编译C文件中的编译选项设置成我们自己的选项
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${App_Link_Flags}")#设置链接生成可执行文件的时候的链接选项
SET(CMAKE_CXX_STANDARD 11)   #设置C++的std，相当于makefile文件中的-std=c++11
LINK_DIRECTORIES("/usr/lib")    #注意，不可信部分链接的库不再${SDK}/lib64中，而是在/usr/lib中，通过本条指令，这样在链接的时候，我们使用的库Cmake就会在/usr/lib中寻找
find_library(SAMPLE_CRYPTO sample_libcrypto /home/ywl/Documents/sgx-sdk/Test/)
ADD_EXECUTABLE(app ${App_Cpp_Files})#生成可执行文件，这里的可执行文件我们定义的名称是main
TARGET_LINK_LIBRARIES(app pthread ${Trust_Enclave} ${SAMPLE_CRYPTO}) 
#可执行文件需要的库，注意链接库的先后顺序，有的库需要依赖前面的库函数，如果顺序错误，可能会报错，说找不到相应函数
