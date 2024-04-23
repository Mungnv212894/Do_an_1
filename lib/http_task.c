#include "http_task.h"
#include "esp_http_client.h"
#include "esp_log.h"
#include "cJSON.h"

#define SERVER_URL "http://your_server_endpoint"

static const char *TAG = "HTTP_SENDER";

void http_sender_init() {
    // Initialize Wi-Fi and other necessary components
}

void http_sender_task(void *pvParameters) {
    while (1) {
        // Receive JSON string from ADC reader task (or create it here)
        char *json_string = "{\"adc_1\": [1, 2, 3, 4, 5], \"adc_2\": [6, 7, 8, 9, 10], \"adc_3\": [11, 12, 13, 14, 15], \"adc_4\": [16, 17, 18, 19, 20], \"adc_5\": [21, 22, 23, 24, 25], \"timestamp\": 1620090000}";

        // Send HTTP POST request with JSON payload
        esp_http_client_config_t config = {
            .url = SERVER_URL,
        };
        esp_http_client_handle_t client = esp_http_client_init(&config);
        esp_http_client_set_method(client, HTTP_METHOD_POST);
        esp_http_client_set_header(client, "Content-Type", "application/json");
        esp_http_client_set_post_field(client, json_string, strlen(json_string));
        esp_err_t err = esp_http_client_perform(client);
        if (err != ESP_OK) {
            ESP_LOGE(TAG, "HTTP POST request failed: %d", err);
        }

        esp_http_client_cleanup(client);

        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay 1 second
    }
}
