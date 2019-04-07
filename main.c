#include "semaphore.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/sem.h>

int main()
{
    int sem_id; //信号量集ID
    key_t key;
    pid_t pid;

    //获取key值
    if((key = ftok(".",'z')) < 0)
    {
        perror("ftok error");
        exit(1);
    }

    //创建信号量集，其中只有一个信号量
    if((sem_id = semget(key,1,IPC_CREAT|0666)) == -1)
    {
        perror("semget error");
        exit(1);
    }

    //初始化：初值设为0资源被占用
    init_sem(sem_id,0);

    if((pid = fork()) == -1)
    {
        perror("Fork Error");
    }
    else if(pid == 0) //子进程
    {
        sleep(2);
        printf("Process child: pid=%d\n",getpid());
        printf("children give sem:\n");
        sem_v(sem_id);//释放资源
    }
    else //父进程
    {
        printf("father wait sem:\n");
        sem_p(sem_id); //等待资源
        printf("Process father: pid=%d\n",getpid());
        printf("father lend sem:\n");
        sem_v(sem_id);//释放资源
        del_sem(sem_id); //删除信号量集
    }

    return 0;
}
