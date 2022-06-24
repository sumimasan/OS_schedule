#include <iostream>
#include <Windows.h>
#include "Common.h"
using namespace  std;


HANDLE RMutex;
HANDLE fSemaphore;
HANDLE queue;
HANDLE WMutex;



int ReadCount=0;
int WriteCount=0;

void ReadThread(ThreadInfo lpPara);
void WriteThread(ThreadInfo lpPara);

int main() {
    InitialThread();
    // Create a mutex with no initial owner
    RMutex = CreateMutex(NULL,FALSE,NULL);
    Check(RMutex);
    WMutex=CreateMutex(NULL,FALSE,NULL);
    Check(WMutex);

    fSemaphore = CreateSemaphore(NULL,              // default security attributes
                             MAX_SEM_COUNT,        //  initial count
                             MAX_SEM_COUNT,//  maximum count
                             NULL);             // unnamed semaphore
    Check(fSemaphore);
    queue= CreateSemaphore(NULL,              // default security attributes
                           QUEUE_COUNT ,        //  initial count
                           QUEUE_COUNT ,//  maximum count
                                 NULL);             // unnamed semaphore
    Check(queue);



    for (int i =0;i<n_thread;i++){
        if (thread_info[i].role=='r'||thread_info[i].role=='R'){
            h_thread[i]= CreateThread(NULL,0,LPTHREAD_START_ROUTINE(ReadThread),&thread_info[i],0,&thread_ID);
        }
        else{
            h_thread[i]= CreateThread(NULL,0,LPTHREAD_START_ROUTINE(WriteThread),&thread_info[i],0,&thread_ID);
        }
        if( h_thread[i] == NULL )
        {
            printf("CreateThread error: %d\n", GetLastError());
            return 1;
        }
    }
   WaitForMultipleObjects(n_thread,h_thread,true,-1);

    for (int i =0;i<n_thread;i++){
        CloseHandle(h_thread[i]);
    }
    cout<<"all reader and writer have finished operating"<<endl;
    return 0;
}

void ReadThread(ThreadInfo lpPara){
    sleep(lpPara.delay);
    cout<<"Reader thread "<<lpPara.tid<<" sends the reading requests"<<endl;

    WaitForSingleObject(queue,INFINITE);
    WaitForSingleObject(RMutex,INFINITE);
    if (ReadCount==0) {
        WaitForSingleObject(fSemaphore, INFINITE);  // handle to semaphore
    }
    ReadCount++;
    ReleaseMutex(RMutex);
    releaseSemaphoreAndCheck(queue);

    /*read action*/
    cout<<"Reader thread "<<lpPara.tid <<" begins to read the file"<<endl;
    sleep(lpPara.persist);
    cout<<"Reader thread "<<lpPara.tid <<" finished reading the file"<<endl;

    WaitForSingleObject(RMutex,INFINITE);
    ReadCount--;
    if(ReadCount==0)
        releaseSemaphoreAndCheck(fSemaphore);
    ReleaseMutex(RMutex);
}

void WriteThread(ThreadInfo lpPara){
    sleep(lpPara.delay);
    cout<<"Writer thread "<<lpPara.tid<< " sends the writing requests"<<endl;

    WaitForSingleObject(WMutex,INFINITE);  //  // handle to semaphore and  time-out interval
    if(WriteCount==0)
        WaitForSingleObject(queue,INFINITE);
    WriteCount++;
    ReleaseMutex(WMutex);

    WaitForSingleObject(fSemaphore,INFINITE);  //  time-out interval  // handle to semaphore
    // write action
    cout << "Writer thread " << lpPara.tid << " begins to write to the file" << endl;
    sleep(lpPara.persist);
    // release the semaphore
    cout << "Writer thread " << lpPara.tid << " finished writing to the file" << endl;
    releaseSemaphoreAndCheck(fSemaphore);

    WaitForSingleObject(WMutex,INFINITE);
    WriteCount--;
    if(WriteCount==0) {
        releaseSemaphoreAndCheck(queue);
    }
    ReleaseMutex(WMutex);
}