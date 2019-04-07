#ifndef SEMAPHORE_H
#define SEMAPHOER_H

//初始化信号量
int init_sem(int sem_id,int value);

//P(sv)操作,如果sv的值大于0，就给它减1；如果它的值为零，就挂起该进程的执行
int sem_p(int sem_id);

//V(sv)操作：如果有其他进程等待sv而被挂起，就让它恢复运行，唤醒它们；如果没有进程因等待sv而挂起，就给它加1
int sem_v(int sem_id);

//删除信号量集
int del_sem(int sem_id);

#endif
