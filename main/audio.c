#include "audio.h"
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <esp_log.h>
#include "driver/i2s_std.h"
#include "driver/gpio.h"
#include "driver/i2s_std.h"
#include "driver/i2s_types.h"
#include <esp_log.h>
#include "esp_check.h"

// speaker settings
#define AUDIO_I2S_SPK_GPIO_DOUT GPIO_NUM_5
#define AUDIO_I2S_SPK_GPIO_BCLK GPIO_NUM_6
#define AUDIO_I2S_SPK_GPIO_WS GPIO_NUM_7

static i2s_chan_handle_t _i2s_ch_tx; // I2S 发送通道
// typedef std::shared_ptr<I2sOutput> Ptr;
static const char *WavTAG = "WavFile";
static const char *OutputTAG = "Output";

WavFile file = {I2S_SLOT_MODE_STEREO, 16000, I2S_DATA_BIT_WIDTH_16BIT, NULL};

bool OpenWav(const char *path)
{
    // 以二进制格式打开 wav 音频文件
    file.fp = fopen(path, "rb");
    if (file.fp == NULL)
    {
        ESP_LOGE(WavTAG, "\tFailed to open wav file:%s", path);
        return false;
    }

    // wav 文件的前 44 个字节存储到 header[] 中
    // 文件指针 fp 后移 44 个字节后，指向了音频数据
    uint8_t header[44];
    size_t bytesRead = fread(&header, sizeof(uint8_t), 44, file.fp);
    if (bytesRead <= 0)
    {
        ESP_LOGE(WavTAG, "\tFail to parse wav file:%s", path);
        fclose(file.fp);
        return false;
    }
    else
    {
        ESP_LOGI(WavTAG, "\tSucceed to parse wav file:%s", path);
    }
    file.sampleRate = *(uint32_t *)(header + 24);    // 采样率
    file.numChannels = *(uint16_t *)(header + 22);   // 声道数
    file.bitsPerSanple = *(uint32_t *)(header + 34); // 位深度
    return true;
}

// 初始化 I2S 发送通道，并使能（不使能不能播放）
void Init()
{
    ESP_LOGI(OutputTAG, "Init output channel...");

    // 1、创建通道
    i2s_chan_config_t chcfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_0, I2S_ROLE_MASTER);
    ESP_ERROR_CHECK(i2s_new_channel(&chcfg, &_i2s_ch_tx, NULL));

    // 2、配置通道
    // 用到之前从 wav 文件头中解析出来的三个属性
    i2s_data_bit_width_t i2s_data_bit_width; // 默认
    i2s_slot_mode_t i2s_slot_mode;           // 默认
    // 根据实际的位深度进行修改
    switch (file.bitsPerSanple)
    {
    case 24:
        i2s_data_bit_width = I2S_DATA_BIT_WIDTH_24BIT;
        break;
    case 32:
        i2s_data_bit_width = I2S_DATA_BIT_WIDTH_32BIT;
        break;
    default:
        i2s_data_bit_width = I2S_DATA_BIT_WIDTH_16BIT;
    }
    // 根据实际的声道数进行修改
    switch (file.numChannels)
    {
    case 1:
        i2s_slot_mode = I2S_SLOT_MODE_MONO;
        break;
    default:
        i2s_slot_mode = I2S_SLOT_MODE_STEREO;
    }
    i2s_std_config_t spkr_config = {
        .clk_cfg = {
            .sample_rate_hz = file.sampleRate,
            .clk_src = I2S_CLK_SRC_DEFAULT,
            .mclk_multiple = I2S_MCLK_MULTIPLE_384,
        },
        .slot_cfg = I2S_STD_PCM_SLOT_DEFAULT_CONFIG(i2s_data_bit_width, i2s_slot_mode),
        .gpio_cfg = {.mclk = I2S_GPIO_UNUSED,
                     .bclk = AUDIO_I2S_SPK_GPIO_BCLK, // config.h 中定义好的
                     .ws = AUDIO_I2S_SPK_GPIO_WS,     // config.h 中定义好的
                     .dout = AUDIO_I2S_SPK_GPIO_DOUT, // config.h 中定义好的
                     .din = I2S_GPIO_UNUSED,
                     .invert_flags = {.mclk_inv = false, .bclk_inv = false, .ws_inv = false}}};
    ESP_ERROR_CHECK(i2s_channel_init_std_mode(_i2s_ch_tx, &spkr_config));

    // 3、使能通道
    ESP_ERROR_CHECK(i2s_channel_enable(_i2s_ch_tx));
}

// 将长度为 len 的 data 数据写入到 i2s 通道中，即播放
void Write(int16_t *data, size_t len)
{
    ESP_LOGI(OutputTAG, "Playing...");
    size_t bytes_written = 0;
    ESP_ERROR_CHECK(i2s_channel_write(_i2s_ch_tx, data, len * sizeof(int16_t), &bytes_written, 1000));
}

// 主循环
void Playing()
{
    if (file.fp == NULL)
        return;
    // 从 wav 文件中读取1024 * sizeof(int16_t) 个数据
    // fp 指针同步后移，因为是 FILE*，所以 wavFile_ 中存储的 fp_ 也同步后移
    int16_t buffer[1024];
    int len = fread(buffer, sizeof(int16_t), 1024, file.fp);

    // len 为实际读取到的数据长度，上面 fread() 的 1024 为读取的最大长度
    // 若 len == 0，则表示音频数据结束，播放完毕
    if (len > 0)
    {
        // 写入 I2S 通道
        Write(buffer, len);
    }
    else
    {
        fclose(file.fp);
    }
}

static void PlayMusic(void *arg)
{
    OpenWav("/sdcard/game/audio/bgm.wav");
    Init();
    while (true)
    {
        Playing();
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void test()
{
    xTaskCreate(PlayMusic, "main_loop", 4096 * 2, NULL, 2, NULL);
}