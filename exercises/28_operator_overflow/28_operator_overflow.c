#include <stdio.h>
#include <limits.h>

#define CHECK_OVERFLOW(carry) \
    carry ? "Overflow" : "Not Overflow"

int check_add_overflow_asm(unsigned int a, unsigned int b) {
    unsigned char carry;
    __asm__ volatile(
        "add %[b], %[a]\n\t"   // a += b, CF=1 表示无符号加法溢出
        "setc %[carry]"         // carry = CF
        : [carry] "=r" (carry), [a] "+r" (a)
        : [b] "r" (b)
        : "cc"
    );
    return carry;
}

int check_sub_overflow_asm(unsigned int a, unsigned int b) {
    unsigned char carry;
    __asm__ volatile(
        "sub %[b], %[a]\n\t"   // a -= b, CF=1 表示借位（无符号下溢）
        "setc %[carry]"         // carry = CF
        : [carry] "=r" (carry), [a] "+r" (a)
        : [b] "r" (b)
        : "cc"
    );
    return carry;
}

int check_mul_overflow_asm(unsigned int a, unsigned int b) {
    unsigned int high_bits;
    unsigned char overflow;
    __asm__ volatile(
        "mov %[a], %%eax\n\t"   // eax = a (被乘数)
        "mul %[b]\n\t"          // edx:eax = eax * b
        "mov %%edx, %[high]\n\t" // high_bits = edx（乘积高32位）
        "seto %[ov]"            // overflow = OF（高32位非零则OF=1）
        : [high] "=r" (high_bits), [ov] "=r" (overflow)
        : [a] "r" (a), [b] "r" (b)
        : "eax", "edx"
    );
    return overflow || (high_bits != 0);
}

int check_div_overflow_asm(unsigned int a, unsigned int b) {
    unsigned char is_div_zero;
    __asm__ volatile(
        "test %[b], %[b]\n\t"   // b & b → 设置 ZF
        "sete %[zero]"          // ZF=1（即 b==0）→ is_div_zero=1
        : [zero] "=r" (is_div_zero)
        : [b] "r" (b)
        : "cc"
    );
    return is_div_zero;
}

int main(void) {
    printf("(UINT_MAX + 1)Add: %s\n", CHECK_OVERFLOW(check_add_overflow_asm(UINT_MAX, 1)));   // 1
    printf("(1, 0)Add: %s\n", CHECK_OVERFLOW(check_add_overflow_asm(1, 0)));
    printf("(0, 1)Sub: %s\n", CHECK_OVERFLOW(check_sub_overflow_asm(0, 1)));          // 1
    printf("(2, 1)Sub: %s\n", CHECK_OVERFLOW(check_sub_overflow_asm(2, 1)));
    printf("(UINT_MAX, 2)Mul: %s\n", CHECK_OVERFLOW(check_mul_overflow_asm(UINT_MAX, 2)));   // 1
    printf("(1, 2)Mul: %s\n", CHECK_OVERFLOW(check_mul_overflow_asm(1, 2)));
    printf("(10, 0)Div: %s\n", CHECK_OVERFLOW(check_div_overflow_asm(10, 0)));                         // 1
    printf("(2, 1)Div: %s\n", CHECK_OVERFLOW(check_div_overflow_asm(2, 1)));
    return 0;
}
