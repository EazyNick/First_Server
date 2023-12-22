#include "session.h"
#include <iostream>
#include <boost/bind.hpp>

session::session(boost::asio::io_service& io_service) : socket_(io_service) {
}

tcp::socket& session::socket() {
    return socket_;
}

void session::start() {
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        boost::bind(&session::handle_read, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void session::handle_read(const boost::system::error_code& error, size_t bytes_transferred) {
    if (!error) {
        std::cout << "Received data: " << data_ << std::endl;
    }
    else {
        delete this;
    }
}
