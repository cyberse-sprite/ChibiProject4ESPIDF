#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_pm.h"
#include "iot_button.h"
#include "esp_sleep.h"
#include "esp_idf_version.h"
#include "button_gpio.h"

button_handle_t gpio_btn1 = NULL;
button_handle_t gpio_btn2 = NULL;
button_handle_t gpio_btn3 = NULL;

void button_init(void (*confirm)(), void (*confirm_long)(), void (*left)(), void (*right)())
{
    // create gpio button
    const button_config_t btn_cfg1 = {0};
    const button_gpio_config_t btn_gpio_cfg1 = {
        .gpio_num = 40,
        .active_level = 0,
    };
    const button_config_t btn_cfg2 = {0};
    const button_gpio_config_t btn_gpio_cfg2 = {
        .gpio_num = 38,
        .active_level = 0,
    };
    const button_config_t btn_cfg3 = {0};
    const button_gpio_config_t btn_gpio_cfg3 = {
        .gpio_num = 39,
        .active_level = 0,
    };

    iot_button_new_gpio_device(&btn_cfg1, &btn_gpio_cfg1, &gpio_btn1);
    iot_button_new_gpio_device(&btn_cfg2, &btn_gpio_cfg2, &gpio_btn2);
    iot_button_new_gpio_device(&btn_cfg3, &btn_gpio_cfg3, &gpio_btn3);

    iot_button_register_cb(gpio_btn1, BUTTON_SINGLE_CLICK, NULL, confirm, NULL);
    iot_button_register_cb(gpio_btn1, BUTTON_LONG_PRESS_START, NULL, confirm_long, NULL);
    iot_button_register_cb(gpio_btn2, BUTTON_SINGLE_CLICK, NULL, left, NULL);
    iot_button_register_cb(gpio_btn3, BUTTON_SINGLE_CLICK, NULL, right, NULL);
}
