
#ifndef EXCHANGE_H_
#define EXCHANGE_H_

#include "../comm/CommWebSocket.h"

namespace exchangeClient{
class Exchange{
public:
    void start();
    
private:
    CCommWebSocket m_commChannel{};
};
}

#endif /* EXCHANGE_H_ */