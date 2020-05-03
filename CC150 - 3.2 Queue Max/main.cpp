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

inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}
inline float min(float a, float b) {return a<b?a:b;}


class MaxQueue
{
public:
    queue<int> q;
    deque<int> qmax;

    MaxQueue() {}

    void push(int a){
        q.push(a);
        while(qmax.size() && a > qmax.back()){
            qmax.pop_back();
        }
        qmax.push_back(a);
    }

    int max(){return qmax.front();}

    void pop(){
        if(q.front() == qmax.front())
            qmax.pop_front();
        q.pop();
    }

    int size(){ return q.size(); }
};

int main()
{
    MaxQueue a;

    for(auto i : {14,5,1,2,11,1,7,8,5,2,1})
        a.push(i);

    while(a.size()){
        cout<<a.max()<<" ";
        a.pop();
    }


}
