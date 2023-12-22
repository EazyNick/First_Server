#include <boost/asio.hpp>
#include <iostream>
#include <array>

using boost::asio::ip::tcp;

int main() {
    try {
        boost::asio::io_service io_service;
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 12345));
        tcp::socket socket(io_service);
        acceptor.accept(socket);

        std::array<char, 128> data; // ���� ũ�� ����
        boost::system::error_code error;
        size_t length = socket.read_some(boost::asio::buffer(data), error);

        if (error) {
            throw boost::system::system_error(error); // ���� ���� ó��
        }

        std::cout.write(data.data(), length);
        std::cout << std::endl;

        boost::asio::write(socket, boost::asio::buffer("Hello, client!\n"));
    }
    catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
