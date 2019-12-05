//socket udp 客户端
//模拟手机APP端
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "mobile_app.h"

int main(void)
{
    //创建网络通信对象
    struct sockaddr_in addr;
    socklen_t len = 0;
    int sockfd = 0;
    unsigned char buf[256] = {0};
    unsigned char recv_buf[512] = {0};
    int ret = -1;
    
    /* CMD： 0x0020 frame data */
    unsigned char send_data[] = {
        0x5A, 0x5A, 0x03, 0x02, 0x00, 0x49, 0x00, 0x20,
        0x5C, 0xEF, 0x67, 0xD4, 0xA8, 0x0D, 0x0A
    };

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1324);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    while(1)
    {
        memset(buf, 0, 256);
        memset(recv_buf, 0, 512);
        
        printf("Please input send data：");
        if (fgets(buf, sizeof(buf), stdin) == NULL)
        {
            printf("client get string data fail\n");
            continue;
        }
        
        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = '\0';        

        if (!strncmp(buf, "exit", 4))
        {
            sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&addr, sizeof(addr));
            printf("client will stop!\n");
            break;            
        }
        //ret = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&addr, sizeof(addr));
        ret = sendto(sockfd, send_data, sizeof(send_data), 0, (struct sockaddr*)&addr, sizeof(addr));
        if (ret < 0)
        {
            printf("client send data error!\n");
            continue;            
        }
        
        len = sizeof(addr);
        
        while(1)
        {
            ret = recvfrom(sockfd, recv_buf, sizeof(recv_buf), 0, (struct sockaddr*)&addr, &len);
            if (ret < 0)
            {
                printf("client recv data fail\n");
                continue;            
            }
            #if 1
            int i = 0;
            printf("recv data(%d): ", ret);
            for (i = 0; i < ret; i++)
            {
                if ((i % 16) == 0)
                    printf("\n");
                
                printf("%02x ", recv_buf[i]);
            }
            printf("\n");
            #endif
        }
    }
    
    close(sockfd);
    
    return 0;
}