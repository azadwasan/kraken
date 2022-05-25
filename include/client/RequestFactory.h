#ifndef REQUESTFACTORY_H_
#define REQUESTFACTORY_H_

#include <string>

enum class Ticks{
    R_10,
    R_25,
    R_50,
    R_75,
    R_100
};

namespace exchangeClient{
class CRequestFactory{
public:
    static std::string createRequestTick(Ticks=Ticks::R_10);

private:
    static const char * toString(Ticks tick);
};
}

#endif