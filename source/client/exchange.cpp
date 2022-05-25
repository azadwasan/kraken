#include "client/Exchange.h"
#include "common/config.h"
#include "client/RequestFactory.h"

using namespace exchangeClient;

CExchange::CExchange():m_commChannel{*this}{}

void CExchange::start(){
    m_commChannel.start();
}

void CExchange::ExchangeUpdate(UpdateType update) {
    switch (update)
    {
    case UpdateType::Connect:
        std::cout << " **** Exchange::ExchangeUpdate, Connect update received **** " << std::endl;
        m_commChannel.sendRequest(CRequestFactory::createRequestTick());
        break;
    case UpdateType::Disconnect:
        /* code */
        break;
    case UpdateType::Request:
        std::cout << " **** Exchange::ExchangeUpdate, Request update received **** " << std::endl;
        m_commChannel.readResponse(true);
        break;
    case UpdateType::Response:
        /* code */
        break;
    
    default:
        std::cout << "Exchange::ExchangeUpdate:: Unknown update" << std::endl;
        break;
    }
}
