#include "telnet_session.hpp"

#include "telnet_server.hpp"

#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

namespace ba = boost::asio;
namespace bs = boost::system;
using boost::asio::ip::tcp;

TelnetSession::TelnetSession(ba::io_service& io_service)
    : mSocket(io_service)
{
}

void TelnetSession::start()
{
    mSocket.async_read_some(boost::asio::buffer(data, max_length),
        boost::bind(&TelnetSession::handle_read, this,
            ba::placeholders::error, ba::placeholders::bytes_transferred));
}

void TelnetSession::handle_read(const bs::error_code& error, size_t bytes_transferred)
{
    if (!error)
    {
        std::cout << "TelnetSession::handle_read " << (int) bytes_transferred << " bytes\n";
        ba::async_write(mSocket,
            ba::buffer(data, bytes_transferred), 
            boost::bind(&TelnetSession::handle_write, this, ba::placeholders::error));
    }
    else
    {
        std::cout << "TelnetSession::handle_read error: " << error << std::endl;
        delete this;
    }
}

void TelnetSession::handle_write(const bs::error_code& error)
{
    if (!error)
    {
        std::cout << "TelnetSession::handle_write\n";
        mSocket.async_read_some(ba::buffer(data, max_length),
            boost::bind(&TelnetSession::handle_read, this,
                ba::placeholders::error, ba::placeholders::bytes_transferred));
    }
    else
    {
        std::cout << "TelnetSession::handle_write error: " << error << std::endl;
        delete this;
    }
}

