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

class Solution {
public:
    /////////////// leetcode passed  ///////////////////
    int maximalRectangle(vector<vector<char>>& matrix) {  /// 注意matrix的元素是 char ！！
        if(matrix.empty()) return 0;

        int m=matrix.size(), n=matrix[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));

        for(int i=0; i<m; ++i){
            for(int j=n-1; j>=0; --j){
                if(j==n-1)
                    dp[i][j] = matrix[i][j]=='1';
                else
                    dp[i][j] = matrix[i][j]=='1' ? dp[i][j+1]+1 : 0;
            }
        }

        int maxarea=0;
        for(int i=0; i<m; ++i){
            for(int j=0; j<n; ++j){
                int k=i;
                int minw=dp[k][j];
                for(;k<m && matrix[k][j]!='0'; ++k){
                    minw = min(minw, dp[k][j]);  /// 写法要谨慎， 先求min_width, 再求面积。 面积每一步都要更新。
                    maxarea = max(maxarea, minw*(k-i+1));
                }
            }
        }
        return maxarea;
    }

////////// leetcode passed, n^2 ///////////////////////
    int maximalRectangle(vector<vector<char>>& matrix) {
        if(matrix.empty() || matrix[0].empty()) return 0;

        vector<int> dp(matrix[0].size(), 0);
        int result=0;

        for(int i=0; i<matrix.size(); ++i){
            for(int j=0; j<matrix[i].size(); ++j)
                dp[j] = matrix[i][j]=='0' ? 0 : (dp[j] + matrix[i][j] -'0');

            dp.push_back(0);

            stack<int> st;

            int tmp_max=0;
            for(int k=0; k<dp.size(); ++k){
                if(st.empty() || dp[k] > dp[st.top()])
                    st.push(k);
                else{
                    while(!st.empty() && dp[st.top()] > dp[k]){
                        int cur_top = st.top();
                        st.pop();
                        int left = st.empty() ? -1 : st.top();
                        tmp_max = max(tmp_max, (k-left-1)*dp[cur_top]);
                    }
                    st.push(k);
                }
            }
            result = max(result, tmp_max);
            dp.pop_back();
        }

        return result;
    }
};


int main()
{
	Solution a;

    cout<<a.maximalRectangle({ {0} });
}
