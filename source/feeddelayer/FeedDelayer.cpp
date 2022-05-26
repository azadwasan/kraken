#include <thread>
#include <iostream>
#include "feeddelayer/FeedDelayer.h"
#include "common/config.h"
#include "feeddelayer/DelayedFeedListener.h"

using namespace exchangeClient;

CFeedDelayer::CFeedDelayer(IDelayedFeedistener& listener):m_delayedFeedListener{listener}{}

void CFeedDelayer::threadLoop(){
    while(m_continue){
        std::this_thread::sleep_for(config::FEED_DELAY_ERROR_TOLERANCE_MILI_SEC);//We can't sleep longer than the tolerable error in delay.
        const std::lock_guard<std::mutex> lock{m_mutex};
        if(!m_dataFeed.empty()){
            auto end = std::chrono::steady_clock::now();
            std::chrono::duration<double> elapsedSeconds = end - m_dataFeed.front().time;
            if(elapsedSeconds.count() >= config::FEED_DELAY_SEC) {
                m_delayedFeedListener.FeedUpdate(m_dataFeed.front().data);
                m_dataFeed.pop();
            }
        }
    }
}

void CFeedDelayer::FeedUpdate(const std::string& data){
    std::cout << "***** Realtime Data received *****" << std::endl;

    const std::lock_guard<std::mutex> lock{m_mutex};
    m_dataFeed.push({data, std::chrono::steady_clock::now()});
}

void CFeedDelayer::Exit(){
    m_continue =false;
}
