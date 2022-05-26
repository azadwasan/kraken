#include "include/client/ExchangeClient.h"

int main(int argc, char** argv)
{
    exchangeClient::CExchangeClient{}.start();
    return EXIT_SUCCESS;
}