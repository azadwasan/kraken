#ifndef CONFIG_H_
#define CONFIG_H_

namespace exchangeClient{
    namespace config{
        constexpr const char* EXCHANGE_URL = "ws.kraken.com";
        constexpr const char* PORT = "443";
        constexpr const char* ADD_ID = ""; //TODO: To be added - This id should not be here. It should be loaded from external source.
    }
}

#endif /* CONFIG_H_ */