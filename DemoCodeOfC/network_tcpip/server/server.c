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

void get_server_config_info(uint8_t *server_ip, uint8_t *server_port)
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

void server_listen_thread(void *agrs)
{
    int32_t server_socket;
    int32_t client_socket;
    uint8_t server_ip[16] = {0};   //max len: 255.255.255.255
    uint8_t server_port[6] = {0};  //0 - 65535
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int32_t addr_len = sizeof(client_addr);
    
    int32_t data_len;
    uint8_t data_buf[512];

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket");
        return SERVER_FAIL;
    }
 
    get_server_config_info(server_ip, server_port);
    //printf("server_info: ip(%s) port(%s)\n", server_ip, server_port);
    
    bzero(&server_addr, sizeof(server_addr)); 
    server_addr.sin_family = AF_INET;
    server_addr.sin_port= htons(atoi(server_port));
    server_addr.sin_addr.s_addr= inet_addr(server_ip);
    
    if(bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("connect");
        return SERVER_FAIL;
    }
    
    if(listen(server_socket, 5) < 0)
    {
        perror("listen");
        return SERVER_FAIL;
    }
    
    printf("wait client connect\n");
    while (TRUE)
    {
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, (socklen_t*)&addr_len);
        if(client_socket < 0)
        {
            perror("accept");
            continue;
        }
            
        printf("client IP is %s\n", inet_ntoa(client_addr.sin_addr));
        printf("client port is %d\n", htons(client_addr.sin_port));
    }
    
    close(server_socket);
    
    return 0;
}

void client_data_transfer_thread(void *args)
{
    while(TRUE)
    { 
        printf("wait receive mesage...\n");
        data_len = recv(client_socket, data_buf, 512, 0);
        if(data_len < 0)
        {
            perror("recv null");
            continue;
        }
        data_buf[data_len] = '\0';
        printf("recv: %s\n", data_buf);
        
        send(client_socket, data_buf, data_len, 0);
        
        
    }
    close(client_socket);
    
    return ;    
}

int main(void)
{
    
    return 0;
}
