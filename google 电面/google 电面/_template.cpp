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
#include <string> 
#include <unordered_set>
#include <set>
#include <map>
#include <utility>
#include <sstream>

using namespace std;

/*
	

	[ left <-------------------->  mid  <--------------------->  right ]

		[2,5,3,5,2,1,3,5,||6,7]              [2,5,3,5,2,1,3,5,6,7]  ||  
					
						[2,5,3,5,2,1,3,5,6,7||]  

*/

// Binary search solution!! 
/* let's say the binary search range is like 
	[...,23		,24		,25		,26		,27		,28		,29		,....], we can regard it as 
	[...,分4块，分4块，	分5块，	分5块，	分5块，	分6块，	分6块，	,....]

	所以我们要用二分找出最小的 “分5块” 的元素， 类比于二分找包含重复元素的数组中的第一个target的位置

	[... 2, 3, 3, 3, 3, 4, 5, 6, 7, 8...........], binary search find the first 3. 

	search range : (left, Right], so " while(left+1<right)", and in while loop, "return right" 

*/
class Solution
{
public:
	int minmax(vector<int>& vec){
		if (vec.size() < 5){
			int mmax = vec[0];
			for (auto i:vec) {
				mmax = max(mmax, i);
			}
			return mmax; 
		}
		int left = 0, right = sum(vec); 
		while (left + 1 < right){ // 
			int mid = left + ((right - left) >> 1); 
			cout << "**************" << endl; 
			cout << "mid: " << mid << endl; 
			if (toosmall(vec, mid)) // (left,  so left can not contain the right answer! 
				left = mid;
			else
				right = mid;
		}
		return right; 
	}

	bool toosmall(vector<int>& vec, int pivot){
		int target_times = 4; 
		int times = 0, tmp = pivot; 
		int i = 0; 
		for (; i < vec.size(); ++i){
			cout << "tmp, times, vec[i]: " << tmp << ", " << times << ", " << vec[i] << endl;
			if (times == target_times)
				return true;
			if (tmp < vec[i]){
				tmp = pivot;
				++times;
				--i;
				continue;
			}
			tmp -= vec[i];
		}
		// as long as times<target_times, the answer is always included in these situations.! 
		return false;
	}

	int sum(vector<int>& vec){
		int res = 0;
		for (auto i : vec)
			res += i;
		return res;
	}
};


// DFS solution. Record sum(i,j) first as buffer, then dfs to find the minmax. 
// In fact 不是个好办法， 当剩余最后一个区间的时候需要区别对待， 代码量其实也不小了。 
/*
class Solution2{
public:
	vector<vector<int>> buf; 

	vector<vector<int>> proc(vector<int>& vec){
		vector<vector<int>> res(vec.size() + 1, vector<int>(vec.size() + 1, 0)); 
		for (int i = 0; i < vec.size()+1; ++i){
			for (int j = i+1; j < vec.size() + 1; ++j){
				if (i == j - 1)
					buf[i][j] = vec[i];
				else
					buf[i][j] = buf[i][j - 1] + vec[j]; 
			}
		}
		return res; 
	}

	int minmax(vector<int>& vec){
		buf = proc(vec);
		int tmp = 0, res = INT_MAX; 
		dfs(vec, 0, 0, tmp, res);
		return res; 
	}
	void dfs(vector<int>& vec, int start, int times, int tmp, int res){
		if (times == 5){
			tmp = max(tmp, buf[start][vec.size() - 1]);
			res = min(tmp, res); 
			return;
		}
		for (int i = start; i < vec.size()+1; ++i){
			int tmpsum = buf(start, i); 
			int tmp2 = tmp; 
			tmp = max(tmp, tmpsum);
			dfs(vec, i + 1, times + 1, tmp, res);
			tmp = tmp2;
		}
	}
};
*/

// dynamic programming solution. 
//             <<<<<----------------<<<<<<<------------： 
// [  <-------------------->  |  <------->  |  <-------------->   ]
//                            p             i
//							f(p, k-1)      f(i,k)
//		k是分开的隔间的数目
/*
		要找到 f(i,k) 和 f(p,k-1) 的关系， 动归的思想。 

		关系是 f(i, k) = min (
							max( f(p, k-1), sum(p+1, i)  ) , 
							max( f(p-1, k-1), sum(p, i)  )
							)
			其中， min 是 从i到0 的取值中的min。 

		大意是， 要求得f（i，k） ，就是比较 i到p+1中的sum以及f（p，k-1）. 当p从i移动到0时， sum在不断增加， f(p,k-1)在不断减小。 因此可以用二分
*/
class Solution3{
public:
	vector<vector<int>> cache; 

	int minmax(vector<int>& vec){
		if (vec.empty())
			return 0; 					 
		cache = vector<vector<int>>(vec.size(), vector<int>(5, -1));
		return dp(vec, vec.size() - 1, 5);
	}

	int dp(vector<int>& vec, int end, int k){
		if (cache[end][k-1]!=-1)
			return cache[end][k-1];
		if (k == 1){
			cache[end][k-1] = sum(vec, 0, end);
			return cache[end][k - 1];
		}
		if (end == 0){
			cache[end][k - 1] = vec[0];
			return cache[end][k - 1];
		}
		// find the point where f(p,k-1) is close to sum(p+1,i)
		int p = goodpoint(vec, end, k); 
		// need to consider 2 points: p and p-1. Because you don't know which condition is the best 
		// condition, the f(p,k-1) or f(p-1, k-1)
		cache[end][k - 1] =  min(
			max(dp(vec, p, k - 1), sum(vec, p + 1, end)),
			max(dp(vec, p - 1, k - 1), sum(vec, p, end))
			);
		return cache[end][k - 1];
	}

	int goodpoint(vector<int>& vec, int end, int k){
		// binary search to find the best point.
		if (end == 0)
			return 0;
		int left = 0, right = end + 1;
		while (left + 1 < right){
			int mid = left + (right - left) / 2;
			if (dp(vec, mid, k - 1) <= sum(vec, mid + 1, end))
				left = mid;
			else
				right = mid;
		}
		return right;
	}

	int sum(vector<int>& vec, int left, int right){
		int res = 0;
		for (int i = left; i <= right; ++i)
			res += vec[i]; 
		return res; 
	}
};

int main()
{
	Solution3 a;
	vector<int> b = { 2, 5, 4, 6, 7, 6, 2, 9, 6, 3, 2, 0 }; 
	vector<int> c = { 2, 5, 4, 6 };
	vector<int> d = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	cout << a.minmax(d); 
}
