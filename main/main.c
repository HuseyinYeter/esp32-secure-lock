#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_log.h"

#define LED_1 GPIO_NUM_21
#define LED_2 GPIO_NUM_23
#define BUTTON_1 GPIO_NUM_18
#define BUTTON_2 GPIO_NUM_19

#define PASSWORD_LENGTH 4

int correct_password[PASSWORD_LENGTH] = {2, 2, 1, 2};

int user_input[PASSWORD_LENGTH];
int input_index = 0;

void app_main(void)
{
    gpio_config_t led_adjustment = {
        .pin_bit_mask = (1ULL << LED_1) | (1ULL << LED_2),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };

    gpio_config_t button_adjustment = {
        .pin_bit_mask = (1ULL << BUTTON_1) | (1ULL << BUTTON_2),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };

    gpio_config(&led_adjustment);
    gpio_config(&button_adjustment);

    while (1)
    {

        int pressed_button = 0;

        if (gpio_get_level(BUTTON_1) == 0)
        {
            pressed_button = 1;
            vTaskDelay(pdMS_TO_TICKS(500));
        }

        if (gpio_get_level(BUTTON_2) == 0)
        {
            pressed_button = 2;
            vTaskDelay(pdMS_TO_TICKS(500));
        }

        if (pressed_button != 0)
        {
            ESP_LOGI("LOCK", "Buton %d basıldı", pressed_button);

            user_input[input_index] = pressed_button;
            input_index++;

            if (input_index == PASSWORD_LENGTH)
            {

                int *ui = user_input;
                int *pi = correct_password;
                int correct = 1;
                for (int i = 0; i < PASSWORD_LENGTH; i++)
                {
                    if (*ui != *pi)
                    {
                        correct = 0;
                        break;
                    }
                    ui++;
                    pi++;
                }

                if (correct)
                {
                    gpio_set_level(LED_1, 1);
                    gpio_set_level(LED_2, 0);
                    ESP_LOGI("LOCK", "SIFRE DOGRU\n");
                }
                else
                {
                    gpio_set_level(LED_2, 1);
                    gpio_set_level(LED_1, 0);
                    ESP_LOGI("LOCK", "SIFRE YANLIS\n");
                }
                input_index = 0;
            }
        }

        vTaskDelay(pdMS_TO_TICKS(200));
    }
}
