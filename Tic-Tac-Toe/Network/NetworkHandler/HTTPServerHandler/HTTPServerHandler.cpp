//
//  HTTPServerHandler.cpp
//  Tic-Tac-Toe
//
//  Created by George Endo on 1.07.2019.
//  Copyright © 2019 George Endo. All rights reserved.
//

#include <iostream>

#include "HTTPServerHandler.hpp"

namespace asio = boost::asio;
namespace beast = boost::beast;
using tcp = asio::ip::tcp;

HTTPServerHandler::HTTPServerHandler(asio::io_context& io, tcp::endpoint ep) : _acceptor(asio::make_strand(io)), _io(io) {
    beast::error_code ec;
    _acceptor.open(ep.protocol(), ec);
    _acceptor.set_option(asio::socket_base::reuse_address(true), ec);
    _acceptor.bind(ep, ec);
    _acceptor.listen(asio::socket_base::max_listen_connections, ec);
}

void HTTPServerHandler::run(){
    do_accept();
}

void HTTPServerHandler::do_accept(){
    _acceptor.async_accept(asio::make_strand(_io),
                           beast::bind_front_handler(&HTTPServerHandler::on_accept, shared_from_this()));
}

void HTTPServerHandler::on_accept(beast::error_code ec, tcp::socket socket){
    if(!ec){
        HTTPSession::ptr tmp = std::make_shared<HTTPSession>(std::move(socket));
        tmp->request_handler = this->request_handler;
        tmp->run();
    }
    
    do_accept();
}
