#include <string>

namespace exchange_client{

enum class ws_status{
    disconnected,
    connected,
    error
};

class IWebSocket{
    virtual void start(const std::string&, const std::string&, const std::string&)=0;
    virtual ws_status getStatus() = 0;
    virtual void sendRequest(const std::string&) = 0;
    virtual void registerListener() = 0;
    virtual void disconnect() = 0;
};
}