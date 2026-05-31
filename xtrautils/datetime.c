#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, const char *argv[]) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    _Bool desc = false;
    if (argc >= 2) {
        for (int i = 1; i < argc; i++) {
            if (0 == strncmp(
                "--desc",
                argv[i],
                strlen("--desc")
            )) {
                desc = true;
            }
        }
    }

    if (desc) {
        printf(
            "%d-%02d-%02d-%02d-%02d\n",
            t->tm_year + 1900,
            t->tm_mon + 1,
            t->tm_mday,
            t->tm_hour,
            t->tm_min
        );
    } else {
        printf(
            "%02d-%02d-%d-%02d-%02d\n",
            t->tm_mday,
            t->tm_mon + 1,
            t->tm_year + 1900,
            t->tm_hour,
            t->tm_min
        );
    }

    return 0;
}
