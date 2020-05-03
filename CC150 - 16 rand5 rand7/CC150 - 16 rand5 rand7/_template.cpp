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
	int rand5() {}

	int rand7(){
		int x = 5 * rand5() + rand5(); 
		if (x < 21){
			return x % 7; 
		}
	}

};

struct dd{
	char a; 
	double b; 
};


int main()
{
	Solution a;

	cout << sizeof dd; 



}

