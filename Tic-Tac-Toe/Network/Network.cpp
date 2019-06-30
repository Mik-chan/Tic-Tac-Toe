//
//  Network.cpp
//  Tic-Tac-Toe
//
//  Created by George Endo on 30.06.2019.
//  Copyright © 2019 George Endo. All rights reserved.
//

#include "Network.hpp"

namespace asio = boost::asio;

Network::Network(){
    _is_running = false;
    _io_thread = nullptr;
}

Network::~Network(){
    if(_io_thread != nullptr){
        if(_is_running)
            _io.stop();
        _io_thread->join();
    }
}

void Network::run(){
    if(_is_running) return;
    _is_running = true;
    
    for(auto handler : _handlers)
        handler->run();
    
    _io.run();
    _is_running = false;
}

void Network::async_run(){
    if(_is_running) return;
    _is_running = true;
    
    for(auto handler : _handlers)
        handler->run();
    
    _io_thread = std::make_shared<std::thread>([](asio::io_context& io){
        io.run();
    }, std::ref(_io));
}

void Network::add_handler(NetworkHandler::ptr handler){
    if(_is_running) return;
    _handlers.push_back(handler);
}

bool Network::is_running() const{
    return _is_running;
}

asio::io_context& Network::io_context(){
    return _io;
}
