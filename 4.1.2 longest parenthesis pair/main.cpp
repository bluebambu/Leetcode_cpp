#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <stack>

using namespace std;

inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}
inline float min(float a, float b) {return a<b?a:b;}


class Solution
{
public:
    int longestValidParentheses(string s)
    {
        vector<int> idx;
        int last = -1;
        int max_len = 0;

        for(int i=0 ; i<s.size();)
        {
            if(s[i]=='(')
                idx.push_back(i++);
            else
            {
                if(idx.empty())
                    last=i++;
                else
                {
                    int tmp = idx.back();
                    idx.pop_back();

                    if(!idx.empty())
                        max_len = max(max_len, i-tmp+1); // 这个地方写错了，不能用 tmp-1， 而应该是 help_stack.back()
                    else
                        max_len = max(max_len, i-last);

                    ++i;
                }
            }
        }

        return max_len;
    }

    int longestValidParentheses2(string s)
    // 这个 是不对的，只能统计出来合法的括号的数目，不能求得最长的合法括号
    {
        int n = s.size();

        vector<char> Pstack;
        auto p=s.begin();

        while(p!=s.end())
        {
            if(*p==')' && Pstack.size() && Pstack.back()=='(')
            // Calling back() on an empty container causes undefined behavior.

            {
                Pstack.pop_back();
                ++p;
                continue;
            }

            Pstack.push_back(*p);
            ++p;
        }

        return n-Pstack.size();
    }

    int longestValidParentheses3(string s)
    {
        vector<char> help_stack;
        int last=-1;
        int maxlen=0;

        for(int i=0; i<s.size(); ++i)
        {
            if(s[i]=='(')
                help_stack.push_back(i);
            else
            {
                if(help_stack.empty())
                    last=i;
                else
                {
                    help_stack.pop_back();

                    if(help_stack.empty())
                        maxlen = max(maxlen, i-last);
                    else
                        maxlen = max(maxlen, i-help_stack.back());
                }
            }

        }

        return maxlen;
    }

    int longestValidParenthesesDP1(string s) {
        if(s.size()<2) return 0;

        int dp[s.size()]={0}, maxlen=0;

        for(int i=s.size()-2; i>=0; --i){
            if(s[i]==')')
                dp[i]=0;
            else{
                int j=i+dp[i+1]+1;
                if(j<s.size() && s[j]==')'){
                // 这里的 <s.size 不是必须的
                    dp[i]=dp[i+1]+2;
                    if(j+1<s.size())
                // 这里的 <s.size 是必需的。 考虑
                // ((() 的情况, 即没有j+1的情况
                        dp[i]+=dp[j+1];

                }else
                    dp[i]=0;
            }

            maxlen=max(maxlen, dp[i]);
        }

        return maxlen;

    }

    ////////////// leetcode passed, traverse from left /////////////
    int longestValidParentheses(string s) {
        int n=s.size(), maxlen=0;
        vector<int> dp(n, 0);

        for(int i=1; i<n; ++i){
            if( s[i]==')' && i-dp[i-1]-1 >=0 && s[i-dp[i-1]-1]=='(' ) {
                dp[i]=dp[i-1]+2;
                if(i-dp[i] >= 0) dp[i]+=dp[i-dp[i]];
            }
            maxlen=max(maxlen, dp[i]);
        }
        cout<<n;
        return maxlen;
    }
    ///////////////// leetcode passed, ////////////////////////////
    int longestValidParentheses(string s) {
        vector<int> stack;
        int start=-1, len, maxlen=0; // start = -1 ！！！！！

        for(int i=0; i<s.size(); ++i){
            if(stack.empty() && s[i]==')')
                start=i;
            else if(s[i]=='(')
                stack.push_back(i);
            else if(s[i]==')'){
                stack.pop_back();
                if(stack.empty()) len=i-start;
                else len=i-stack.back();
                maxlen=max(maxlen, len);
            }
        }
        return maxlen;
    }
};

int main()
{
    Solution a;
    string b("()(()(((((())())((()))(()((())()(()()(()((()))()))))())))))())()()))))(())(()(()()((((((((((((((((((((((((((((())())))()))))))(((");

    auto c=a.longestValidParentheses3(b);
//    for(auto i=0;i<a.size();++i)
        cout<<c;

}
