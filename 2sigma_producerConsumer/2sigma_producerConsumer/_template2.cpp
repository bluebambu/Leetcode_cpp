// _template.cpp : Defines the entry point for the console application.
//
#include <stdafx.h>

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>
#include <unordered_set>
#include <set>
#include <map>
#include <utility>
#include <sstream>
#include <string>
#include <chrono>

using namespace std;

inline int exchg(int &a, int &b)  { int c = a; a = b; b = c; }
inline int log2(int N){ return log10(N) / log10(2); }
inline float min(float a, float b) { return a < b ? a : b; }


struct TreeNode
{
	TreeNode(int a) :val(a), left(nullptr), right(nullptr) {}
	TreeNode(int a, TreeNode* x, TreeNode* y) :val(a), left(x), right(y) {}
	TreeNode() :val(0), left(nullptr), right(nullptr) {}

	int val;
	TreeNode *left;
	TreeNode *right;

};

void print(TreeNode* root){
	queue<TreeNode*> q;
	q.push(root);

	while (q.size()){
		int n = q.size();
		for (int i = 0; i < n; ++i){
			TreeNode* front = q.front();
			q.pop();

			if (!front)
				cout << "# ";
			else{
				cout << front->val << " ";
				q.push(front->left);
				q.push(front->right);
			}
		}
		cout << endl;
	}
}


template <typename C>
void prt1Layer(C v){
	for (auto i : v)
		cout << i << " ";
	cout << endl;
}

template <typename C>
void prt2Layer(C v){
	for (auto i : v){
		for (auto j : i)
			cout << j << " ";
		cout << endl; 
	}
	cout << endl;
}

template <typename C>
void mapprt(C v){
	for (auto i : v)
		cout << i.first << " " << i.second << endl;
	cout << endl;
}
////////////////////////////////////////////////////////////////
//顾名思义，单生产者 - 单消费者模型中只有一个生产者和一个消费者，生产者不停地往产品库中放入产品，
//消费者则从产品库中取走产品，产品库容积有限制，只能容纳一定数目的产品，如果生产者生产产品的速度
//过快，则需要等待消费者取走产品之后，产品库不为空才能继续往产品库中放置新的产品，相反，如果消费
//者取走产品的速度过快，则可能面临产品库中没有产品可使用的情况，此时需要等待生产者放入一个产品后
//，消费者才能继续工作。

#include <windows.h>
#include <cstdlib>
#include <mutex>
#include <thread>
#include <condition_variable>

const int kItemRepoSize = 3; 
const int kItemsToProduce = 100; 

struct ItemRepo{
	int buffer[kItemRepoSize]; 
	size_t read_pos, write_pos; 
	mutex mtx; 
	condition_variable repo_not_full, repo_not_empty; 
};

ItemRepo gItemRepo; 

void ProduceItem(ItemRepo* ir, int item){
	unique_lock<mutex> lock(ir->mtx); 
	while (((ir->write_pos + 1) % kItemRepoSize) == ir->read_pos){
		// item buffer is full, just wait here. 
		cout << "Producer is waiting for an empty slot....\n"; 
		(ir->repo_not_full).wait(lock); // wait for "repo not full" event. 
	}

	// when "repo not full"
	(ir->buffer)[ir->write_pos] = item; 
	(ir->write_pos)++; 

	if ((ir->write_pos) == kItemRepoSize)
		ir->write_pos = 0; //circular buffer

	(ir->repo_not_empty).notify_all(); 
	lock.unlock(); 
}

int ConsumeItem(ItemRepo* ir){
	int data; 
	unique_lock<mutex> lock(ir->mtx); 

	while (ir->write_pos == ir->read_pos){
		// this means buffer is empty, just wait
		cout << "Consumer waiting!\n"; 
		(ir->repo_not_empty).wait(lock); 
	}

	data = (ir->buffer)[ir->read_pos];
	(ir->read_pos)++; 

	if (ir->read_pos >= kItemRepoSize)
		ir->read_pos = 0; // circular

	(ir->repo_not_full).notify_all(); 
	lock.unlock(); 

	return data; 
}

void ProducerTask(){
	for (int i = 1; i <= kItemsToProduce; ++i){
		Sleep(1); 
		gItemRepo.mtx.lock(); 
		cout << "Produce the " << i << "th item.....\n"; 
		gItemRepo.mtx.unlock(); 
		ProduceItem(&gItemRepo, i); 
	}
}

