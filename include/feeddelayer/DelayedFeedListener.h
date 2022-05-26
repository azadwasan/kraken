#ifndef DELAYEDFEEDLISTENER_H_
#define DELAYEDFEEDLISTENER_H_

#include <string>

namespace exchangeClient{
class IDelayedFeedistener{
public:
    virtual void FeedUpdate(const std::string&) = 0;
};
}

#endif /* DELAYEDFEEDLISTENER_H_ */