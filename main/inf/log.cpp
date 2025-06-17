#include "log.h"
#include "esp_log.h"

ChibiLog::ChibiLog()
{
}

void ChibiLog::info(std::string str)
{
    ESP_LOGI("log","%s", str.c_str());
}
