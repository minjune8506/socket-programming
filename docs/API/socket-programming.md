# socket programming API

## socket()

```C
#include <sys/socket.h>

int socket(int domain, int type, int protocol);
```

### Parameter

domain : 소켓의 통신 영역을 지정한다.

- AF_INET : IPv4 기반 인터넷 프로토콜
- AF_INET6 : IPv6 기반 인터넷 프로토콜
- AF_UNIX or AF_LOCAL : 호스트 내에서의 통신

type : 소켓의 종류를 지정한다.

- SOCK_STREAM : 순차적, 안정적인 연결지향형 양방향 통신
- SOCK_DGRAM : 비연결지향형 데이터 그램 방식 통신
- SOCK_RAW : 사용자 정의 4계층 통신

protocol : 소켓에서 사용할 프토토콜을 지정한다.

- IPPROTO_TCP : 전송 계층 프로토콜 TCP 지정
- IPPROTO_UDP : 전송 계층 프로토콜 UDP 지정

### Return Value

성공시 생성된 소켓의 파일 디스크립터 반환

실패시 -1 반환

---

## sockaddr 구조체

```C
struct sockaddr {
	uint8_t		sa_len;			// 주소 길이
	sa_family_t	sa_family;		// 주소 패밀리
	char		sa_data[14]; 	// 주소 값
}
```

``` Plain text
uint8_t : 부호 없는 8비트 정수 <sys/types.h>
```

### sockaddr_in 구조체
```C
#include <netinet/in.h>

struct in_addr {
	u_long s_addr; // 32비트 IP 주소를 저장 할 구조체
}

struct sockaddr_in {
		short          sin_family;	// 주소 체계: AF_INET(IPv4)
		u_short        sin_port;	// 16비트 포트 번호
		struct in_addr sin_addr;	// 32비트 IP 주소
		char           sin_zero[8];	// 전체 크기를 16비트로 맞추기 위한 dummy
}
```

---

## bind()

```C
#include <sys/socket.h>

int bind(int sockfd,
	const struct sockaddr *addr,
	socklen_t addrlen);
```

### Parameter

sockfd : 소켓의 파일 디스크립터

addr : sockaddr 구조체를 가리키는 포인터

addrlen : sockaddr 구조체의 크기

### Return Value

성공시 0을 반환한다.

실패시 -1을 반환한다.

---

## Byte Order

```C
#include <netinet/in.h>

uint32_t htonl(uint32_t hostlong);
uint16_t htons(uint16_t hostshort);
uint32_t ntohl(uint32_t netlong);
uint16_t ntohs(uint16_t netshort);
```

---

## inet_addr()

cp 문자열 IP 주소를 네트워크 바이트 순서 in_addr_t(uint32_t)로 반환한다.

```C
#include <arpa/inet.h>

in_addr_t inet_addr(const char *cp);
```

### Parameter

cp : 문자열로 입력된 Dotted-Decimal 형식의 IP 주소

### Return Value

네트워크 바이트 순서로 변환된값을 반환한다.

잘못된 값을 입력했다면 INADDR_NONE(-1)을 반환한다.

---

## listen()

해당 소켓을 듣기 상태로 만든다.

listen 함수가 호출되면 해당 소켓은 상대방의 연결 요청을 받을 준비를 한다.

프로그램 흐름은 다음 라인으로 넘어가고 운영체제에게 해당 소켓을 통해 연결 요청이 들어올 경우 연결 요청 정보를 저장하라고 시킨다.

```C
#include <sys/types.h>
#include <sys/socket.h>

int listen(int sockfd, int backlog);
```

### Parameter

sockfd : 소켓의 파일 디스크립터

backlog : 저장하고 있을 연결 요청의 최대 수 (백로그 큐)

### Return Value

성공시 0을 반환한다.

실패시 -1을 반환한다.

---

## accept()

accept 함수가 호출되면, 커널은 listen 함수에 의해 생성된 대기열에 연결 요청이 있는지를 확인한다.

연결 요청이 없으면 accept 함수는 연결 요청이 발생할 때까지 프로그램의 제어권을 가진 상태로 대기한다. (Blocking)

연결 요청이 있으면 가장 먼저 연결 요청을 한 프로세스와 통신하기 위한 소켓의 파일 디스크립터를 반환한다.

```C
#include <sys/types.h>
#include <sys/socket.h>

int accept(int sockfd, struct sockaddr *addr, socket_t *addrlen);
```

