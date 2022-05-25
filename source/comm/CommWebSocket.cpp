#include "comm/CommWebSocket.h"
#include "common/config.h"
#include "client/RequestFactory.h"

using namespace exchangeClient;

CCommWebSocket::CCommWebSocket(){
    load_root_certificates(ctx); 

    m_webSocketClient = std::make_shared<CWebSocketBoost>(ioc, ctx);
}


void CCommWebSocket::start(){
    m_webSocketClient->start(config::EXCHANGE_URL, config::PORT, 
        CRequestFactory::createRequestTick()
    );

    ioc.run();

}