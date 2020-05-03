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
// �����˼·�Ƕ��� ����string������ ? �� * ������� ��Ŀ��Ҫ��ʵ���ϸ��򵥣� ֻ�� p ��ͨ����� s û��
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
// ������stringΪ���� ������ 'c' �� '*' ��ʱ��t �� "efghe" ��Ҫ�� s ��ÿһ��'c'�Ժ���ִ��ȶԣ� "cdefg...", "defg...", "efghe...." ..... ÿ�αȶԲ��ɹ�����Ҫ�ص� '*' �Ŵ������� 
// ��Ȼÿһ�λ��ݶ����� s string ��ǰ��һ����  ���Ӧ��Ҳ����д�� double loop ��ʽ��  �� regex expression ��һ���ģ�����Ҫ����������greedy�� 
//
class Solution2{ // s contains no symbols, t does
public:
	bool match(string s, string t){ // *iterator ����Խ�� string.end() ����
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
	bool isMatch(string s, string t){ // *iterator ����Խ�� string.end() ����
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
					for (int k = i; k >= 0; --k){ // �˴� k Ҫ >=0 !! ������ >=1 
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

dp[i][j] =  when t[j]=='*' , ���Բ� dp[i][j-1], ��  abc ? ab,  Ҳ���Բ�  dp[i-k][j-1], �� ab ? ab, a ? ab, [] ? ab. �������� n^2 ���Ӷȡ� 
��һ�������;���ǲ� dp[i-1][j], ��  ab ? ab*  ,  ����� * �� ��ƥ���� self-propagation �ģ� ��Ϊ��� ab ? ab* ƥ�䣬 �� abc ? ab*�� abcd ? ab* ,..... ��ƥ�䡣  
dp[i-1][j] �жϵ���ʼ�������ڵ�һ������� �� dp[i][j] = dp[i][j-1] ������� abc ? ab* �� 

�������������������� ����  adc ? ab*, �� dp[i][j]������Ϊtrue�� 

��ˣ� ������condition�ǣ� 

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

