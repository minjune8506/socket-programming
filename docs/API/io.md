# 입출력 함수

``` Plain text
size_t : unsigned int
ssize_t : signed int

운영체제에 따라서 크기가 달라진다.
32bit OS : 32bit
64bit OS : 64bit
```

---

## open()
```C
#include <fcntl.h>

int
open(const char *path, int oflag, [mode_t mode]);
```

### Parameter

**path** : 읽거나 쓸 파일의 경로

**oflag**
- O_RDONLY : 읽기 전용
- O_WRONLY : 쓰기 전용
- O_RDWR : 읽기 쓰기 전용
- O_CREAT : 해당 파일이 없으면 생성한다. (접근 권한 추가 필요)
- O_EXCL : O_CREAT를 사용할 때 함께 사용하면, 파일이 이미 존재할 때 open()이 실패한다.
- O_TRUNC : 기존 파일 내용을 모두 삭제한다.
- O_APPEND : open 후에 쓰기 포인터가 파일의 끝에 위치하게 된다.
- O_NONBLOCK : 읽을 내용이 없을 때 기다리지 않고 바로 복귀한다.
- O_SYNC : 실제 쓰기가 완료될 때까지 기다린다.

**mode_t mode** : oflag에 O_CREAT가 포함되어 있는 경우 파일의 권한을 설정한다.

### Return Value

파일 열기에 성공하면 파일 디스크립터 값 반환

실패시 -1 반환

---

## read()
```C
#include <unistd.h>

ssize_t
read(int fildes, void *buf, size_t nbyte);
```

### Parameter

**int fildes** : 파일 디스크립터

**void *buf** : 파일을 읽어 들일 버퍼

**size_t nbyte** : 버퍼의 크기

### Return Value

읽어들인 데이터의 크기를 반환한다.

실패시 -1 반환

성공시 nbyte가 무조건 반환되는것은 아니다. 중간에 파일의 끝을 만난다면 nbyte보다 작은 값이 반환될 수 있다.

---

## write()

```C
#include <unistd.h>

ssize_t
write(int fildes, const void *buf, size_t nbyte);
```

### Parameter

**int fildes** : 파일 디스크립터

**void *buf** : 파일에 쓰기를 할 내용을 담은 버퍼

**size_t nbyte** : 쓰기를 할 바이트 개수

### Return Value

쓰기에 성공했다면 쓰기한 바이트 개수를 반환한다.

실패시 -1을 반환한다.

---

## close()

```C
#include <unistd.h>

int
clost(int fildes);
```

### Parameter

**int fildes** : 파일 디스크립터

### Return Value

정상적으로 close() 된 경우 0을 반환한다.

실패시 -1을 반환한다.
