#ifndef ADC_READER_H
#define ADC_READER_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"

#define ADC_CHANNEL_NUM 5
#define ADC_SAMPLES_PER_CHANNEL 100

void adc_reader_init();
void adc_reader_task(void *pvParameters);

#endif /* ADC_READER_H */
