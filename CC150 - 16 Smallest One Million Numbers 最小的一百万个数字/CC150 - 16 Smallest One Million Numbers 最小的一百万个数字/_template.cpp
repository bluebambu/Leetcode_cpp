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
// �������������ʮ�ڸ��������ҵ���С��һ��������֣������޶��˼����ֻ���ܴ�ʮ�ڸ����ֵ��ڴ档���������ֽⷨ��������С�ѣ���ѡ������
// 
// �����������򷽷������ַ��������ˣ����ǰ���ʮ�ڸ����ְ��������У�Ȼ�󷵻�ǰһ��������ɣ�ʱ�临�Ӷ���O(nlgn)��
// 
// Ȼ��������С�����������ǽ���һ������(��������ڶ���)��Ȼ��ǰһ��������ּӽ�ȥ��Ȼ�����ǿ�ʼ����ʣ�µ����֣�����ÿһ�����֣����ǽ��������У�Ȼ��ɾ�������������֡��������ܺ����Ǿ�����һ�������С�����֣�ʱ�临�Ӷ���O(nlgm)������m��������Ҫ�ҵ����ָ�����
// 
// �����������ѡ������ķ��������ַ�������������ʱ�����ҵ���i��������С������������ֶ����ǲ�ͬ�ģ���ô���ǿ�����O(n)��ʱ�����ҵ���i����С�����֣��㷨���£�
// 
// 1. ���ѡȡ�����е�һ�����ֵ���pivot��Ȼ���Դ����ָ����飬��¼�ָ��ߵ����ֵĸ�����
// 
// 2. ������������i�����֣���ô��������������֡�
// 
// 3. ���������ָ�������i����ô��������ߵݹ�������������
// 
// 4. ���������ָ���С��i����ô���ұߵݹ����������������Ǵ�ʱ��rank��Ϊi - left_size��
// 
// �μ��������£�


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

