#include <iostream>
#include <boost/program_options.hpp>
#include "Inet/TcpServer.hpp"
#include "Strategy/HttpStrategy.hpp"
#include <thread>
#include <condition_variable>
#include <mutex>
#include <csignal>

namespace po = boost::program_options;

std::string print(std::string const& msg) {
    std::cout << msg;
    return msg;
}

namespace {
    std::mutex stopServerMutex;
    std::condition_variable stopServerCv;
}

void signalHandler(int signum) {
    std::cout << "Interrupt signal (" << signum << ") received.\n";
    stopServerCv.notify_all();
}


int main(int argc, char** argv) {
    po::options_description desc("Allowed options");
    desc.add_options()
            ("help", "produce help message")
            ("directory", po::value<std::string>(), "http main directory")
            ("port", po::value<uint16_t>(), "server port");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if(vm.count("help")) {
        std::cout << desc << '\n';
        return 1;
    }

    std::string directory;
    uint16_t port = 8888;

    if(vm.count("directory")) {
        std::cout << "Directory: " << vm["directory"].as<std::string>() << '\n';
        directory = vm["directory"].as<std::string>();
    }

    if(vm.count("port")) {
        std::cout << "Port: " << vm["port"].as<uint16_t>() << '\n';
        port = vm["port"].as<uint16_t>();
    }

    if(directory.empty()) {
        return 1;
    }

    std::signal(SIGINT, signalHandler);
    std::signal(SIGTERM, signalHandler);

    TcpServer tcpServer({"127.0.0.1", port}, HttpStrategy(directory));

    std::thread t1([&](){
        std::unique_lock<std::mutex> lk(::stopServerMutex);
        ::stopServerCv.wait(lk);
        tcpServer.stop();
    });
    t1.detach();

    tcpServer.run();

    std::cout << "END";
    return 0;
}
