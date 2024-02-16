#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define SERVER_PORT 8081
int main() {
    int sockfd, client_len;
    struct sockaddr_in server_addr;
    int nodes[10][10];
    int n,i,j,k,count;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        exit(1);
    }


    listen(sockfd, 1);


    client_len = sizeof(server_addr);
    sockfd = accept(sockfd, (struct sockaddr *) &server_addr, &client_len);
    if (sockfd < 0) {
        perror("accept");
        exit(1);
    }


    recv(sockfd, nodes, sizeof(nodes), 0);
    n=3;

   for(i=0;i<n;i++)
   do
   {
        count=0;
        for(i=0;i<n;i++)    {
              for(j=0;j<n;j++)
                      {
                         for(k=0;k<n;k++)
                         {
                            if(nodes[i][j]>nodes[i][k]+nodes[k][j])
                            {
                               nodes[i][j]=nodes[i][k]+nodes[k][j];
                               count++;
                            }
                         }
                      }
        }
   }while(count!=0);
 for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("optimal distance between node %d and node %d is %d\n",i+1,j+1,nodes[i][j]);
                        }
    }

    send(sockfd, nodes, sizeof(nodes), 0);


    close(sockfd);

    return 0;
}

