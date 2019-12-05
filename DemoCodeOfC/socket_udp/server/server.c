//socket udp 服务端
//模拟手表端
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "watch_app.h"

int sockfd = 0;
struct sockaddr_in cli;

void send_data_func(int send_len, unsigned char *send_buf)
{
    if (sendto(sockfd, send_buf, send_len, 0, (struct sockaddr*)&cli, sizeof(cli)) < 0)
    {
        printf("server send data fail\n");
    }
}

int process_recv_data(char *data_buf, int data_len)
{
    int frame_check = -1;
    int res_data_len = 0;
    
    frame_check = one_complete_frame_check(data_buf, data_len);
    if (frame_check == 0)
    {
        printf("Data frame lose something!\n");
        return 0;
    }
    
    res_data_len = process_recv_cmd_info(data_buf, data_len);
    
    return res_data_len;
}

int main(void)
{
    //创建网络通信对象
    struct sockaddr_in addr;
    socklen_t len = 0;
    unsigned char recv_buf[256] = {0};
    int recv_len = 0;
    int ret = -1;
    
    //创建socket对象
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1324);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    //绑定socket对象与通信链接
    ret = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    if(ret < 0)
    {
        printf("bind server fail\n");
        return -1;
    }   
    len = sizeof(cli);

    printf("server is runing......\n");
    while(1)
    {
        memset(recv_buf, 0, 256);
        recv_len = 0;
        
        recv_len = recvfrom(sockfd, recv_buf, sizeof(recv_buf), 0, (struct sockaddr*)&cli, &len);
        if (recv_len <= 0)
        {
            printf("server recv data fail\n");
            continue;            
        }
        
        if (!strncmp(recv_buf, "exit", 4))
        {
            break;
        }
        
        #if 1
        int i = 0;
        printf("recv data(%d): ", recv_len);
        for (i = 0; i < recv_len; i++)
        {
            if ((i % 16) == 0)
                printf("\n");
            
            printf("%02x ", recv_buf[i]);
        }
        printf("\n");
        #endif
        
        process_recv_data(recv_buf, recv_len);
    }
    
    close(sockfd);
    printf("server will stop!\n");

    return 0;
}