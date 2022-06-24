//
// Created by wang HaoLin on 2022/5/6.
//
#ifndef MUTEX_COMMON_H
#define MUTEX_COMMON_H

#define N 5
#define sleep(n) Sleep(n*1000)
#define MAX_SEM_COUNT 1
#define QUEUE_COUNT 1

HANDLE h_thread[20];   // thread array
DWORD n_thread=N;
DWORD thread_ID;



#include <iostream>
#include <Windows.h>
using namespace  std;





struct ThreadInfo{
    int tid;
    char role;
    double  delay;
    double persist;
}thread_info[20];



void InitialThread(){
    int cnt =0;
    while(cnt!=n_thread)
    {

        cin>>thread_info[cnt].tid
           >>thread_info[cnt].role
           >>thread_info[cnt].delay
           >>thread_info[cnt].persist;
        cnt++;
    }
}

int Check(HANDLE Semaphore){
    if (Semaphore == NULL)
    {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }
    else
        return 0;
}

void releaseSemaphoreAndCheck(HANDLE Semaphore){
    if (!ReleaseSemaphore(
             Semaphore,  // handle to semaphore
            1,            // increase count by one
            NULL))       // not interested in previous count
    {
        printf("ReleaseSemaphore error in reader: %d\n", GetLastError());
    }

}

#endif //MUTEX_COMMON_H
