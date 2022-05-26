#include <thread>
#include "client/ExchangeClient.h"
#include "common/config.h"
#include "client/RequestFactory.h"

using namespace exchangeClient;

CExchangeClient::CExchangeClient():m_feedDelayer{*this}, m_commChannel{*this, m_feedDelayer} {
    //Instantiate a seperate thread for feed delayer and let it run indefinitely
    //until someone shuts it down using CFeedDelayer::Exit() public interface.
    std::thread{&CFeedDelayer::threadLoop, &m_feedDelayer}.detach();
}

void CExchangeClient::start(){
    try{
        m_commChannel.start();  //This is where main thread blocks and we wait for the websocket I/O context to return.
    }
    catch(std::exception& e){   //We have the exception handling in place, but we don't take any further actions.
        std::cout << "!!!! Unexpected ERROR happened!!!. Reason = " <<  e.what() << std::endl; //It can be extended for retries and other error handling mechanisms.
    }
}

void CExchangeClient::ExchangeUpdate(UpdateType update) {
    switch (update)
    {
    case UpdateType::Connect:
        m_commChannel.sendRequest(CRequestFactory::createRequestTick());
        break;
    case UpdateType::Disconnect:
        /* HMI client can call this to disconnect the client */
        break;
    case UpdateType::Request:
        m_commChannel.readResponse(true);
        break;
    case UpdateType::Response:
        /*  Here we can forward the response to a client.
            For now, it directly being sent to Feed delayer, instead of redirecting it from here.
            Otherwise, flow would have been a lot more complex. This keeps it simple. 
        */
        break;
    
    default:
        std::cout << "Exchange::ExchangeUpdate:: Unknown update" << std::endl;
        break;
    }
}

void CExchangeClient::FeedUpdate(const std::string& data){
    std::cout<< std::endl << "**** Delayed Tick **** "<< std::endl << std::endl << data << std::endl << std::endl;
}
