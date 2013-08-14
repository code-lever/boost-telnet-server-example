#include "telnet_server.hpp"

#include <stdint.h>

#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

namespace ba = boost::asio;
namespace bs = boost::system;
using boost::asio::ip::tcp;

TelnetServer::TelnetServer(ba::io_service& io_service, uint16_t port)
    : io_service(io_service),
      acceptor(io_service, tcp::endpoint(tcp::v4(), port))
{
    start_accept();
}

void TelnetServer::start_accept()
{
    std::cout << "server::start_accept\n";
    TelnetSession* new_session = new TelnetSession(io_service);
    acceptor.async_accept(new_session->socket(), 
        boost::bind(&TelnetServer::handle_accept, 
            this, new_session, ba::placeholders::error));
}

void TelnetServer::handle_accept(TelnetSession* new_session, const bs::error_code& error)
{
    if (!error)
    {
        std::cout << "accepted connection, starting session\n";
        new_session->start();
    }
    else
    {
        delete new_session;
    }

    start_accept();
}
