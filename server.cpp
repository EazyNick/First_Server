#include "server.h"
#include "session.h"
#include <boost/bind.hpp>

server::server(boost::asio::io_service& io_service, short port)
    : io_service_(io_service), acceptor_(io_service, tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), port))
    //acceptor_(io_service, tcp::endpoint(tcp::v4(), 51235)) 모든 사람 접속 가능
//acceptor_(io_service, tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), port)) 로컬에서만 접근 가능
//acceptor_(io_service, tcp::endpoint(boost::asio::ip::address::from_string("192.168.1.100"), port)) 특정 아이피만 접근 가능

{
    start_accept();
}

void server::start_accept() {
    session* new_session = new session(io_service_);
    acceptor_.async_accept(new_session->socket(),
        boost::bind(&server::handle_accept, this, new_session,
            boost::asio::placeholders::error));
}

void server::handle_accept(session* new_session, const boost::system::error_code& error) {
    if (!error) {
        new_session->start();
    }
    else {
        delete new_session;
    }
    start_accept();
}
