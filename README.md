# TCP Socket API 프로젝트

이 프로젝트는 **TCP 소켓 서버 및 클라이언트**를 관리하는 API를 구현한 것입니다. 서버와 클라이언트 간의 연결을 생성하고 관리하며, TCP Keep-Alive 옵션을 설정하여 연결 상태를 지속적으로 모니터링합니다. 이 API는 주로 **소켓 생성, 연결 관리, 데이터 송수신**에 사용됩니다.



## 주요 기능

- **서버 소켓 생성 및 설정 (TCP Keep-Alive 포함)**
- **클라이언트 소켓 생성 및 서버 연결**
- **클라이언트 연결 해제 및 연결 상태 모니터링**
- **소켓의 RX 및 TX 버퍼 크기 설정**



## 디렉터리 구조

<pre>
├── Makefile 				# 빌드 파일
├── README.md
├── gtest
│   └── gtest-tcp-sock.cc 		# GoogleTest를 이용한 테스트 코드
├── include
│   └── tcp-sock.h			# TCP 소켓 관련 함수 선언
└── src
    └── tcp-sock.c 			# TCP 소켓 관련 함수 구현 
</pre>


## 빌드 방법

1. **GoogleTest 설치**:
   이 프로젝트는 GoogleTest를 사용하여 유닛 테스트를 실행합니다. GoogleTest는 별도로 설치해야 합니다. 설치 방법은 아래와 같습니다.(googletest-1.10.x)
   
    ```bash
   git clone https://github.com/google/googletest.git
   cd googletest
   mkdir build
   cd build
   cmake ..
   make
   sudo make install
   
1. **Makefile을 사용하여 빌드**: 이 프로젝트는 `Makefile`을 사용하여 빌드합니다. 터미널에서 아래 명령어를 실행하여 빌드를 시작할 수 있습니다.
   
   ```bash
   make gtest
   
   ```
   

`Makefile`은 TCP 소켓 라이브러리 및 테스트를 빌드하며, GoogleTest 라이브러리가 설치되어 있어야 합니다.



## 사용 방법

### 1. **소켓 서버 생성**:

`createServerSocket()` 함수는 서버 소켓을 생성하고 TCP 소켓 옵션을 설정합니다. 이 함수는 서버가 사용할 포트를 바인딩하고, 클라이언트의 연결을 수락할 준비를 합니다.

```c
int createServerSocket(int port, int maxClients);
```



### 2. **소켓 클라이언트 생성**:

`createClientSocket()` 함수는 클라이언트 소켓을 생성하고, 서버에 연결을 시도합니다.

```c
int createClientSocket(const char* ip, int port);
```



### 3. **소켓 포트 사용 여부 확인**:

`isPortAvailable()` 함수는 서버 소켓이 바인딩하려는 포트가 이미 사용 중인지 확인합니다.

```c
bool isPortAvailable(int port);
```



### 4. **데이터 송수신**:

`recvMsgBlocking()`, `recvMsgTimeout()` 함수는 데이터를 수신하며, `sendMessage()` 함수는 데이터를 전송합니다.

```c
int recvMsgBlocking(int sock, char* buffer, size_t length);
int sendMessage(int sock, const char* message, size_t length);
int recvMsgTimeout(int iSock, void *pvBuffer, size_t iLength, int iTimeoutMsec);
```





## 테스트 방법

이 프로젝트는 **GoogleTest**를 사용하여 유닛 테스트를 작성하고 실행합니다. 아래 명령어로 테스트를 실행할 수 있습니다.

1. **테스트 빌드**:

   ```bash
   make gtest
   ```

2. **테스트 실행**:

   ```bash
   ./gtest-tcp-sock
   ```

   
