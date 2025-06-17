#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>

enum class VariableType{
    INT,STR,TAG
};

class Variable
{
    VariableType type;
public:
    std::string content;
    Variable();
    Variable(std::string str);
    void SetContent(std::string str);
    int ToInt();
    std::string ToStr();
    bool ToBool();
    std::string getRowData();
    bool isType(VariableType value);
};

#endif // VARIABLE_H
