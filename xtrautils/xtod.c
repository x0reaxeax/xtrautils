#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s uint64\n", argv[0]);
        return EXIT_FAILURE;
    }
    unsigned long long hex = strtoull(argv[1], NULL, 16);
    printf("0x%llx => %llu\n", hex, hex);
    return EXIT_SUCCESS;
}
