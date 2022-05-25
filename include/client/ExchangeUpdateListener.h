
#ifndef EXCHANGEUPDATELISTENER_H_
#define EXCHANGEUPDATELISTENER_H_

enum class UpdateType {
    Connect,
    Disconnect,
    Request,
    Response
};
namespace exchangeClient{
class IExchangeUpdateListener{
public:
    virtual void ExchangeUpdate(UpdateType) = 0;
};
}

#endif /* EXCHANGEUPDATELISTENER_H_ */