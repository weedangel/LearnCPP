#include <stdio.h>
#include <string.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> 
#include <pthread.h>
#include <sys/wait.h>

#include "ring_buf.h"

void *read_thread(void *arg)
{
    int ret = 0;
    char data_buf[512];
    ring_buffer_t *p_ring_buf = (ring_buffer_t *)arg;
    int temp_opt = 0, temp_offset = 0;
    char to_sleep = 0;
    
    sleep(3);
    while(1)
    {
        while (!ring_buffer_is_empty(p_ring_buf))
        {
            memset(data_buf, 0, sizeof(data_buf));
            //temp_opt = rand() % 4;
            temp_opt = 3;
            
            if (temp_opt == 0)
            {
                //printf("read opt: read char\n");
                ret = ring_buffer_read_char(p_ring_buf, &data_buf[0]);
                printf("read char return: %d\n", ret);
            }
            else if (temp_opt == 1)
            {
                //printf("read opt: read block\n");
                ret = ring_buffer_read_block(p_ring_buf, data_buf, sizeof(data_buf));
                printf("read block return: %d\n", ret);
            }
            else if (temp_opt == 2)
            {
                //printf("read opt: read peek\n");
                ret = ring_buffer_peek(p_ring_buf, data_buf, sizeof(data_buf));
                printf("buffer peek return: %d\n", ret);
            }
            else if (temp_opt == 3)
            {
                //printf("read opt: offset\n");
                temp_offset = rand() % 512;
                ret = ring_buffer_read_offset(p_ring_buf, temp_offset);
                printf("read offset return: %d\n", ret);
            }
            else if (temp_opt == 4)
            {
                printf("read opt: print\n");
                ring_buffer_print(p_ring_buf);
            }
            to_sleep = 0;
        }
        
        if (to_sleep == 0)
        {
            printf("read thread to sleep\n");
            to_sleep = 1;
        }

        usleep(1000 * 100);
    }
    
    
    pthread_exit(NULL);
}

int main(void)
{
    pthread_t read_tid;
    int ret = -1, i = 0;
    char temp_data[512];
    int temp_len = 0;
    int sleep_ms = 0;
    
    char data_buf[1024];
    ring_buffer_t ring_buf;
    ring_buffer_t *p_ring_buf = &ring_buf;
    
    //ring_buffer_init(p_ring_buf, data_buf, sizeof(data_buf), RING_BUF_OVERFLOW_DISABLE);
    ring_buffer_init(p_ring_buf, data_buf, sizeof(data_buf), RING_BUF_OVERFLOW_ENABLE);
    srand((int)time(0));
    
    ret = pthread_create(&read_tid, NULL, (void *)read_thread, p_ring_buf);
    if (ret != 0)
    {
        printf ("Create read thread error!/n");
        return -1;
    }
    
    while(1)
    {
        memset(temp_data, 0, sizeof(temp_data));
        temp_len = rand() % 512;
        for(i = 0; i < temp_len; i++)
        {
            temp_data[i] = rand() % 255;
        }
        ret = ring_buffer_write_block(p_ring_buf, temp_data, temp_len);
        //ret = ring_buffer_write_block_ensure(p_ring_buf, temp_data, temp_len);
        printf("write return: %d\n", ret);

        sleep_ms = rand() % 500;
        sleep_ms = sleep_ms < 2 ? 2 : sleep_ms;
        usleep(1000 * sleep_ms);
    }
    
    pthread_join(read_tid, NULL);

    return 0;
}