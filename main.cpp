#include "include/client/exchange.h"

int main(int argc, char** argv)
{
    exchange_client::Exchange{}.start();
    return EXIT_SUCCESS;
}