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


class Solution
{
public:
    string compression(string s){
        string result;
        for(int i=0; i<s.size(); ){
            char c=s[i];
            int j=i;
            while(s[j]==c && j<s.size())
                ++j;
            int num = j-i;
            result += c;
            result += '0'+num;
            i=j;
        }
        return result.size() > s.size() ? s : result;
    }

};

int main()
{
    Solution a;

    cout<<a.compression("abcd");


}
