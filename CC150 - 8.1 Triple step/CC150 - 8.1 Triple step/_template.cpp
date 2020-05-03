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
	int steps(int n){
		int t4, t3 = 1, t2 = 0, t1 = 0; 
		for (int i = 0; i < n; ++i){
			t4 = t3 + t2 + t1; 
			t1 = t2; 
			t2 = t3; 
			t3 = t4;
		}
		return t4; 
	}

};

int main()
{
	Solution a;
	cout << a.steps(5); 


}

