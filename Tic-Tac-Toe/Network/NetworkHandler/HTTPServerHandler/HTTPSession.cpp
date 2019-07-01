//
//  HTTPSession.cpp
//  Tic-Tac-Toe
//
//  Created by George Endo on 1.07.2019.
//  Copyright © 2019 George Endo. All rights reserved.
//

#include "HTTPSession.hpp"

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace http = boost::beast::http;
using tcp = boost::asio::ip::tcp;

HTTPSession::HTTPSession(tcp::socket&& socket) : _stream(std::move(socket)) {}

void HTTPSession::run(){
    do_read();
}

void HTTPSession::respond(http::response<http::string_body>&& msg){
    auto sp = std::make_shared<http::response<http::string_body>>(std::move(msg));
    _res = sp;
    
    http::async_write(_stream, *sp,
                      beast::bind_front_handler(&HTTPSession::on_write, shared_from_this(),
                                                sp->need_eof()));
}


void HTTPSession::do_read(){
    _req = {};
    
    _stream.expires_after(std::chrono::seconds(30));
    
    http::async_read(_stream, _buff, _req,
                     beast::bind_front_handler(&HTTPSession::on_read, shared_from_this()));
}

void HTTPSession::on_read(beast::error_code ec, size_t bytes_transfered){
    boost::ignore_unused(bytes_transfered);
    
    if(ec == http::error::end_of_stream)
        return do_close();
    
    if(ec)
        return;
    
    request_handler(_req, shared_from_this());
}


void HTTPSession::on_write(bool close, beast::error_code ec, size_t bytes_transfered){
    boost::ignore_unused(bytes_transfered);
    
    if(ec)
        return;
    
    if(close)
        return do_close();
    
    _res = nullptr;
    
    do_read();
}

void HTTPSession::do_close(){
    beast::error_code ec;
    _stream.socket().shutdown(tcp::socket::shutdown_send, ec);
}
