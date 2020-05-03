#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;

template<typename T>
struct LL{
    LL(T x):val(x), next(nullptr) {}
    T val;
    LL<T> *next;
};

template<typename T>
class QueueLL{
private:
    LL<T> *front, *tail;
    int size;
public:
    QueueLL(): front(nullptr),tail(nullptr),size(0) {}

    void push(T item){
        LL<T>* tmp = new LL<T>(item);
        tmp->next = tail;
        tail = tmp;
        size++;
        if(size==1)
            front=tail;
    }

    T top(){
        if(size==0)
           throw runtime_error("Nothing to pop!!");
        return front->val;
    }

    void pop(){
        if(size==0)
            throw runtime_error("Nothing to pop!!");
        LL<T>* tmp = front;
        front = front->next;
        delete tmp;
        --size;
    }

    int cap(){
        return size;
    }
};


int main()
{
	QueueLL<int> q;

	for(int i=0; i<8; ++i){
        q.push(i*2);
        cout<<q.cap()<<" ";
        // q.pop();
        cout<<q.top()<<" ";
	}
	q.pop();

}
