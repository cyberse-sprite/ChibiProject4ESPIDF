#ifndef TRIGGER_H
#define TRIGGER_H

#include <functional>
#include <map>
#include <string>
class Trigger
{
    std::map<std::string,std::function<std::string()>> triggers;
public:
    std::string triggered(std::string);
    void triggeredAll();
    void addTricker(std::string name,std::function<std::string()> func);
    void removeTricker(std::string name);
    void clearTrickers();

};

#endif // TRIGGER_H
