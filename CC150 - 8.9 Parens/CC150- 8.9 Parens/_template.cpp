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



class Solution
{
public:
	vector<string> parens(int n){
		vector<string> result; 
		string path; 
		parens(n, 0, 0, path, result);
		return result; 
	}
	void parens(int n, int left, int right, string& path, vector<string>& result){
		if (left == n && right == n){
			result.push_back(path);
			return; 
		}
		if (left < n){
			path.push_back('(');
			parens(n, left + 1, right, path, result);
			path.pop_back();
		}
		if (right < left){
			path.push_back(')');
			parens(n, left, right + 1, path, result);
			path.pop_back();
		}
	}
};

int main()
{
	Solution a;

	auto b = a.parens(5);

	for (string i : b){
		for (auto j : i)
			cout << j; 
		cout <<endl; 
	}
}

