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
    vector<int> alphabetic(int n) {
        vector<int> result;
        for(int i=1; i<=9; ++i){
            int first = i, f_max=i;
            while(f_max < n) f_max*=10;
            f_max = f_max == i ? i : f_max/10;

            if(f_max!=i){
                for(; f_max>i; f_max/=10){
                    int second = f_max;
                    for(int j=0; second+j<n && second+j > f_max/10; ++j){
                        result.push_back(second + j);
                    }
                }
            }else
                result.push_back(i);
        }
        return result;
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

    auto b=a.alphabetic(23);

    for(auto i:b)
        cout<<i<<" ";

}
