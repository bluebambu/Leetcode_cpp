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
    /////////// passed  //////
    void merge2(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        if(nums1.empty()) {nums1=nums2; return;}
        if(nums2.empty())   return;

        int i=m+n-1,
                j=m-1,
                k=n-1;

        while(k>=0){

            nums1[i--] = nums1[j] > nums2[k] ? nums1[j--] : nums2[k--];


            }
        }
    }

    ////////////////
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        if(n==0) return;

        int i_merge = m+n-1, i_1=m-1, i_2=n-1;

        for(;i_1>=0 && i_2>=0; ){
            if(nums1[i_1]>nums2[i_2]){
                nums1[i_merge--]=nums1[i_1--];
            }else{
                nums1[i_merge--]=nums2[i_2--];
            }
        }

        if(i_1<0)
            while(i_merge>=0)
                nums1[i_merge--]=nums2[i_2--];
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
