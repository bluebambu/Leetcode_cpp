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
/////////////// Leetcode passed, 20ms /////////////////////////////
    vector<vector<string>> partition(string s) {
        vector<vector<string>> result;
        vector<string> path;
        if(s.empty()) return result;
        dfs(s, 0, path, result);
        return  result;
    }

    void dfs(string& s, int start, vector<string>& path, vector<vector<string>>& result){
        if(start==s.size()){
            result.push_back(path);
            return;
        }

        for(int i=start; i<s.size(); ++i){
            string temp=s.substr(start, i-start+1);
            if(palindrome(temp)){
                path.push_back(temp);
                dfs(s, i+1, path, result);
                path.pop_back();
            }
        }
    }

    bool palindrome(string& temp){
        for(int i=0, j=temp.size()-1; i<j; ++i, --j){
            if(temp[i]!=temp[j])
                return false;
        }
        return true;
    }


///////////////////  DFS + DP， 用 dp 保存状态  //////////////////////
///  一个长度为n的字符串，有 n-1 个地方可以砍断，每个地方可断可不断，因此复杂度为 O(2^{n-1})

    vector<vector<string>> partition2(string s) {
        int n=s.size();
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        for(int i=0; i<n; ++i){
            for(int j=0; j<=i; ++j){
                dp[j][i] = s[i]==s[j] && ((i-j<2) || dp[j+1][i-1]);
                // 注意 i j 的位置
            }
        }

        vector<vector<string>> result;
        vector<string> path;

        dfs(s, 0, dp, path, result);
        return result;
    }

    void dfs(string& s, int start, vector<vector<bool>>& dp, vector<string>& path, vector<vector<string>>& result){
        if(start==s.size()){
            result.push_back(path);
            return;
        }

        for(int i=start; i<s.size(); ++i){
                if(dp[start][i]){
                    path.push_back(s.substr(start, i-start+1));
                    dfs(s, i+1, dp, path, result);
                    path.pop_back();
                }
        }
    }

};

int main()
{
    Solution a;

    string b="a";

    auto c=a.partition2(b);
//
////    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1),
//                                                    new TreeNode(4)),
//                                    new TreeNode(8, new TreeNode(7),
//                                                    new TreeNode(9)));
//    /*      6
//        3       8
//     1    4   7    9
//
//    */
//
//    a.flatten(tree);



}
