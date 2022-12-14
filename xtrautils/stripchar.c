/* just use `stripstr.c` */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned long long uintptr_t;

char *skipchar(char *str, char c, size_t *nstrip) {
    size_t ioff = 0;
    while (*(str + ioff) == c) {
        ioff++;
    }

    *nstrip += (ioff - 1);

    return (str + ioff);
}

int main(int argc, char const *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "usage: %s string stripchar\n", argv[0]);
        return EXIT_FAILURE;
    }

    int raw_output = 0;
    if (argc == 4 && EXIT_SUCCESS == strcmp(argv[3], "-r")) {
        raw_output = 1;
    }

    size_t i;
    size_t slen = strlen(argv[1]);
    size_t n_stripped = 0;

    unsigned char *buffer = strdup(argv[1]);
    unsigned char stripchar = argv[2][0];

    if (strlen(argv[2]) > 2) {
        stripchar = (unsigned char) strtol(argv[2], NULL, 16);
    }

    for (i = 0; i < slen; i++) {
        if (buffer[i] == stripchar) {
            strncpy(&buffer[i], skipchar(&buffer[i], stripchar, &n_stripped), slen - i);
            n_stripped++;
        }

        if (0 == buffer[i]) {
            break;
        }
    }

    if (raw_output) {
        printf("%s", buffer);
    } else {
        printf("[+] Stripped %zu bytes: '%s'\n", n_stripped, buffer);
    }

    free(buffer);

    return EXIT_SUCCESS;
}

