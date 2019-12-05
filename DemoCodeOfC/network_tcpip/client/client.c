/*******************************************************************************
*project: TCP/IP communication(server)
*author : zhouzhijun
*time   : 2019/05/29
*allright reserved
*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "common.h"

void get_server_host_info(uint8_t *server_ip, uint8_t *server_port)
{
    int local_test = 1;
    
    strcpy(server_port, "6666");
    if (local_test)
    {
        strcpy(server_ip, "127.0.0.1");
    }
    else
    {
        strcpy(server_ip, "192.168.1.207");
    }
}
 
int main(void)
{
    int client_socket;
    struct sockaddr_in server_addr;
    uint8_t server_ip[16] = {0};   //max len: 255.255.255.255
    uint8_t server_port[6] = {0};  //0 - 65535
    char send_buf[200];
    char recv_buf[200];
    int data_len;
    
    if((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket");
        return SERVER_FAIL;
    }
    
    get_server_host_info(server_ip, server_port);
    //printf("server_host: ip(%s) port(%s)\n", server_ip, server_port);
    
    bzero(&server_addr, sizeof(server_addr)); 
    server_addr.sin_family = AF_INET;
    server_addr.sin_port= htons(atoi(server_port));
    server_addr.sin_addr.s_addr= inet_addr(server_ip);
    
    if(connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("connect");
        return SERVER_FAIL;
    }
    
    while(TRUE)
    {
        printf("Please input send data:");
        memset(send_buf, 0, 200);
        if (fgets(send_buf, 200, stdin) == NULL)
        {
            printf("Get send data fail\n");
            continue;
        }
        if (send_buf[strlen(send_buf) - 1] == '\n')
        {
            send_buf[strlen(send_buf) - 1] = '\0';
        }
        send(client_socket, send_buf, strlen(send_buf), 0);
        
        if((strncmp(send_buf, "quit", 4) == 0) || (strncmp(send_buf, "exit", 4) == 0))
        {
            break;
        }    

        memset(recv_buf, 0, 200);
        data_len = recv(client_socket, recv_buf, 200, 0);
        recv_buf[data_len] = '\0';
        printf("recv: %s\n", recv_buf);
    }
    close(client_socket);
    
    return 0;
}
 
