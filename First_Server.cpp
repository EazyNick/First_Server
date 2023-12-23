#include <boost/asio.hpp>
#include <iostream>
#include <array> // array�� ���� ũ�� �迭�� ����ϱ� ����

using boost::asio::ip::tcp;

int main() {

    unsigned short Port_Number = 12333;

    try {
        //��Ʈ��ŷ �۾��� �ʿ��� I/O ����. ��Ʈ��ũ �۾��� ���� �߽����� ��ü��, �񵿱�(����) �۾��� �����ϴ� �� ���
        boost::asio::io_service io_service;
        // tcp::acceptor ��ü�� Ŭ���̾�Ʈ�� ������ ����(accept)�ϱ� ���� ��ü�Դϴ�. 
        // �� �ڵ�� IPv4 �ּҸ� ����ϰ�, 12345 ��Ʈ���� ������ ��ٸ����� acceptor�� �ʱ�ȭ
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), Port_Number));
        while (true) {
            //��ü�� TCP ������ ���� ������ �����մϴ�. io_service�� �̿��Ͽ� �� ������ ����
            tcp::socket socket(io_service);
            //�޼ҵ�� Ŭ���̾�Ʈ�� ������ ���������� �����մϴ�. 
            //Ŭ���̾�Ʈ�� ������ �õ��� ������ �� ���ο��� ������ ���ŷ(����)�˴ϴ�
            acceptor.accept(socket);


            //C++ ǥ�� ���̺귯���� ���� ũ�� �迭. ���⼭�� 128����Ʈ ũ���� �迭�� ����
            std::array<char, 128> data; // ���� ũ�� ����
            //Boost ���̺귯������ �����ϴ� ���� �ڵ� ��ü. ��Ʈ��ũ �۾� �� �߻��� �� �ִ� ������ �����ϰ� ����
            boost::system::error_code error;

            // read_some �޼ҵ�� �������κ��� �����͸� ���������� �н��ϴ�. ���� �����ʹ� data �迭�� ����ǰ�, 
            // ���� ����Ʈ ���� length ������ �����մϴ�. 
            // ���� ������ �߻��ϸ�, error ��ü�� �ش� ������ ����˴ϴ�.
            size_t length = socket.read_some(boost::asio::buffer(data), error);

            if (error) { // ������ �ִٸ�
                //system_error ���ܴ� ���� �ڵ�� ���õ� �޽����� �����ϰ� �־ ����뿡 �����մϴ�.
                throw boost::system::system_error(error); // ���� ���� ó��
            }

            // �������κ��� ���� �����͸� �ֿܼ� ���
            // data �迭�� �����͸� length ����Ʈ��ŭ ǥ�� ��� ��Ʈ���� ���� �Լ�
            std::cout.write(data.data(), length);
            std::cout << std::endl;

            // socket�� ���� Ŭ���̾�Ʈ�� �����͸� �����ϴ�. 
            // "Hello, client!\n" ���ڿ��� boost::asio::buffer�� ����Ͽ� ���۷� ��ȯ�ϰ�, 
            // boost::asio::write �Լ��� �� �����͸� Ŭ���̾�Ʈ���� ����
            boost::asio::write(socket, boost::asio::buffer("Hello, client! �ѱ۵�!\n"));

            // ��� ����Ͽ� �ܼ� �޽����� �� �� �ְ� �մϴ�. Test
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    catch (std::exception& e) {
        //e.what()�� �߻��� ���ܿ� ���� ������ ���ڿ��� ��ȯ�մϴ�. 
        // �� �޽����� std::cerr�� ���� ���� ��Ʈ���� ��µǰ�, �ֿܼ� ǥ��
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // �� �κ��� ������� ������, ���� ���� �� While������ break �ɰ� �� ����
    std::cout << "Press Enter to exit...";
    // �����ϱ��� Ű�Է� ��ٸ�
    std::cin.get();

    // ���α׷��� ���������� ������ ��ġ��, 0 ���� ��ȯ
    return 0;
}
