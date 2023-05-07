#include <iostream> // std::cout
#include <thread> // std::thread
#include <mutex> // std::mutex
#include <queue>
#include <vector>
#include<condition_variable>
#include<Windows.h>
#include "ͼ�λ�����.h"
using namespace std;

mutex m;// �������ķ����ǻ����������һ��ֻ����һ�����̷���
const int MAX_CACHE_LENGTH = 20;//����������������
condition_variable condProducer;
condition_variable condConsumer;
int ID = 0;

struct Product {
	int id;//������Ʒ��id
	string type;//������Ʒ������
};

queue<Product> Q;
void ProducerActor()
{
	unique_lock<mutex> lockerProducer(m);//����������֤�������ķ����ǻ����

	cout << this_thread::get_id() << "�������" << endl;
	while (Q.size() >= MAX_CACHE_LENGTH) {
		//��ǰ�������Ѿ����ˣ���ô�ý�����Ҫ����ͣ
		showMessage("The current buffer is full, wait");
		Sleep(500);
		condProducer.wait(lockerProducer);//���ͷŻ��������ȴ�������
	}
	//������Ʒ
	ID = ID % 20 + 1;
	Product temp = { ID, "***" };
	Q.push(temp);
	string message = "produce:" + to_string(ID);
	showMessage(message);
	cout << this_thread::get_id() << "			��������Ʒ" << ID << endl;
	SetCellRed(1, ID);
	Sleep(100);
	condConsumer.notify_one();
	cout << "[" << this_thread::get_id() << "] �ͷ�����" << endl;
}
void ConsumerActor()
{
	unique_lock<mutex> lockerConsumer(m);//����������֤�������ķ����ǻ����
	cout << this_thread::get_id() << "�������" << endl;
	while (Q.empty()) {
		showMessage("The current cache is empty, wait");
		Sleep(500);
		//��ǰ�������ǿյ��ˣ���ô�ý�����Ҫ����ͣ
		condConsumer.wait(lockerConsumer);//���ͷŻ��������ȴ�������
	}
	//������Ʒ
	Product temp = Q.front();
	Q.pop();
	string message = "consume:" + to_string(temp.id);
	showMessage(message);
	SetCellGray(1, temp.id);
	cout << this_thread::get_id() << "					��������Ʒ" << temp.id << endl;
	Sleep(100);
	condProducer.notify_one();
	cout << "[" << this_thread::get_id() << "] �ͷ�����" << endl;
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
//��ʼ���߳�
void ThreadInit(int producerNum, int consumerNum)
{
	vector<thread> producerThread;
	vector<thread> consumerThread;//�������߳�
	for (int i = 0; i < producerNum; i++)
		producerThread.push_back(thread(ProducerTask));//���������߽���

	for (int i = 0; i < consumerNum; i++)
		consumerThread.push_back(thread(ConsumerTask));//���������߽���

	//ʹ��join���ʹ���̵߳�������ִ��
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
	
	cout << "�����������ߵ�������";
	cin >> producerNum;
	cout << "�����������ߵ�������";
	cin >> consumerNum;
	draw(producerNum, consumerNum);
	ThreadInit(producerNum, consumerNum);
	return 0;
}
