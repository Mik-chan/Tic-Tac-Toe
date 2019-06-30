//
//  WebSocketSession.hpp
//  Tic-Tac-Toe
//
//  Created by George Endo on 30.06.2019.
//  Copyright © 2019 George Endo. All rights reserved.
//

#ifndef WebSocketSession_hpp
#define WebSocketSession_hpp

#include <memory>
#include <string>

#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>

class WebSocketSession : public std::enable_shared_from_this<WebSocketSession> {
public:
    typedef std::shared_ptr<WebSocketSession> ptr;
    
    explicit WebSocketSession(boost::asio::ip::tcp::socket&& socket);
    
    void run();
    
    void write(const std::string& msg);
    
    bool is_listening() const;
    int id() const;
    
    std::function<void(std::string, int)> read_handler = [](std::string, int){};
    
private:
    
    void on_accept(boost::beast::error_code ec);
    
    void do_read();
    void on_read(boost::beast::error_code ec, std::size_t bytes_transferred);
    
    std::string buff_to_str(const boost::beast::flat_buffer& buff) const;
    
    boost::beast::websocket::stream<boost::beast::tcp_stream> _ws;
    boost::beast::flat_buffer _buff;
    bool _is_listening;
    int connection_id;
};

#endif /* WebSocketSession_hpp */
