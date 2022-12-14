#include <stdio.h>
#include <string.h>



int main(int argc, const char *argv[]) {
    if (argc < 3) {
        return 1;
    }

    int (*scmp)(const char *str1, const char *str2, size_t nbytes) = strncmp;

    if (0 == strncmp(argv[1], "-i", strlen(argv[2]))) {
        scmp = strncasecmp;
    }

    size_t arg1_slen = strlen(argv[argc - 2]);
    size_t arg2_slen = strlen(argv[argc - 1]);

    if (arg1_slen == arg2_slen) {
        if (0 == scmp(argv[argc - 2], argv[argc - 1], arg1_slen)) {
            printf("[+] Match\n");
            return 0;
        }
    }

    printf("[-] Mismatch\n");
    return 0;
}
