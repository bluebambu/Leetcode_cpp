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

class Solution2 {
public:
    /// lc passed
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        if(!n)  return result;
        string path;
        dfs(n, 0, 0, path, result);
        return result;
    }

    void dfs(int n, int left, int right, string& path, vector<string>& result){
        if(left==n && right==n){
            result.push_back(path);
            return;
        }
        if(left<=n){
            path.push_back('(');
            dfs(n, left+1, right, path, result);
            path.pop_back();
        }
        if(right<=n && right<left){
            path.push_back(')');
            dfs(n, left, right+1, path, result);
            path.pop_back();
        }
    }
};


class Solution {
 public:
vector<string> generateParenthesis(int n) {
    vector<string> result;
    string str("(");
    result.push_back(str);
    vector<int> left({1});
    for(int pos = 1;pos < 2*n;++pos) {
            // pos 是现在括号的长度，从1 ～ 5，
        int tmp = left.size();
        // 也可以是 result.size()
        for(int i = 0;i < tmp;++i) {
            if(left[i] < n) {
                if(pos - left[i] < left[i]) {
                // pos - left[i]   means that when left[i]<n,
                // the number of ')' in the current string.
                    result.push_back(result[i] + ')');
                    left.push_back(left[i]);
                }
                result[i] += '(';
                left[i]++;
            }
            else {
                result[i] += ')';
                continue; // 多余
            }
        }
    }
    return result;
}

///////////////////////////////////////////////////////////////////
vector<string> generateParenthesis2(int n) {
    vector<string> res;
    dfs(n, n, "", res);
    return res;
}

void dfs(int l, int r, string path, vector<string>& res) {
    if (l < 0 || r < 0 || l > r)
        return;
    if (l == 0 && r == 0)
        res.push_back(path);
    dfs(l-1, r, path+'(', res);
    dfs(l, r-1, path+')', res);
}



};


int main()
{
    Solution a;

    vector<int> intset {1,2,3};

    auto b = a.generateParenthesis2(3);

    for(auto i:b)
    {for(auto j: i)
            cout<<j;
     cout<<endl;
    }


}
