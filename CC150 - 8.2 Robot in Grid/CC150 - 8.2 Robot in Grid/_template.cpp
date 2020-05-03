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


// complexity: This solution is O ( 2r+c), since each path has r+c steps and 
// there are two choices we can make at each step
class Solution
{
public:
	vector<string> path(vector<vector<char>>& matrix){
		vector<string> result;
		string path; 
		path(matrix, 0, 0, path, result);
		return result; 
	}
	void path(vector<vector<char>>& matrix, 
			  int i, int j, string& path, vector<string>& result){
		//
		if (i == matrix.size() - 1 && j == matrix[0].size() - 1 && matrix[i][j] == '.'){
			path.push_back(matrix[i][j]);
			result.push_back(path); 
			path.pop_back(); 
			return; 
		}
		if (i >= matrix.size() || j >= matrix[0].size())
			return; 
		if (matrix[i][j] == 'x')
			return; 
		path.push_back(matrix[i][j]); 
		path(matrix, )
	}

};

int main()
{
	Solution a;

	"...x......"
	"......x..."
	"...x....x."
	".x.x......"

}

