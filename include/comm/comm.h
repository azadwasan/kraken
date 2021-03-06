
#ifndef COMM_H_
#define COMM_H_


#include <string>

namespace exchangeClient{

enum class WebsocketStatus{
    disconnected,
    connected,
    error
};

class ICommChannel{
    virtual void start() = 0;
    virtual WebsocketStatus getStatus() = 0;
    virtual void sendRequest(const std::string&) = 0;
    virtual void registerListener() = 0;
    virtual void disconnect() = 0;
};
}
#endif