### Parameter

sockfd : 주소 정보를 입력할 소켓의 파일 디스크립터 (client)

addr : 연결 요청한 상대방(client)의 주소를 저장하기 위한 공간

addrlen : addr 주소 공간의 크기

### Return Value

성공시 연결 요청한 프로세스와 통신하기 위한 소켓의 파일 디스크립터를 반환한다.

실패시 -1을 반환한다.

---

## connect()

client의 주소와 포트번호는 운영체제가 자동으로 입력한다.

```C
#include <sys/types.h>
#include <sys/socket.h>

int connect(int sockfd, 
			const struct sockaddr *addr, 
			socklen_t addrlen);
```

### Parameter

sockfd : 연결 후 데이터 전송을 책임지는 소켓의 파일 디스크립터

addr : 목적지 프로세스의 주소 (server의 주소)

addrlen : addr 주소 공간의 크기

### Return Value

성공시 0을 반환한다.

실패시 -1을 반환한다.

---

## get / setsockopt()

getsockopt()는 현재 소켓 옵션값을 가져오기 위해 사용한다.

setsockopt()는 소켓 옵션값을 변경하기 위해 사용한다.

```C
#include <sys/types.h>
#include <sys/socket.h>

int
getsockopt(int socket, int level, int optname, void *optval, socklen_t *optlen);

int
setsockopt(int socket, int level, int optname, const void *optval, socklen_t optlen);
```

### Parameter

socket : 옵션을 설정하고자 하는 소켓의 파일 디스크립터

level : 옵션의 프로토콜 레벨

|Protocol Level|MACRO|
|:--|:--|
|Socket|SOL_SOCKET|
|Internet Protocol|IPPROTO_IP|
|Transmission Control Protocol|IPPROTO_TCP|
|User Datagram Protocol|IPPROTO_UDP|

optname : 옵션의 이름

optval : 옵션의 값이 저장되어 있는 버퍼의 포인터

optlen : optval 버퍼의 크기

### Return Value

성공시 0 반환

실패시 -1 반환

### SOL_SOCKET 옵션
|Option|Set|Type|Description|
|:--|:--|:--|:--|
|SO_DEBUG|O|int|하위 프로토콜 모듈에서 디버깅 정보를 저장하게 한다.|
|SO_REUSEADDR|O|int|소켓의 로컬 주소를 재활용하는 것을 허용한다.|
|SO_KEEPALIVE|O|int|소켓의 연결상태 확인을 위해 하위 프로토콜이 주기적으로 메시지를 보내는 것을 허용한다.|
|SO_DONTROUTE|O|int|라우팅을 허용하지 않는다.|
|SO_LINGER|O|struct linger|안정적인 패킷 전송을 보장하는 하위 프로토콜의 연결이 끊어졌을 때 전송되지 못한 메시지들을 처리할 방법을 규정한다.|
|SO_BROADCAST|O|int|브로드캐스팅 허용 여부 결정|
|SO_OOBINLINE|O|int|OOB 트래픽을 normal 트래픽과 함께 처리한다.|
|SO_SNDBUF|O|size_t|소켓의 출력 버퍼의 크기를 정한다.|
|SO_RCVBUF|O|size_t|소켓의 입력 버퍼의 크기를 정한다.|
|SO_STYLE|X|int|communication 방법론을 확인한다.(STREAM or DATAGRAM)|
|SO_TYPE|X|int|SO_STYLE과 동일하다.|
|SO_ERROR|X|int|이전 에러 상태를 표시한다.|

### IPPROTO_TCP 옵션

|Option|Set|Type|Description|
|:--|:--|:--|:--|
|TCP_MAXSEG|O|int|TCP가 다루는 데이터 세그먼트의 최대 크기를 지정한다.|
|TCP_NODELAY|O|int|Nagle 알고리즘 사용 여부를 결정한다.|

### IPPROTO_UDP 옵션

|Option|Set|Type|Description|
|IP_MTU|X|int|MTU의 크기를 읽어온다.(연결된 상태만 확인 가능)|
|IP_MTU_DISCOVER|O|int|Path MTU Discovery 프로시저 관련 옵션|
|IP_TTL|O|int|IP 헤더의 TTL 필드에 관련된 옵션|
|IP_TOS|O|int|IP 헤더의 TOS 필드에 관련된 옵션|
