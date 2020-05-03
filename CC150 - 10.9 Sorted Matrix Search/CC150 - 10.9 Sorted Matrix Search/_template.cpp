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
	int MatrixSearch(vector<vector<int>>& matrix, int target){
		int start = 0, end = matrix.size() * (matrix.at(0).size());
		while (start < end){
			int mid = start + (end - start) / 2;
			int x = mid / matrix[0].size(), y = mid % matrix[0].size(); 
			
			if (matrix[x][y]==target)
				return 
		}
	}

};

int main()
{
	Solution a;


}

