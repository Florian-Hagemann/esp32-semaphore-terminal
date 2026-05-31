#include "temp_sensor.h"
#include "driver/temperature_sensor.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static volatile float latest_temp = 0.0f;

static void temp_monitor_task(void *pvParameters) {
    temperature_sensor_handle_t temp_sensor = NULL;
    temperature_sensor_config_t temp_sensor_config = TEMPERATURE_SENSOR_CONFIG_DEFAULT(-10, 80);

    temperature_sensor_install(&temp_sensor_config, &temp_sensor);

    temperature_sensor_enable(temp_sensor);

    while(1) {
        float tsens_out;
        
        if (temperature_sensor_get_celsius(temp_sensor, &tsens_out) == ESP_OK) {
            latest_temp = tsens_out; 
        }

        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}
float get_latest_temperature(void) {
    return latest_temp;
}

void start_temperature_monitoring(void) {
    xTaskCreate(
        temp_monitor_task,
        "Temp Monitor Task",
        3072,
        NULL,
        1,
        NULL
    );
}