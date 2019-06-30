//
//  Network.hpp
//  Tic-Tac-Toe
//
//  Created by George Endo on 30.06.2019.
//  Copyright © 2019 George Endo. All rights reserved.
//

#ifndef Network_hpp
#define Network_hpp

#include <vector>
#include <thread>
#include <memory>
#include <boost/asio.hpp>

#include "NetworkHandler.hpp"

class Network{
public:
    Network();
    ~Network();
    
    void run();
    void async_run();
    
    void add_handler(NetworkHandler::ptr handler);
    
    bool is_running() const;
    
    boost::asio::io_context& io_context();
    
private:
    bool _is_running;
    boost::asio::io_context _io;
    std::vector<NetworkHandler::ptr> _handlers;
    std::shared_ptr<std::thread> _io_thread = nullptr;
};

#endif /* Network_hpp */
