//
//  WebSocketServerHandler.hpp
//  Tic-Tac-Toe
//
//  Created by George Endo on 30.06.2019.
//  Copyright © 2019 George Endo. All rights reserved.
//

#ifndef WebSocketServerHandler_hpp
#define WebSocketServerHandler_hpp

#include <memory>
#include <functional>
#include <string>
#include <vector>

#include "NetworkHandler.hpp"
#include "WebSocketSession.hpp"

#include <boost/asio.hpp>
#include <boost/beast/core.hpp>

class WebSocketServerHandler : public NetworkHandler, public std::enable_shared_from_this<WebSocketServerHandler> {
public:
    typedef std::shared_ptr<WebSocketServerHandler> ptr;

    WebSocketServerHandler(boost::asio::io_context& io, boost::asio::ip::tcp::endpoint ep);
    
    void run();
    
    WebSocketSession::ptr get_session(int id);
    
    std::function<void(std::string, int)> read_handler = [](std::string, int){};
    
private:
    void do_accept();
    void on_accept(boost::beast::error_code ec, boost::asio::ip::tcp::socket socket);
    
    boost::asio::ip::tcp::acceptor _acceptor;
    boost::asio::io_context& _io;
    std::vector<WebSocketSession::ptr> _sessions;
};


#endif /* WebSocketServerHandler_hpp */
