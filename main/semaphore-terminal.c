#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "cli.h"
#include "temp_sensor.h"

SemaphoreHandle_t xSemaphore;

void output_temp_task(void *pvParameters) {

    while(1) {

        xSemaphoreTake(xSemaphore, portMAX_DELAY);

        printf("The internal temperature is %.2f \n", get_latest_temperature());

    }

}

void app_main(void)
{
    xSemaphore = xSemaphoreCreateBinary();

    start_cli();
    start_temperature_monitoring();

    xTaskCreate(
        output_temp_task,
        "Temperature Output",
        1024,
        NULL,
        1,
        NULL
    );
}
