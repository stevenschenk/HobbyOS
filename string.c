#include <string.h>

size_t strlen(string str) {
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

bool strcmp(string stra, string strb) {
    size_t size = strlen(stra);
    if(size != strlen(strb)) return false;

    for(uint8_t i = 0; i < size; i++) {
        if(stra[i] != strb[i]) return false;
    }

    return true;
}