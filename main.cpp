#include "include/client/exchange.h"

int main(int argc, char** argv)
{
    exchangeClient::Exchange{}.start();
    return EXIT_SUCCESS;
}