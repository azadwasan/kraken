#include "../../include/comm/comm_ws.h"
#include "../../include/common/config.h"

using namespace exchange_client;

CCommWebSocket::CCommWebSocket(){
    load_root_certificates(ctx); 
}


void CCommWebSocket::start(){
    std::string tick_request{        R"({
        "event": "subscribe",
        "pair": [
            "XBT/USD",
            "XBT/EUR"
        ],
        "subscription": {
            "name": "ticker"
        }
        })"
    };
    // This holds the root certificate used for verification
    std::make_shared<session>(ioc, ctx)->start(config::EXCHANGE_URL, config::PORT, 
        tick_request.c_str()
    );

    // Run the I/O service. The call will return when
    // the socket is closed.
    ioc.run();

}