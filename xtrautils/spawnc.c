#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, const char *argv[]) {

    const char *filename = (argc < 2) ? "main.c" : argv[1];

    FILE *fp = fopen(filename, "a");
    if (NULL == fp) {
        perror("Error:");
        return EXIT_FAILURE;
    }

    const char *code[] = {
        "#include <stdio.h>",
        "#include <string.h>",
        "#include <stdlib.h>",
        "int main(int argc, const char *argv[]) {",
        "",
        "    return EXIT_SUCCESS;",
        "}"
    };

    for (int i = 0; i < sizeof(code) / sizeof(code[0]); i++) {
        fwrite(code[i], strlen(code[i]), 1, fp);
    }

    fclose(fp);
    return EXIT_SUCCESS;
}
