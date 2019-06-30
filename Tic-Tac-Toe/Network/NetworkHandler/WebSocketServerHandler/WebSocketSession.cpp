//
//  WebSocketSession.cpp
//  Tic-Tac-Toe
//
//  Created by George Endo on 30.06.2019.
//  Copyright © 2019 George Endo. All rights reserved.
//

#include "WebSocketSession.hpp"

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace http = boost::beast::http;
namespace websocket = boost::beast::websocket;

using tcp = asio::ip::tcp;

WebSocketSession::WebSocketSession(boost::asio::ip::tcp::socket&& socket) : _ws(std::move(socket)) {
    _is_listening = false;
    
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int> dist(std::numeric_limits<int>::min(),
                                            std::numeric_limits<int>::max());
    
    connection_id = dist(engine);
}

void WebSocketSession::run(){
    _is_listening = true;
    
    _ws.set_option(websocket::stream_base::timeout::suggested(beast::role_type::server));
    _ws.set_option(websocket::stream_base::decorator(
                                                     [](websocket::response_type& res)
                                                     {
                                                         res.set(http::field::server,
                                                                 std::string(BOOST_BEAST_VERSION_STRING) +
                                                                 " websocket-server-async");
                                                     }));
    _ws.async_accept(beast::bind_front_handler(&WebSocketSession::on_accept, shared_from_this()));
}

void WebSocketSession::write(const std::string& msg){
    if(!_is_listening) return;
    beast::error_code ec;
    _ws.write(asio::buffer(msg), ec);
}

bool WebSocketSession::is_listening() const{
    return _is_listening;
}

int WebSocketSession::id() const{
    return connection_id;
}

void WebSocketSession::on_accept(beast::error_code ec){
    if(ec){
        _is_listening = false;
        return;
    }
    
    do_read();
}

void WebSocketSession::do_read(){
    _ws.async_read(_buff, beast::bind_front_handler(&WebSocketSession::on_read, shared_from_this()));
}

void WebSocketSession::on_read(beast::error_code ec, std::size_t bytes_transferred){
    boost::ignore_unused(bytes_transferred);
    
    if(ec == websocket::error::closed){
        _is_listening = false;
        return;
    }
    
    if(ec){
        _is_listening = false;
        return;
    }
    
    read_handler(buff_to_str(_buff), connection_id);
    _buff.clear();
    
    do_read();
}

std::string WebSocketSession::buff_to_str(const beast::flat_buffer& buff) const{
    asio::const_buffer tmp_buff = buff.data();
    const char* p = reinterpret_cast<const char*>(tmp_buff.data());
    return std::string(p, p + tmp_buff.size());
}
