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
#include <chrono>
#include <bitset>

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

// 下面来看一种投机取巧的方法，直接利用了built - in的函数bitset的count函数可以直接返回1的个数，题目中说了不提倡用这种方法，写出来只是多一种思路而已：
// 解法二：

class Solution1 {
public:
	vector<int> countBits(int num) {
		vector<int> res;
		for (int i = 0; i <= num; ++i) {
			res.push_back(bitset<32>(i).count());
		}
		return res;
	}
};


// 下面这种方法相比第一种方法就要简洁很多了，这个规律找的更好，规律是，从1开始，遇到偶数时，其1的个数和该偶数除以2得到的数字的1的个数相同，遇到奇数时，其1的个数等于该奇数除以2得到的数字的1的个数再加1，参见代码如下：
// 解法三：

class Solution2 {
public:
	vector<int> countBits(int num) {
		vector<int> res{ 0 };
		for (int i = 1; i <= num; ++i) {
			if (i % 2 == 0) res.push_back(res[i / 2]);
			else res.push_back(res[i / 2] + 1);
		}
		return res;
	}
};


// 下面这种方法就更加巧妙了，巧妙的利用了i&(i - 1)， 这个本来是用来判断一个数是否是2的指数的快捷方法，比如8，二进制位1000, 那么8&(8 - 1)为0，只要为0就是2的指数, 那么我们现在来看一下0到15的数字和其对应的i&(i - 1)值：

// i    bin    '1'    i&(i - 1)
// 0    0000    0
// ---------------------- -
// 1    0001    1    0000
// ---------------------- -
// 2    0010    1    0000
// 3    0011    2    0010
// ---------------------- -
// 4    0100    1    0000
// 5    0101    2    0100
// 6    0110    2    0100
// 7    0111    3    0110
// ---------------------- -
// 8    1000    1    0000
// 9    1001    2    1000
// 10   1010    2    1000
// 11   1011    3    1010
// 12   1100    2    1000
// 13   1101    3    1100
// 14   1110    3    1100
// 15   1111    4    1110

// 我们可以发现每个i值都是i&(i - 1)对应的值加1，这样我们就可以写出代码如下：
// 解法四：

class Solution3 {
public:
	vector<int> countBits(int num) {
		vector<int> res(num + 1, 0);
		for (int i = 1; i <= num; ++i) {
			res[i] = res[i & (i - 1)] + 1;
		}
		return res;
	}
};


class Solution {
public:
	vector<int> countBits(int num) {
		vector<int> res; 
		res.push_back(0); 
		for (int i = 1; i <= num; ++i){
			if (i % 2 == 0){
				res.push_back(res[i / 2]); 
			}
			else{
				res.push_back(res[i / 2] + 1); 
			}
		}
		return res; 
	}
};

int main(){
	Solution a;

	vector<int> b = { 7, 2, 5, 10, INT_MAX };


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

