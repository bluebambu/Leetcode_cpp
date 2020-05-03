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
    ////// leetcode pass ////////////
    /// 这里 dp[i]的意思是， 以 s[i-1] 作为一个独立的code， 能decode 的ways的number. 这样 0 的case 就好理解了！！！！
    int numDecodings(string s) {
        if(s.empty()) return 0;

        vector<int> dp(s.size()+1, 0);
        dp[0]=1;

        for(int i=1; i<=s.size(); ++i){
            if(s[i-1]=='0'){
                if(s[i-2]=='1' || s[i-2]=='2')
                    dp[i]=dp[i-2];  /// 必须等于 i-2。 如果写成 =dp[i-1]，就意味着 ‘0’ 可以翻译成一个字母，实际上不行。 参考 “110”
                else
                    return 0; /// 必须要return， 或者 = 0. 参考 “100”
            }else{
                if(s[i - 2] == '1' || s[i - 2] == '2' && s[i - 1] >= '1' && s[i - 1] <= '6')
                    dp[i]=dp[i-1] + dp[i-2];
                else
                    dp[i]=dp[i-1];
            }
        }
        return dp[s.size()];
    }
    /////////// leetcode passed, O(1) space //////////////////////
    int numDecodings(string s) {
        if(s.empty()) return 0;

        int cur=1, prev=0;

        for(int i=1; i<=s.size(); ++i){
            if(s[i-1]=='0') cur=0;

            if(i<2 || !(s[i-2]=='1' || s[i-2]=='2' && s[i-1]<='6'))
                prev=0;

            int tmp=cur;
            cur=cur+prev;
            prev=tmp;
        }
        return cur;
    }

};


int main()
{
	Solution a;


}
