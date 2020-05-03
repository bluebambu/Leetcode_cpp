// _template.cpp : Defines the entry point for the console application.
//
#include <stdafx.h>

#include <iostream>
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

template <typename T>
void vprt(vector<T> v){
	for (auto i : v)
		cout << v << " ";
	cout << endl;
}

template <typename T>
void vvprt(vector<vector<T>> v){
	for (auto i : v){
		for (auto j : i){
			cout << j << " ";
		}
		cout << endl;
	}
	cout << endl;
}

template <typename C>
void setprt(C v){
	for (auto i : v)
		cout << i << " ";
	cout << endl;
}

template <typename C>
void mapprt(C v){
	for (auto i : v)
		cout << i.first << " " << i.second << endl;
	cout << endl;
}
////////////////////////////////////////////////////////////////
//Discuss 
//Pick One 


//The Hamming distance between two integers is the number of positions at which the corresponding bits are different.
//Now your job is to find the total Hamming distance between all pairs of the given numbers. 
//Example:
//Input: 4, 14, 2

//Output: 6

//Explanation: In binary representation, the 4 is 0100, 14 is 1110, and 2 is 0010 (just
//showing the four bits relevant in this case). So the answer will be:
//HammingDistance(4, 14) + HammingDistance(4, 2) + HammingDistance(14, 2) = 2 + 2 + 2 = 6.

//Note:
//Elements of the given array are in the range of 0 to 10^9 
//Length of the array will not exceed 10^4. 
// 
// 这道题是之前那道Hamming Distance的拓展，由于有之前那道题的经验，我们知道需要用异或来求每个位上的情况，那么我们需要来找出某种规律来，
// 比如我们看下面这个例子，4，14，2和1：
// 4  : 0 1 0 0
// 14 : 1 1 1 0
// 2  : 0 0 1 0
// 1  : 0 0 0 1
// 我们先看最后一列，有三个0和一个1，那么它们之间相互的汉明距离就是3，即1和其他三个0分别的距离累加，然后在看第三列，累加汉明距离为4，
// 因为每个1都会跟两个0产生两个汉明距离，同理第二列也是4，第一列是3。我们仔细观察累计汉明距离和0跟1的个数，我们可以发现其实就是0的个
// 数乘以1的个数，发现了这个重要的规律，那么整道题就迎刃而解了，只要统计出每一位的1的个数即可，参见代码如下：

// pass AC. 
class Solution {
public:
	int totalHammingDistance(vector<int>& nums) {
		int res = 0; 
		int n = nums.size(); 
		for (int i = 0; i < 32; ++i){
			int oneNum = 0; 
			int m = (1 << i); 
			for (int j = 0; j < n; ++j){
				if (nums[j] & m)
					++oneNum; 
			}
			res += oneNum * (n - oneNum); 
		}
		return res; 
	}
};


class Solution2 {
public:
	int totalHammingDistance(vector<int>& nums) {
		int res = 0; 
		for (int i = 0; i < 32; ++i){
			int one = (1 << i );
			int numone = 0; 
			for (int j = 0; j < nums.size(); ++j){
				if (nums[j] & one > 0)
					numone += 1; 
			}
			res += numone*(nums.size() - numone); 
		}
		return res; 
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


}

