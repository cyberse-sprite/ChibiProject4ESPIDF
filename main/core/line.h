#ifndef LINE_H
#define LINE_H

#include "core/object/variableobject.h"
#include <string>

class Line:public VariableObject
{
    std::string name;
public:
    Line(std::string);

    std::string GetName();
    bool GetIf();
};

#endif // LINE_H
