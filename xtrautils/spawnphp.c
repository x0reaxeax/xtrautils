#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <net/if.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>



int main(int argc, char const *argv[]) {

    if (argc < 2) {
        fprintf(
            stderr,
            "Usage: %s <interface>\n",
            argv[0]
        );
        return EXIT_FAILURE;
    }

    int fd;
    char *inetaptr = NULL;
    char execbuf[64] = { 0 };
    struct ifreq ifr = { 0 };

    fd = socket(AF_INET, SOCK_DGRAM, 0);

    if (-EXIT_FAILURE == fd) {
        fprintf(
            stderr,
            "[-] socket() - E%u\n",
            errno
        );
        return EXIT_FAILURE;
    }

    strncpy(
        ifr.ifr_name,
        argv[1],
        IFNAMSIZ - 1
    );

    
    if (ioctl(fd, SIOCGIFADDR, &ifr) < 0) {
        fprintf(
            stderr,
            "[-] ioctl() - E%u\n",
            errno
        );
        close(fd);
        return EXIT_FAILURE;
    }

    close(fd);

    inetaptr = inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);

    printf(
        "[%s]: '%s'\n", 
        argv[1],
        inetaptr
    );

    snprintf(
        execbuf,
        sizeof(execbuf),
        "sudo php -S %s:80 -t .",
        inetaptr
    );


    system(execbuf);

    return EXIT_SUCCESS;
}
