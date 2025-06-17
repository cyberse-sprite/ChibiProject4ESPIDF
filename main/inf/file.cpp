#include "file.h"
#include "sdkconfig.h"
#include "esp_log.h"
#include "log.h"

#define EXAMPLE_MAX_CHAR_SIZE 256
FATFS File::fs_;
bool File::mounted_ = false;

bool File::open(std::string name, std::string mode)
{
    file_ = new FIL;
    std::string target = "0:/game/" + name;
    FRESULT res;
    // —— 挂载只做一次 ——
    if (!mounted_)
    {
        res = f_mount(&fs_, "0:", 1);
        if (res != FR_OK)
            return false;
        mounted_ = true;
    }
    FILINFO fileInfo;
    res = f_stat(target.c_str(), &fileInfo);
    if (res == FR_OK)
    {
        LOG->info("文件"+target+"存在，大小: " + std::to_string(fileInfo.fsize));
    }
    else
    {
        LOG->info("文件不存在");
    }
    // —— 直接用 c_str()，不 malloc/free ——
    res = f_open(file_, target.c_str(), FA_READ);
    return (res == FR_OK);
}

std::string File::read(size_t size)
{
    char line[EXAMPLE_MAX_CHAR_SIZE] = "";
    UINT br = 0;
    f_read(file_, line, size, &br);
    isEnd = (br != size);
    return std::string(line);
}

uint16_t File::readuint16_t()
{
    uint16_t num=0;
    UINT br = 0;
    f_read(file_, &num, 2, &br);
    isEnd = (br != 2);
    return num;
}

uint16_t File::readuint16_t_swap()
{
    uint16_t num=0;
    UINT br = 0;
    f_read(file_, &num, 2, &br);
    isEnd = (br != 2);
    return num;
}

uint8_t File::readuint8_t()
{
    uint8_t num=0;
    UINT br = 0;
    f_read(file_, &num, 1, &br);
    isEnd = (br != 1);
    return num;
}

std::string File::readLine()
{
    char line[EXAMPLE_MAX_CHAR_SIZE] = "";
    auto res = f_gets(line, EXAMPLE_MAX_CHAR_SIZE, file_);
    isEnd = (res == NULL);
    for (int i = 0; i < EXAMPLE_MAX_CHAR_SIZE; i++)
    {
        if (line[i] == '\r')
            line[i] = '\0';
        if (line[i] == '\n')
        {
            line[i] = '\0';
            break;
        }
    }
    std::string text=std::string(line);
    // LOG->info("content:"+text);
    return text;
}

void File::write(std::string str)
{
}

bool File::end()
{
    return isEnd;
}

void File::close()
{
    if (file_)
    {
        f_close(file_);
        delete file_;
    }
    file_ = NULL;
}
