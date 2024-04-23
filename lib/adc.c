#include "adc.h"
#include "esp_log.h"
#include "cJSON.h"

static const char *TAG = "ADC_READER";

void adc_reader_init() {
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_0);
    adc1_config_channel_atten(ADC1_CHANNEL_1, ADC_ATTEN_DB_0);
    adc1_config_channel_atten(ADC1_CHANNEL_2, ADC_ATTEN_DB_0);
    adc1_config_channel_atten(ADC1_CHANNEL_3, ADC_ATTEN_DB_0);
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_0);
}

void adc_reader_task(void *pvParameters) {
    uint32_t adc_data[ADC_CHANNEL_NUM][ADC_SAMPLES_PER_CHANNEL];

    while (1) {
        // Read ADC data from each channel
        for (int i = 0; i < ADC_CHANNEL_NUM; i++) {
            for (int j = 0; j < ADC_SAMPLES_PER_CHANNEL; j++) {
                adc_data[i][j] = adc1_get_raw(i);
                vTaskDelay(pdMS_TO_TICKS(10));
            }
        }

        // Create JSON payload
        cJSON *root = cJSON_CreateObject();
        if (root == NULL) {
            ESP_LOGE(TAG, "Failed to create JSON object");
            continue;
        }

        for (int i = 0; i < ADC_CHANNEL_NUM; i++) {
            cJSON *array = cJSON_CreateArray();
            if (array == NULL) {
                ESP_LOGE(TAG, "Failed to create JSON array");
                cJSON_Delete(root);
                continue;
            }

            // Add ADC data array to JSON payload
            for (int j = 0; j < ADC_SAMPLES_PER_CHANNEL; j++) {
                cJSON_AddItemToArray(array, cJSON_CreateNumber(adc_data[i][j]));
            }

            char channel_name[16];
            sprintf(channel_name, "adc_%d", i+1);
            cJSON_AddItemToObject(root, channel_name, array);
        }

        // Convert JSON payload to string
        char *json_string = cJSON_Print(root);
        cJSON_Delete(root);

        // (Send JSON string to HTTP sender task for further processing)
        free(json_string);

        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay 1 second
    }
}
