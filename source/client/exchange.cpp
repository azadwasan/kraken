#include "client/exchange.h"
#include "common/config.h"
using namespace exchangeClient;

void Exchange::start(){
    m_commChannel.start();
}