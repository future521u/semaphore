#include <sys/sem.h>
#include <sys/types.h>
#include <semaphore.h>
#include <stdio.h>

union semun
{
    int val; //set SETVAL
    struct semid_ds *buf;
    unsigned short *array;
};

int init_sem(int sem_id,int value)
{
    union semun tmp;
    tmp.val = value;
    
    if(semctl(sem_id,0,SETVAL,tmp) == -1) //0:信号量集数值上的下标，表示一个信号量
    {
        perror("Init Semaphore Error");
        return -1;
    }
    return 0;
}

int sem_p(int sem_id)
{
    struct sembuf sbuf;
    sbuf.sem_num = 0; //序号
    sbuf.sem_op = -1; //P操作
    sbuf.sem_flg = SEM_UNDO;//通常为SEM_UNDO，是操作系统跟踪信号，并再进程没有释放该信号量而终止时，操作系统释放信号量
    if(semop(sem_id,&sbuf,1) == -1)
    {
        perror("P operator Error");
        return -1;
    }

    return 0;
}

int sem_v(int sem_id)
{
    struct sembuf sbuf;
    sbuf.sem_num = 0;
    sbuf.sem_op = 1;
    sbuf.sem_flg = SEM_UNDO;

    if(semop(sem_id,&sbuf,1) == -1)
    {
        perror("V operator Error");
        return -1;
    }

    return 0;
}

int del_sem(int sem_id)
{
    union semun tmp;
    if(semctl(sem_id,0,IPC_RMID,tmp) == -1) //IPC_RMID删除信号量
    {
        perror("Delete Semaphore Error");
        return -1;
    }

    return 0;
}
