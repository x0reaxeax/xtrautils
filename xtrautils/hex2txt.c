#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage %s hexnum\n", argv[0]);
        return EXIT_FAILURE;
    }

    unsigned long long res = strtoull(argv[1], NULL, 16);
    unsigned char *ptr = (unsigned char *) &res;
    for (long long i = sizeof(unsigned long long) - 1; i > -1; i--) {
        printf("%c", *(ptr + i));
    }
    putchar('\n');
    return EXIT_SUCCESS;
}
