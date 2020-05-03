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

// 18.6 Describe an algorithm to find the smallest one million numbers in one billion numbers.Assume that the computer memory can hold all one billion numbers.
// 
// 
// 
// 这道题让我们在十亿个数字中找到最小的一百万个数字，而且限定了计算机只有能存十亿个数字的内存。这题有三种解法，排序，最小堆，和选择排序。
// 
// 首先来看排序方法，这种方法简单明了，就是把这十亿个数字按升序排列，然后返回前一百万个即可，时间复杂度是O(nlgn)。
// 
// 然后来看最小堆做法，我们建立一个最大堆(大的数字在顶端)，然后将前一百万个数字加进去。然后我们开始遍历剩下的数字，对于每一个数字，我们将其加入堆中，然后删掉堆中最大的数字。遍历接受后，我们就有了一百万个最小的数字，时间复杂度是O(nlgm)，其中m是我们需要找的数字个数。
// 
// 最后我们来看选择排序的方法，这种方法可以在线性时间内找到第i个最大或最小的数，如果数字都不是不同的，那么我们可以在O(n)的时间内找到第i个最小的数字，算法如下：
// 
// 1. 随机选取数组中的一个数字当做pivot，然后以此来分割数组，记录分割处左边的数字的个数。
// 
// 2. 如果左边正好有i个数字，那么返回左边最大的数字。
// 
// 3. 如果左边数字个数大于i，那么继续在左边递归调用这个方法。
// 
// 4. 如果左边数字个数小于i，那么在右边递归调用这个方法，但是此时的rank变为i - left_size。
// 
// 参见代码如下：


class Solution
{
public:
	int partition(vector<int> &array, int left, int right, int pivot) {
		while (true) {
			while (left <= right && array[left] <= pivot) ++left;
			while (left <= right && array[right] > pivot) --right;
			if (left > right) return left - 1;
			swap(array[left], array[right]);
		}
	}

	int find_max(vector<int> &array, int left, int right) {
		int res = INT_MIN;
		for (int i = left; i <= right; ++i) {
			res = max(res, array[i]);
		}
		return res;
	}

	int selection_rank(vector<int> &array, int left, int right, int rank) {
		int pivot = array[rand() % (right - left + 1) + left];
		int left_end = partition(array, left, right, pivot);
		int left_size = left_end - left + 1;
		if (left_size == rank + 1) return find_max(array, left, left_end);
		else if (rank < left_size) return selection_rank(array, left, left_end, rank);
		else return selection_rank(array, left_end + 1, right, rank - left_size);
	}

};

int main()
{
	Solution a;



}

