#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

int N = 100;//内存总量 
int rest = 100;//剩余空间块数 
int procNum = 0;//进程总数
bool st[200];//表示该块空间是否被使用
int id[200];//表示被使用的内存块所属于的进程id

//查看内存函数 
void Query()
{
	printf("内存总量：%d块, ", N);
	printf("已用空间：%d块, ", N - rest);
	printf("剩余空间：%d块, ", rest);
	printf("进程总数：%d个\n", procNum);
	printf("已使用的内存块(%d)：\n", N - rest);
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
		puts("内存空间不足，进程创建失败！");
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
	puts("创建进程成功！");
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
	if (!flg) puts("该进程不存在！");
	else puts("进程已结束！"), procNum--;
}

void Menu()
{
	puts("\n操作菜单：");
	puts("1. 创建进程");
	puts("2. 结束进程");
	puts("3. 查看内存");
	puts("4. 退出程序");
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
	puts("初始化结果如下：");
	Query();
	while (true)
	{
		Menu();
		int op;
		printf("请输入您要进行的操作：");
		scanf("%d", &op);
		if (op == 1)
		{
			int name, num;
			printf("请输入进程号（小于100）和所需页面：");
			scanf("%d%d", &name, &num);
			Alloc(name, num);
		}
		else if (op == 2)
		{
			int name;
			printf("请输入进程号：");
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
