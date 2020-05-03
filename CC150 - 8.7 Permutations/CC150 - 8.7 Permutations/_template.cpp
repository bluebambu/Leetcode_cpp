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
	vector<vector<int>>  perm(vector<int>& v){
		sort(v.begin(), v.end());
		vector<vector<int>> result; 
		perm(v, 0, result);
		return result; 
	}
	void perm(vector<int>& v, int i,vector<vector<int>>& result){
		if (i == v.size()){
			result.push_back(v); 
			return; 
		}
		for (int j = i; j < v.size(); ++j){
			// 1,1,1,2,2,2,2,2 ��ÿһ��block�� ��ֻȡ��һ������ 
			// ����ֻ�� v[j] != v[i], ��Ϊ�����һ������ i ���������2����֮�� ��ÿ��2�����
			// n-1�����ֵ�permutation���ǻ���ͬ�� ���յ�����Ҳ���ǻ���ͬ�� ���� 
			while (j>i && j<v.size() && v[j] == v[j - 1]) 
				++j;
			if (j < v.size()){
				swap(v[i], v[j]);
				perm(v, i + 1, result);
				swap(v[i], v[j]);
			}
		}
	}
};

int main()
{
	Solution a;
	vector<int> b{ 1, 2, 2, 2, 2 };
	auto c = a.perm(b); 

	for (auto i : c){
		for (auto j : i)
			cout << j; 
		cout << endl; 
	}


}

