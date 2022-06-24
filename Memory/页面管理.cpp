//#include<iostream>
//#include<vector>
//#include<algorithm>
//using namespace std;
//void menu();
//void initial();
//
//int total = 100; // �ڴ�����
//int usedPage = 18; // ʹ�õ��ڴ��
//int remainPage = 82; // ʣ����ڴ��
//int threadCnt = 0; // ��������
//
//vector<int> used;
//vector<int> remain;
//int main() {
//	initial();
//	while (true)
//	{
//		menu();
//		cout << "��������Ҫ���еĲ��� ��" << endl;
//		int input;
//		cin >> input;
//		switch (input)
//		{
//		case 1:
//			;
//			break;
//		case 2:
//			break;
//		case 4:
//			return 0;
//		default:
//			break;
//		}
//		
//	}
//	return 0;
//}
//
//void initial() {
//	int init[] = { 11,16,25,29,34,41,53,54,61,62,67,75,82,90,93,95,96,97 };
//	cout << "��ʼ��������£�" << endl;
//	cout << "�ڴ�����:" <<total<< endl;
//	cout << "ʣ��ռ䣺"<<remainPage << endl;
//	printf("��ʹ�õ��ڴ�飨%d)\n", usedPage);
//
//	for (int i = 0;i <18;i++) {
//		used.push_back(init[i]);
//		cout << used[i] << " ";
//	}
//	printf("\n");
//
//
//}
//void menu() {
//	cout << "�����˵�: " << endl;
//	cout << "1.�������� " << endl;
//	cout << "2.�������� " << endl;
//	cout << "3.�鿴�ڴ� " << endl;
//	cout << "4.�˳����� " << endl;
//}
//
//void CreateProcess() {
//	cout << "��������̺ţ�С��100�� ������ҳ��: ";
//	int id;
//	int needPage;
//	cin >> id >> needPage;
//	if (needPage<= remainPage) {
//
//		cout << "�������̳ɹ���" << endl;
//	}
//	else {
//		cout << "��������ʧ�ܣ�" << endl;
//		cout << "��ǰ����ҳ����:" << remainPage << " С������ҳ����" << needPage << endl;
//	}
//}
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

int N = 100;//�ڴ����� 
int rest = 100;//ʣ��ռ���� 
int procNum = 0;//��������
bool st[200];//��ʾ�ÿ�ռ��Ƿ�ʹ��
int id[200];//��ʾ��ʹ�õ��ڴ�������ڵĽ���id

//�鿴�ڴ溯�� 
void Query()
{
	printf("�ڴ�������%d��, ", N);
	printf("���ÿռ䣺%d��, ", N - rest);
	printf("ʣ��ռ䣺%d��, ", rest);
	printf("����������%d��\n", procNum);
	printf("��ʹ�õ��ڴ��(%d)��\n", N - rest);
	for (int i = 0;i < N;i++)
	{
		if (st[i]) printf("%d ", i);
	}
	puts("");

}

void Alloc(int name, int num)
{
	if (num > rest)
	{
		puts("�ڴ�ռ䲻�㣬���̴���ʧ�ܣ�");
		return;
	}

	for (int i = 0, j = 0;i < N && j < num;i++)
	{
		if (!st[i])
		{
			st[i] = true;
			id[i] = name;
			j++;
			rest--;
		}
	}
	procNum++;
	puts("�������̳ɹ���");
}

void Recycle(int name)
{
	bool flg = false;
	for (int i = 0;i < N;i++)
	{
		if (st[i] && id[i] == name)
		{
			st[i] = false;
			id[i] = 0;
			flg = true;
			rest++;
		}
	}
	if (!flg) puts("�ý��̲����ڣ�");
	else puts("�����ѽ�����"), procNum--;
}

void Menu()
{
	puts("\n�����˵���");
	puts("1. ��������");
	puts("2. ��������");
	puts("3. �鿴�ڴ�");
	puts("4. �˳�����");
}

void init()
{
	int init[] = {11,16,25,29,34,41,53,54,61,62,67,75,82,90,93,95,96,97};
	for (int i = 0;i < 18;i++)
		st[init[i]] = true;
	rest -= 18;
}

int main()
{
	init();
	puts("��ʼ��������£�");
	Query();
	while (true)
	{
		Menu();
		int op;
		printf("��������Ҫ���еĲ�����");
		scanf("%d", &op);
		if (op == 1)
		{
			int name, num;
			printf("��������̺ţ�С��100��������ҳ�棺");
			scanf("%d%d", &name, &num);
			Alloc(name, num);
		}
		else if (op == 2)
		{
			int name;
			printf("��������̺ţ�");
			scanf("%d", &name);
			Recycle(name);
		}
		else if (op == 3)
		{
			Query();
		}
		else if (op == 4)
		{
			break;
		}
	}
	return 0;
}
