
#ifndef EXCHANGE_H_
#define EXCHANGE_H_

#include "../comm/comm_ws.h"

namespace exchange_client{
class Exchange{
public:
    void start();
private:
    CCommWebSocket m_commChannel{};
};
}

#endif /* EXCHANGE_H_ */