#include<iostream>
#include<queue>
#include<time.h>
#include<Windows.h>
#define N 10
using namespace std;


struct task
{
	int id;
	string name;  //任务名
	int  type;
	int arriveTime;  // 到达时间
	int needTime;	//需要时间
	int deadLine;	//截止时间
	int execTime;	//已经执行时间
	int waitTime;	//已经等待时间
	int finished;	//是否完成
	int reached;	//是否到达
}tasks[N];

string types[] = { "0","重要且紧急","重要不紧急","不重要紧急","不重要不紧急"};
string name[] = {"操作系统","数学作业","背英语单词","健身","图书馆讲座","核酸检测","洗衣服","刷手机"};

int tin[] = { 1,1,2,2,3,3,4,4 };
int arr[] = {200,100,150,100,50,0,200,400 };
int	need[] = { 800,600,0,0,200,100,50,50 };
int dead[] = {2000,2500,0,0,800,500};

queue<task> p1;
queue<task> p2;
queue<task> p3;
queue<task> p4;
int n = 8;
int timeSlice = 200;  // 固定番茄钟大小
int maxEndure = 1000; // 不紧急任务最大忍受时间
int curTime = 0;	// 当前时间
int execTime = 0;    // 当前正在执行任务的执行时间

int initial();   // 初始化任务
int schedule();		//调度任务返回id
void execute(task& t);  // 执行任务
void updateReach(int execTime);	//更新新到的任务和当前时间
void printTask(task& t); // 
void traverse();	// 遍历任务

int main() {

	int id = initial();
	do {
		task& t = tasks[id];
		execute(t);
		updateReach(execTime);
		printTask(t);
	} while (id = schedule());

	return 0;
	
}

void printTask(task& t)
{
	if (t.type == 2 || t.type == 4) {
		t.waitTime = 0;
		t.execTime = 0;
		if (t.type == 2) p2.push(t);
		else p4.push(t);
		cout << "当前时间" << curTime << " 任务:" << t.id << " " << t.name << " 任务类型 " \
		<< types[t.type] << " 执行了一个番茄钟 " << execTime << endl;
	}
	else {
		if (t.type == 1 && t.execTime < t.needTime) {
			p1.push(t);
			cout << "当前时间" << curTime << " 任务:" << t.id << " " << t.name \
			<< " 任务类型 " << types[t.type] << " 执行了一个番茄钟 " << execTime << endl;
		}
		else {
			t.finished = 1;
			t.waitTime = 0;
			cout << "当前时间" << curTime << " 任务:" << t.id << " " << t.name << " 任务类型 "\
			<< types[t.type] << " 已完成"<<" 执行了一个番茄钟 "<<execTime << endl;
		}
	}
}

void execute(task &t) {
	if (t.type == 2) {
		execTime = timeSlice;
	}
	else {
		execTime = min(timeSlice, t.needTime - t.execTime);
	}
	
	Sleep(execTime * 10);
	t.execTime += execTime;
	curTime += execTime;
}


void updateReach(int execTime) {
	for (int i = 1;i <=n;i++) {
		if (tasks[i].arriveTime <= curTime) {
			tasks[i].reached = 1;
		}
	}
	for (int i = 1;i <= n;i++) {
		if (tasks[i].reached && !tasks[i].finished)
			tasks[i].waitTime += min(execTime,curTime-tasks[i].arriveTime);
	}
	
}

int schedule() {
	for (int i = 1;i <=n;i++) {
		if(tasks[i].type==3 && curTime+tasks[i].needTime-tasks[i].execTime >= tasks[i].deadLine\
			&& !tasks[i].finished && tasks[i].reached)
			return i;
		else if ((tasks[i].type == 4 || tasks[i].type == 2) && tasks[i].waitTime>=maxEndure\
			&&tasks[i].reached) {
			return i;
		}
	}
	if (!p1.empty()) {
		task t = p1.front();
		p1.pop();
		return t.id;
	}
	else {
		int tid= p2.front().id;
		p2.pop();
		return tid;
	}
	
}

void  traverse() {
	for (int i = 1;i <= n;i++) {
		cout << tasks[i].id<<" :  " << tasks[i].name <<"deadline:  " <<tasks[i].deadLine<<endl;
	}
}
int initial() {
	int min = 10000;
	int id=0;
	for (int i = 1;i <=n;i++) {
		tasks[i].id = i;
		tasks[i].type = tin[i-1];
		tasks[i].name = name[i-1];
		tasks[i].arriveTime = arr[i-1];
		tasks[i].needTime = need[i-1];
		tasks[i].deadLine = dead[i-1];
		if (tasks[i].arriveTime < min) {
			min = tasks[i].arriveTime;
			id = i;
		}
		switch (tasks[i].type)
		{
		case 1:
			p1.push(tasks[i]);
			break;
		case 2:
			p2.push(tasks[i]);
			break;
		case 3:
			p3.push(tasks[i]);
			break;
		default:
			break;
		}
	}
	return id;
}
