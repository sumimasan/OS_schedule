//�ڴ����
//����2-6-1  virtumem.cpp
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <process.h>

unsigned _stdcall simulator(void *);
unsigned _stdcall inspector(void *);
LPVOID BASE_PTR;
int Actnum=0;
int main(int argc,  char* argv[])
{
	unsigned ThreadID[2];
	_beginthreadex(NULL, 0, simulator, NULL, 0, &ThreadID[0]);
	_beginthreadex(NULL, 0, inspector, NULL, 0, &ThreadID[1]);
	getchar();
	
	
	SYSTEM_INFO systemInfo;
	GetSystemInfo(&systemInfo);
	printf("��������ҳ��С%u\n",systemInfo.dwPageSize);
	
	return 0;
}
unsigned _stdcall simulator(void *)
{
	DWORD OldProtect;
	int randnum;
	printf("Now the simulator procedure has been started.\n");
	srand((unsigned)time(NULL));
	randnum=-1;
	while(1) {
		Sleep(500);
		while(Actnum!=0) {
			Sleep(500);
		}

		randnum=20&rand();
		printf("***************randnum=%d, rand()=%f******************\n", randnum, rand());
		switch(randnum) {
		case 0:
			if (BASE_PTR=VirtualAlloc(NULL, 1024*32, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE)) {
				sprintf((char*)BASE_PTR,"memory has been malloced\n");/*�������ڴ���൱��malloc����new����һ���ˣ�����д��*/
				Actnum=1;      
//				Ŀǰִ�ж��������ı������ύ 
			}
			break;
		case 1:
			if (VirtualFree(BASE_PTR, 1024*32, MEM_DECOMMIT)) {
				Actnum=2;
//				ǰִ�ж��������ĳ���
			}
			break;
		case 2:
			if (VirtualFree(BASE_PTR, 0, MEM_RELEASE)) {
				Actnum=3;
//				ǰִ�ж��������ĳ��䲢�ͷ����ռ�
			}
			break;
		case 3:
			if (VirtualProtect(BASE_PTR, 1024*32, PAGE_READONLY, &OldProtect)) {
				Actnum=4;
//				Ŀǰִ�ж������ı�����ڴ�ҳ�ı���
			}
			break;
		case 4:
			if (VirtualLock(BASE_PTR, 1024*12)) {
				Actnum=5;
//				Ŀǰִ�ж�������������ڴ�ҳ
			}
			break;
		case 5:
			if (BASE_PTR=VirtualAlloc(NULL, 1024*32, MEM_RESERVE, PAGE_READWRITE)) { //�����Ǳ�����ַ��û�з���
				Actnum=6;
//				Ŀǰִ�ж��������ı���
			}
			break;
		default:
			break;
		}
	}
	return 0;
}
unsigned _stdcall inspector(void *)
{
	char para1[3000];
	char tempstr[100];
	MEMORYSTATUSEX Vmeminfo;
	Vmeminfo.dwLength = sizeof(Vmeminfo);
	MEMORY_BASIC_INFORMATION inspectorinfo1;
	int structsize = sizeof(MEMORY_BASIC_INFORMATION);
	printf("Hi,  now inspector begin to work\n");
	SIZE_T before_ullAvailPhys= 0;
	SIZE_T before_ullAvailVirtual=0;
	while(1) {
		Sleep(1000);
		if(Actnum!=0) {
			switch(Actnum) {
			case 1:
				printf((char*)BASE_PTR);//��д����Ϣ�������				
				memset(&inspectorinfo1, 0, structsize);		
				VirtualQuery((LPVOID)BASE_PTR, &inspectorinfo1, structsize);
				strcpy(para1, "Ŀǰִ�ж��������ı������ύ\n");
				break;
			case 2:
				memset(&inspectorinfo1, 0, structsize);
				VirtualQuery((LPVOID)BASE_PTR, &inspectorinfo1, structsize);
				strcpy(para1, "Ŀǰִ�ж��������ĳ���\n");
				break;
			case 3:
				memset(&inspectorinfo1, 0, structsize);
				VirtualQuery((LPVOID)BASE_PTR, &inspectorinfo1, structsize);
				strcpy(para1, "Ŀǰִ�ж��������ĳ��䲢�ͷ����ռ�\n");
				break;
			case 4:
				memset(&inspectorinfo1, 0, structsize);
				VirtualQuery((LPVOID)BASE_PTR, &inspectorinfo1, structsize);
				strcpy(para1, "Ŀǰִ�ж������ı�����ڴ�ҳ�ı���\n");
				break;
			case 5:
				memset(&inspectorinfo1, 0, structsize);
				VirtualQuery((LPVOID)BASE_PTR, &inspectorinfo1, structsize);
				strcpy(para1, "Ŀǰִ�ж�������������ڴ�ҳ\n");
				break;
			case 6:
				memset(&inspectorinfo1, 0, structsize);
				VirtualQuery((LPVOID)BASE_PTR, &inspectorinfo1, structsize);
				strcpy(para1, "Ŀǰִ�ж��������ı���\n");
				break;
			default:
				break;
			}
			sprintf(tempstr, "��ʼ��ַ:0X%x\n", inspectorinfo1.BaseAddress);
			strcat(para1, tempstr);
			sprintf(tempstr, "�����С:0X%x\n", inspectorinfo1.RegionSize);
			strcat(para1, tempstr);
			sprintf(tempstr, "Ŀǰ״̬:0X%x\n", inspectorinfo1.State);
			strcat(para1, tempstr);
			sprintf(tempstr, "����ʱ���ʱ���:0X%x\n", inspectorinfo1.AllocationProtect);
			strcat(para1, tempstr);
			sprintf(tempstr, "��ǰ���ʱ���:0X%x\n", inspectorinfo1.Protect);
			strcat(para1, tempstr);
			strcat(para1, "(״̬:10000����δ���䣻1000�����ύ��2000��������)\n");
			strcat(para1, "(������ʽ��0����������1�����ֹ���ʣ�2����ֻ����4�����д;\n10�����ִ");
			strcat(para1, "��;20����ɶ���ִ��;40����ɶ�д��ִ��);\n********************************\n");
			GlobalMemoryStatusEx(&Vmeminfo);
			
			
			strcat(para1, "��ǰ����洢ͳ������\n");
			sprintf(tempstr, "�����ڴ�������%zu(KBYTES)\n",  Vmeminfo.ullTotalPhys/1024);
			strcat(para1, tempstr);
			sprintf(tempstr, "���������ڴ棺%zu(KBYTES)\n",  Vmeminfo.ullAvailPhys/1024);
//			sprintf(tempstr, "�����ڴ�仯��0x%x\n",  abs(Vmeminfo.ullAvailPhys-before_ullAvailPhys));
			strcat(para1, tempstr);
			sprintf(tempstr, "ҳ���ļ�������%zu(KBYTES)\n",  Vmeminfo.ullTotalPageFile/1024);
			strcat(para1, tempstr);
			sprintf(tempstr, "����ҳ���ļ�����%zu(KBYTES)\n",  Vmeminfo.ullAvailPageFile/1024);
			strcat(para1, tempstr);
			sprintf(tempstr, "���ռ�������%zu(BYTES)\n",  Vmeminfo.ullTotalVirtual);
			strcat(para1, tempstr);
			sprintf(tempstr, "�������ռ�����%zu(BYTES)\n",  Vmeminfo.ullAvailVirtual);
			strcat(para1, tempstr);
			sprintf(tempstr, "����洢ʹ�ø��ɣ�%%%lu\n\n\n\n",  Vmeminfo.dwMemoryLoad);
			before_ullAvailPhys=Vmeminfo.dwMemoryLoad;
			strcat(para1, tempstr);
			printf("%s", para1);
		
			Actnum=0;
			Sleep(500);
		}
	}
	return 0;
}
