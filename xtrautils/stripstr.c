#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "usage: %s string strip\n", argv[0]);
        return 1;
    }

    size_t nstripped = 0;
    size_t slen = strlen(argv[1]);
    size_t needle_len = strlen(argv[2]);
    char *ptr = argv[1];

    while ((ptr = strstr(ptr, argv[2])) != NULL) {
        snprintf(ptr, (slen - 1) - (ptr - argv[1]), "%s", (ptr + needle_len));
        nstripped += needle_len;
    }

    printf("[+] Stripped %zu characters: '%s'\n", nstripped, argv[1]);
    return 0;
}
