////
//// Created by wang haolin on 2022/5/22.
////
//#include <windows.h>
//#include <stdio.h>
//#include <process.h>
//#include<algorithm>
//#include <deque>
//#include <iostream>
//
//using namespace std;
//
//#define N 15
//
//
//
//LPVOID BASE_PTR[N];
//int n = 15;
//deque<int> stack;
//int Visit[15] = { 3,4,2,6,4,3,7,4,3,6,3,4,8,4,6 };
//
//int miss = 0;
//int hit = 0;
//
//unsigned _stdcall simulator(LPVOID i);
//int main() {
//    SYSTEM_INFO systemInfo;
//    GetSystemInfo(&systemInfo);
//    printf("处理器分页大小:%u \n", systemInfo.dwPageSize);
//    for (int i = 1;i < N;i++) {
//        BASE_PTR[i] = VirtualAlloc(NULL, 1024 * 32, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
//    }
//
//    unsigned ThreadId[N];
//    for (int i = 0;i < n;i++) {
//        HANDLE hThread=(HANDLE)   _beginthreadex(NULL, 0, simulator, (int *)i, 0, &ThreadId[i]);
//        WaitForSingleObject(hThread, INFINITE);
//        CloseHandle(hThread);
//    }
//
//    cout << "命中率为: " << hit / float(n) << endl;
//    cout << "缺页次数为： " << miss << endl;
//    return 0;
//}
//
//unsigned _stdcall simulator(LPVOID info) {
//    int *i =  (int*) info;
//    int flag = 1;
//    for (deque<int>::iterator it = stack.begin();it!=stack.end();) {
//        if (Visit[*i] == *it) {
//            hit++;
//            flag = 0;
//            it= stack.erase(it);
//        }
//        else {
//            it++;
//        }
//    }
//    if (flag) {
//        miss++;
//        if (stack.size() == 3) {
//            cout << "置换页面为 :" << stack.front() << endl;
//            stack.pop_front();
//        }
//
//    }
//    stack.push_back(Visit[*i]);
//    return 0;
//}