#ifndef LOG_H
#define LOG_H

#include <string>
class ChibiLog
{
public:
    ChibiLog();
    void info(std::string);
};

extern ChibiLog* LOG;

#endif // LOG_H
