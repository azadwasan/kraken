
#ifndef EXCHANGE_H_
#define EXCHANGE_H_

#include "../websocket/ws_boost.h"

namespace exchange_client{
class Exchange{
public:
    Exchange();
    void start();

private:
    // The io_context is required for all I/O
    net::io_context ioc;
    // The SSL context is required, and holds certificates
    ssl::context ctx{ssl::context::tlsv12_client};
};
}

#endif /* EXCHANGE_H_ */