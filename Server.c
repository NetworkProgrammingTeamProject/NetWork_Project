#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define MAX_CLIENTS 5
#define BUFFER_SIZE 1024

void send_menu(SOCKET client_socket, char* buf) { // 메뉴 출력문 전송 함수
    strcpy(buf, "------게임 선택------\n1.숫자야구\n2.행맨\n3.369\n메뉴를 선택하세요 >> ");
    if (send(client_socket, buf, strlen(buf), 0) == SOCKET_ERROR)
        printf("데이터 전송에 실패했습니다.\n");
}

void number_baseball() { // 숫자야구 함수

}

void hang_man(){ // 행맨 함수

}

void three_six_nine() { // 369 함수

}

void start_game(SOCKET client_socket, int select, char* buf) {
    switch (select) { // 클라이언트로부터 메뉴 입력 받아서 게임 실행하는 함수 
    case 1:
        printf("숫자야구가 선택되었습니다.");
        number_baseball();
        break;
    case 2:
        printf("행맨이 선택되었습니다.");
        hang_man();
        break;
    case 3:
        printf("369가 선택되었습니다.");
        three_six_nine();
        break;
    default:
        printf("start_game ERR: 잘못된 입력");
        break;
    }
}

void init(SOCKET client_socket, char* buf) { // 클라이언트와 연결되고나서 서버 기본 세팅
    send_menu(client_socket, buf);
    memset(buf, '\0', BUFFER_SIZE);
    if (recv(client_socket, buf, BUFFER_SIZE, 0) == SOCKET_ERROR)
        printf("데이터 수신에 실패했습니다.\n");
    printf("선택한 메뉴: %s", buf);
    start_game(client_socket, buf[0] - '0', buf);
}

int main() {
    WSADATA wsa;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server, client;
    char buffer[BUFFER_SIZE];

    // Winsock 초기화
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Winsock 초기화에 실패했습니다.\n");
        return 1;
    }
   
    // 소켓 생성
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("소켓을 생성할 수 없습니다.\n");
        return 1;
    }

    // 서버 주소 설정
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(7777);  // 포트 번호는 필요에 따라 수정 가능

    // 소켓 바인딩
    if (bind(server_socket, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("소켓을 바인딩할 수 없습니다.\n");
        closesocket(server_socket);
        return 1;
    }
    printf("서버가 시작되었습니다.\n");

    // 클라이언트 접속 대기
    listen(server_socket, MAX_CLIENTS);

    // 클라이언트 연결 수락
    int addr_len = sizeof(struct sockaddr_in);
    if ((client_socket = accept(server_socket, (struct sockaddr*)&client, &addr_len)) == INVALID_SOCKET) {
        printf("클라이언트 연결을 수락할 수 없습니다.\n");
        closesocket(server_socket);
        return 1;
    }
    printf("클라이언트가 연결되었습니다.\n");
    
    init(client_socket, buffer);

    // 클라이언트와의 통신
    while (1) {
        //클라이언트로부터 데이터 수신
        /*memset(buffer, '0', BUFFER_SIZE);
        if (recv(client_socket, buffer, BUFFER_SIZE, 0) == SOCKET_ERROR) {
            printf("데이터 수신에 실패했습니다.\n");
            break;
        }*/

        // 클라이언트로 데이터 전송
        /*memset(buffer, '\0', BUFFER_SIZE);
        fgets(buffer, BUFFER_SIZE, stdin);
        if (send(client_socket, buffer, strlen(buffer), 0) == SOCKET_ERROR) {
            printf("데이터 전송에 실패했습니다.\n");
            break;
        }
        printf("클라이언트: %s", buffer);*/
    }

    // 소켓 종료
    closesocket(server_socket);
    closesocket(client_socket);
    WSACleanup();

    return 0;
}
