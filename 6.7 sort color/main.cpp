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
    /// 这样好理解些， lc pass
    void sortColors(vector<int>& nums) {
        int i=0, j=nums.size()-1, k=i;

        while(k<=j){
            if(nums[k]==0) ///  0 和 2 可以互换位置
                swap(nums[i++], nums[k]);

            if(nums[k]==2)
                swap(nums[j--], nums[k]);

            if( k<i || nums[k]==1)
                ++k;
        }
    }


    /// passed, 太tricky了  不稳定
    void sortColors(vector<int>& nums) {
        int i=0, j=nums.size()-1, k=i;

        while(k<=j){
            if(nums[k]==0) /// 如果 0 和 2 互换位置， 都会出错
                swap(nums[i++], nums[k]);

            if(nums[k]==2)
                swap(nums[j--], nums[k]);
            else
                ++k;
        }
    }

    /// leetcode passed, 2 pointers ////
    void sortColors(vector<int>& nums) {
        int red=0, blue=nums.size()-1;

        for(int i=0; i<nums.size(); ++i){
                /// while 条件非常重要！ 考虑 i==red的情况。
                /// 同时要注意 i 可以 等于 blue 和 red
            while(nums[i]!=1 && i <=blue && i>=red){
                if(nums[i]==0)
                    swap(nums[i], nums[red++]);
                if(nums[i]==2)
                    swap(nums[i], nums[blue--]);
            }
        }
    }

    /// leetcode passed, helper array  ////////
    void sortColors(vector<int>& nums) {
        vector<int> count(3, 0);
        for(auto i:nums)
            ++count[i];

        int j=0;
        for(int i=0; i<count.size(); ++i)
            for(int k=0; k<count[i]; ++k)
                nums[j++]=i;
    }


    /// leetcode passed, partition ///
    void sortColors(vector<int>& nums) {
        int i=0, j=0, idx=0;

        /// 注意这里是 或， 不是 且
        for(; i<nums.size() || j<nums.size(); ++j){
            if(j==nums.size()){
                j=i;
                idx++;
            }

            if(nums[j]==idx)
                swap(nums[i++], nums[j]);
            cout<<j;
        }
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
