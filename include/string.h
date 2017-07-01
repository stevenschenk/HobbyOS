#ifndef STRING
#define STRING

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

typedef char * string;

extern size_t strlen(string str);
extern bool strcmp(string stra, string strb);



#endif
