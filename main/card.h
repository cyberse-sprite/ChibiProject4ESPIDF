#ifndef CARD_H
#define CARD_H
#include <esp_err.h>
#ifdef __cplusplus
extern "C"
{
#endif
    void card_init();
    void card_unmount();
#ifdef __cplusplus
}
#endif
#endif