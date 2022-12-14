#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s {-s} text\n", argv[0]);
        return EXIT_FAILURE;
    }

    char space = '\0';
    if (EXIT_SUCCESS == strncmp(argv[1], "-s", 2)) {
        space = ' ';
    }

    size_t slen = strlen(argv[argc - 1]);

    printf("[%s] = { ", argv[argc - 1]);
    for (size_t i = 0; i < slen; i++) {
        printf("%02x%c", argv[argc - 1][i], space);
    }
    printf("%c}\n", (space != ' ') ? ' ' : '\0');

    return EXIT_SUCCESS;
}
