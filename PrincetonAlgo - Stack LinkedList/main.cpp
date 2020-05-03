#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>
#include <exception>


using namespace std;

template<typename T>
struct LL{
    T val;
    LL* next;
    LL(T x):val(x),next(nullptr) {}
};


template<typename T>
class StackLL{
private:
    LL<T> *top;
    int capacity;

public:
    StackLL():capacity(0),top(nullptr) {}

    void push(T item){
        LL<T> *tmp = new LL<T>(item);
        tmp->next = top;
        top=tmp;
        ++capacity;
    }

    int size(){
        return capacity;
    }

    T pop(){
        if(capacity==0)
            throw exception::exception("Nothing to pop!!");
        LL<T> *tmp=top;
        top=top->next;
        T tmpv = tmp->val;
        delete tmp;
        --capacity;
        return tmpv;
    }
};



int main()
{
	StackLL<int> a;

	for(int i=1; i<8; ++i){
        a.push(i*i+4);
        cout<<a.size()<<" ";
        //int b=a.pop();
        //cout<<b<<endl;
	}

	try{
    for(int i=1; i<9; ++i){
        a.pop();
        cout<<a.size()<<" ";
        //int b=a.pop();;
        //cout<<b<<endl;
	}
	}catch(exception& e){
        cerr<<e.what();
	}






}
