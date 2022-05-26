
#ifndef EXCHANGE_H_
#define EXCHANGE_H_

#include "../comm/CommWebSocket.h"
#include "ExchangeUpdateListener.h"
#include "feeddelayer/FeedDelayer.h"
#include "feeddelayer/DelayedFeedListener.h"

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