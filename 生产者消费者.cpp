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
		cout << "��ǰ�������������ȴ�" << endl;
		condProducer.wait(lockerProducer);//���ͷŻ��������ȴ�������
	}
	//������Ʒ
	ID = ID % 20 + 1;
	Product temp = { ID, "***" };
	Q.push(temp);

	cout << this_thread::get_id() << "			��������Ʒ" << ID << endl;
	SetCellRed(1, ID);
	Sleep(1000);
	condConsumer.notify_one();
	cout << "[" << this_thread::get_id() << "] �ͷ�����" << endl;
}
void ConsumerActor()
{
	unique_lock<mutex> lockerConsumer(m);//����������֤�������ķ����ǻ����
	cout << this_thread::get_id() << "�������" << endl;
	while (Q.empty()) {
		cout << "��ǰ�������ǿյģ��ȴ�" << endl;
		//��ǰ�������ǿյ��ˣ���ô�ý�����Ҫ����ͣ
		condConsumer.wait(lockerConsumer);//���ͷŻ��������ȴ�������
	}
	//������Ʒ
	Product temp = Q.front();
	Q.pop();

	cout << this_thread::get_id() << "					��������Ʒ" << temp.id << endl;

	SetCellGray(1, temp.id);
	Sleep(1000);

	condProducer.notify_one();
	cout << "[" << this_thread::get_id() << "] �ͷ�����" << endl;
}


void ProducerTask() {
	while (1) {
		ProducerActor();
	}
}

void ConsumerTask() {
	while (1) {
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

	//ʹ��join���ʹ�ý��̵�������ִ��
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
	draw();
	ThreadInit(producerNum, consumerNum);
	return 0;
}
