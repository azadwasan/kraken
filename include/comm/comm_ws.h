#ifndef COMM_WS_H_
#define COMM_WS_H_

#include "comm.h"
#include "../comm/websocket/ws_boost.h"

namespace exchange_client{
class CCommWebSocket: public ICommChannel{
public:
    CCommWebSocket();
    void start();
    ws_status getStatus() override{return ws_status::disconnected;}
    void sendRequest(const std::string&) override{}
    void registerListener() override{}
    void disconnect() override{}

private:
    // The io_context is required for all I/O
    net::io_context ioc;
    // The SSL context is required, and holds certificates
    ssl::context ctx{ssl::context::tlsv12_client};
};
}

#endif /* COMM_WS_H_*/