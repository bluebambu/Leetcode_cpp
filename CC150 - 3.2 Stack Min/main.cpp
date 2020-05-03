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


class StackMin
{public:
    vector<int> st;
    vector<int> min;

    StackMin() {}

    void push_back(int x){
        st.push_back(x);
        if(min.empty())
            min.push_back(x);
        else if(min.back() > x)
            min.push_back(x);
        else
            min.push_back(min.back());
    }

    void pop(){
        st.pop_back();
        min.pop_back();
    }

    int theMin(){
        return min.back();
    }

    int size(){
        return st.size();
    }
};

int main()
{
    StackMin a;

    for(int i=9;i>=0; --i)
        a.push_back(abs(i-5));

    for(auto i:a.min)
        cout<<i<<" ";
    cout<<endl;

    for(int i=9; i>=0; --i){
        cout<<a.theMin();
        a.pop();

    }


}
