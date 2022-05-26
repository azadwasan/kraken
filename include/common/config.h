#ifndef CONFIG_H_
#define CONFIG_H_

#include <chrono>

namespace exchangeClient{
    namespace config{
        constexpr const char* EXCHANGE_URL =   "ws.binaryws.com";
        constexpr const char* EXCHANGE_TARGET = "/websockets/v3?app_id=";
        constexpr const char* PORT = "443";
        constexpr const char* APP_ID = "1089"; //This id should not be here. It should be loaded from external source.
        using namespace std::literals::chrono_literals;
        constexpr double FEED_DELAY_SEC = 60;   //1 min or 60 secs, as required by the problem statement.
        //The reason behind the following constant is that, we allow the thread to sleep. But, we can't let it sleep longer than the 
        //maximum error in the delay to send the data. For example, here we have defined 1000ms, which means, the reported data will be sent
        // at the most FEED_DELAY_MILI_SEC + FEED_DELAY_ERROR_TOLERANCE_MILI_SEC, i.e. 1 Min and 1 secs.
        constexpr auto FEED_DELAY_ERROR_TOLERANCE_MILI_SEC = 1000ms;   //This is the maximum error we can tolerate in the delay.
                
    }
}

#endif /* CONFIG_H_ */