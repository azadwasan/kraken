#include "../../include/websocket/ws_boost.h"

using namespace exchange_client;

session::session(net::io_context& ioc, ssl::context& ctx)
        : m_resolver(net::make_strand(ioc))
        , m_ws(net::make_strand(ioc), ctx)
{
}

// Report a failure
void session::fail(beast::error_code ec, char const* what)
{
    m_status = ws_status::error;
    std::cerr << what << ": " << ec.message() << "\n";
}

// Start the asynchronous operation
void session::start(const std::string& host, const std::string& port, const std::string& text)
{
    // Save these for later
    m_host = host;
    m_text = text;

    // Look up the domain name
    m_resolver.async_resolve(
        host,
        port,
        beast::bind_front_handler(
            &session::resolve_cb,
            shared_from_this()));
}

void session::resolve_cb(
    beast::error_code ec,
    tcp::resolver::results_type results)
{
    if(ec)
        return fail(ec, "resolve");

    // Set a timeout on the operation
    beast::get_lowest_layer(m_ws).expires_after(std::chrono::seconds(TIMEOUT));

    // Make the connection on the IP address we get from a lookup
    beast::get_lowest_layer(m_ws).async_connect(
        results,
        beast::bind_front_handler(
            &session::connect_cb,
            shared_from_this()));
}

void
session::connect_cb(beast::error_code ec, tcp::resolver::results_type::endpoint_type ep)
{
    if(ec)
        return fail(ec, "connect");

    // Set a timeout on the operation
    beast::get_lowest_layer(m_ws).expires_after(std::chrono::seconds(TIMEOUT));

    // Set SNI Hostname (many hosts need this to handshake successfully)
    if(! SSL_set_tlsext_host_name(
            m_ws.next_layer().native_handle(),
            m_host.c_str()))
    {
        ec = beast::error_code(static_cast<int>(::ERR_get_error()),
            net::error::get_ssl_category());
        return fail(ec, "connect");
    }

    // Update the host_ string. This will provide the value of the
    // Host HTTP header during the WebSocket handshake.
    // See https://tools.ietf.org/html/rfc7230#section-5.4
    m_host += ':' + std::to_string(ep.port());
    
    // Perform the SSL handshake
    m_ws.next_layer().async_handshake(
        ssl::stream_base::client,
        beast::bind_front_handler(
            &session::ssl_handshake_cb,
            shared_from_this()));
}

void
session::ssl_handshake_cb(beast::error_code ec)
{
    if(ec)
        return fail(ec, "ssl_handshake");

    // Turn off the timeout on the tcp_stream, because
    // the websocket stream has its own timeout system.
    beast::get_lowest_layer(m_ws).expires_never();

    // Set suggested timeout settings for the websocket
    m_ws.set_option(
        websocket::stream_base::timeout::suggested(
            beast::role_type::client));

    // Set a decorator to change the User-Agent of the handshake
    m_ws.set_option(websocket::stream_base::decorator(
        [](websocket::request_type& req)
        {
            req.set(http::field::user_agent,
                std::string(BOOST_BEAST_VERSION_STRING) +
                    VERSION_STRING);
        }));

    // Perform the websocket handshake
    m_ws.async_handshake(m_host, "/",
        beast::bind_front_handler(
            &session::handshake_cb,
            shared_from_this()));
}

void
session::handshake_cb(beast::error_code ec)
{
    if(ec)
        return fail(ec, "handshake");

    // Send the message
    m_ws.async_write(
        net::buffer(m_text),
        beast::bind_front_handler(
            &session::write_cb,
            shared_from_this()));
}

void
session::write_cb(
    beast::error_code ec,
    std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);

    if(ec)
        return fail(ec, "write");

    // Read a message into our buffer
    m_ws.async_read(
        buffer_,
        beast::bind_front_handler(
            &session::read_cb,
            shared_from_this()));
}

void session::read_cb(beast::error_code ec, std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);

    if(ec)
        return fail(ec, "read");

    std::cout << beast::make_printable(buffer_.data()) << std::endl;
    buffer_.consume(buffer_.size());
    m_ws.async_read(
        buffer_,
        beast::bind_front_handler(
            &session::read_cb,
            shared_from_this()));

    // Close the WebSocket connection
    // ws_.async_close(websocket::close_code::normal,
    //     beast::bind_front_handler(
    //         &session::on_close,
    //         shared_from_this()));
}

void
session::close_cb(beast::error_code ec)
{
    if(ec)
        return fail(ec, "close");

    // If we get here then the connection is closed gracefully

    // The make_printable() function helps print a ConstBufferSequence
    std::cout << beast::make_printable(buffer_.data()) << std::endl;
}
