#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(void) {

    char readbuf[64] = { 0 };
    char nameserver[32] = { 0 };
    const char * const resolvcfg_path = "/etc/resolv.conf";
    FILE *fp = fopen(resolvcfg_path, "r");

    if (NULL == fp) {
        perror("cannot open %s - ");
        return EXIT_FAILURE;
    }

    while (fgets(readbuf, sizeof(readbuf), fp)) {
        if (EXIT_SUCCESS == strncmp(readbuf, "nameserver", strlen("nameserver"))) {
            strncpy(nameserver, &readbuf[strlen("nameserver ")], sizeof(nameserver));
            break;
        }
    }

    fclose(fp);

    char *newline = strchr(nameserver, '\n');
    if (NULL != newline) {
        strncpy(newline, ":3.0\0", 5);
    }

    printf("export DISPLAY=\"%s\"\n", nameserver);

    return EXIT_SUCCESS;
}
