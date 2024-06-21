#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#define PORT 8080
#define MAX_CLIENTS 100

int clients[MAX_CLIENTS];
int client_count = 0;
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

void broadcast_message(char *message) {
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < client_count; i++) {
        if (send(clients[i], message, strlen(message), 0) < 0) {
            perror("send");
            continue;
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

void *handle_client(void *arg) {
    int client_sock = *(int *)arg;
    char buffer[1024];

    while (1) {
        int bytes_received = recv(client_sock, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) {
            perror("recv");
            close(client_sock);
            pthread_exit(NULL);
        }

        buffer[bytes_received] = '\0';
        broadcast_message(buffer);
    }

    close(client_sock);
    pthread_exit(NULL);
}

void *server_shell(void *arg) {
    char command[256];
    char result[1024];
    FILE *fp;

    while (1) {
        printf("server> ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0; // Remove newline character

        if (strlen(command) == 0) continue;

        fp = popen(command, "r");
        if (fp == NULL) {
            perror("popen");
            continue;
        }

        while (fgets(result, sizeof(result), fp) != NULL) {
            printf("%s", result);
            broadcast_message(result);
        }

        pclose(fp);
    }
}

int main() {
    int server_sock, new_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    pthread_t tid;

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == -1) {
        perror("socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(server_sock);
        exit(1);
    }

    if (listen(server_sock, 10) < 0) {
        perror("listen");
        close(server_sock);
        exit(1);
    }

    printf("Server started on port %d\n", PORT);

    pthread_create(&tid, NULL, server_shell, NULL);

    while (1) {
        new_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_len);
        if (new_sock < 0) {
            perror("accept");
            continue;
        }

        pthread_mutex_lock(&clients_mutex);
        clients[client_count++] = new_sock;
        pthread_mutex_unlock(&clients_mutex);

        pthread_create(&tid, NULL, handle_client, (void *)&new_sock);
    }

    close(server_sock);
    return 0;
}
