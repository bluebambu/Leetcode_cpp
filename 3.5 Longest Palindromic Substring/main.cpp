#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <string.h>

using namespace std;

inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}
inline float min(float a, float b) {return a<b?a:b;}


class Solution
{
public:
    int longestPalindromeDP(string str){

    }

    string longestPalindromeDP(string str)
    // leetcode 上的 动态规划 解法
    {
        int len = str.size();
        bool dp[len][len];
        // 定义是 dp[i][j]， 所以 i<j, 只用到一半的矩阵

        fill_n(&dp[0][0], len*len, false);

        for(int j=0; j<len ; ++j)
        {
            dp[j][j]=true;
        }

        int maxlen=0, location=0;

        for(int j=0;j<len;++j)
        {
            for(int i=0; i<j ; ++i)
            {
                if(i==j-1 && str[i]==str[j])
                    dp[i][j]=true;
                else if(dp[i+1][j-1]==true && str[i]==str[j])
                    dp[i][j]=true;

                if(dp[i][j] && (j-i+1)> maxlen)
                    {
                        maxlen =  j-i+1;
                        location = i;
                    }
            }
        }


        return str.substr(location,maxlen);


    }


    string longestPalindromeDP2(string str)
    {
        const int n=str.size();
        bool dp[n][n];
        int maxlen=0;
        int lmax=0;

        fill_n(&dp[0][0], n*n, false);

        for(int i=0; i<n; ++i)
            dp[i][i]=true;

        for(int i=0; i<n-1; ++i)
            dp[i][i+1] = (str[i]==str[i+1]);

        for(int i=2; i<n; ++i)
            for(int j=0; j+i<n; ++j)
                dp[j][j+i] = (dp[j+1][i+j-1] && (str[j]==str[i+j]));

        for(int i=0; i<n; ++i)
            for(int j=i+1; j<n; ++j)
            {
                if(dp[i][j]==true && (j-i+1) > maxlen)
                {
                    maxlen=j-i+1;
                    lmax=i;
                }
            }

        return str.substr(lmax,maxlen); // substr( location, length )


    }


    string longestPalindromeDP3(string str)
    {
        int n=str.size();

        bool idx[n][n];

        fill_n(&idx[0][0], n*n, false);

        for(int i=0; i<n; ++i)
        {
            idx[i][i]=true;

            if(i+1 < n && str[i]==str[i+1]) idx[i][i+1]==true;
        }

        for(int i=2; i<n; ++i)
            for(int j=0; j<i-1; ++j)
            {
                if(idx[j+1][i-1] && str[j]==str[i]) idx[j][i]=true;
            }

        int lidx=0, maxlen = 0;

        for(int i=0; i<n; ++i)
            for(int j=i+1; j<n; ++j)
            {
                if(idx[i][j]==true && maxlen < j-i+1)
                {
                    maxlen = j-i+1;
                    lidx = i;

                }
            }

        return str.substr(lidx, maxlen);

    }


    string longestPalindrome4(string s) {
        int n = s.length(), i;
        if(n<2)
            return s;

        int leftMost=0, rightMost=0;
        i = 0;
        int start, end;
        while(i<n)
        {
            start = i;
            end = i;
            i++;
            while(i<n && s[i]==s[start])
            {
                i++;
            }
            end = i-1;

            while(start-1>=0 && end+1<n && s[start-1]==s[end+1])
            {
                start--;
                end++;
            }

            if(rightMost-leftMost <= end-start)
            {
                leftMost = start;
                rightMost = end;
            }
        }

        return s.substr(leftMost, rightMost-leftMost+1);
    }
//////////////////////// Leetcode passed /////////////////////////////////////
    string longestPalindrome(string s) {
        int n=s.size();
        if(n==1) return s;

        bool dp[n][n]={0};
        int maxlen=0;
        int idx=0;

        for(int i=0; i<n; ++i){
            for(int j=0; j<=i; ++j){ // 这里 j 可以等于 i ， 因为要考虑  j==i的情况
                if(i==j)
                    dp[j][i]=1;
                else if(i==j+1 && s[j]==s[i])
                    dp[j][i]=1;
                else{
                    dp[j][i] = dp[j+1][i-1] && (s[j]==s[i]);
                }

                if(dp[j][i] && (i-j+1) > maxlen){
                    maxlen=i-j+1;
                    idx=j;
                }
            }
        }
        return s.substr(idx, maxlen);
    }
};

int main()
{
    Solution a;
    string b("oiwueriuoiksznnmvwoieuiruotioiwueamanaplanacanalpanamabamanaplanacanalpanamasdjlkgjoiuwoijelkrjigoiwjelkjanmvnxvnwoiejfoiwe");

    auto c=a.longestPalindromeDP3(b);
    for(auto i : c)
        cout<<i;

}
