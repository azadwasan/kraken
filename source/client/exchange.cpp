#include "client/exchange.h"
#include "common/config.h"
#include "client/RequestFactory.h"

using namespace exchangeClient;

Exchange::Exchange():m_commChannel{*this}{}

void Exchange::start(){
    m_commChannel.start();
}

void Exchange::ExchangeUpdate(UpdateType update) {
    switch (update)
    {
    case UpdateType::Connect:
//        std::cout << " **** Exchange::ExchangeUpdate, Connect update received **** " << std::endl;
        m_commChannel.sendRequest(CRequestFactory::createRequestTick());
        break;
    case UpdateType::Disconnect:
        /* code */
        break;
    case UpdateType::Request:
        /* code */
        break;
    case UpdateType::Response:
        /* code */
        break;
    
    default:
        std::cout << "Exchange::ExchangeUpdate:: Unknown update" << std::endl;
        break;
    }
}
