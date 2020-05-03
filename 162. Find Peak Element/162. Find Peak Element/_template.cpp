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


struct TreeNode
{
	TreeNode(int a) :val(a), left(nullptr), right(nullptr) {}
	TreeNode(int a, TreeNode* x, TreeNode* y) :val(a), left(x), right(y) {}
	TreeNode() :val(0), left(nullptr), right(nullptr) {}

	int val;
	TreeNode *left;
	TreeNode *right;

};

void print(TreeNode* root){
	queue<TreeNode*> q;
	q.push(root);

	while (q.size()){
		int n = q.size();
		for (int i = 0; i<n; ++i){
			TreeNode* front = q.front();
			q.pop();

			if (!front)
				cout << "# ";
			else{
				cout << front->val << " ";
				q.push(front->left);
				q.push(front->right);
			}
		}
		cout << endl;
	}
}


// A peak element is an element that is greater than its neighbors.
// 
// Given an input array where num[i] �� num[i + 1], find a peak element and return its index.
// 
// The array may contain multiple peaks, in that case return the index to any one of the peaks is fine.
// 
// You may imagine that num[-1] = num[n] = -��.
// 
// For example, in array[1, 2, 3, 1], 3 is a peak element and your function should return the index number 2.
// 
// click to show spoilers.
// 
// Credits:
// Special thanks to @ts for adding this problem and creating all test cases.
// 
// ��������������һ����ֵ�������ֵ�����Ǿֲ������ֵ�������ñ����������������ֵ�϶������
// Time Limit Exceeded������Ҫ����ʹ�������ڶ��ֲ��ҷ�������ʱ�䣬����ֻ����Ҫ�ҵ�����һ����
// ֵ����ô������ȷ�����ֲ����۰���м��Ǹ�Ԫ�غ󣬺ͽ������Ǹ�Ԫ�رȽ��´�С��������ڣ���˵
// ����ֵ��ǰ�棬���С�����ں��档�����Ϳ����ҵ�һ����ֵ�ˣ��������£�

// ������Ҫ�����ҳ������еķ�ֵԪ�أ��������±ꡣ���з�ֵԪ����ָ��Ԫ�ش�������Ԫ�أ�num[-1] = num[n] = -�ޣ���
// ��������������Ԫ�����ظ�������ж����ֵ����������һ�����ɡ�����Ҫ���O(logn)�Ӷȡ�
// 
// ֱ��˼·���Ǳ���һ�����飬�����������Ӷ���O(n)������Ҫ�ﵽO(logn)���������뵽�����ˡ��ҵ��м�Ԫ��nums[m]������
// ������Ԫ�رȽϣ����nums[m]�������ߵģ���nums[m]��ֱ���Ƿ�ֵ�ˣ�����ѡȡ����nums[m]��һ����Ŷ��ּ��ɡ�����ÿ
// �λ�ѡ���������Ҳ࣬�������������Ԫ�ض����бȽϣ�ֻ��Ҫ�Ƚ�һ�༴�ɣ�����ѡ����nums[m]���Ҳ�Ԫ��nums[m + 1]���бȽϣ���
// 
// ����������ȡ�������Ҷ˵�l��r��Ȼ������ֵm1����(l + r) / 2��m2����m1 + 1�������Ƚ�nums[m1]��nums[m2]�Ĵ�С��
// 
// ���nums[m1]С��nums[m2]����ô˵��nums[m1]�϶��������Ƿ�ֵ����m1���Ҳ�һ�����ڷ�ֵ����Ϊ���nums[m2]����nums[m2 + 1]��
// ��ôm2�����Ƿ�ֵ������nums[m2 + 1]���ܾ��Ƿ�ֵ���������nums[m2 + 2]�Ļ������Դ����ƣ�����ȷ���ⲿ��һ�����ڷ�ֵ�����
// ������l����m2�����Ž��ж���������
// 
// ���nums[m1]����nums[m2]����ô˵��nums[m2]�϶��������Ƿ�ֵ����m2�����һ�����ڷ�ֵ������ͬ�ϡ���˿�����r����m1�����Ž��ж���������
// 
// ���l����rʱ����������l���ɡ�
// 
// ʱ�临�Ӷȣ�O(logn)
// 
// �ռ临�Ӷȣ�O(1)

class Solution {
public:
	int findPeakElement(vector<int>& nums) {
		if (nums.empty())
			return 0; 

		int left = 0, right = nums.size() - 1; 
		while (left < right){
			int mid = left + (right - left) / 2;
			if (nums[mid] < nums[mid + 1])
				left = mid + 1;
			else
				right = mid; 
		}
		return left; 
	}
};



// directly find the global max
// 
class Solution2 {
public:
	int findPeakElement(vector<int>& nums) {
		if (nums.empty())
			return 0;

		int res = nums[0], ind = 0;
		for (int i = 1; i<nums.size(); ++i){
			if (nums[i]>res){
				res = nums[i];
				ind = i;
			}
		}
		return ind;
	}
};

int main()
{
	Solution a;

	//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
	3       8
	1    4   7    9

	*/

	a.flatten(tree);


}

