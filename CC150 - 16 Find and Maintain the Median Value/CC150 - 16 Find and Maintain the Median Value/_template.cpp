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
	priority_queue<int> smallNums; 
	priority_queue<int, vector<int>, greater<int>> largeNums; 
public:
	void addNum(int i){
		smallNums.push(i); 
		largeNums.push(smallNums.front()); 
		smallNums.pop();
		if (smallNums.size() < largeNums.size()){
			smallNums.push(largeNums.front()); 
			largeNums.pop();
		}
	}

	int median(){
		return smallNums.size() != largeNums.size() ? smallNums.front() : (0.5*smallNums.front() + 0.5*largeNums.front());   
	}

};

int main()
{
	Solution a; 

	for (int i = 0; i < 10; ++i){

	}

}

