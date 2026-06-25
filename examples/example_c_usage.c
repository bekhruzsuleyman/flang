#include <stdio.h>
#include <stdint.h>

extern uint64_t number();

int main() {
    printf("Number from FLANG: %lu\n", number());
    return 0;
}