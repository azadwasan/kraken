#include "include/client/Exchange.h"

int main(int argc, char** argv)
{
    exchangeClient::CExchange{}.start();
    return EXIT_SUCCESS;
}