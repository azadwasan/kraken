#include "../../include/client/exchange.h"
#include "../../include/common/config.h"
using namespace exchangeClient;

void Exchange::start(){
    m_commChannel.start();
}