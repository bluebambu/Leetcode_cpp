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
    /////////// leetcode passed  ///////////////
    int maxProfit(vector<int>& prices) {
        if(prices.size()<2) return 0;

        vector<int> left(prices.size(), 0);
        vector<int> right(prices.size(), 0);

        int profit=0;
        int valley=prices[0], peak=prices[prices.size()-1];

        for(int i=1; i<prices.size(); ++i){
            valley = min(valley, prices[i]);
            left[i] = max(left[i-1], prices[i]-valley); // left[i] 与 left[i-1] 比较
            /// 不能写成 left[i] = prices[i]-valley， 因为这样意味着， left 区间 和 right区间 总有一个交汇点， 这个不符合题意！！
        }

        for(int i=prices.size()-2; i>=0; --i){
            peak = max(peak, prices[i]);
            right[i] = max(right[i+1], peak-prices[i]);
        }

        for(int i=0; i<prices.size(); ++i){
            profit=max(profit, left[i]+right[i]);
        }

        return profit;
    }

    //////// leetcode passed ////////////////
        int maxProfit2(vector<int>& prices) {
        if(prices.size()<2) return 0;

        vector<int> left(prices.size(), 0);
        vector<int> right(prices.size(), 0);

        int minimum=INT_MAX, cur=0;

        for(int i=0; i<prices.size();++i){
            minimum=min(prices[i],minimum);
            cur=max(cur, prices[i]-minimum);  // 直接重复 sell stock I 的答案
            left[i]=cur;
        }

        minimum=INT_MIN, cur=0;

        for(int i=prices.size()-1; i>=0;--i){
            minimum=max(prices[i],minimum);
            cur=max(cur, minimum-prices[i]);
            right[i]=cur;
        }

        int result=0;

        for(int i=0; i<prices.size();++i){
            result=max(result, left[i]+right[i]);
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

//    a.flatten(tree);

    cout<<-4%3;
}
