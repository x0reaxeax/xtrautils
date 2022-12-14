#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s shellcode\n", argv[0]);
        return 1;
    }

    size_t slen = strlen(argv[1]);
    size_t shellcodesz = 0;

    printf("{ ");
    for (size_t i = 2; i < slen; i += 4, shellcodesz++) {
        printf("0x%c%c%c ", argv[1][i], argv[1][i+1], (i + 2) != slen ? ',' : '\0');
    }

    printf("}\n[+] Shellcode size: %zu\n", shellcodesz);
    printf("[+] Unformatted length: %zu\n", slen);
    return 0;
}
