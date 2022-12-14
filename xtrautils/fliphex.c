#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s hexbytes\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t slen = strlen(argv[1]);
    size_t prefix = 0;

    if (0 == strncmp(argv[1], "0x", 2)) {
        prefix = 2;
        slen -= 2;
    }

    for (size_t i = 0 + prefix; i < slen; i++) {
        if (!isxdigit(argv[1][i])) {
            printf("bad value: argv[1][%zu] - '%c' is not a valid hex digit\n", i, argv[1][i]);
            return EXIT_FAILURE;
        }
    }

    size_t offset = 0;

    char cpybuf[slen + 1];
    memset(cpybuf, 0, slen + 1);

    if (0 != (slen % 2)) {
        offset = 1;
        cpybuf[0] = '0';
    }

    memcpy(&cpybuf[offset], (argv[1] + prefix), slen);

    slen = (0 != (slen % 2)) ? slen + 1 : slen;

    printf("0x");
    for (long i = (slen - 2), j = (slen / 2) - 1; i > ~0; i-=2, j--) {
        char byte[2] = { 0 };
        memcpy(byte, &cpybuf[i], 2);
        printf("%02x", (unsigned char) strtol(byte, NULL, 16));
    }
    putchar('\n');


    return EXIT_SUCCESS;
}
