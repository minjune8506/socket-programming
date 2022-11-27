# 소켓 API

## 네트워크 주소

다른 호스트상에서 실행 중인 두 프로세스가 정보를 주고 받으려면 두 개의 주소가 필요하다.

- 호스트를 식별하기 위한 IP 주소
- 호스트에 도착한 데이터를 해당 프로세스에게 전달하기 위한 Port 번호

## 바이트 순서

컴퓨터에서 데이터를 바이트 단위로 다룬다.

데이터를 바이트 단위로 다루는 것은 대부분의 컴퓨터에서 공통적인 일이지만 여러 바이트로 구성된 데이터를 메모리에 저장하는 방식은 컴퓨터 구조에 따라 다를 수 있다.

네트워크를 거치는 데이터는 Big-Endian 방식을 사용하기로 약속했고, 이것을 Network Byte Order라고 한다.

### Big Endian

최상위 바이트(MSB)부터 차례로 저장하는 방식

![Bid Endian](https://upload.wikimedia.org/wikipedia/commons/thumb/5/54/Big-Endian.svg/400px-Big-Endian.svg.png)

### Little Endian

최하위 바이트부터 차례로 저장하는 방식

![Little Endian](https://upload.wikimedia.org/wikipedia/commons/thumb/e/ed/Little-Endian.svg/400px-Little-Endian.svg.png)

## 주소 변환

프로그램이 사용자에게 입력받는 주소는 Dotted-Decimal 형식의 문자열 IP 주소 또는 호스트 이름일 것이다.

각각의 경우에 따라서 주소를 변환하는 방법이 필요하다.
```C
int inet_addr(const char *cp);
```
