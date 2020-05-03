// _template.cpp : Defines the entry point for the console application.
//
#include <stdafx.h>

#include <iostream>
#include <functional>
#include <numeric>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>
#include <unordered_set>
#include <set>
#include <map>
#include <utility>
#include <sstream>
#include <string>
#include <chrono>

using namespace std;

inline int exchg(int &a, int &b)  { int c = a; a = b; b = c; }
inline int log2(int N){ return log10(N) / log10(2); }
inline float min(float a, float b) { return a < b ? a : b; }


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
		for (int i = 0; i < n; ++i){
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


template <typename C>
void prt1Layer(C v){
	for (auto i : v)
		cout << i << " ";
	cout << endl;
}

template <typename C>
void prt2Layer(C v){
	for (auto i : v){
		for (auto j : i)
			cout << j << " ";
		cout << endl; 
	}
	cout << endl;
}

template <typename C>
void mapprt(C v){
	for (auto i : v)
		cout << i.first << " " << i.second << endl;
	cout << endl;
}
////////////////////////////////////////////////////////////////
// Given a non-empty array containing only positive integers, find if the array can be partitioned into two subsets such that the sum of elements in both subsets is equal.

// Note:

//     Each of the array element will not exceed 100.
//     The array size will not exceed 200.

// Example 1:
// Input: [1, 5, 11, 5]
// Output: true
// Explanation: The array can be partitioned as [1, 5, 5] and [11].

// Example 2:
// Input: [1, 2, 3, 5]
// Output: false
// Explanation: The array cannot be partitioned into equal sum subsets.


// passed
class Solution {
public:
	bool canPartition(vector<int>& nums) {
		int total = accumulate(nums.begin(), nums.end(), 0); 
		if (total % 2)
			return false; 

		int half = total / 2; 
		vector<bool> dp(half + 1, false);
		dp[0] = true; 

		for (int i = 0; i < nums.size(); ++i){
			for (int j = half; j >= nums[i]; --j){
				dp[j] = dp[j] || dp[j - nums[i]]; 
			}
		}

		return dp[half]; 
	}
};


// ����⻹������bitset�������о�Ҳʮ�ֵ����bisets�Ĵ�С��Ϊ5001��
// Ϊɶ�أ���Ϊ��Ŀ��˵������ĳ��Ⱥ�ÿ�����ֵĴ�С�����ᳬ��100����ô
// ���ĺ�Ϊ10000����ôһ�����5000��ǰ���ټ��ϸ�0������5001�ˡ�����
// ��ʼ�������λ��ֵΪ1��Ȼ�������������֮�ͣ�Ȼ�����Ǳ������֣�����
// ������������num�����ǰ�bits����ƽ��numλ��Ȼ���ٻ���ԭ����bits����
// �����еĿ��ܳ��ֵĺ�λ���϶�Ϊ1���ٸ�������˵�ɣ������������[2,3]��
// ˵����ʼ��bitsΪ1��Ȼ���������2��bits��Ϊ101�����ǿ��Կ�����bits[2]
// ���Ϊ��1��Ȼ�������3��bits��Ϊ��101101�����ǿ���bits[5],bits[3],
// bits[2]���ֱ�Ϊ1�ˣ����ô����˿��ܵĺ�2��3��5���������Ǳ�������������
// ��ȥ��bits[sum >> 1]�Ƿ�Ϊ1���ɣ��μ��������£�

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        bitset<5001> bits(1);
        int sum = accumulate(nums.begin(), nums.end(), 0);
        for (int num : nums) bits |= bits << num;
        return (sum % 2 == 0) && bits[sum >> 1];
    }
};






int main(){
	Solution a; 

	vector<int> b = { 4, 1, -9, 0, INT_MAX }; 


	//TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
		3       8
	1    4   7    9
	*/



	///////////////////////////
	auto start = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	cout << endl << microseconds << " microseconds elapsed..." << endl;
}

