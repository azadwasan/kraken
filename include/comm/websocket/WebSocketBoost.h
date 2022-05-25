//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

//------------------------------------------------------------------------------
//
// Example: WebSocket SSL client, asynchronous
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//  The reference code was taken from the source as referenced above.
//  It has been modified and extended to fit our needs.
//
//------------------------------------------------------------------------------

#ifndef WS_BOOST_H_
#define WS_BOOST_H_

#include "../../common/root_certificates.hpp"
#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/asio/strand.hpp>
#include <cstdlib>
#include <functional>
#include <memory>
#include <iostream>
#include "../comm.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
namespace ssl = boost::asio::ssl;       // from <boost/asio/ssl.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

//------------------------------------------------------------------------------

namespace exchangeClient{
// Sends a WebSocket message and prints the response
class WebSocketBoost : public std::enable_shared_from_this<WebSocketBoost>
{
public:
    // Resolver and socket require an io_context
    explicit WebSocketBoost(net::io_context&, ssl::context&);

    void start(const std::string&, const std::string&, const std::string&);
    ws_status getStatus() {return m_status;}
    void sendRequest(const std::string&);
    void registerListener() {}
    void disconnect();

private:
    void fail(beast::error_code ec, char const* what);

    void resolve_cb( beast::error_code ec, tcp::resolver::results_type results);

    void connect_cb(beast::error_code ec, tcp::resolver::results_type::endpoint_type ep);

    void ssl_handshake_cb(beast::error_code ec);

    void handshake_cb(beast::error_code ec);

    void write_cb(beast::error_code ec, std::size_t bytes_transferred);

    void read_cb(beast::error_code ec, std::size_t bytes_transferred);

    void close_cb(beast::error_code ec);

private:
    tcp::resolver m_resolver;
    websocket::stream<beast::ssl_stream<beast::tcp_stream>> m_ws;
    beast::flat_buffer buffer_;
    std::string m_host{};
    std::string m_text{};
    ws_status m_status{ws_status::disconnected};

    static constexpr uint8_t TIMEOUT = 30;
    static constexpr const char* VERSION_STRING = "EXCHANGE_CLIENT";
};
}

#endif /* WS_BOOST_H_ */