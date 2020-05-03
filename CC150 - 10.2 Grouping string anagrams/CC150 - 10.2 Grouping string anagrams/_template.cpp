// _template.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <string>
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


struct comp{
	bool operator()(string a, string b){
		string c = a, d = b;

		sort(a.begin(), a.end());
		sort(b.begin(), b.end());
		return a.size()>b.size()  && a > b;
	}
};


class Solution // hashmap to store all the elements
{
public:
	bool anagram(string& a, string& b){
		if (a.size() != b.size())
			return false; 

		vector<int> ha(26); 
		for (int i = 0; i < a.size(); ++i){
			ha[a[i] - 'a']++;
		}

		vector<int> hb(26); 
		for (int i = 0; i < b.size(); ++i)
			hb[b[i] - 'a']++; 

		return ha == hb; 
	}

	void AnaramSort(vector<string>& v){
		unordered_map<string, vector<string>> map; 
		for (int i = 0; i < v.size(); ++i){
			string copy = v[i]; 
			sort(copy.begin(), copy.end()); 
			map[copy].push_back(v[i]); 
		}

		int k = 0;
		for (auto iter = map.begin(); iter != map.end(); ++iter){
			vector<string>& tmp = iter->second; 
			for (int j = 0; j < tmp.size(); ++j)
				v[k++] = tmp[j]; 
		}
	}
};

int main()
{
	vector<string> ac{ "a", "b", "ab", "adf", "afd", "ba", "ffdc", "fda" };


	Solution a; 
	a.AnaramSort(ac); 

	for (auto i : ac)
		cout << i << " ";

}