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
#include <climits>

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
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> matrix(n, vector<int>(n, 0));
        int begin=0, end=n-1;
        int num=1;

        while(begin<=end){
            for(int i=begin; i<=end; ++i) matrix[begin][i]=num++;
            for(int i=++begin; i<=end; ++i) matrix[i][end]=num++;
            for(int i=--end; i>=begin-1; --i) matrix[end+1][i]=num++;
            for(int i=end; i>=begin; --i) matrix[i][begin-1]=num++;
        }
        return matrix;
    }


};

int main()
{
    Solution a;

//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1),
                                                    new TreeNode(4)),
                                    new TreeNode(8, new TreeNode(7),
                                                    new TreeNode(9)));
    /*      6
        3       8
     1    4   7    9

    */
    auto b=a.generateMatrix(3);


    for(auto i:b)
        for(auto j:i)
            cout<<j<<" ";

    cout<<endl<<bitset<8*sizeof(int)>(-2147483648);
    int dividend = -2147483648, divisor=-1;
    cout<<endl<< ((dividend ^ divisor)>>31);
    cout<<LONG_MAX<<" "<<LLONG_MAX;
}
