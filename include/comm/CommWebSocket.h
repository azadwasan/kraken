#ifndef COMMONWEBSOCKET_H_
#define COMMONWEBSOCKET_H_

#include "comm.h"
#include "../comm/websocket/WebSocketBoost.h"

namespace exchangeClient{
class IExchangeUpdateListener;
class CCommWebSocket: public ICommChannel{
public:
    CCommWebSocket(IExchangeUpdateListener&);
    void start() override;
    ws_status getStatus() override{return ws_status::disconnected;}
    void sendRequest(const std::string&) override;
    void registerListener() override{}
    void disconnect() override{}

private:
    // The io_context is required for all I/O
    net::io_context ioc;
    // The SSL context is required, and holds certificates
    ssl::context ctx{ssl::context::tlsv12_client};
    std::shared_ptr<CWebSocketBoost> m_webSocketClient{};
};
}

#endif /* COMMONWEBSOCKET_H_ */