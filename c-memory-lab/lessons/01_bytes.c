#include <stdio.h>

static void print_bytes(const void *address, size_t size)
{
    printf("address before %p\n", address);
    const unsigned char *bytes = address;
    printf("address %p\n", address);
    printf("bytes %p\n", bytes);

    for (size_t i = 0; i < size; ++i) {
        printf("%02x ", (unsigned int)bytes[i]); // bytes[i]  =  从 (bytes + i × sizeof(*bytes)) 这个地址开始，读 sizeof(*bytes) 个字节

    }
    putchar('\n');
}

int main(void)
{
    char letter = 'A';
    int number = 0x12345678;
    double decimal = 3.25;

    printf("对象       地址            大小   值\n");
    printf("letter     %p   %zu     %c\n", (void *)&letter, sizeof letter, letter);
    printf("number     %p   %zu     %#x\n", (void *)&number, sizeof number, (unsigned int)number);
    printf("decimal    %p   %zu     %.2f\n\n", (void *)&decimal, sizeof decimal, decimal);

    printf("number 的内存字节（从低地址到高地址）：\n");
    print_bytes(&number, sizeof number);

    /* TRY: 把 number 改成 1、256、-1，预测并观察字节变化。 */
    return 0;
}

// 对象       地址            大小   值
// letter     0x100000000   1     A
// number     0x100000004   4     0x12345678
// decimal    0x10000000c   8     3.25
// number 的内存字节（从低地址到高地址）
// 0x100000004  4
