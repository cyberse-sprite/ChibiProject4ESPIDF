#ifndef FILE_H
#define FILE_H

#include <string>
#include <ff.h>

class File
{
    FIL *file_ = NULL;
    static FATFS fs_;
    static bool mounted_;
    bool isEnd = false;

public:
    File() {};
    ~File() { close(); };
    bool open(std::string, std::string);
    std::string read(size_t);
    uint16_t readuint16_t();
    uint16_t readuint16_t_swap();
    uint8_t readuint8_t();
    std::string readLine();
    void write(std::string);
    bool end();
    void close();
};

#endif
