#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char BYTE;

int main(int argc, const char *argv[]) {

    if (argc < 4) {
        fprintf(stderr, "usage: %s file pattern size\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t len = strtoul(argv[3], NULL, 0);
    BYTE *payload = malloc(strlen(argv[2]));
    FILE *fp = fopen(argv[1], "rb");

    if (NULL == fp) {
        fprintf(stderr, "[-] Unable to open file '%s' for reading - E%d\n", argv[1], errno);
        return EXIT_FAILURE;
    }

    fseek(fp, 0, SEEK_END);
    size_t filesz = (size_t) ftell(fp);
    rewind(fp);

    BYTE *buffer = malloc(filesz + 1);
    if (NULL == buffer) {
        fprintf(stderr, "[-] Unable to allocate memory - E%d\n", errno);
        return EXIT_FAILURE;
    }

    fread(buffer, filesz, 1, fp);
    fclose(fp);

    for (size_t x = 0, y = 0; x < strlen(argv[2]) / 2; x++, y += 2) {
        BYTE conv[2] = { 0 };
        memcpy(conv, &argv[2][y], 2);
        payload[x] = (BYTE) strtoul(conv, NULL, 16);
    }

    size_t i = 0;
    for (; i < filesz; i++) {
        if (payload[0] == buffer[i]) {
            for (size_t j = 0; j < len / 2; j++) {
                if (j - 1 == len) {
                     printf("[+] Payload located at offset %zu (%llx)\n", i, i);
                     return 0;
                }
                if (payload[j] != buffer[i + j]) {
                    break;
                }
            }
        }
    }


    return EXIT_SUCCESS;
}
