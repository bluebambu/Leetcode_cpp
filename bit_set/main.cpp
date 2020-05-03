#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>
#include <bitset>

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


class Solution
{
public:
    void flatten(TreeNode* root) {

        }

};

int main()
{
    const int max_scan = 5000000;

    bitset<max_scan> bitmap;

    for(int i=0; i<100; ++i)
        cout<<(bitmap[i] = i%9);

    bitmap.reset();

    for(int i=0; i<100; ++i)
        cout<<bitmap[i];


}
