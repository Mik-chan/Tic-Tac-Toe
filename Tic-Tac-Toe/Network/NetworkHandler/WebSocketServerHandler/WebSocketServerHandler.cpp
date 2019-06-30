//
//  WebSocketServerHandler.cpp
//  Tic-Tac-Toe
//
//  Created by George Endo on 30.06.2019.
//  Copyright © 2019 George Endo. All rights reserved.
//

#include <iostream>

#include "WebSocketServerHandler.hpp"

namespace asio = boost::asio;
namespace beast = boost::beast;
using tcp = asio::ip::tcp;

WebSocketServerHandler::WebSocketServerHandler(asio::io_context& io, tcp::endpoint ep) : _io(io), _acceptor(io) {
    beast::error_code ec;
    
    _acceptor.open(ep.protocol(), ec);
    _acceptor.set_option(asio::socket_base::reuse_address(true), ec);
    _acceptor.bind(ep, ec);
    _acceptor.listen(asio::socket_base::max_listen_connections, ec);
}

void WebSocketServerHandler::run(){
    do_accept();
}

void WebSocketServerHandler::do_accept(){
    _acceptor.async_accept(asio::make_strand(_io), beast::bind_front_handler(&WebSocketServerHandler::on_accept, shared_from_this()));
}

void WebSocketServerHandler::on_accept(beast::error_code ec, tcp::socket socket){
    _sessions.erase(std::remove_if(_sessions.begin(), _sessions.end(), [](WebSocketSession::ptr session){
     return !session->is_listening();
     }), _sessions.end());
    
    if(ec)
        return;
    else{
        _sessions.push_back(std::make_shared<WebSocketSession>(std::move(socket)));
        _sessions.back()->read_handler = read_handler;
        _sessions.back()->run();
    }
    
    do_accept();
}

WebSocketSession::ptr WebSocketServerHandler::get_session(int id){
    std::vector<WebSocketSession::ptr>::iterator search = std::find_if(_sessions.begin(),
                                                                       _sessions.end(),
                                                                       [id](WebSocketSession::ptr session){
                                                                           return session->id() == id;
                                                                       });
    if(search == _sessions.end()) return nullptr;
    return *search;
}
