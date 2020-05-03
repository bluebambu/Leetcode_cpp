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
    /// lc passed
    bool canJump(vector<int>& nums) {
        if(nums.empty()) return true;
        int farthest=nums[0];

        for(int i=0; i<nums.size(); ++i){
            if(farthest<i)
                return false;
            if(farthest < i+nums[i])
                farthest=i+nums[i];
            if(farthest>=nums.size()-1)
                return true;
        }

        return false;
    }
    /////////////////////////////////////

    bool canJump(vector<int>& nums) {
        int right=0;

        for(int i=0; i<nums.size(); ++i){
            if(right>=i)
                right=max(right, i+nums[i]);
            else{
                return false;
            }
        }
        return true;
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

    a.flatten(tree);


}
