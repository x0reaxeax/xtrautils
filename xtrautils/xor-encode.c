#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, const char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "usage: %s bytes string\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t slen_rbytes = strlen(argv[1]);
    size_t slen_xorstr = strlen(argv[2]);

    if (0 != (slen_rbytes % 2) || slen_xorstr != (slen_rbytes / 2)) {
        fprintf(stderr, "[-] invalid data (%zu / %zu)\n", slen_rbytes, slen_xorstr);
        return EXIT_FAILURE;
    }

    printf("[+] xor str: ");
    for (size_t i = 0, j = 0; i < slen_rbytes; i+=2, j++) {
        unsigned char byte;
        unsigned char cbuf[2] = { 0 };
        memcpy(cbuf, &argv[1][i], sizeof(cbuf));
        byte = (unsigned char) strtol(cbuf, NULL, 16);
        printf("\\x%02x", byte ^ argv[2][j]);
    }

    printf("[+] hex str: ");
    for (size_t i = 0; i < slen_xorstr; i++) {
        printf("0x%02x ", (unsigned char) argv[2][i]);
    }
    putchar('\n');
    
    return EXIT_SUCCESS;
}
