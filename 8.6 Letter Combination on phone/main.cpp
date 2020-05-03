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

class Solution2 {
    vector<string> map{ "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
public:
    /// lc passed, iterative solution
    ///
    vector<string> letterCombinations(string digits) {
        vector<string> result, buffer;
        if(digits.empty()) return result;

        result.push_back(string());
        for(int i=0; i<digits.size(); ++i){
            for(int j=0; j<result.size(); ++j){
                string cur = result[j];

                for(int k=0; k<map[digits[i]-'0'-1].size(); ++k){
                    string tmp=cur;
                    tmp.push_back(map[digits[i]-'0'-1][k]);
                    buffer.push_back(tmp);
                }
            }
            result=buffer;
            buffer.clear();
        }
        return result;
    }
};


class Solution
{
public:
    const vector<string> keyboard {
            " ", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
    };  // 0 ~ 9

    vector<string> letterCombinations(string digits) {
        vector<string> result;
        string path;
        if(digits.empty()) return result;
        dfs(digits, 0, path, result);
        return result;

    }

    void dfs(string& digits, int location, string path, vector<string>& result){
        if(path.size()==digits.size()){
            result.push_back(path);
            return;
        }

        for(auto i:keyboard[digits[location]-'0']){
            dfs(digits, location+1, path+i, result);
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
