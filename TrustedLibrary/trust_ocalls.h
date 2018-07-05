#ifndef _TRUST_OCALLS_H_
#define _TRUST_OCALLS_H_

#if defined(__cplusplus)
extern "C" {
#endif

void ocall_print_string(const char *str);

void ocall_log(int level, const char *str);

#if defined(__cplusplus)
}
#endif
#endif