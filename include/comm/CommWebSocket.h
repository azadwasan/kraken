#ifndef COMMONWEBSOCKET_H_
#define COMMONWEBSOCKET_H_

#include "comm.h"
#include "../comm/websocket/WebSocketBoost.h"

/*
    This class serves as an abstraction layer over the Boost Websocket interface.
    The same interface can be implemented by any other class to provide abstraction for some other library.
    Its role is to enable communication with the Boost websocket library.
*/
namespace exchangeClient{
class IExchangeUpdateListener;
class IExchangeFeedListener;
class CCommWebSocket: public ICommChannel{
public:
    CCommWebSocket(IExchangeUpdateListener&, IExchangeFeedListener&);
    void start() override;
    WebsocketStatus getStatus() override;
    void sendRequest(const std::string&) override;
    void readResponse(bool=false);
    void registerListener() override{} //This is the generic interface for extension to allow multiple listeners to be registered.
    void disconnect() override;

private:
    // The io_context is required for all I/O
    net::io_context ioc;
    // The SSL context is required, and holds certificates
    ssl::context ctx{ssl::context::tlsv12_client};
    std::shared_ptr<CWebSocketBoost> m_webSocketClient{};
};
}

#endif /* COMMONWEBSOCKET_H_ */