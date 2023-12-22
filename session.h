#ifndef SESSION_H
#define SESSION_H

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class session {
public:
    session(boost::asio::io_service& io_service);
    tcp::socket& socket();
    void start();

private:
    void handle_read(const boost::system::error_code& error, size_t bytes_transferred);

    tcp::socket socket_;
    enum { max_length = 1024 };
    char data_[max_length];
};

#endif // SESSION_H