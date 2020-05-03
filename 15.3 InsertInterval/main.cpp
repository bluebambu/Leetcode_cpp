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

struct Interval {
int start;
int end;
Interval() : start(0), end(0) { }
Interval(int s, int e) : start(s), end(e) { }
};

class Solution
{
public:
    vector<Interval> insert(vector<Interval> &intervals, Interval newInterval)
    {

    }
};


int main()
{
    Solution a;

    vector<int> intset {1,2,3};

    auto b = a.permute3(intset);

    for(auto i:b)
    {for(auto j: i)
            cout<<j<<" ";
     cout<<endl;
    }
}
