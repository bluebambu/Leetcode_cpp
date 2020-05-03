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
///////////////// 根本算不出来，当 vector<int> coins= {3,7,405,436};   int money = 8839; 时， 太多步骤了 ////////////////////////
    int coinChange(vector<int>& coins, int amount) {
        int result=INT_MAX;
        vector<int> path;
        dfs(coins, coins.size()-1, amount, path, result);
        result = (result==INT_MAX)? -1 : result;
        return result;
    }

    void dfs(vector<int>& coins, int idx, int remain, vector<int> path, int& result){
        if(remain==0){
            result=min(int(path.size()), result);
            return;
        }

        if(idx<0) return;
        if(remain<0) return;

        int n=remain/coins[idx];
        for(int i=0; i<=n; ++i){
            dfs(coins, idx-1, remain-i*coins[idx], path, result);
            path.push_back(coins[idx]);
        }
    }

//////////////////////根本算不出来，当 vector<int> coins= {3,7,405,436};   int money = 8839; 时， 太多步骤了 /////////////////////////////////////////////////////////////
    int coinChange2(vector<int>& coins, int amount) {
        int result=INT_MAX;
        vector<int> path;
        dfs2(coins, coins.size()-1, amount, 0, result);
        result = (result==INT_MAX)? -1 : result;
        return result;
    }

    void dfs2(vector<int>& coins, int idx, int remain, int len, int& result){
        if(remain==0){
            result=min(len, result);
            return;
        }

        if(idx<0) return;
        if(remain<0) return;

        int n=remain/coins[idx];
        for(int i=n; i>=0; --i){
            dfs2(coins, idx-1, remain-i*coins[idx], len+i, result);
        }
    }
/////////////////////////////////////////////////////////////////////////////////////////
    int coinChange3(vector<int>& coins, int amount){
        vector<int> DP(amount+1, INT_MAX-1);
        // DP[i]: the result when amount = i;
        int n = coins.size(), i, j;
        DP[0] = 0; // no coins when amount = 0
        for(i=1; i<=amount; i++)
        {
            for(j=0; j<n; j++)
            {
                if(i-coins[j]>=0)
                    DP[i] = min(DP[i], DP[i-coins[j]]+1);
            }
        }

        if(DP[amount] == INT_MAX-1)
            return -1;
        else
            return DP[amount];
    }
////////////////// Passed hackerank ////////////////////
    int main() {
        /* Enter your code here. Read input from STDIN. Print output to STDOUT */
        int amount, n, tmp;
        cin>>amount>>n;
        vector<int> C;
        while(cin>>tmp) C.push_back(tmp);

        vector<vector<long>> dp(n+1, vector<long>(amount+1, 0)); // long 防止溢出
        for(int i=0; i<=n; ++i)         // dp 与 vector 的lable不一样！ 要注意调整
            dp[i][0]=1;  //  初始条件很必要！！

        for(int i=1; i<=n; ++i){
            for(int j=0; j<=amount; ++j){
                long x = (j-C[i-1])>=0 ? dp[i][j-C[i-1]] : 0; // dp 与 vector 的lable不一样！ 要注意调整
                long y = (i-1)>=0      ? dp[i-1][j]      : 0;
                dp[i][j]=x+y;
            }
        }

        cout<<dp[n][amount];
    }


    ////////////////// Passed hackerank ////////////////////
    int main() {
        /* Enter your code here. Read input from STDIN. Print output to STDOUT */
        int amount, n, tmp;
        cin>>amount>>n;
        vector<int> C;
        while(cin>>tmp) C.push_back(tmp);

        vector<long> dp(amount+1, (long)0);
        dp[0]=1;

        for(int i=1; i<=n; ++i){
            for(int j=1; j<=amount; ++j){
                long x= (j-C[i-1]) >= 0 ? dp[j-C[i-1]] : 0 ;
                dp[j] += x;
            }
        }

        cout<<dp[amount];

        return 0;
    }
};

int main()
{
    Solution a;

    vector<int> coins= {3,7,405,436};
    int money = 8839;

    cout<<a.coinChange3(coins, money);
}
