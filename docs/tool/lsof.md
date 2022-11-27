# lsof (list open files)

시스템에서 열려있는 파일에 대한 정보를 출력해주는 명령어

특정 프로세스가 열고 있는 파일 디스크립터를 조회하고 시스템을 모니터링하는데 도움이 된다.

## Column

COMMAND : 실행한 명령어

PID : 프로세스 ID

USER : 명령어를 실행한 사용자

FD : File Descriptor의 종류

TYPE : 파일의 종류

DEVICE : 디바이스 번호

SIZE/OFF : 파일의 크기나 현재 offset

## 사용 예시

lsof -i TCP : 열려있는 모든 TCP 포트를 확인한다.

lsof -i TCP:22 : 22번 포트로 TCP 연결한 프로세스들을 확인한다.

lsof -i TCP:1024-2048 : 1024 ~ 2048 포트를 TCP로 열고 있는 프로세스 확인

lsof -d number : 현재 사용중인 File Descriptor 기준으로 정보 출력

lsof -i TCP:3350 -n : 호스트 이름대신 IP로 정보를 출력한다.
