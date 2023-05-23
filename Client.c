#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define BUFFER_SIZE 1024

int main() {
    WSADATA wsa;
    SOCKET client_socket;
    struct sockaddr_in server;
    char buffer[BUFFER_SIZE];

    // Winsock 초기화
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Winsock 초기화에 실패했습니다.\n");
        return 1;
    }

    // 소켓 생성
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("소켓을 생성할 수 없습니다.\n");
        return 1;
    }

    // 서버 주소 설정
    server.sin_addr.s_addr = INADDR_ANY;  // 서버의 IP 주소 입력
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);  // 서버의 포트 번호 입력

    // 서버에 연결
    if (connect(client_socket, (struct sockaddr*)&server, sizeof(server)) < 0) {
        printf("서버에 연결할 수 없습니다.\n");
        closesocket(client_socket);
        return 1;
    }

    printf("서버에 연결되었습니다. 메시지를 입력하세요.\n");

    // 메시지 입력 및 전송
    while (1) {
        memset(buffer, '\0', BUFFER_SIZE);
        fgets(buffer, BUFFER_SIZE, stdin);

        // 서버로 데이터 전송
        if (send(client_socket, buffer, strlen(buffer), 0) < 0) {
            printf("데이터 전송에 실패했습니다.\n");
            break;
        }

        // 서버로부터 데이터 수신
        memset(buffer, '\0', BUFFER_SIZE);
        if (recv(client_socket, buffer, BUFFER_SIZE, 0) < 0) {
            printf("데이터 수신에 실패했습니다.\n");
            break;
        }

        printf("서버: %s\n", buffer);
    }

    // 소켓 종료
    closesocket(client_socket);
    WSACleanup();

    return 0;
}
