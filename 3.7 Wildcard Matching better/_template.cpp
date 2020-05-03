// _template.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

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

inline int exchg(int &a, int &b)  { int c = a; a = b; b = c; }
inline int log2(int N){ return log10(N) / log10(2); }
inline float min(float a, float b) { return a<b ? a : b; }



// possibly right, but TLE.....
// 我这个思路是对于 两个string都包含 ? 和 * 的情况。 题目的要求实际上更简单， 只有 p 有通配符， s 没有
class Solution
{
public:
	bool match(string s, string t){
		
		return wm(s, s.size() - 1, t, t.size() - 1); 
	}

	bool wm(string a, int ia, string b, int ib){
		if (ia == -1 && ib == -1)
			return true; 
		if (ib == -1)
			return wm(b, ib, a, ia); 
		if (ia == -1){
			for (; ib >= 0; --ib)
				if (b[ib] != '*')
					return false; 
			return true; 
		}

		if (a[ia] != '*' && b[ib] != '*')
			return (a[ia] == '?' || b[ib] == '?' || a[ia]==b[ib]) && wm(a, ia-1, b, ib-1); 
		if (b[ib] == '*')
			return wm(b, ib, a, ia); 
		if (a[ia] == '*'){
			bool tmp = false; 

			while (a[ia] == '*')
				--ia; 

			for (; ib >= -1; --ib){
				if (ib - 1 >= -1 && b[ib] == '*' && b[ib] == b[ib - 1])
					continue;
				tmp |= wm(a, ia, b, ib); 
				if (tmp)
					return true; 
			}
			return false; 
		}
		if (a[ia] == '*' && b[ia] == '*'){
			if (ib < ia)
				return wm(b, ib, a, ia); 

			while (a[ia] == '*')
				--ia; 

			bool tmp = false;  
			for (; ib >= -1; --ib){
				if (ib-1>=-1 && b[ib] == '*' && b[ib] == b[ib-1])
					continue;
				tmp |= wm(a, ia, b, ib); 
				if (tmp)
					return true; 
			}
			return false; 
		}
	}

};



// string s:	abcdefghefghe 
// string t:	ab*efghe
//
// 以上两string为例， 当到达 'c' 和 '*' 的时候，t 的 "efghe" 需要和 s 的每一个'c'以后的字串比对： "cdefg...", "defg...", "efghe...." ..... 每次比对不成功后都需要回到 '*' 号处继续。 
// 当然每一次回溯都是在 s string 上前进一步。  因此应该也可以写成 double loop 形式。  和 regex expression 是一样的，都需要遍历而不能greedy。 
//
class Solution2{ // s contains no symbols, t does
public:
	bool match(string s, string t){ // *iterator 允许越界 string.end() ！！
		string::iterator scur = s.begin(), tcur = t.begin(), sstar = s.end(), tstar = t.end(); 

		while (scur != s.end()){
			if (tcur != t.end() && (*scur == *tcur || *tcur == '?'))
				++scur, ++tcur; 
			else if (tcur!= t.end() && *tcur == '*'){
				sstar = scur; 
				tstar = tcur; 
				tcur += 1; 
			}
			else if (tstar != t.end()){ // one matching trial has failed, restart another one
				scur = ++sstar; 
				tcur = tstar + 1; 
			}
			else
				return false;
		}
		while (tcur != t.end() && *tcur == '*')
			++tcur; 
		return tcur == t.end(); 
	}
};

// old version answer
// 
class Solution3 {
public:
	bool isMatch(char *s, char *p) {
		char *scur = s, *pcur = p, *sstar = NULL, *pstar = NULL;
		while (*scur) {
			if (*scur == *pcur || *pcur == '?') {
				++scur;
				++pcur;
			}
			else if (*pcur == '*') {
				pstar = pcur++;
				sstar = scur;
			}
			else if (pstar) {
				pcur = pstar + 1;
				scur = ++sstar;
			}
			else return false;
		}
		while (*pcur == '*') ++pcur;
		return !*pcur;
	}
};

// recursion solution
class Solution4 {
public:
	bool isMatch(string s, string t){ // *iterator 允许越界 string.end() ！！
	}
};


// DP solution, TLE!!
class Solution5 {
public:
	bool isMatch(string s, string t){
		int m = s.size(), n = t.size(); 
		vector<vector<bool>> dp(m+1, vector<bool>(n+1, false)); 

		dp[0][0] = true; 

		for (int j = 1; j < n+1; ++j){
			dp[0][j] = dp[0][j - 1] && (t[j - 1] == '*'); 
		}

		for (int i = 1; i < m + 1; ++i){
			dp[i][0] = false; 
		}

		for (int j = 1; j < n + 1; ++j){
			for (int i = 1; i < m + 1; ++i){
				if (t[j - 1] == '*'){
					for (int k = i; k >= 0; --k){ // 此处 k 要 >=0 !! 不能是 >=1 
						dp[i][j] = ( dp[i][j] || dp[k][j - 1]); 
						if (dp[i][j])
							break;
					}
				}
				else{
					dp[i][j] = dp[i - 1][j - 1] && (s[i - 1] == t[j - 1] || t[j - 1] == '?'); 
				}
			}
		}
		return dp[m][n]; 
	}
};


// DP, better answer, passed
/*
string s:	abc
string t:	ab*

dp[i][j] =  when t[j]=='*' , 可以查 dp[i][j-1], 即  abc ? ab,  也可以查  dp[i-k][j-1], 即 ab ? ab, a ? ab, [] ? ab. 但这样是 n^2 复杂度。 
另一个巧妙的途径是查 dp[i-1][j], 即  ab ? ab*  ,  这个带 * 号 的匹配是 self-propagation 的， 因为如果 ab ? ab* 匹配， 则 abc ? ab*， abcd ? ab* ,..... 都匹配。  
dp[i-1][j] 判断的起始点来自于第一种情况， 即 dp[i][j] = dp[i][j-1] 的情况， abc ? ab* 。 

如果两种情况都不成立， 比如  adc ? ab*, 那 dp[i][j]不可能为true。 

因此， 完整的condition是： 

dp[i][j] =  when t[j]=='*'  {
				if dp[i][j-1]==true
					dp[i][j] = true; 
				else // if( dp[i][j-1] == false )
					dp[i][j] = dp[i-1][j]; 
*/
class Solution6 {
public:
	bool isMatch(string s, string t){
		int m = s.size(), n = t.size();
		vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));

		dp[0][0] = true;

		for (int j = 1; j < n + 1; ++j){
			dp[0][j] = dp[0][j - 1] && (t[j - 1] == '*');
		}

		for (int i = 1; i < m + 1; ++i){
			dp[i][0] = false;
		}

		for (int j = 1; j < n + 1; ++j){
			for (int i = 1; i < m + 1; ++i){
				if (t[j - 1] == '*'){
					if (dp[i][j - 1])
						dp[i][j] = true; 
					else{
						dp[i][j] = dp[i - 1][j]; 
					}
				}
				else
					dp[i][j] = dp[i - 1][j - 1] && (s[i - 1] == t[j - 1] || t[j - 1] == '?'); 
			}
		}
		return dp[m][n];
	}
};



int main()
{
	Solution6 a;

	cout << a.isMatch("a", "a*");

}

