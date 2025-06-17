#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/FreeRTOSConfig.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "card.h"
#include "screen.h"
#include "button.h"
#include "audio.h"
#include "core/game.h"
#include "core/actuator.h"
#include "core/render.h"
#include <esp_lcd_panel_ops.h>
#include "esp_task_wdt.h"
#include <string.h>
#include "inf/file.h"
#include "core/object/characterobject.h"
#include "core/archive.h"
#include "core/scriptfunction.h"
#include <ff.h>

Game *GAME;

esp_lcd_panel_handle_t panel;

uint16_t reverse[128*128];

static const char *TAG = "main";
static void d_left()
{
    ACT->Trigger("ButtonA");
    ESP_LOGI(TAG, "left");
}
static void d_confirm()
{
    ACT->Trigger("ButtonB");
    ESP_LOGI(TAG, "confirm");
}
static void d_right()
{
    ACT->Trigger("ButtonC");
    ESP_LOGI(TAG, "right");
}
static void d_confirm_long()
{
    ACT->Trigger("ButtonBLong");
    ESP_LOGI(TAG, "long");
}

static void d_fresh(void *arg)
{
    while (true)
    {
        GAME->fresh();
        vTaskDelay(pdMS_TO_TICKS(50));
        for(int i=0;i<128*128;i++){
            reverse[i]=(RENDER->canvas[i] >> 8) | (RENDER->canvas[i] << 8);
        }
        esp_lcd_panel_draw_bitmap(panel, 0, 0, 128, 128, reverse);
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

extern "C" void app_main(void)
{
    panel = test_screen();
    card_init();
    button_init(d_confirm, d_confirm_long, d_left, d_right);
    GAME = new Game();
    ACT->callScript("start", "main");
    ACT->run();
    xTaskCreate(d_fresh, "fresh_loop", 1024 * 4, NULL, 2, NULL);
}

extern "C" void vApplicationIdleHook(void)
{
    esp_task_wdt_reset();
}