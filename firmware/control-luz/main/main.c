#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "ld2420.h"
#include "esp_log.h"
#include "tiempo.h"

#define LED_PRESENCIA_PIN 1
#define LD2420_RX 7
#define LD2420_TX 6
#define LD2420_BAUD 115200
#define DIST_MIN_CM 20
#define DIST_MAX_CM 400

static const char *TAG = "control-luz";
static ld2420_t radar;

void app_main(void) {
    gpio_set_direction(LED_PRESENCIA_PIN, GPIO_MODE_OUTPUT);
    ld2420_init(&radar, LD2420_RX, LD2420_TX, LD2420_BAUD);
    for (;;) {
        ld2420_update(&radar);
        uint16_t dist = ld2420_distancia_cm(&radar);
        bool mov = ld2420_movimiento(&radar);
        bool presencia = mov && (dist >= DIST_MIN_CM && dist <= DIST_MAX_CM);
        gpio_set_level(LED_PRESENCIA_PIN, presencia ? 1 : 0);
        ESP_LOGI(TAG, "Presencia: %s", presencia ? "SI" : "no");
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}
