#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

struct Sensor;

typedef bool (*sensor_read_fn)(struct Sensor *sensor, float *temperature);

struct Sensor {
    sensor_read_fn read;
    void *context;
};

struct FakeSensorData {
    float next_value;
    bool connected;
};

/* ---- 第二个驱动实现：真实传感器（模拟 ADC 原始值换算） ---- */
struct RealSensorData {
    uint32_t adc_raw;      /* ADC 原始读数，假设 0~4095 对应 0~100 摄氏度 */
};

static bool fake_sensor_read(struct Sensor *sensor, float *temperature)
{
    struct FakeSensorData *data = sensor->context;
    if (!data->connected || temperature == NULL) {
        return false;
    }
    *temperature = data->next_value;
    return true;
}

static bool real_sensor_read(struct Sensor *sensor, float *temperature)
{
    struct RealSensorData *data = sensor->context;
    if (temperature == NULL) {
        return false;
    }
    /* 换算：adc_raw / 4095.0 * 100.0 = 摄氏度 */
    *temperature = (float)data->adc_raw / 4095.0F * 100.0F;
    return true;
}

static void application_poll(struct Sensor *sensor)
{
    float temperature = 0.0F;
    if (sensor->read(sensor, &temperature)) {
        printf("temperature=%.1f C\n", (double)temperature);
    } else {
        printf("sensor read failed\n");
    }
}

int main(void)
{
    struct FakeSensorData fake = {.next_value = 26.5F, .connected = true};
    struct Sensor sensor = {.read = fake_sensor_read, .context = &fake};

    application_poll(&sensor);
    fake.connected = false;
    application_poll(&sensor);

    /* TRY: 新增另一个驱动实现，不修改 application_poll。 */
    struct RealSensorData real = {.adc_raw = UINT32_C(1230)};
    struct Sensor real_sensor = {.read = real_sensor_read, .context = &real};

    application_poll(&real_sensor);   /* 上层代码 application_poll 完全没改 */

    return 0;
}
// temperature=26.5F
// sensor read failed

