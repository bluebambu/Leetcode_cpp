#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>
#include <utility>

using namespace std;

inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}
inline float min(float a, float b) {return a<b?a:b;}


template<typename Object>
class vector
{
private:
    int capacity;
    int size;
    Object* pobj;
public:
    vector(int a):size(a), capacity(2*a) {
        pobj = new Object[capacity];
    }

    vector(int a, Object b):size(a), capacity(2*a) {
        pobj = new Object[capacity];
        for(int i=0; i<size; ++i)
            pobj[i] = b;
    }

    int size(){return size; }
    int capacity() {return capacity; }
    Object back() {return pob[size-1];}

    void reserve(int a){
        if(a <= capacity())
            return;
        Object* newArr = new Object[a];
        for(int i=0; i<size; ++i)
            newArr[i] = pobj[i];
        swap(pobj, newArr);
        delete [] newArr;
        capacity = a;
    }

    void resize(int a){
        if(a > capacity){
            reserve( a * 2);
        }
        size = a;
    }

    void push_back(Object a){
        if(size == capacity)
            reserve(2*capacity);
        pobj[size++] = a;
    }


};

int main()
{


}
