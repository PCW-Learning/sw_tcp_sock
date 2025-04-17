#ifndef TCP_SOCK_H
#define TCP_SOCK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h> // TCP_KEEPIDLE 등 TCP 옵션 정의


/**
 * @brief   버퍼 크기를 정의합니다.
 * @details 데이터 송수신에 사용되는 버퍼의 크기를 바이트 단위로 나타냅니다.
 */
#define BUFFER_SIZE 1024

/**
 * @brief 포트가 사용 중인지 확인하는 함수
 *
 * @details 서버 소켓이 바인딩하려는 포트가 이미 사용 중인지 확인합니다.
 *
 * @param port 확인할 포트 번호
 * @return true 사용 중인 경우
 * @return false 사용 중이 아닌 경우
 */
int isPortAvailable(int iPort);

/**
 * @brief 서버 소켓을 생성하고 필요한 옵션을 설정합니다. TCP Keep-Alive 옵션 포함.
 * 
 * @param iPort 서버가 연결을 수신할 포트 번호
 * @param iMaxClients 허용할 최대 클라이언트 수
 * 
 * @return 서버 소켓에 대한 파일 디스크립터를 반환.
 */
int createServerSocket(int, int);

/**
 * @brief 클라이언트 소켓을 생성하여 서버에 연결합니다.
 * 
 * @param kpchIp 서버의 IP 주소
 * @param iPort 서버의 포트 번호
 * 
 * @return 생성된 클라이언트 소켓 파일 디스크립터를 반환. 실패 시 -1을 반환합니다.
 */
int createClientSocket(const char*, int);

/**
 * @brief 클라이언트 연결 해제 처리
 * 
 * @details 클라이언트가 연결을 종료할 때 해당 소켓을 닫고 관련된 리소스를 정리합니다.
 * 
 * @param iClientSockfd 연결이 해제된 클라이언트 소켓 파일 디스크립터
 */
void handleClientDisconnection(int);

/**
 * @brief 클라이언트 연결 상태 확인
 * 
 * @details 클라이언트 소켓들이 여전히 유효한 연결 상태인지 확인하고, 연결이 끊어진 경우 해당 소켓을 닫습니다.
 * 
 * @param piClientSockets 클라이언트 소켓 파일 디스크립터 배열
 * @param iMaxClients 최대 클라이언트 수
 */
void checkClientConnections(int*, int);

/**
 * @brief 소켓의 RX 및 TX 버퍼 크기 설정
 * 
 * @param iSock 소켓 파일 디스크립터
 * @param iRxSize 수신 버퍼 크기 (바이트 단위)
 * @param iTxSize 송신 버퍼 크기 (바이트 단위)
 */
void setSocketBufferSize(int, int, int);

/**
 * @brief TCP 소켓을 통해 메시지 전송
 *
 * @param iSock 데이터를 전송할 소켓 디스크립터
 * @param cpvBuffer 전송할 데이터의 포인터
 * @param iLength 전송할 바이트 수
 * @return 성공 시 전송한 바이트 수, 실패 시 -1 반환
 */
int sendMessage(int, const void *, size_t);

/**
 * @brief TCP 소켓에서 메시지 수신(전체 수신 완료까지 블로킹).
 *
 * @param iSock 데이터를 수신할 소켓 디스크립터
 * @param pvBuffer 수신 데이터를 저장할 버퍼 포인터
 * @param iLength 수신할 바이트 수
 * @return 성공 시 수신한 바이트 수, 실패 시 -1 반환
 */
int recvMsgBlocking(int, void *, size_t);

/**
 * @brief TCP 소켓에서 메시지 수신(지정한 시간만큼 대기 후 타임아웃 처리).
 *
 * @param iSock 데이터를 수신할 소켓 디스크립터
 * @param pvBuffer 수신 데이터를 저장할 버퍼 포인터
 * @param iLength 수신할 바이트 수
 * @param iTimeoutMsec 타임아웃 시간(밀리초)
 * @return 성공 시 수신한 바이트 수, 타임아웃 시 0, 실패 시 -1 반환
 */
int recvMsgTimeout(int, void *, size_t, int);

#ifdef __cplusplus
}
#endif

#endif
