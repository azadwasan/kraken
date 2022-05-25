
#ifndef EXCHANGE_H_
#define EXCHANGE_H_

#include "../comm/CommWebSocket.h"
#include "ExchangeUpdateListener.h"

namespace exchangeClient{
class CExchange:public IExchangeUpdateListener{
public:
    CExchange();
    void start();

    void ExchangeUpdate(UpdateType) override;
private:
    CCommWebSocket m_commChannel;
};
}

#endif /* EXCHANGE_H_ */