#ifndef FEEDDELAYER_H_
#define FEEDDELAYER_H_

#include <queue>
#include <mutex>
#include <atomic>
#include <chrono>
#include "client/ExchangeFeedListener.h"

namespace exchangeClient{
class IDelayedFeedistener;
class CFeedDelayer:public IExchangeFeedListener{
public:
    CFeedDelayer(IDelayedFeedistener& listener);
    void threadLoop();
    void Exit();

    /* IExchangeFeedistener Implementation */
    void FeedUpdate(const std::string&) override;

private:
    struct TimestampedData{
        std::string data;
        std::chrono::time_point<std::chrono::steady_clock> time;
    };

private:
    std::queue<TimestampedData> m_dataFeed{};
    std::mutex m_mutex{};
    std::atomic<bool> m_continue{true};
    IDelayedFeedistener& m_delayedFeedListener;
};
}


#endif /* FEEDDELAYER_H_ */