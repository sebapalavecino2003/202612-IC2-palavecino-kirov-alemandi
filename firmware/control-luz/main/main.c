#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "ld2420.h"
#include "esp_log.h"

#define LED_PRESENCIA_PIN 1
#define LD2420_RX 7
#define LD2420_TX 6
#define LD2420_BAUD 115200

static const char *TAG = "control-luz";
static ld2420_t radar;

void app_main(void) {
    gpio_set_direction(LED_PRESENCIA_PIN, GPIO_MODE_OUTPUT);
    if (ld2420_init(&radar, LD2420_RX, LD2420_TX, LD2420_BAUD)) {
        ESP_LOGI(TAG, "Radar LD2420 inicializado");
    } else {
        ESP_LOGE(TAG, "Error inicializando radar");
    }
    for (;;) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
