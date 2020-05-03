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

// In the "100 game," two players take turns adding, to a running total, any integer from 1..10. The player who first causes the running total to reach or exceed 100 wins. 
// What if we change the game so that players cannot re-use integers? 
// For example, two players might take turns drawing from a common pool of numbers of 1..15 without replacement until they reach a total >= 100.
// Given an integer maxChoosableInteger and another integer desiredTotal, determine if the first player to move can force a win, assuming both players play optimally. 
// You can always assume that maxChoosableInteger will not be larger than 20 and desiredTotal will not be larger than 300. 
// Example 
// Input:
// maxChoosableInteger = 10
// desiredTotal = 11

// Output:
// false

// Explanation:
// No matter which integer the first player choose, the first player will lose.
// The first player can choose an integer from 1 up to 10.
// If the first player choose 1, the second player can only choose integers from 2 up to 10.
// The second player will win by choosing 10 and get a total = 11, which is >= desiredTotal.
// Same with other integers chosen by the first player, the second player will always win.


// pass AC. State suppression. DFS+DP. 
class Solution {
public:
	bool canIWin(int maxChoosableInteger, int desiredTotal) {
		if ((1 + maxChoosableInteger)*maxChoosableInteger / 2 < desiredTotal)
			return false;
		if (maxChoosableInteger >= desiredTotal)
			return true; 
		unordered_map<int, bool> visited; 
		return helper(maxChoosableInteger, desiredTotal, 0, visited); 
	}

	bool helper(int maxInt, int target, int used, unordered_map<int, bool>& visited){
		if (target <= 0)
			return false; 
		if (visited.count(used))
			return visited[used]; 

		for (int i = 1; i <= maxInt; ++i){
			int bit = (1 << (i - 1)); 
			if ((bit & used) == 0){
				if (!helper(maxInt, target - i, used | bit, visited)){
					visited[used] = true; 
					return true; 
				}
			}
		}
		visited[used] = false; 
		return false; 
	}
};

// {18,79} case is very slow, TLE.
class Solution2 {
public:
    bool canIWin(int maxChoosableInteger, int desiredTotal) {
		// max, tot
		// 0-me 1-oponent
		for (int i = 1; i <= maxChoosableInteger; ++i){
			int v=0;
			unordered_map<int, unordered_map<int, unordered_map<int, int>>> m;
			if (dfs(i, v, 0, desiredTotal, maxChoosableInteger, m))
				return true; 
		}
		return false; 
    }

	bool dfs(int cur, int v, int plyr, int tot, int cmax, unordered_map<int, unordered_map<int, unordered_map<int, int>>>& m) {
		//cout << cur << ' ' << plyr << ' ' << tot << endl; 
		if (tot <= cur)
			return true; 

		if (m.count(v) && m[v].count(cur) && m[v][cur].count(plyr))
			return m[v][cur][plyr]; 

		v |= (1 << cur - 1);
		for (int i = 1; i <= cmax; ++i){
			if (!(v & (1 << i - 1))){
				if (dfs(i, v, !plyr, tot - cur, cmax, m)){
					v ^= (1 << cur - 1);
					m[v][cur][plyr] = false; 
					return false; 
				}
			}
		}
		v ^= (1 << cur - 1); 

		m[v][cur][plyr] = true;
		return true; 
	}
};


class Solution3 {
public:
	bool canIWin(int maxChoosableInteger, int desiredTotal) {
		if ((1 + maxChoosableInteger)*maxChoosableInteger / 2 < desiredTotal)
			return false; 
		if (desiredTotal < maxChoosableInteger)
			return true; 
		unordered_map<int, bool> m; 
		return dfs(0, desiredTotal, maxChoosableInteger, m); 
	}

	bool dfs(int stt, int tot, int cmax, unordered_map<int, bool>& m){
		if (m.count(stt))
			return m[stt]; 

		for (int i = cmax; i >= 1; --i){
			if (!(stt&(1 << i - 1))){
				if (i >= tot)
					return true; 

				stt |= (1 << i - 1); 
				if (!dfs(stt, tot - i, cmax, m)){
					stt ^= (1 << i - 1);
					m[stt] = true; 
					return true; 
				}
				stt ^= (1 << i - 1); 
			}
		}
		m[stt] = false; 
		return false; 
	}
}; 


// pass
class Solution4 {
public:
	bool canIWin(int maxChoosableInteger, int desiredTotal) {
		if (desiredTotal < 1)
			return true; 
		if ((maxChoosableInteger + 1)*maxChoosableInteger / 2 < desiredTotal)
			return false; 

		unordered_map<int, bool> m; 
		return win(maxChoosableInteger, desiredTotal, 0, m); 
	}
	bool win(int maxI, int tot, int state, unordered_map<int, bool>& m){
		if (m.count(state))
			return m[state]; 

		if (tot <= 0)
			return false; 
		int orig = state; 

		for (int i = 1; i <= maxI; ++i){
			if (!(state & (1 << i - 1))){
				state |= (1 << i - 1); 
				if (!win(maxI, tot - i, state, m)){
					m[orig] = true; 
					return true; 
				}
				state ^= (1 << i - 1); 
			}
		}
		m[orig] = false; 
		return false; 
	}
}; 

class Solution5 {
public:
	bool canIWin(int maxChoosableInteger, int desiredTotal) {
		unordered_set<int> picked; 
		auto r = win(maxChoosableInteger, desiredTotal, picked); 
		for (auto k : picked) cout << k << " "; 
		return r; 
	}
	bool win(int maxint, int remain, unordered_set<int>& picked){
		if (remain <= 0) return false; 
		for (int i = 1; i <= maxint; ++i){
			if (picked.count(i) == 0){
				picked.insert(i); 
				if (!win(maxint, remain - i, picked)){
					picked.erase(i); 
					return true; 
				}
				picked.erase(i); 
			}
		}
		return false; 
	}
};


// pass
class Solution6 {
public:
	unordered_map<int, bool> cache; 
	bool canIWin(int maxChoosableInteger, int desiredTotal) {
		if (desiredTotal == 0) return true; 
		if (maxChoosableInteger*(maxChoosableInteger + 1) < desiredTotal * 2) return false; 
		return dfs(maxChoosableInteger, desiredTotal, 0); 
	}
	bool dfs(int maxint, int remain, int status){
		if (remain <= 0) return false; 
		if (cache.count(status)) return cache[status]; 
		bool r = false; 
		for (int i = 1; i <= maxint; ++i){
			if ((status & (1 << i - 1)) == 0){
				if (!dfs(maxint, remain - i, status | (1 << i - 1))){
					cache[status] = true; 
					return true; 
				}
			}
		}
		cache[status] = false; 
		return false; 
	}
};

int main(){													 
	Solution5 a;

	cout << a.canIWin(10, 11) << endl;  // false; 
	cout << a.canIWin(4, 6) << endl;	// true; 
	cout << a.canIWin(6, 7) << endl;  // false; 
	cout << a.canIWin(10, 40) << endl;  // false; 
	cout << a.canIWin(18, 79) << endl;  // true, heavy cost calc
	cout << a.canIWin(20, 210) << endl;  // false, heavy cost calc

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

