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
    printf( "��ǰ����洢ͳ������\n");
    printf("�����ڴ�������%zu KBYTES\n", Vmeminfo.ullTotalPhys / 1024);
    printf("���������ڴ棺%zu KBYTES\n", Vmeminfo.ullTotalPhys / 1024);
    printf("ҳ���ļ�������%zu KBYTES\n", Vmeminfo.ullTotalPageFile / 1024);
    printf("����ҳ���ļ�����%zu KBYTES\n", Vmeminfo.ullAvailPageFile / 1024);
    printf("���ռ�������%zu BYTES\n", Vmeminfo.ullTotalVirtual / 1024);
    printf("�������ռ�����%zu BYTES\n", Vmeminfo.ullAvailVirtual / 1024);
    printf("����洢ʹ�ø��ɣ�%%%lu\n\n\n\n", Vmeminfo.dwMemoryLoad);
    return 0;
  

}