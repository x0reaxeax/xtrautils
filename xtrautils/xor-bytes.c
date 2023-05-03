#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char byte_t;

int main(int argc, const char *argv[]) {
    if (3 > argc) {
        fprintf(stderr, "usage: %s bytestr xor-byte {diff}\n", argv[0]);
        return EXIT_FAILURE;
    }

    byte_t diff = (4 <= argc) ? (byte_t) (byte_t) strtoul(argv[3], NULL, 0) : 0;
    const byte_t xorbyte = (byte_t) strtoul(argv[2], NULL, 16);
    const size_t strsz = strlen(argv[1]);
    const size_t fmtsz = strsz / 2;
    byte_t afmt[fmtsz];
    
    memset(afmt, 0, fmtsz);
    printf("{ ");
    for (size_t i = 0, j = 0; j < fmtsz; i+=2, j++) {
        byte_t bbuf[2] = { 0 };
        memcpy(bbuf, &argv[1][i], sizeof(bbuf));
        afmt[j] = (byte_t) (((byte_t) strtoul(bbuf, NULL, 16) + diff) ^ xorbyte);
        printf("0x%02x%c ", afmt[j],  (j + 1) != fmtsz ? ',' : '\0');
    }
    printf(
        "}\n[+] payload size: %zu (0x%llx)\n"
        "[+] xor byte: %u (0x%02x)\n"
        "[+] diff: %u (0x%02x)\n",
        fmtsz, fmtsz,
        xorbyte, xorbyte,
        diff, diff
    );

    return EXIT_SUCCESS;
}
