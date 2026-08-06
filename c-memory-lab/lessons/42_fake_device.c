#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef bool (*sensor_read_fn)(void *context, float *out);

struct Sensor {
    sensor_read_fn read;
    void *context;
};

struct FakeSensor {
    const float *values;
    size_t count;
    size_t index;
    size_t fail_at;
};

static bool fake_read(void *context, float *out)
{
    struct FakeSensor *fake = context;
    if (out == NULL || fake->index >= fake->count || fake->index == fake->fail_at)
        return false;
    *out = fake->values[fake->index++];
    return true;
}

int main(void)
{
    const float values[] = {20.0F, 21.5F, 23.0F};
    struct FakeSensor fake = {
        .values = values,
        .count = sizeof values / sizeof values[0],
        .index = 0U,
        .fail_at = 1U
    };
    struct Sensor sensor = {.read = fake_read, .context = &fake};
    float value = 0.0F;
    bool first_ok = sensor.read(sensor.context, &value);

    printf("first=%s value=%.1f\n",
           first_ok ? "ok" : "fail", (double)value);
    bool second_ok = sensor.read(sensor.context, &value);
    printf("second=%s\n", second_ok ? "ok" : "fail");

    /* TRY: 用 fake 测试连续失败 3 次后进入故障状态。 */
    return 0;
}
