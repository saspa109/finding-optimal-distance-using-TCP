#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define SERVER_PORT 8081

int main(int argc, char *argv[]) {
    int sockfd, client_len;
    struct sockaddr_in server_addr;
    int nodes[10][10];
    int n;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    client_len = sizeof(server_addr);
    if (connect(sockfd, (struct sockaddr *) &server_addr, client_len) < 0) {
        perror("connect");
        exit(1);
    }


    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("Enter the distance between node %d and node %d: ", i + 1, j + 1);
            scanf("%d", &nodes[i][j]);
        }
    }


    send(sockfd, nodes, sizeof(nodes), 0);
        int res[10][10];
    recv(sockfd, res, sizeof(res), 0);
    printf("The optimal distance is:\n");
        for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("optimal distance between node %d and node %d is %d\n",i+1,j+1,res[i][j]);
        }
    }
    close(sockfd);
    return 0;
}
