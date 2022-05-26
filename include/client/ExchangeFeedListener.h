#ifndef EXCHANGEFEEDLISTENER_H_
#define EXCHANGEFEEDLISTENER_H_

#include <string>

namespace exchangeClient{
class IExchangeFeedListener{
public:
    virtual void FeedUpdate(const std::string&) = 0;
};
}

#endif /* EXCHANGEFEEDLISTENER_H_ */