#ifndef __TELNET_SESSION_HPP__
#define __TELNET_SESSION_HPP__

#include <boost/asio.hpp>

namespace ba = boost::asio;
namespace bs = boost::system;
using boost::asio::ip::tcp;

class TelnetSession
{
public:
    TelnetSession(ba::io_service& io_service);

    tcp::socket& socket() { return mSocket; }

    void start();

    enum { max_length = 10 };

private:
    void handle_read(const bs::error_code& error, size_t bytes_transferred);

    void handle_write(const bs::error_code& error);

    tcp::socket mSocket;
    char data[max_length];
};

#endif

