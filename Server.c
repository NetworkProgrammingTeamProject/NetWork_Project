#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define MAX_CLIENTS 5
#define BUFFER_SIZE 1024

void send_menu(SOCKET client_socket, char* buf) { // �޴� ��¹� ���� �Լ�
    strcpy(buf, "------���� ����------\n1.���ھ߱�\n2.���\n3.369\n�޴��� �����ϼ��� >> ");
    if (send(client_socket, buf, strlen(buf), 0) == SOCKET_ERROR)
        printf("������ ���ۿ� �����߽��ϴ�.\n");
}

void number_baseball() { // ���ھ߱� �Լ�

}

void hang_man(){ // ��� �Լ�

}

void three_six_nine() { // 369 �Լ�

}

void start_game(SOCKET client_socket, int select, char* buf) {
    switch (select) { // Ŭ���̾�Ʈ�κ��� �޴� �Է� �޾Ƽ� ���� �����ϴ� �Լ� 
    case 1:
        printf("���ھ߱��� ���õǾ����ϴ�.");
        number_baseball();
        break;
    case 2:
        printf("����� ���õǾ����ϴ�.");
        hang_man();
        break;
    case 3:
        printf("369�� ���õǾ����ϴ�.");
        three_six_nine();
        break;
    default:
        printf("start_game ERR: �߸��� �Է�");
        break;
    }
}

void init(SOCKET client_socket, char* buf) { // Ŭ���̾�Ʈ�� ����ǰ��� ���� �⺻ ����
    send_menu(client_socket, buf);
    memset(buf, '\0', BUFFER_SIZE);
    if (recv(client_socket, buf, BUFFER_SIZE, 0) == SOCKET_ERROR)
        printf("������ ���ſ� �����߽��ϴ�.\n");
    printf("������ �޴�: %s", buf);
    start_game(client_socket, buf[0] - '0', buf);
}

int main() {
    WSADATA wsa;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server, client;
    char buffer[BUFFER_SIZE];

    // Winsock �ʱ�ȭ
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Winsock �ʱ�ȭ�� �����߽��ϴ�.\n");
        return 1;
    }
   
    // ���� ����
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("������ ������ �� �����ϴ�.\n");
        return 1;
    }

    // ���� �ּ� ����
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(7777);  // ��Ʈ ��ȣ�� �ʿ信 ���� ���� ����

    // ���� ���ε�
    if (bind(server_socket, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("������ ���ε��� �� �����ϴ�.\n");
        closesocket(server_socket);
        return 1;
    }
    printf("������ ���۵Ǿ����ϴ�.\n");

    // Ŭ���̾�Ʈ ���� ���
    listen(server_socket, MAX_CLIENTS);

    // Ŭ���̾�Ʈ ���� ����
    int addr_len = sizeof(struct sockaddr_in);
    if ((client_socket = accept(server_socket, (struct sockaddr*)&client, &addr_len)) == INVALID_SOCKET) {
        printf("Ŭ���̾�Ʈ ������ ������ �� �����ϴ�.\n");
        closesocket(server_socket);
        return 1;
    }
    printf("Ŭ���̾�Ʈ�� ����Ǿ����ϴ�.\n");
    
    init(client_socket, buffer);

    // Ŭ���̾�Ʈ���� ���
    while (1) {
        //Ŭ���̾�Ʈ�κ��� ������ ����
        /*memset(buffer, '0', BUFFER_SIZE);
        if (recv(client_socket, buffer, BUFFER_SIZE, 0) == SOCKET_ERROR) {
            printf("������ ���ſ� �����߽��ϴ�.\n");
            break;
        }*/

        // Ŭ���̾�Ʈ�� ������ ����
        /*memset(buffer, '\0', BUFFER_SIZE);
        fgets(buffer, BUFFER_SIZE, stdin);
        if (send(client_socket, buffer, strlen(buffer), 0) == SOCKET_ERROR) {
            printf("������ ���ۿ� �����߽��ϴ�.\n");
            break;
        }
        printf("Ŭ���̾�Ʈ: %s", buffer);*/
    }

    // ���� ����
    closesocket(server_socket);
    closesocket(client_socket);
    WSACleanup();

    return 0;
}
