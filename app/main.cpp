#include <iostream>
#include <boost/program_options.hpp>
#include "Inet/TcpServer.hpp"

namespace po = boost::program_options;

int main(int argc, char** argv) {
    po::options_description desc("Allowed options");
    desc.add_options()
            ("help", "produce help message")
            ("directory", po::value<std::string>(), "http main directory")
            ("addr", po::value<std::string>(), "http server address")
            ("port", po::value<std::string>(), "http server port");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if(vm.count("help")) {
        std::cout << desc << '\n';
        return 1;
    }

    if(vm.count("directory")) {
        std::cout << vm["directory"].as<std::string>() << '\n';
    }
    if(vm.count("addr")) {
        std::cout << vm["addr"].as<std::string>() << '\n';
    }
    if(vm.count("port")) {
        std::cout << vm["port"].as<std::string>() << '\n';
    }

    TcpServer tcpServer({"127.0.0.1", 8888});
    tcpServer.run();

    return 0;
}
