#include <stdint.h>
#include <stdio.h>

enum DeviceState {
    DEVICE_OFF,
    DEVICE_RUNNING,
    DEVICE_ERROR
};

union WordView {
    uint32_t word;
    uint8_t bytes[4];
};

int main(void)
{
    enum DeviceState state = DEVICE_RUNNING;
    union WordView view = {.word = UINT32_C(0x12345678)};

    printf("state=%d, union 大小=%zu\n", state, sizeof view);
    printf("word=%#010x, bytes=%02x %02x %02x %02x\n",
           view.word, view.bytes[0], view.bytes[1], view.bytes[2], view.bytes[3]);

    /* TRY: 用 switch 将每个 DeviceState 转换成可读字符串。 */
    return 0;
}

// state=1, union 大小=8                
// word=0x12345678, bytes=%02x %02x %02x %02x