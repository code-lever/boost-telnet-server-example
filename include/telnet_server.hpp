#ifndef __TELNET_SERVER_HPP__
#define __TELNET_SERVER_HPP__

#include "telnet_session.hpp"

#include <stdint.h>

#include <boost/asio.hpp>

namespace ba = boost::asio;
namespace bs = boost::system;
using boost::asio::ip::tcp;

class TelnetServer
{
public:
    TelnetServer(ba::io_service& io_service, uint16_t port);

private:
    void start_accept();
    void handle_accept(TelnetSession* new_session, const bs::error_code& error);

    ba::io_service& io_service;
    tcp::acceptor acceptor;
};

#endif

