#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>
#include <ctime>
#include <time.h>

using namespace std;

inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}
inline float min(float a, float b) {return a<b?a:b;}

struct node{
    time_t timer;
    string info;
    node(string x):info(x) {time(&timer);}
};

class RateLimiter
{
public:
    RateLimiter(int cap):capacity(cap) {}

    queue<node*> q;
    int capacity;
    time_t oldest = 0;

    void push(node* n){
        if(q.size()==0){
            q.push(n);
            return;
        }

        oldest = q.front()->timer;
        time_t diff = n->timer - oldest;


        if(q.size()<capacity){
            q.push(n);
            oldest = n->timer;
            if(diff > 0.01) q.pop();
        }else{
            if(diff > 0.01){
                q.pop();
                q.push(n);
                oldest = n->timer;
            }else{
                cout<<"Full in the queue!";
            }
        }
    }

    void prt(){
        while(q.size()){
            cout<<q.front()->info<<endl;
            q.pop();
        }
    }

};

int main()
{
    RateLimiter a(10);

    for(int i=0; i<11; ++i){
        char c = 'a'+i ;
        string s(2,c);
        node* p = new node(s);
        a.push(p);
    }

    cout<<endl<<endl;
    a.prt();



}
