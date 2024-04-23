#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "adc.h"
#include "http_task.h"

void app_main() {
    // Initialize ADC reader
    adc_reader_init();

    // Initialize HTTP sender
    http_sender_init();

    // Create tasks for ADC reader and HTTP sender
    xTaskCreate(adc_reader_task, "adc_reader_task", 10000, NULL, 5, NULL);
    xTaskCreate(http_sender_task, "http_sender_task", 10000, NULL, 5, NULL);
}
