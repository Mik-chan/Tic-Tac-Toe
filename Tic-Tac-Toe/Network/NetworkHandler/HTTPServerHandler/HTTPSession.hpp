//
//  HTTPSession.hpp
//  Tic-Tac-Toe
//
//  Created by George Endo on 1.07.2019.
//  Copyright © 2019 George Endo. All rights reserved.
//

#ifndef HTTPSession_hpp
#define HTTPSession_hpp

#include <memory>

#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>

class HTTPSession : public std::enable_shared_from_this<HTTPSession> {
public:
    typedef std::shared_ptr<HTTPSession> ptr;
    
    explicit HTTPSession(boost::asio::ip::tcp::socket&& socket);
    
    void run();
    
    void respond(boost::beast::http::response<boost::beast::http::string_body>&& msg);
    
    std::function<void(boost::beast::http::request<boost::beast::http::string_body>, HTTPSession::ptr)> request_handler = [](boost::beast::http::request<boost::beast::http::string_body>, HTTPSession::ptr){};
    
private:
    
    void do_read();
    void on_read(boost::beast::error_code ec, size_t bytes_transfered);
    
    void on_write(bool close, boost::beast::error_code ec, size_t bytes_transfered);
    
    void do_close();
    
    boost::beast::flat_buffer _buff;
    boost::beast::tcp_stream _stream;
    boost::beast::http::request<boost::beast::http::string_body> _req;
    std::shared_ptr<void> _res;
};


#endif /* HTTPSession_hpp */
