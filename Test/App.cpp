#include <iostream>
#include <string.h>
#include <unistd.h>
#include <cstdio>
#include "EnclaveApp.h"

using namespace std;
#define memcpy_s(dst,dst_size,src,max_count)  memcpy(dst,src,max_count)
#define Sleep(n) usleep((n)*1000)


/* Application entry */
int SGX_CDECL main(int argc, char *argv[])
{
    (void)(argc);
    (void)(argv);

    EnclaveApp app;
    string name = "TestEnclave";
    app.sayhello(name);
        
    printf("Enter a character before exit ...\n");
    getchar();
    return 0;
}