void ConsumerTask(){
	static int cnt = 0; 
	while (1){
		Sleep(1); 
		int item = ConsumeItem(&gItemRepo); 
		gItemRepo.mtx.lock(); 
		cout << "Consume the " << item << "th item!\n"; 
		gItemRepo.mtx.unlock(); 
		if (++cnt == kItemsToProduce)
			break;
	}
}

void InitItemRepo(ItemRepo* ir){
	ir->write_pos = 0; 
	ir->read_pos = 0; 
}


////////////////////////////////////////////////////////////////////////////////////////////////
//  单生产者-多消费者模型
// 与单生产者和单消费者模型不同的是，单生产者-多消费者模型中可以允许多个消费者同时从产品库中取走产品。
// 所以除了保护产品库在多个读写线程下互斥之外，还需要维护消费者取走产品的计数器，代码如下:
#include <unistd.h>

#include <cstdlib>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

static const int kItemRepositorySize  = 4; // Item buffer size.
static const int kItemsToProduce  = 10;   // How many items we plan to produce.

struct ItemRepository {
    int item_buffer[kItemRepositorySize];
    size_t read_position;
    size_t write_position;
    size_t item_counter;
    std::mutex mtx;
    std::mutex item_counter_mtx;
    std::condition_variable repo_not_full;
    std::condition_variable repo_not_empty;
} gItemRepository;

typedef struct ItemRepository ItemRepository;


void ProduceItem(ItemRepository *ir, int item)
{
    std::unique_lock<std::mutex> lock(ir->mtx);
    while(((ir->write_position + 1) % kItemRepositorySize) == ir->read_position) { // item buffer is full, just wait here.
        std::cout << "Producer is waiting for an empty slot...\n";
        (ir->repo_not_full).wait(lock);
    }

    (ir->item_buffer)[ir->write_position] = item;
    (ir->write_position)++;

    if (ir->write_position == kItemRepositorySize)
        ir->write_position = 0;

    (ir->repo_not_empty).notify_all();
    lock.unlock();
}

int ConsumeItem(ItemRepository *ir)
{
    int data;
    std::unique_lock<std::mutex> lock(ir->mtx);
    // item buffer is empty, just wait here.
    while(ir->write_position == ir->read_position) {
        std::cout << "Consumer is waiting for items...\n";
        (ir->repo_not_empty).wait(lock);
    }

    data = (ir->item_buffer)[ir->read_position];
    (ir->read_position)++;

    if (ir->read_position >= kItemRepositorySize)
        ir->read_position = 0;

    (ir->repo_not_full).notify_all();
    lock.unlock();

    return data;
}


void ProducerTask()
{
    for (int i = 1; i <= kItemsToProduce; ++i) {
        // sleep(1);
        std::cout << "Producer thread " << std::this_thread::get_id()
            << " producing the " << i << "^th item..." << std::endl;
        ProduceItem(&gItemRepository, i);
	}

	std::cout << "Producer thread " << std::this_thread::get_id()
		<< " is exiting..." << std::endl;
}

void ConsumerTask()
{
    bool ready_to_exit = false;
    while(1) {
        Sleep(1);
        std::unique_lock<std::mutex> lock(gItemRepository.item_counter_mtx);
		if (gItemRepository.item_counter < kItemsToProduce) {
			int item = ConsumeItem(&gItemRepository);
			++(gItemRepository.item_counter);
			std::cout << "Consumer thread " << std::this_thread::get_id()
				<< " is consuming the " << item << "^th item" << std::endl;
		}
		else 
			ready_to_exit = true;

		lock.unlock();
		if (ready_to_exit == true)
			break;
	}

    std::cout << "Consumer thread " << std::this_thread::get_id()
		<< " is exiting..." << std::endl;
}

void InitItemRepository(ItemRepository *ir)
{
    ir->write_position = 0;
    ir->read_position = 0;
    ir->item_counter = 0;
}

int main3()
{
    InitItemRepository(&gItemRepository);
    std::thread producer(ProducerTask);
    std::thread consumer1(ConsumerTask);
    std::thread consumer2(ConsumerTask);
    std::thread consumer3(ConsumerTask);
    std::thread consumer4(ConsumerTask);

    producer.join();
    consumer1.join();
    consumer2.join();
    consumer3.join();
    consumer4.join();
}


/////////////////////////////////////////////////////////////////////////////////////
// 多生产者-单消费者模型

