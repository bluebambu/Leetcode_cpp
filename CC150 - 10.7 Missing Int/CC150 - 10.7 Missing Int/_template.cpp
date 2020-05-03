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
#include <bitset>

using namespace std;

inline int exchg(int &a, int &b)  { int c = a; a = b; b = c; }
inline int log2(int N){ return log10(N) / log10(2); }
inline float min(float a, float b) { return a<b ? a : b; }

class Solution_1
{
public:
	int miss(vector<int>& v){
		const long long len = 4000000000; 
		bitset<len> bits(0); 

		for (int i = 0; i < v.size(); ++i){
			bits[v[i]] = 1;
		}


	}

};


class Solution_2{ // What if you have only 1O MB of memory? 
public:
	const int datasize = 1000000000; 
	const int blockSize = 1000000; 
	int blockNo = datasize / blockSize; 
	
	int miss(vector<int>& v){
		vector<int> blocks(blockNo, 0); 

		for (int i = 0; i < v.size(); ++i){
			blocks[v[i] / blockSize]++;
		}

		int start = -1;
		for (int i = 0; i < blocks.size(); ++i){
			if (blocks[i] < blockSize){
				start = i;
			}
		}

		bitset<blockSize> oneBlock; 
		int begin = start*blockSize, end = begin + blockSize; 
		for (int i = 0; i < v.size(); ++i){
			if (v[i] >= begin && v[i] < end){
				oneBlock[v[i] - begin] = 1; 
				break; 
			}
		}

		for (int i = 0; i < blockSize; ++i){
			if (oneBlock[i] != 1)
				return i + begin; 
		}

		return -1; 
	}
};


int main()
{
	Solution_1 a;




}

