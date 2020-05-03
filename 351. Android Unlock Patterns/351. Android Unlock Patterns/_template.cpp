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
#include <set>
#include <unordered_set>

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

// Given an Android 3x3 key lock screen and two integers m and n, where 1 ≤ m ≤ n ≤ 9, count the total number of 
// unlock patterns of the Android lock screen, which consist of minimum of m keys and maximum n keys.

// Rules for a valid pattern :
// Each pattern must connect at least m keys and at most n keys.
// All the keys must be distinct.
// If the line connecting two consecutive keys in the pattern passes through any other keys, the other keys must 
// have previously selected in the pattern.No jumps through non selected key is allowed.

// The order of keys used matters.

// Explanation :
// 			| 1 | 2 | 3 |
// 			| 4 | 5 | 6 |
// 			| 7 | 8 | 9 |
// 			Invalid move : 4 - 1 - 3 - 6
// 			Line 1 - 3 passes through key 2 which had not been selected in the pattern.

// 			Invalid move : 4 - 1 - 9 - 2
// 			Line 1 - 9 passes through key 5 which had not been selected in the pattern.

// 			Valid move : 2 - 4 - 1 - 3 - 6
// 			Line 1 - 3 is valid because it passes through key 2, which had been selected in the pattern

// 			Valid move : 6 - 5 - 4 - 1 - 9 - 2
// 			Line 1 - 9 is valid because it passes through key 5, which had been selected in the pattern.

// 		Example :
// 				Given m = 1, n = 1, return 9.


// 这道题乍一看题目这么长以为是一个设计题，其实不是，这道题还是比较有意思的，起码跟实际结合的比较紧密。
// 这道题说的是安卓机子的解锁方法，有9个数字键，如果密码的长度范围在[m, n]之间，问所有的解锁模式共有多少种，
// 注意题目中给出的一些非法的滑动模式。那么我们先来看一下哪些是非法的，首先1不能直接到3，必须经过2，同理的有4到6，
// 7到9，1到7，2到8，3到9，还有就是对角线必须经过5，例如1到9，3到7等。我们建立一个二维数组jumps，用来记录两个数字键之间是否有中间键，
// 然后再用一个一位数组visited来记录某个键是否被访问过，然后我们用递归来解，我们先对1调用递归函数，在递归函数中，
// 我们遍历1到9每个数字next，然后找他们之间是否有jump数字，如果next没被访问过，并且jump为0，或者jump被访问过，
// 我们对next调用递归函数。数字1的模式个数算出来后，由于1, 3, 7, 9是对称的，所以我们乘4即可，然后再对数字2调用递归函数，
// 2, 4, 6, 9也是对称的，再乘4，最后单独对5调用一次，然后把所有的加起来就是最终结果了，参见代码如下：

// CAUTION!!! 1->8, 2->9, 沒有正穿過某一個數，所以算valid...... holy shit！！


class Solution {
public:
	int numberOfPatterns(int m, int n) {
		vector<bool> visited(10, false); 
		vector<vector<int>> jumps(10, vector<int>(10, -1)); 

		vector<vector<int>> param = { 
			{ 1, 3, 2 }, 
			{ 1, 7, 4 }, 
			{ 1, 9, 5 }, 
			{ 2, 8, 5 }, 
			{ 4, 6, 5 }, 
			{ 7, 9, 8 },
			{ 3, 9, 6 }, 
			{ 3, 7, 5 }, 
		}; 

		for (auto i : param){
			jumps[i[0]][i[1]] = jumps[i[1]][i[0]] = i[2]; 
		}

		int r1 = 0; 
		calc(1, 1, r1, m, n, visited, jumps); 
		int r2 = 0; 
		calc(2, 1, r2, m, n, visited, jumps); 
		int r3 = 0; 
		calc(5, 1, r3, m, n, visited, jumps); 

		//cout << r1 << endl;
		//cout << r2 << endl;
		//cout << r3 << endl;

		return 4 * r1 + 4 * r2 + r3;
	}

	void calc(int pos, int len, int& res, int m, int n, vector<bool>& visited, vector<vector<int>>& jumps){
		if (len > n)
			return; 
		if (len >= m && len <= n)
			++res; 

		visited[pos] = true; 
		for (int i = 1; i < 10; ++i){
			if (i!=pos && !visited[i] && (jumps[pos][i]==-1 || visited[jumps[pos][i]])){
				calc(i, len + 1, res, m, n, visited, jumps); 
			}
		}
		visited[pos] = false; 
	}
};



class Solution2 {
public:
	int unlock(int m, int n){
		int res = 0; 
		vector<vector<int>> jumps(10, vector<int>(10, 0)); 
		vector<vector<int>> param = {
			{ 1, 3, 2 },
			{ 4, 6, 5 },
			{ 7, 9, 8 },
			{ 1, 7, 4 },
			{ 2, 8, 5 },
			{ 3, 9, 6 },
			{ 1, 9, 5 },
			{ 3, 7, 5 }
		};

		for (auto i : param){
			jumps[i[0]][i[1]] = i[2]; 
			jumps[i[1]][i[0]] = i[2]; 
		}

		vector<bool> bits(10, false); 
		vector<int> path; 
		helper(m, n, jumps, bits, path, res); 
		return res; 
	}

