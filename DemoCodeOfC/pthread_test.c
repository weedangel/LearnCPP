#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <unistd.h>
#include <pthread.h>

unsigned char str_data[256];

#if 0
void* write_func(void* argc)
{
    pthread_mutex_t *mutex_p = (pthread_mutex_t *)argc;
    unsigned char temp_data[256];
    
    printf("write thread runing......\n");
    while(1)
    {
        memset(temp_data, 0, 256);
        printf("Please input data: ");
        if (fgets(temp_data, 256, stdin) == NULL)
        {
            printf("fgets data fail\n");
            continue;
        }
        temp_data[strlen(temp_data) - 1] = '\0';
        
        pthread_mutex_lock(mutex_p);
        memset(str_data, 0, 256);
        memcpy(str_data, temp_data, strlen(temp_data));
        pthread_mutex_unlock(mutex_p);
    }

    pthread_exit(NULL);
}

void* read_func(void* argc)
{
    pthread_mutex_t *mutex_p = (pthread_mutex_t *)argc;
    
    printf("read thread runing......\n");
    
    while(1)
    {
        pthread_mutex_lock(mutex_p);
        printf("str_data: %s\n", str_data);
        pthread_mutex_unlock(mutex_p);
        sleep(1);
    }

    pthread_exit(NULL);
}
#else  
#include <semaphore.h>

sem_t write_sem, read_sem;

void* write_func(void* argc)
{
    printf("write thread runing......\n");
    while(1)
    {
        sem_wait(&write_sem);
        memset(str_data, 0, 256);
        printf("Please input data: ");
        if (fgets(str_data, 256, stdin) == NULL)
        {
            printf("fgets data fail\n");
            continue;
        }
        str_data[strlen(str_data) - 1] = '\0';
        sem_post(&read_sem);
        if (!strncmp(str_data, "exit", 4))
            break;
    }

    pthread_exit(NULL);
}

void* read_func(void* argc)
{
    printf("read thread runing......\n");
    
    while(1)
    {
        sem_wait(&read_sem);
        if (!strncmp(str_data, "exit", 4))
            break;
        printf("str_data: %s\n", str_data);
        sem_post(&write_sem);
    }

    pthread_exit(NULL);
}
#endif

int main(void)
{
    pthread_t read_tid, write_tid;
    void *ret = NULL;
    void *argc = NULL;

#if 0    
    pthread_mutex_t mutex;
    if (pthread_mutex_init (&mutex, NULL) != 0)
    {
        perror("Create mutex fail");
        return -1;
    }
    argc = (void *)&mutex;
#else
    if (sem_init(&write_sem,0,1) != 0)
    {
        perror("create write sem fail");
        return -1;
    }
    
    if (sem_init(&read_sem,0,0) != 0)
    {
        perror("create write sem fail");
        return -1;
    }
    argc = NULL;
#endif

    if (pthread_create(&write_tid, NULL, write_func, argc) < 0)
    {
        perror("Create write thread fail");
        return -1;
    }
    
    if (pthread_create(&read_tid, NULL, read_func, argc) < 0)
    {
        perror("Create read thread fail");
        return -1;
    }
    
    //pthread_cancel(tid); 
    
    pthread_join(write_tid, &ret);
    pthread_join(read_tid, &ret);
    
    sem_destroy(&write_sem);
    sem_destroy(&read_sem);
    
    printf("main func stop!!!\n");

    return 0;
}
 
