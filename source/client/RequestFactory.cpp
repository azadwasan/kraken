#include <sstream>
#include "client/RequestFactory.h"

using namespace exchangeClient;

std::string CRequestFactory::createRequestTick(Ticks tick) noexcept{
    return std::string{R"({ "ticks": ")"} + toString(tick) + R"("})";
}

constexpr const char* CRequestFactory::toString(Ticks tick) noexcept{
    switch (tick)
    {
    case Ticks::R_10:
        return "R_10";
    case Ticks::R_25:
        return "R_25";
    case Ticks::R_50:
        return "R_50";
    case Ticks::R_75:
        return "R_75";
    case Ticks::R_100:
        return "R_100";
    default:
        return "";
    }
}