#include "trust_ocalls.h"
#include "stdio.h"
#include "DrmEnclave_u.h"

void ocall_print_string(const char *str)
{
    /* Proxy/Bridge will check the length and null-terminate 
     * the input string to prevent buffer overflow. 
     */
    printf("%s", str);
}

void ocall_log(int level, const char *str){
    printf("%s", str);
}
