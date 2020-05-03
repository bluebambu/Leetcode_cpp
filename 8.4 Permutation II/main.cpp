// _template.cpp : Defines the entry point for the console application.
//


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
			while (j>i && j<v.size() && v[j] == v[j - 1]) ++j; // 1,.....2,2.... 可以变成 2,..1,2,... 和 2,..2,1,.... ，  但是这两个permutation会在之后的permute中变成一个， 实际上是重复的。 
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