// 与单生产者和单消费者模型不同的是，多生产者-单消费者模型中可以允许多个生产者同时向产品库中放入产品。
// 所以除了保护产品库在多个读写线程下互斥之外，还需要维护生产者放入产品的计数器，代码如下:

#include <unistd.h>

#include <cstdlib>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

static const int kItemRepositorySize  = 4; // Item buffer size.
static const int kItemsToProduce  = 10;   // How many items we plan to produce.

struct ItemRepository {
    int item_buffer[kItemRepositorySize];
    size_t read_position;
    size_t write_position;
    size_t item_counter;
    std::mutex mtx;
    std::mutex item_counter_mtx;
    std::condition_variable repo_not_full;
    std::condition_variable repo_not_empty;
} gItemRepository;

typedef struct ItemRepository ItemRepository;


void ProduceItem(ItemRepository *ir, int item) {
    std::unique_lock<std::mutex> lock(ir->mtx);
    while(((ir->write_position + 1) % kItemRepositorySize) == ir->read_position) { // item buffer is full, just wait here.
        std::cout << "Producer is waiting for an empty slot...\n";
        (ir->repo_not_full).wait(lock);
    }

    (ir->item_buffer)[ir->write_position] = item;
    (ir->write_position)++;

    if (ir->write_position == kItemRepositorySize)
        ir->write_position = 0;

    (ir->repo_not_empty).notify_all();
    lock.unlock();
}

int ConsumeItem(ItemRepository *ir)
{
    int data;
    std::unique_lock<std::mutex> lock(ir->mtx);
    // item buffer is empty, just wait here.
    while(ir->write_position == ir->read_position) {
        std::cout << "Consumer is waiting for items...\n";
        (ir->repo_not_empty).wait(lock);
    }

    data = (ir->item_buffer)[ir->read_position];
    (ir->read_position)++;

    if (ir->read_position >= kItemRepositorySize)
        ir->read_position = 0;

    (ir->repo_not_full).notify_all();
    lock.unlock();

    return data;
}


void ProducerTask() {
    bool ready_to_exit = false;
    while(1) {
        Sleep(1);
        std::unique_lock<std::mutex> lock(gItemRepository.item_counter_mtx);
        if (gItemRepository.item_counter < kItemsToProduce) {
            ++(gItemRepository.item_counter);
            ProduceItem(&gItemRepository, gItemRepository.item_counter);
            std::cout << "Producer thread " << std::this_thread::get_id()
                << " is producing the " << gItemRepository.item_counter
                << "^th item" << std::endl;
        } else 
			ready_to_exit = true;

        lock.unlock();
        if (ready_to_exit == true) 
			break;
    }
    std::cout << "Producer thread " << std::this_thread::get_id()
                << " is exiting..." << std::endl;
}

void ConsumerTask()
{
    static int item_consumed = 0;
    while(1) {
        Sleep(1);
        ++item_consumed;
        if (item_consumed <= kItemsToProduce) {
            int item = ConsumeItem(&gItemRepository);
            std::cout << "Consumer thread " << std::this_thread::get_id()
                << " is consuming the " << item << "^th item" << std::endl;
        } else 
			break;
    }

    std::cout << "Consumer thread " << std::this_thread::get_id()
                << " is exiting..." << std::endl;
}

void InitItemRepository(ItemRepository *ir)
{
    ir->write_position = 0;
    ir->read_position = 0;
    ir->item_counter = 0;
}

int main4()
{
    InitItemRepository(&gItemRepository);
    std::thread producer1(ProducerTask);
    std::thread producer2(ProducerTask);
    std::thread producer3(ProducerTask);
    std::thread producer4(ProducerTask);
    std::thread consumer(ConsumerTask);

    producer1.join();
    producer2.join();
    producer3.join();
    producer4.join();
    consumer.join();
}


///////////////////////////////////////////////////////////////////////////////////////
// 多生产者-多消费者模型

// 该模型可以说是前面两种模型的综合，程序需要维护两个计数器，分别是生产者已生产产品的数目和消费者已取走产品的数目。
// 另外也需要保护产品库在多个生产者和多个消费者互斥地访问。

#include <unistd.h>

#include <cstdlib>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

static const int kItemRepositorySize  = 4; // Item buffer size.
static const int kItemsToProduce  = 10;   // How many items we plan to produce.

