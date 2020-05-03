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


class Solution
{
public:
    //////////// leetcode passed ///////////////////////////
    /// 注意  dp[0][0] 应该指 s1  s2 都没有提供元素， 所以 dp 的 size 应该是 dp[n+1][m+1]
    /// 如果用 dp[n][m] , 则 dp[0][0] 为 s1  s2 的首元素都进去了 s3， 与本意不符合！！
    bool isInterleave(string s1, string s2, string s3) {
        int n=s1.size(), m=s2.size(), L=s3.size();
        if(L!=n+m) return false;
        if(s1.empty()) return s2==s3;
        if(s2.empty()) return s1==s3;

        vector<vector<bool>> dp(n+1, vector<bool>(m+1, false));

        for(int i=0; i<n+1; ++i){
            for(int j=0; j<m+1; ++j){
                if(i==0 && j==0)
                    dp[0][0]=true;
                else if(i==0 && j!=0)
                    dp[i][j] =  dp[i][j-1] && s2[j-1]==s3[j-1];
                else if(j==0 && i!=0)
                    dp[i][j] =  dp[i-1][j] && s1[i-1]==s3[i-1];
                else
                    dp[i][j] =  (dp[i-1][j] && s1[i-1]==s3[i+j-1]) || (dp[i][j-1] && s2[j-1]==s3[i+j-1]);
            }
        }
        return dp[n][m];
    }

    ///////////// 转换成一维数组 ， pass ////////////////
    //
    //                  (i, j-1)  <-  (i,  j)
    //                                   |
    //                                   V
    //                                (i-1, j)
    bool isInterleave(string s1, string s2, string s3) {
        int n=s1.size(), m=s2.size(), L=s3.size();
        if(L!=n+m) return false;
        if(s1.empty()) return s2==s3;
        if(s2.empty()) return s1==s3;

       vector<bool> dp(m+1, false);

        for(int i=0; i<n+1; ++i){
            for(int j=0; j<m+1; ++j){
                if(i==0 && j==0)
                    dp[j]=true;
                else if(i==0 && j!=0)
                    dp[j]= dp[j-1] && s2[j-1]==s3[j-1];
                else if(j==0 && i!=0)
                    dp[j]= dp[j] && s1[i-1]==s3[i-1];
                else
                    dp[j]= (dp[j]&& s1[i-1]==s3[i+j-1]) || (dp[j-1] && s2[j-1]==s3[i+j-1]);
            }
        }
        return dp[m];
    }
};


int main()
{
	Solution a;


}
