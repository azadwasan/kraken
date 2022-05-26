#include <thread>
#include <iostream>
#include "feeddelayer/FeedDelayer.h"
#include "common/config.h"
#include "feeddelayer/DelayedFeedListener.h"

using namespace exchangeClient;

CFeedDelayer::CFeedDelayer(IDelayedFeedistener& listener):m_delayedFeedListener{listener}{}

void CFeedDelayer::threadLoop(){
    while(m_continue){
        std::this_thread::sleep_for(config::FEED_DELAY_MILI_SEC);
        const std::lock_guard<std::mutex> lock{m_mutex};
        if(!m_dataFeed.empty()){
            m_delayedFeedListener.FeedUpdate(m_dataFeed.front());
            m_dataFeed.pop();
        }
    }
}

void CFeedDelayer::FeedUpdate(const std::string& data){
    std::cout << "***** Realtime Data received *****" << std::endl;

    const std::lock_guard<std::mutex> lock{m_mutex};
    m_dataFeed.push(data);
}

void CFeedDelayer::Exit(){
    m_continue =false;
}
