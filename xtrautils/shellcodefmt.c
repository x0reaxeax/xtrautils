#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s -r shellcode\n", argv[0]);
        return 1;
    }

    size_t shiftwidth = 4;
    char *ptr = argv[argc - 1];
    for (int i = 1; i < argc; i++) {
        if (0 == strcmp(argv[i], "-r")) {
            shiftwidth = 2;
            break;
        } else {
            ptr = argv[i];
        }
    }

    size_t slen = strlen(ptr);
    size_t shellcodesz = 0;

    printf("\nBYTE shellcode[] = { \n    ");
    for (size_t i = (4 == shiftwidth) ? 2 : 0; i < slen; i += shiftwidth, shellcodesz++) {
        if (0 != shellcodesz && 0 == (shellcodesz % 8)) {
            printf("\n    ");
        }
        printf("0x%c%c%c ", ptr[i], ptr[i+1], (i + 2) != slen ? ',' : '\0');
    }

    printf("\n};\n[+] Shellcode size: %zu\n", shellcodesz);
    printf("[+] Unformatted length: %zu\n", slen);
    return 0;
}
