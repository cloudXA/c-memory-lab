#include <stddef.h>
#include <stdio.h>

enum AverageResult {
    AVERAGE_OK,
    AVERAGE_INVALID_ARGUMENT,
    AVERAGE_EMPTY
};

static enum AverageResult average(const int *values, size_t count, double *out)
{
    if (values == NULL || out == NULL) {
        return AVERAGE_INVALID_ARGUMENT;
    }
    if (count == 0U) {
        return AVERAGE_EMPTY;
    }

    long long total = 0;
    for (size_t i = 0; i < count; ++i) {
        total += values[i];
    }
    *out = (double)total / (double)count;
    return AVERAGE_OK;
}

int main(void)
{
    const int values[] = {10, 20, 30};
    double result = 0.0;
    enum AverageResult status = average(values, 3U, &result);

    if (status != AVERAGE_OK) {
        fprintf(stderr, "average failed: %d\n", status);
        return 1;
    }
    printf("average=%.2f\n", result);

    /* TRY: 分别传 NULL 和 count=0，验证调用者不会使用无效输出。 */
    return 0;
}
