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
    /// passed, 80ms
    int minCut(string s) {
        if(s.empty()) return 0;
        int n=s.size();
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        vector<int> mincut(n, 0);

        for(int i=0; i<n; ++i){
            mincut[i] = i;
            for(int j=i; j>=0; --j){

                if(s[j]==s[i] && (i-j<2 || dp[j+1][i-1])){
                    dp[j][i]=true;

                    if(j==0)
                        mincut[i]=0;
                    else if(mincut[i] > mincut[j-1]+1)
                        mincut[i] = mincut[j-1]+1;
                }
            }
        }
        return mincut[n-1];
    }
};


class Solution
{
public:
/////// leetcode passed ,  160ms /////////
    int minCut(string s) {
        if(s.size()<2) return 0;

        vector<vector<bool>> dp(s.size(), vector<bool>(s.size(), false));

        for(int j=0; j<s.size(); ++j){
            for(int i=0; i<=j; ++i){
                dp[i][j] = i==j? true : ( s[i]==s[j] ? (dp[i+1][j-1] || i+1==j) : false) ;
            }
        }

        vector<int> pdp(s.size(), 0);

        for(int i=s.size()-1; i>=0; --i){
            int mindp=INT_MAX;

            for(int j=i; j<=s.size()-1; ++j){
                if(dp[i][j]){
                    if(j==s.size()-1)
                        mindp=0;
                    else
                        mindp=min(mindp, pdp[j+1]+1);
                }
            }
            pdp[i]=mindp;
        }

        return pdp[0];
    }

    /////  better solution, combine 2 loops ,    ////////////
    int minCut(string s) {
        if(s.empty()) return 0;
        int n = s.size();
        vector<vector<bool>> pal(n,vector<bool>(n,false));
        vector<int> d(n);
        for(int i=n-1;i>=0;i--)
        {
            d[i]=n-i-1;
            for(int j=i;j<n;j++)
            {
                if(s[i]==s[j] && (j-i<2 || pal[i+1][j-1])) /// trick： 当 i+1 > j-1 时， pal 都是false的.......
                {
                   pal[i][j]=true;
                   if(j==n-1)
                       d[i]=0;
                   else if(d[j+1]+1<d[i])
                       d[i]=d[j+1]+1;
                }
            }
        }
        return d[0];
    }
};


int main()
{
	Solution a;


}
