#include <iostream> // std::cout
#include <thread> // std::thread
#include <mutex> // std::mutex
#include <queue>
#include <vector>
#include<condition_variable>
#include<Windows.h>
#include "图形化界面.h"
using namespace std;

mutex m;// 缓存区的访问是互斥操作，即一个只能由一个进程访问
const int MAX_CACHE_LENGTH = 20;//缓存区中最大的数量
condition_variable condProducer;
condition_variable condConsumer;
int ID = 0;

struct Product {
	int id;//生产物品的id
	string type;//生产物品的种类
};

queue<Product> Q;
void ProducerActor()
{
	unique_lock<mutex> lockerProducer(m);//创建锁，保证缓存区的访问是互斥的

	cout << this_thread::get_id() << "获得了锁" << endl;
	while (Q.size() >= MAX_CACHE_LENGTH) {
		//当前缓存区已经满了，那么该进程需要被暂停
		showMessage("The current buffer is full, wait");
		Sleep(500);
		condProducer.wait(lockerProducer);//先释放互斥锁，等待被唤醒
	}
	//生产商品
	ID = ID % 20 + 1;
	Product temp = { ID, "***" };
	Q.push(temp);
	string message = "produce:" + to_string(ID);
	showMessage(message);
	cout << this_thread::get_id() << "			生产了商品" << ID << endl;
	SetCellRed(1, ID);
	Sleep(100);
	condConsumer.notify_one();
	cout << "[" << this_thread::get_id() << "] 释放了锁" << endl;
}
void ConsumerActor()
{
	unique_lock<mutex> lockerConsumer(m);//创建锁，保证缓存区的访问是互斥的
	cout << this_thread::get_id() << "获得了锁" << endl;
	while (Q.empty()) {
		showMessage("The current cache is empty, wait");
		Sleep(500);
		//当前缓存区是空的了，那么该进程需要被暂停
		condConsumer.wait(lockerConsumer);//先释放互斥锁，等待被唤醒
	}
	//消耗商品
	Product temp = Q.front();
	Q.pop();
	string message = "consume:" + to_string(temp.id);
	showMessage(message);
	SetCellGray(1, temp.id);
	cout << this_thread::get_id() << "					消耗了商品" << temp.id << endl;
	Sleep(100);
	condProducer.notify_one();
	cout << "[" << this_thread::get_id() << "] 释放了锁" << endl;
}


void ProducerTask() {
	while (1) {
		Sleep(10);
		ProducerActor();
	}
}

void ConsumerTask() {
	while (1) {
		Sleep(10);
		ConsumerActor();
	}
}
//初始化线程
void ThreadInit(int producerNum, int consumerNum)
{
	vector<thread> producerThread;
	vector<thread> consumerThread;//消费者线程
	for (int i = 0; i < producerNum; i++)
		producerThread.push_back(thread(ProducerTask));//创建生产者进程

	for (int i = 0; i < consumerNum; i++)
		consumerThread.push_back(thread(ConsumerTask));//创建消费者进程

	//使用join语句使得线程得以完整执行
	for (int i = 0; i < producerNum; i++) {
		if (producerThread[i].joinable())
			producerThread[i].join();
	}
	for (int i = 0; i < consumerNum; i++) {
		if (consumerThread[i].joinable())
			consumerThread[i].join();
	}
}



int main() {

	int producerNum;
	int consumerNum;
	
	cout << "请输入生产者的数量：";
	cin >> producerNum;
	cout << "请输入消费者的数量：";
	cin >> consumerNum;
	draw(producerNum, consumerNum);
	ThreadInit(producerNum, consumerNum);
	return 0;
}
