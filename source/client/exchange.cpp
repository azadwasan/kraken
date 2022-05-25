#include "../../include/client/exchange.h"
#include "../../include/common/config.h"
using namespace exchange_client;

void Exchange::start(){
    m_commChannel.start();
}