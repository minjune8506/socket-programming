# TCP 소켓

네트워크를 통해 들어온 데이터를 적절한 프로세스에게 전달하는 것이 전송 계층 프로토콜의 임무이다.

- 프로세스 데이터를 IP 계층으로 전달
- IP계층으로부터 받은 데이터를 프로세스에게 전달

통신 프로토콜 상에서 호스트 A에서 동작하는 TCP 모듈과 호스트 B에서 동작하는 TCP 모듈을 서로 counter part가 된다.

## TCP 기능

- 호스트 안에서 프로세스 식별을 통한 데이터의 전송
- 신뢰적이고 순차적인 데이터 전송
- 흐름제어와 혼잡제어

## TCP 헤더

![TCP Header](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FqhOsg%2FbtqEHOG7Ygi%2FKXyiPBrguUJTWCZEjDhjf0%2Fimg.png)

- Source Port, Destination Port : TCP 세그먼트를 보내는 프로세스가 사용하는 port 번호와 TCP 세스먼트를 받는 프로세스가 사용하는 port 번호
- Sequence Number : TCP는 데이터를 바이트 스트림으로 처리한다. TCP 세그먼트 중 헤더 다음에 오는 데이터 부분은 바이트 스트림을 순차적으로 잘라서 구성된다. 전체 바이트 스트림에서 해당 TCP 세그먼트에 실려있는 바이트 번호 중 가장 빠른 번호
- Acknowledgement Number : 성공적인 데이터 전달 여부를 상대방에게 알린다. 다음에 전송 받을 Sequence Number
- Header Length : 기본적인 TCP 헤더의 길이는 20byte이다. 가변적인 옵션이 추가될 수 있따. 4byte 단위로 나타낸다. Header Length가 5이면 5 * 4 = 20byte를 의미한다.
- Reserved Field : 미래에 추가될 기능을 위해 남겨둔 비트들
- TCP Flags : TCP 세그먼트의 기능을 표시하기 위한 플래그
	- CWR : 혼잡제어
	- ECE : 혼잡제어
	- URG : 긴급 데이터 포함 여부
	- ACK : Ack 필드가 유효한지를 나타낸다.
	- PHS : 긴급한 데이터 처리 요청
	- RST : 연결 리셋
	- SYN : 연결 시작
	- FIN : 연결 종료
- Window Size : 수신 버퍼의 크기를 알린다.
- TCP Checksum : 세그먼트의 데이터 무결성을 검사하기 위한 필드
- Urgent Pointer : 긴급 데이터를 가리키는 포인터

## TCP 상태

TCP는 연결지향형 프로토콜이다.

통신을 하는 두 호스트에서 실행 중인 TCP 모듈은 연결되어 있다.

![TCP Finite State Machine](https://www.site.uottawa.ca/~elsaddik/abedweb/applets/Applets/TCP/state2.jpg)

Passive Open : TCP 연결을 위해 대기 상태로 돌입한다. (Server) LISTEN

Active Open : TCP 연결을 SYN 세그먼트를 전송한다. (Client)

### 3-Way HandShake

![3-Way HandShake](https://t1.daumcdn.net/cfile/tistory/99087C405C18E3CD28)

### 4-Way HandShake

![4-Way HandSHake](https://images.velog.io/images/nnnyeong/post/fd5029e1-b84c-4fa3-9f7b-d5f702f1b1b9/image.png)

## TCP 흐름 제어

TCP는 수신 받은 데이터를 운영체제가 제공하는 버퍼에 순서대로 채운다.

버퍼에 있는 데이터들은 해당 포트에서 대기하고 있는 응용 프로그램이 데이터를 가져갈 때까지 유지된다.

버퍼의 크기는 유한하며 데이터가 가득 찬 경우 TCP는 더이상 데이터를 받을 수 없는 상태가 된다.

이런 이유로 TCP는 상대방의 버퍼에 공간이 있을 때만 데이터를 전송한다.

흐름제어를 위해 Sliding Window라는 개념을 이용한다.

TCP 헤더의 Window 부분이 이에 해당한다.
