#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#define PORT 8080

void *receive_messages(void *arg) {
    int sock = *(int *)arg;
    char buffer[1024];
    int bytes_received;

    while ((bytes_received = recv(sock, buffer, sizeof(buffer), 0)) > 0) {
        buffer[bytes_received] = '\0';
        printf("%s", buffer);
    }

    if (bytes_received == 0) {
        printf("Server disconnected\n");
    } else {
        perror("recv");
    }

    close(sock);
    pthread_exit(NULL);
}

int main() {
    int sock;
    struct sockaddr_in server_addr;
    pthread_t tid;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        close(sock);
        exit(1);
    }

    printf("Connected to server\n");

    pthread_create(&tid, NULL, receive_messages, (void *)&sock);

    pthread_join(tid, NULL);

    return 0;
}