	void helper(int m, int n, 
		vector<vector<int>>& jumps, 
		vector<bool>& bits, 
		vector<int>& path, 
		int& res
		){
		if (path.size() >= m && path.size() <= n){
			++res; 
		// for (auto i : path)
		// 	cout << i << " "; 
		// cout << endl; 
		}
		if (path.size() > n)
			return; 

	
		for (int i = 1; i < 10; ++i){
			if (
				path.empty() ||
				( !bits[i] && (!jumps[path.back()][i] || (bits[jumps[path.back()][i]]))  )
				){
				path.push_back(i); 
				bits[i] = true; 
				helper(m, n, jumps, bits, path, res); 
				bits[i] = false; 
				path.pop_back(); 
			}
		}
	}
};

class Solution3 {
public:
	int numberOfPatterns(int m, int n) {
		int a = 0; 
		dfs(1, 1, (1<<0), m, n, a);
		int b = 0; 
		dfs(1, 2, (1<<1), m, n, b);
		int c = 0; 
		dfs(1, 5, (1<<4), m, n, c);
		cout << a << ' ';
		cout << b << ' ';
		cout << c << ' ';
		return a*4+b*4+c; 
	}

	void dfs(int len, int last, int v, int m, int n, int& cnt){
		if (len >= m && len <= n)
			++cnt; 
		if (len == n) {
			return;
		}

		for (int i = 1; i < 10; ++i){
			int curv = v; 
			if ((!exist(curv, i)) && (exist(curv, mid(i, last)))){
				curv |= (1 << i-1); 
				dfs(len + 1, i, curv, m, n, cnt); 
			}
		}
	}

	bool exist(int v, int i){
		if (i == -1)
			return true; 
		return (v&(1 << i-1)) > 0 ; 
	}

	int mid(int cur, int last){
		if (
			((cur == 1 && last == 3) || (cur == 3 && last == 1)) ||
			((cur == 1 && last == 7) || (cur == 7 && last == 1)) ||
			((cur == 9 && last == 3) || (cur == 3 && last == 9)) ||
			((cur == 9 && last == 7) || (cur == 7 && last == 9)) ||
			((cur == 1 && last == 9) || (cur == 9 && last == 1)) ||
			((cur == 2 && last == 8) || (cur == 8 && last == 2)) ||
			((cur == 7 && last == 3) || (cur == 3 && last == 7)) ||
			((cur == 4 && last == 6) || (cur == 6 && last == 4))
			)
			return (cur + last) / 2;
		else
			return -1; 
	}
};

class Solution4 {
public:
	int numberOfPatterns(int m, int n) {
		int tr1 = 0;
		dfs(1, 1, m, n, tr1, 1); 
		
		int tr2 = 0;
		dfs(2, 1, m, n, tr2, 2); 

		int tr5 = 0;
		dfs(5, 1, m, n, tr5, 1<<4); 

		cout << tr1 << ' '; 
		cout << tr2 << ' '; 
		cout << tr5 << ' '; 

		return tr1 * 4 + tr2 * 4 + tr5; 
	}

	void dfs(int last, int cnt, int m, int n, int& res, int v){
		if (cnt >= m && cnt <= n){
			res += 1; 
		}
		if (cnt == n)
			return;

		for (int i = 1; i < 10; ++i){
			if (!(v & 1 << i - 1)){
				if (mid(last, i) == -1 || (v & 1 << mid(last, i) - 1)){
					dfs(i, cnt + 1, m, n, res, v | 1 << i - 1);
				}
			}
		}
	}

	int mid(int cur, int last){
		if (
			((cur == 1 && last == 3) || (cur == 3 && last == 1)) ||
			((cur == 1 && last == 7) || (cur == 7 && last == 1)) ||
			((cur == 9 && last == 3) || (cur == 3 && last == 9)) ||
			((cur == 9 && last == 7) || (cur == 7 && last == 9)) ||
			((cur == 1 && last == 9) || (cur == 9 && last == 1)) ||
			((cur == 2 && last == 8) || (cur == 8 && last == 2)) ||
			((cur == 7 && last == 3) || (cur == 3 && last == 7)) ||
			((cur == 4 && last == 6) || (cur == 6 && last == 4))
			)
			return (cur + last) / 2;
		else
			return -1; 
	}
}; 



int main() {
	Solution a;
	cout << a.numberOfPatterns(1, 6)<<endl ; 


	Solution2 b; 
	cout << b.unlock(1, 6)<<endl ; 

	Solution3 c;
	cout << c.numberOfPatterns(1, 6)<<endl ; 

	Solution4 d;
	cout << d.numberOfPatterns(1, 6)<<endl ; 

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

