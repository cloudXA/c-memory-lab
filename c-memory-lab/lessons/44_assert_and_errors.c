#include <assert.h>
#include <stddef.h>
#include <stdio.h>

enum CopyResult { COPY_OK, COPY_INVALID_ARGUMENT, COPY_NO_SPACE };

static enum CopyResult copy_bytes(unsigned char *destination, size_t capacity,
                                  const unsigned char *source, size_t length)
{
    assert(capacity == 0U || destination != NULL);

    if ((length > 0U && source == NULL) || (capacity > 0U && destination == NULL))
        return COPY_INVALID_ARGUMENT;
    if (length > capacity) return COPY_NO_SPACE;

    for (size_t i = 0; i < length; ++i) destination[i] = source[i];
    return COPY_OK;
}

int main(void)
{
    const unsigned char source[] = {1U, 2U, 3U};
    unsigned char destination[3];
    enum CopyResult result = copy_bytes(destination, sizeof destination,
                                        source, sizeof source);
    printf("copy result=%d\n", result);

    /* TRY: 解释断言适合抓编程错误，错误码适合处理运行时可恢复错误。 */
    return result == COPY_OK ? 0 : 1;
}
