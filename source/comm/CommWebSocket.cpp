#include "comm/CommWebSocket.h"
#include "common/config.h"
#include "client/RequestFactory.h"
#include "client/ExchangeUpdateListener.h"

using namespace exchangeClient;

CCommWebSocket::CCommWebSocket(IExchangeUpdateListener& listener){
    load_root_certificates(ctx); 

    m_webSocketClient = std::make_shared<CWebSocketBoost>(ioc, ctx, listener);
}

void CCommWebSocket::start(){
    if(m_webSocketClient){
        m_webSocketClient->start(config::EXCHANGE_URL, config::PORT, 
            CRequestFactory::createRequestTick()
        );
    }
    ioc.run();
}

void CCommWebSocket::sendRequest(const std::string& request){
    if(m_webSocketClient){
        m_webSocketClient->sendRequest(request);
    }    
}
