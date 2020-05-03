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
    TreeNode* SortedArrayToBST(vector<int> sorted)
    {
        return BSTRoot(sorted.begin(), sorted.end());
    }

    TreeNode* BSTRoot(vector<int>::iterator abegin, vector<int>::iterator aend)
    {
        if(abegin == aend) return new TreeNode(*abegin);
        int len = aend - abegin;
        auto mid = abegin + len/2;

        TreeNode* root = new TreeNode(*mid);

        root->left = BSTRoot(abegin, mid);
        root->right = BSTRoot(mid+1, aend);

        return root;
    }

    ///////////////////////////////////////////////

    TreeNode* sortedArrayToBST(vector<int>& nums) {
        if(nums.empty()) return nullptr;
        return sortarray(nums, 0, nums.size()-1);
    }

    TreeNode* sortarray(vector<int>& nums, int start, int end){
        if(start>end) return nullptr;
        if(start==end) return new TreeNode(nums[start]);

        int mid = start + (end-start)/2;
        TreeNode* cur=new TreeNode(nums[mid]);
        cur->left = sortarray(nums, start, mid-1);
        cur->right= sortarray(nums, mid+1, end);
        return cur;
    }

    ///////////////////////////////////////////////////

    // 不成功！！！
    TreeNode* sortedArrayToBST4(vector<int>& nums) {
        if(nums.empty()) return nullptr;

        typedef pair<TreeNode*, pair<int, int>> unite;
        vector<unite> stack;

        stack.push_back(unite(nullptr, pair<int, int>(0, nums.size()-1)));

        unite cur=stack.back();
        unite& head = cur;

        while(stack.size()){
            cur=stack.back();
            stack.pop_back();

            int start = cur.second.first;
            int end = cur.second.second;
            int mid = start+(end-start)/2;

            if(start>end){
                continue;
            }

            if(start==end){
                (cur.first)=new TreeNode(nums[start]);
                continue;
            }

            (cur.first)=new TreeNode(nums[mid]);

            unite left(nullptr, pair<int, int>(start, mid-1));
            unite right(nullptr, pair<int, int>(mid+1, end));

            (cur.first)->left = left.first;
            (cur.first)->right = right.first;

            stack.push_back(right);
            stack.push_back(left);
        }

        return head.first;
    }
};

int main()
{
    Solution a;

    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
    /*      6
        3       8
     1    4   7    9

    */
    vector<int> c = {1,3};

    auto b = a.sortedArrayToBST4(c);

    cout<<b->val;
}
