#include <iostream>
#include <boost/program_options.hpp>
#include "Inet/TcpServer.hpp"
#include <thread>
#include "ConnectionAcceptor.hpp"
#include "Strategy/EchoStrategy.hpp"
#include "Strategy/HttpStrategy.hpp"

namespace po = boost::program_options;

std::string print(std::string const& msg) {
    std::cout << msg;
    return msg;
}

int main(int argc, char** argv) {
    po::options_description desc("Allowed options");
    desc.add_options()
            ("help", "produce help message")
            ("directory", po::value<std::string>(), "http main directory");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if(vm.count("help")) {
        std::cout << desc << '\n';
        return 1;
    }

    std::string directory;

    if(vm.count("directory")) {
        std::cout << vm["directory"].as<std::string>() << '\n';
        directory = vm["directory"].as<std::string>();
    }

    if(directory.empty()) {
        return 1;
    }

    TcpServer tcpServer({"127.0.0.1", 8888}, HttpStrategy(directory));

    std::thread t1([&tcpServer](){
        std::this_thread::sleep_for(std::chrono::seconds(300));
        tcpServer.stop();
    });
    t1.detach();

    tcpServer.run();

    std::cout << "END";
    return 0;
}
