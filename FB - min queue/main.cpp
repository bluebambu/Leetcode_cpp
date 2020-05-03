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


struct TreeNode
{
    TreeNode(int a):val(a), left(nullptr), right(nullptr) {}
    TreeNode(int a, TreeNode* x, TreeNode* y):val(a), left(x), right(y) {}
    TreeNode():val(0), left(nullptr), right(nullptr) {}

    int val;
    TreeNode *left;
    TreeNode *right;

};

/// implemented by 2 queues ///
class minQueue
{
private:
    queue<int> main, mincheck;
public:
    minQueue() {}

    void push(int i){
        main.push(i);
        mincheck.push(i);
        if(i<mincheck.front())
            while(mincheck.front()>i)
                mincheck.pop();
        else{
            while(mincheck.front()!=i){
                if(mincheck.front()<=i)
                    mincheck.push(mincheck.front());
                mincheck.pop();
            }
            mincheck.push(i);
            mincheck.pop();
        }
    }

    void pop(){
        if(main.front()==mincheck.front())
            mincheck.pop();
        main.pop();
    }

    int front(){
        return main.front();
    }

    int checkMin(){
        return mincheck.front();
    }
};

int main()
{
    minQueue a;

    for(auto i:{4,6,5,7})
        a.push(i);

    cout<<a.front()<<" "<<a.checkMin();
    a.pop();
    a.pop();
    a.pop();
    a.pop();

    for(auto i:{1,5,-1})
        a.push(i);
    cout<<a.front()<<" "<<a.checkMin();

}
