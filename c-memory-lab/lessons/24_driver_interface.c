#include <stdbool.h>
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

static bool fake_sensor_read(struct Sensor *sensor, float *temperature)
{
    struct FakeSensorData *data = sensor->context;
    if (!data->connected || temperature == NULL) {
        return false;
    }
    *temperature = data->next_value;
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
    return 0;
}
