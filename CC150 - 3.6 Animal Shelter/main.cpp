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

using namespace std;

inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}
inline float min(float a, float b) {return a<b?a:b;}

struct animal{
    int timestamp;
};

struct cat : public animal{
    int catNum;
};

struct dog : public animal{
    int dogNum;
};


class Solution
{
public:
    void flatten(TreeNode* root) {

        }

};

int main()
{
}
