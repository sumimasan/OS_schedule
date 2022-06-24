////
//// Created by wang haolin on 2022/4/29.
////
//#include <iostream>
//#include <Windows.h>
//using namespace  std;
//#include "Common.h"
//
//
//
//HANDLE full;
//HANDLE empty;
//HANDLE mutex;
//
//
//int Buffer[MAX_SEM_COUNT];
//int in=0;
//int out=0;
//
//
//
//void Producer(ThreadInfo lpPara);
//void Consumer(ThreadInfo lpPara);
//
//
//int ProducerAndComsumer() {
//    InitialThread();
//    // Create a mutex with no initial owner
//    mutex = CreateMutex(
//            NULL,              // default security attributes
//            FALSE,             // initially the caller does not own the mutex
//            NULL);             // unnamed mutex
//
//    if (mutex == NULL)
//    {
//        printf("CreateMutex error: %d\n", GetLastError());
//        return 1;
//    }
//
//    empty = CreateSemaphore(NULL,              // default security attributes
//                          MAX_SEM_COUNT,        //  initial count
//                          MAX_SEM_COUNT,//  maximum count
//                          NULL);             // unnamed semaphore
//
//    if (empty == NULL)
//    {
//        printf("CreateSemaphore error: %d\n", GetLastError());
//        return 1;
//    }
//
//    full = CreateSemaphore(NULL,              // default security attributes
//                                 0,        //  initial count
//                                 MAX_SEM_COUNT,//  maximum count
//                                 NULL);             // unnamed semaphore
//
//    if (full == NULL)
//    {
//        printf("CreateSemaphore error: %d\n", GetLastError());
//        return 1;
//    }
//
//
//    for (int i =0;i<n_thread;i++){
//        if (thread_info[i].role=='r'||thread_info[i].role=='R'){
//            h_thread[i]= CreateThread(NULL,0,LPTHREAD_START_ROUTINE(Producer),&thread_info[i],0,&thread_ID);
//        }
//        else{
//            h_thread[i]= CreateThread(NULL,0,LPTHREAD_START_ROUTINE(Consumer),&thread_info[i],0,&thread_ID);
//        }
//        if( h_thread[i] == NULL )
//        {
//            printf("CreateThread error: %d\n", GetLastError());
//            return 1;
//        }
//    }
//    WaitForMultipleObjects(n_thread,h_thread,true,-1);
//
//    for (int i =0;i<n_thread;i++){
//        CloseHandle(h_thread[i]);
//    }
//    cout<<"all producer and consumer have finished operating"<<endl;
//    return 0;
//}
//
//
//
//void Producer(ThreadInfo lpPara){
//    sleep(lpPara.delay);
//    cout<<"Producer thread "<<lpPara.tid<<" sends the Producing requests"<<endl;
//
//    WaitForSingleObject(empty,INFINITE);  // no time-out interval
//    WaitForSingleObject(mutex,INFINITE);
//
//    /*read action*/
//    cout<<"Producer thread "<<lpPara.tid <<" begins to Produce the product"<<endl;
//    Buffer[in]=lpPara.tid;
//    in =(in+1)%(MAX_SEM_COUNT);
//    sleep(lpPara.persist);
//    cout<<"Producer thread "<<lpPara.tid <<" finished Producing the product"<<endl;
//
//
//    ReleaseMutex(mutex);
//    if (!ReleaseSemaphore(
//            full,  // handle to semaphore
//            1,            // increase count by one
//            NULL))       // not interested in previous count
//    {
//        printf("ReleaseSemaphore error in reader: %d\n", GetLastError());
//    }
//}
//
//void  Consumer(ThreadInfo lpPara){
//    sleep(lpPara.delay);
//
//    cout<<"Consumer thread "<<lpPara.tid<< " sends the consuming requests"<<endl;
//    WaitForSingleObject(
//            full,    // handle to semaphore
//            INFINITE);  //  time-out interval
//    WaitForSingleObject(mutex,INFINITE);
//
//    // write action
//    cout << "Consumer thread " << lpPara.tid << " begins to Consume to the product" << endl;
//    int nextc = Buffer[out];
//    out=(out+1)%MAX_SEM_COUNT;
//    sleep(lpPara.persist);
//
//    // release the semaphore
//    cout << "Consumer thread " << lpPara.tid << " finished Consuming to the product" << endl;
//    ReleaseMutex(mutex);
//    if (!ReleaseSemaphore(
//            empty,  // handle to semaphore
//            1,            // increase count by one
//            NULL))       // not interested in previous count
//    {
//        printf("ReleaseSemaphore error in writer: %d\n", GetLastError());
//    }
//}