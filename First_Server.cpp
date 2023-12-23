#include <boost/asio.hpp>
#include <iostream>
#include <array> // array는 고정 크기 배열을 사용하기 위함

using boost::asio::ip::tcp;

int main() {

    unsigned short Port_Number = 12333;

    try {
        //네트워킹 작업에 필요한 I/O 서비스. 네트워크 작업을 위한 중심적인 객체로, 비동기(독립) 작업을 관리하는 데 사용
        boost::asio::io_service io_service;
        // tcp::acceptor 객체는 클라이언트의 연결을 수락(accept)하기 위한 객체입니다. 
        // 이 코드는 IPv4 주소를 사용하고, 12345 포트에서 연결을 기다리도록 acceptor를 초기화
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), Port_Number));
        while (true) {
            //객체는 TCP 연결을 위한 소켓을 생성합니다. io_service를 이용하여 이 소켓을 생성
            tcp::socket socket(io_service);
            //메소드는 클라이언트의 연결을 동기적으로 수락합니다. 
            //클라이언트가 연결을 시도할 때까지 이 라인에서 실행이 블로킹(정지)됩니다
            acceptor.accept(socket);


            //C++ 표준 라이브러리의 고정 크기 배열. 여기서는 128바이트 크기의 배열을 선언
            std::array<char, 128> data; // 고정 크기 버퍼
            //Boost 라이브러리에서 제공하는 에러 코드 객체. 네트워크 작업 중 발생할 수 있는 에러를 저장하고 있음
            boost::system::error_code error;

            // read_some 메소드는 소켓으로부터 데이터를 동기적으로 읽습니다. 읽은 데이터는 data 배열에 저장되고, 
            // 읽은 바이트 수를 length 변수에 저장합니다. 
            // 만약 에러가 발생하면, error 객체에 해당 에러가 저장됩니다.
            size_t length = socket.read_some(boost::asio::buffer(data), error);

            if (error) { // 에러가 있다면
                //system_error 예외는 에러 코드와 관련된 메시지를 포함하고 있어서 디버깅에 유용합니다.
                throw boost::system::system_error(error); // 실제 에러 처리
            }

            // 소켓으로부터 읽은 데이터를 콘솔에 출력
            // data 배열의 데이터를 length 바이트만큼 표준 출력 스트림에 쓰는 함수
            std::cout.write(data.data(), length);
            std::cout << std::endl;

            // socket을 통해 클라이언트로 데이터를 보냅니다. 
            // "Hello, client!\n" 문자열을 boost::asio::buffer를 사용하여 버퍼로 변환하고, 
            // boost::asio::write 함수로 이 데이터를 클라이언트에게 전송
            boost::asio::write(socket, boost::asio::buffer("Hello, client! 한글돼!\n"));

            // 잠시 대기하여 콘솔 메시지를 볼 수 있게 합니다. Test
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    catch (std::exception& e) {
        //e.what()은 발생한 예외에 대한 설명을 문자열로 반환합니다. 
        // 이 메시지는 std::cerr을 통해 에러 스트림에 출력되고, 콘솔에 표시
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // 이 부분은 실행되지 않지만, 추후 종료 시 While문에서 break 걸고 쓸 예정
    std::cout << "Press Enter to exit...";
    // 종료하기전 키입력 기다림
    std::cin.get();

    // 프로그램이 성공적으로 실행을 마치면, 0 값을 반환
    return 0;
}
