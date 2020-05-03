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
	vector<vector<int>> subset(vector<int>& v){
		int n = v.size(); 
		vector<vector<int>> result; 
		for (int i = 0; i < (1 << n); ++i){
			vector<int> tmp; 
			for (int j = 0; j < n; ++j){
				if ((i >> j) & 1){
					tmp.push_back(v[j]);
				}
			}
			result.push_back(tmp); 
		}
		return result; 
	}

	vector<vector<int>> subset2(vector<int>& v){
		vector<vector<int>> result; 
		vector<int> path; 
		subset2(v, 0, path, result); 
		return result; 
	}
	void subset2(vector<int>& v, int i, vector<int>& path, vector<vector<int>>& result){
		if (i == v.size()){
			result.push_back(path);
			return;
		}
		subset2(v, i + 1, path, result); 
		path.push_back(v[i]); 
		subset2(v, i + 1, path, result); 
		path.pop_back(); 
	}
};

int main()
{
	Solution a;
	vector<int> c{1,2,3,4 };
	auto b = a.subset2(c); 

	for (auto i : b){
		for (auto j : i)
			cout << j;
		cout << endl;
	}

}

