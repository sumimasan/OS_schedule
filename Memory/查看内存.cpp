#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <process.h>
#include<iostream>
using namespace std;

int main() {
 

    MEMORYSTATUSEX Vmeminfo;
    Vmeminfo.dwLength = sizeof(Vmeminfo);


    GlobalMemoryStatusEx(&Vmeminfo);
    printf( "当前整体存储统计如下\n");
    printf("物理内存总数：%zu KBYTES\n", Vmeminfo.ullTotalPhys / 1024);
    printf("可用物理内存：%zu KBYTES\n", Vmeminfo.ullTotalPhys / 1024);
    printf("页面文件总数：%zu KBYTES\n", Vmeminfo.ullTotalPageFile / 1024);
    printf("可用页面文件数：%zu KBYTES\n", Vmeminfo.ullAvailPageFile / 1024);
    printf("虚存空间总数：%zu BYTES\n", Vmeminfo.ullTotalVirtual / 1024);
    printf("可用虚存空间数：%zu BYTES\n", Vmeminfo.ullAvailVirtual / 1024);
    printf("物理存储使用负荷：%%%lu\n\n\n\n", Vmeminfo.dwMemoryLoad);
    return 0;
  

}