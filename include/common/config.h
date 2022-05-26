#ifndef CONFIG_H_
#define CONFIG_H_

#include <chrono>

namespace exchangeClient{
    namespace config{
//        constexpr const char* EXCHANGE_URL = "ws.kraken.com";
//        constexpr const char* EXCHANGE_URL = "wss://ws.binaryws.com/websockets/v3?app_id=";
        constexpr const char* EXCHANGE_URL =   "ws.binaryws.com";
        constexpr const char* EXCHANGE_TARGET = "/websockets/v3?app_id=1089";
        constexpr const char* PORT = "443";
        constexpr const char* APP_ID = ""; //This id should not be here. It should be loaded from external source.
        using namespace std::literals::chrono_literals;
        constexpr auto FEED_DELAY_MILI_SEC = 10000ms;
    }
}

#endif /* CONFIG_H_ */