
#ifndef EXCHANGE_H_
#define EXCHANGE_H_

#include "../comm/CommWebSocket.h"
#include "ExchangeUpdateListener.h"
#include "feeddelayer/FeedDelayer.h"
#include "feeddelayer/DelayedFeedListener.h"

/*
    This class serves as the central controller, hence holds both the communication channel interface and the feed delayer.
    It also serves to control the communication with the online exchange
    and as a listener of the updates from the feed delayer and accordingly prints the output.
*/

namespace exchangeClient{
class CExchangeClient:public IExchangeUpdateListener, IDelayedFeedistener{
public:
    CExchangeClient();
    void start();

    /*    IExchangeUpdateListener Implementation  */ 
    void ExchangeUpdate(UpdateType) override;

    /*    IExchangeUpdateListener Implementation  */ 
    void FeedUpdate(const std::string&) override;

private:
    CFeedDelayer m_feedDelayer;
    CCommWebSocket m_commChannel;
};
}

#endif /* EXCHANGE_H_ */