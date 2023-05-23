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

    // Winsock �ʱ�ȭ
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Winsock �ʱ�ȭ�� �����߽��ϴ�.\n");
        return 1;
    }

    // ���� ����
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("������ ������ �� �����ϴ�.\n");
        return 1;
    }

    // ���� �ּ� ����
    server.sin_addr.s_addr = INADDR_ANY;  // ������ IP �ּ� �Է�
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);  // ������ ��Ʈ ��ȣ �Է�

    // ������ ����
    if (connect(client_socket, (struct sockaddr*)&server, sizeof(server)) < 0) {
        printf("������ ������ �� �����ϴ�.\n");
        closesocket(client_socket);
        return 1;
    }

    printf("������ ����Ǿ����ϴ�. �޽����� �Է��ϼ���.\n");

    // �޽��� �Է� �� ����
    while (1) {
        memset(buffer, '\0', BUFFER_SIZE);
        fgets(buffer, BUFFER_SIZE, stdin);

        // ������ ������ ����
        if (send(client_socket, buffer, strlen(buffer), 0) < 0) {
            printf("������ ���ۿ� �����߽��ϴ�.\n");
            break;
        }

        // �����κ��� ������ ����
        memset(buffer, '\0', BUFFER_SIZE);
        if (recv(client_socket, buffer, BUFFER_SIZE, 0) < 0) {
            printf("������ ���ſ� �����߽��ϴ�.\n");
            break;
        }

        printf("����: %s\n", buffer);
    }

    // ���� ����
    closesocket(client_socket);
    WSACleanup();

    return 0;
}
