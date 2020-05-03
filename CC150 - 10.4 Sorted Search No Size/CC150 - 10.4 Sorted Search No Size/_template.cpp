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
	int binarysearch(vector<int>& v, int start, int end, int target){
		if (start >= end)
			return -1; 

		int mid; 
		while (start < end){
			mid = start + (end - start) / 2;
			if (v[mid] == target)
				return mid;
			else if (v[mid] > target || v[mid]== -1 ) // -1 is supposed to be much bigger than v[mid]
				end = mid;
			else
				start = mid + 1;
		}

		if (start >= end)
			return -1; 
	}

	int noSize(vector<int>& v, int target){
		//..
		int seed = 1; 
		while ( v[seed] <= target &&  v[seed] != -1) // condition is a bit tricky! 
			seed *= 2; 
		return binarysearch(v, seed / 2, seed, target); 
	}

};




int main()
{
	Solution a;

	vector<int> b{ 1, 3, 6, 8, 12, 18, 20, 23, 26, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	vector<int> c{ 0 }; 

	cout << a.noSize(b, 23); 
}

