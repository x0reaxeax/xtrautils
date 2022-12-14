#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        char *endptr;
        char buf[17] = { 0 };
        char *prefix = (strncmp(argv[i], "0x", 2) == 0) ? argv[i] + 2 : argv[i];
        size_t cpysz = (strlen(prefix) > 16) ? 16 : strlen(prefix);
        strncpy(buf, prefix, cpysz);
        unsigned long long num = strtoull(buf, &endptr, 16);
        cpysz = ((size_t) endptr - (size_t) prefix);
        cpysz = (cpysz > sizeof(buf) - 1) ? sizeof(buf) - 1 : cpysz;
        if (*endptr == 0) {
            printf("['0x%s'] = %llu\n", buf, num);
        }
    }
    return 0;
}
