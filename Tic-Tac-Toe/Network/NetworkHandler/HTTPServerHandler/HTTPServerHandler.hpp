//
//  HTTPServerHandler.hpp
//  Tic-Tac-Toe
//
//  Created by George Endo on 1.07.2019.
//  Copyright © 2019 George Endo. All rights reserved.
//

#ifndef HTTPServerHandler_hpp
#define HTTPServerHandler_hpp

#include <memory>

#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>

#include "NetworkHandler.hpp"
#include "HTTPSession.hpp"

class HTTPServerHandler : public NetworkHandler, public std::enable_shared_from_this<HTTPServerHandler>{
public:
    typedef std::shared_ptr<HTTPServerHandler> ptr;
    
    HTTPServerHandler(boost::asio::io_context& io, boost::asio::ip::tcp::endpoint ep);
    
    void run();
    
    std::function<void(boost::beast::http::request<boost::beast::http::string_body>, HTTPSession::ptr)> request_handler = [](boost::beast::http::request<boost::beast::http::string_body>, HTTPSession::ptr){};
    
private:
    void do_accept();
    void on_accept(boost::beast::error_code ec, boost::asio::ip::tcp::socket socket);
    
    boost::asio::ip::tcp::acceptor _acceptor;
    boost::asio::io_context& _io;
};


#endif /* HTTPServerHandler_hpp */
