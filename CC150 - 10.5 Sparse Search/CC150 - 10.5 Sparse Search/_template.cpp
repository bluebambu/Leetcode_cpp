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
	int SparseSearch(vector<string>& v, string target){
		if (v.empty())
			return -1; 

		int start = 0, end = v.size(); 
		while (start < end){
			int mid = start + (end - start) / 2;
			if (v[mid] == target)
				return mid; 
			else if (v[mid] > target){
				while (v[mid] > target)
					--mid; 
				end = mid + 1;
			}
			else{
				while (v[mid] < target)
					++mid; 
				start = mid; 
			}
		}

		return -1; 
	}

};

int main()
{
	Solution a;
	
	vector<string> b{ "at", "", "", "", "ball", "", "", "", "car", "", "", "", "", "", "dad", "", };

	cout << a.SparseSearch(b, "car"); 


}

