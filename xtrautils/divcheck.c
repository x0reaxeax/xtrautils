#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint64_t fast_div_check(uint64_t number, uint64_t divisor) {
    uint64_t itr;
    for (itr = divisor; itr <= number; itr += divisor);
    if (number == itr - divisor) {
        return number;
    }
    return 0;
}


int main(int argc, const char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "uasge: %s number {divisor}\n", argv[0]);
        return EXIT_SUCCESS;
    }

    const uint64_t number = strtoull(argv[1], NULL, 0);

    if (3 == argc) {
        const uint64_t divisor = strtoull(argv[2], NULL, 0);
        printf(
            "[*] %llu %s divisible by %llu\n",
            number, 
            (fast_div_check(number, divisor)) ? "is" : "is NOT",
            divisor
        );
        return EXIT_SUCCESS;
    }

    _Bool prime = 1;
    for (uint64_t i = 2; i < number; i++){
        if (fast_div_check(number, i)) {
            printf("[*] %llu is divisible by %llu\n", number, i);
            prime = 0;
        }
    }

    if (prime) {
        printf("[*] %llu is a prime\n", number);
    }

    return EXIT_SUCCESS;

}