struct ItemRepository {
    int item_buffer[kItemRepositorySize];
    size_t read_position;
    size_t write_position;
    size_t produced_item_counter;
    size_t consumed_item_counter;
    std::mutex mtx;
    std::mutex produced_item_counter_mtx;
    std::mutex consumed_item_counter_mtx;
    std::condition_variable repo_not_full;
    std::condition_variable repo_not_empty;
} ;

ItemRepository gItemRepository;


void ProduceItem(ItemRepository *ir, int item)
{
    std::unique_lock<std::mutex> lock(ir->mtx);
    while(((ir->write_position + 1) % kItemRepositorySize)
        == ir->read_position) { // item buffer is full, just wait here.
        std::cout << "Producer is waiting for an empty slot...\n";
        (ir->repo_not_full).wait(lock);
    }

    (ir->item_buffer)[ir->write_position] = item;
    (ir->write_position)++;

    if (ir->write_position == kItemRepositorySize)
        ir->write_position = 0;

    (ir->repo_not_empty).notify_all();
    lock.unlock();
}

int ConsumeItem(ItemRepository *ir)
{
    int data;
    std::unique_lock<std::mutex> lock(ir->mtx);
    // item buffer is empty, just wait here.
    while(ir->write_position == ir->read_position) {
        std::cout << "Consumer is waiting for items...\n";
        (ir->repo_not_empty).wait(lock);
    }

    data = (ir->item_buffer)[ir->read_position];
    (ir->read_position)++;

    if (ir->read_position >= kItemRepositorySize)
        ir->read_position = 0;

    (ir->repo_not_full).notify_all();
    lock.unlock();

    return data;
}

void ProducerTask()
{
    bool ready_to_exit = false;
    while(1) {
        Sleep(1);
        std::unique_lock<std::mutex> lock(gItemRepository.produced_item_counter_mtx);
        if (gItemRepository.produced_item_counter < kItemsToProduce) {
            ++(gItemRepository.produced_item_counter);
            ProduceItem(&gItemRepository, gItemRepository.produced_item_counter);
            std::cout << "Producer thread " << std::this_thread::get_id()
                << " is producing the " << gItemRepository.produced_item_counter
                << "^th item" << std::endl;
        } else 
			ready_to_exit = true;

        lock.unlock();
        if (ready_to_exit == true) 
			break;
    }
    std::cout << "Producer thread " << std::this_thread::get_id()
                << " is exiting..." << std::endl;
}

void ConsumerTask()
{
    bool ready_to_exit = false;
    while(1) {
        Sleep(1);
        std::unique_lock<std::mutex> lock(gItemRepository.consumed_item_counter_mtx);
        if (gItemRepository.consumed_item_counter < kItemsToProduce) {
            int item = ConsumeItem(&gItemRepository);
            ++(gItemRepository.consumed_item_counter);
            std::cout << "Consumer thread " << std::this_thread::get_id()
                << " is consuming the " << item << "^th item" << std::endl;
        } else 
			ready_to_exit = true;

        lock.unlock();
        if (ready_to_exit == true) 
			break;
    }
    std::cout << "Consumer thread " << std::this_thread::get_id()
                << " is exiting..." << std::endl;
}

void InitItemRepository(ItemRepository *ir)
{
    ir->write_position = 0;
    ir->read_position = 0;
    ir->produced_item_counter = 0;
    ir->consumed_item_counter = 0;
}

int main4()
{
    InitItemRepository(&gItemRepository);
    std::thread producer1(ProducerTask);
    std::thread producer2(ProducerTask);
    std::thread producer3(ProducerTask);
    std::thread producer4(ProducerTask);

    std::thread consumer1(ConsumerTask);
    std::thread consumer2(ConsumerTask);
    std::thread consumer3(ConsumerTask);
    std::thread consumer4(ConsumerTask);

    producer1.join();
    producer2.join();
    producer3.join();
    producer4.join();

    consumer1.join();
    consumer2.join();
    consumer3.join();
    consumer4.join();
}



int main(){
	
	InitItemRepo(&gItemRepo); 
	thread producer(ProducerTask); 
	thread consumer(ConsumerTask); 

	producer.join(); 
	consumer.join(); 




	vector<int> b = { 4, 1, -9, 0, INT_MAX }; 


	//TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
		3       8
	1    4   7    9
	*/



	///////////////////////////
	auto start = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	cout << endl << microseconds << " microseconds elapsed..." << endl;
}

