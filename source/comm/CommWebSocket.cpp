#include "comm/CommWebSocket.h"
#include "common/config.h"
#include "client/RequestFactory.h"

using namespace exchangeClient;

CCommWebSocket::CCommWebSocket(IExchangeUpdateListener& updateListener, IExchangeFeedListener& feedListener){
    load_root_certificates(ctx); 
    m_webSocketClient = std::make_shared<CWebSocketBoost>(ioc, ctx, updateListener, feedListener);
}

void CCommWebSocket::start(){
    if(m_webSocketClient){
        m_webSocketClient->connect(config::EXCHANGE_URL, config::PORT, std::string{config::EXCHANGE_TARGET}+config::APP_ID);
    }
    ioc.run();
}

WebsocketStatus CCommWebSocket::getStatus(){
    if(m_webSocketClient){
        return m_webSocketClient->getStatus();
    }
    return WebsocketStatus::disconnected;
}


void CCommWebSocket::sendRequest(const std::string& request){
    if(m_webSocketClient){
        m_webSocketClient->sendRequest(request);
    }    
}

void CCommWebSocket::readResponse(bool continous){
    if(m_webSocketClient){
        m_webSocketClient->readResponse(continous);
    }    
}

void CCommWebSocket::disconnect(){
    if(m_webSocketClient){
        m_webSocketClient->disconnect();;
    }    
}
