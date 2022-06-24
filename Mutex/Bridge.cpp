//
// Created by wang haolin on 2022/5/7.
//
#include <iostream>
#include <Windows.h>
#include "Common.h"
using namespace  std;

HANDLE nMutex;
HANDLE sMutex;
HANDLE s;


void NorthWalker(ThreadInfo lpPara);
void SouthWalker(ThreadInfo lpPara);

int main() {
   InitialThread();
   nMutex=CreateMutex( NULL,              // default security attributes
                       FALSE,             // initially the caller does not own the mutex
                       NULL);
   Check(nMutex);
   sMutex=CreateMutex(NULL,              // default security attributes
                       FALSE,             // initially the caller does not own the mutex
                       NULL);
   Check(sMutex);

   s= CreateSemaphore(NULL,              // default security attributes
                                MAX_SEM_COUNT,        //  initial count
                                MAX_SEM_COUNT,//  maximum count
                                NULL);
   Check(s);

   for (int i =0;i<n_thread;i++){
       if (thread_info[i].role=='r'||thread_info[i].role=='R'){
           h_thread[i]= CreateThread(NULL,0,LPTHREAD_START_ROUTINE(NorthWalker),&thread_info[i],0,&thread_ID);
       }
       else{
           h_thread[i]= CreateThread(NULL,0,LPTHREAD_START_ROUTINE(SouthWalker),&thread_info[i],0,&thread_ID);
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
   cout<<"all NorthWalker and SouthWalker have finished operating"<<endl;
   return 0;
}

void NorthWalker(ThreadInfo lpPara){
   sleep(lpPara.delay);
   cout<<"NorthWalker thread "<<lpPara.tid<<" sends the Northern requests"<<endl;
   WaitForSingleObject(s,INFINITE);  // no time-out interval

   WaitForSingleObject(nMutex,INFINITE);  // no time-out interval
   cout<<"NorthWalker thread "<<lpPara.tid<<" begins to cross the bridge from North"<<endl;
   ReleaseMutex(nMutex);

   cout<<"NorthWalker thread "<<lpPara.tid<<" is on the  the bridge "<<endl;
   sleep(lpPara.persist);

   WaitForSingleObject(sMutex, INFINITE);  // no time-out interval
   cout<<"NorthWalker thread "<<lpPara.tid<<" finished to cross the bridge to South"<<endl;
   ReleaseMutex(sMutex);
   releaseSemaphoreAndCheck(s);
}

void SouthWalker(ThreadInfo lpPara){
   sleep(lpPara.delay);
   cout<<"SouthWalker thread "<<lpPara.tid<<" sends the Southern requests"<<endl;
   WaitForSingleObject(s,INFINITE);  // no time-out interval

   WaitForSingleObject(sMutex,INFINITE);  // no time-out interval
   cout<<"SouthWalker thread "<<lpPara.tid<<" begins to cross the bridge from South"<<endl;
   ReleaseMutex(sMutex);

   cout<<"SouthWalker thread "<<lpPara.tid<<" is on the  the bridge "<<endl;
   sleep(lpPara.persist);

   WaitForSingleObject(nMutex, INFINITE);  // no time-out interval
   cout<<"SouthWalker thread "<<lpPara.tid<<" finished to cross the bridge to North"<<endl;
   ReleaseMutex(nMutex);
   releaseSemaphoreAndCheck(s);
}

