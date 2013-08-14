#include "telnet_server.hpp"

#include <iostream>

#include <boost/asio.hpp>
#include <boost/program_options.hpp>

namespace ba = boost::asio;
namespace po = boost::program_options;

int main(int argc, char* argv[])
{
    po::variables_map vm;
    ba::io_service io_service;

    try
    {
        po::options_description description;
        description.add_options()
            ("port,p", po::value<uint16_t>()->default_value(21), "TCP port for Telnet server")
            ("help", "display help message and exit")
        ;

        po::store(po::parse_command_line(argc, argv, description), vm);
        po::notify(vm);

        if (vm.count("help"))
        {
            std::cout << "Usage: " << argv[0] << " [options]" << std::endl;
            std::cout << description;
            return 0;
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    try
    {
        TelnetServer ts(io_service, vm["port"].as<uint16_t>());
        std::cout << "Before io_service.run()\n";
        io_service.run();
        std::cout << "After io_service.run()\n";
    }
    catch (std::exception& e)
    {
        std::cerr << "TELNET SERVER ERROR: " << e.what() << std::endl;
    }

    return 0;
}
