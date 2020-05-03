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


struct TreeNode {
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
// Given an array of scores that are non-negative integers. Player 1 picks one of the numbers from either end of the array followed by the player 2 and then player 1 and so on. Each time a player picks a number, that number will not be available for the next player. This continues until all the scores have been chosen. The player with the maximum score wins.

// Given an array of scores, predict whether player 1 is the winner. You can assume each player plays to maximize his score.

// Example 1:

// Input: [1, 5, 2]
// Output: False
// Explanation: Initially, player 1 can choose between 1 and 2. 
// If he chooses 2 (or 1), then player 2 can choose from 1 (or 2) and 5. If player 2 chooses 5, then player 1 will be left with 1 (or 2). 
// So, final score of player 1 is 1 + 2 = 3, and player 2 is 5. 
// Hence, player 1 will never be the winner and you need to return False.

// Example 2:

// Input: [1, 5, 233, 7]
// Output: True
// Explanation: Player 1 first chooses 1. Then player 2 have to choose between 5 and 7. No matter which number player 2 choose, player 1 can choose 233.
// Finally, player 1 has more score (234) than player 2 (12), so you need to return True representing player1 can win.

// Note:



// wrong answer!! 
class Solution {
public:
	bool PredictTheWinner(vector<int>& nums) {
		int n = nums.size(); 
		vector<vector<bool>> visited(n, vector<bool>(2, -1)); 
		return helper(nums, 0, 1, 0, 0, visited) || helper(nums, n-1, 0, 0, 0, visited); 
	}

	bool helper(vector<int>& nums, int meid, bool isLeft, int mesum, int hesum, vector<vector<bool>>& visited){
		int n = nums.size(); 
		if (n % 2 == 0 && (isLeft ? meid > n / 2 -1 : meid < n / 2 - 1)){
			return mesum > hesum; 
		}
		if (n % 2 == 1 && (isLeft ? meid > n / 2 : meid < n / 2)){
			return mesum > hesum; 
		}

		int heid = n - meid - 1; 

		bool cur =  helper(nums, meid + 1, isLeft, mesum + nums[meid], hesum + nums[heid], visited) && 
			helper(nums, heid-1, !isLeft, mesum + nums[meid], hesum + nums[heid], visited) && 
			helper(nums, meid + 2, isLeft, mesum + nums[meid], hesum + nums[meid+1], visited) &&
			helper(nums, heid, !isLeft, mesum + nums[meid], hesum + nums[meid+1], visited) ; 

		return cur; 
	}
};


// pass AC
class Solution2 {
public:
	bool PredictTheWinner(vector<int>& nums) {
		if (nums.size() == 1) // for case nums = {0}
			return true; 

		int n = nums.size(); 
		return canWin(nums, 0, n - 1, 0, 0, 1); 
	}

	bool canWin(vector<int>& nums, int st, int end, int mesum, int hesum, int player){
		if (st == end){
			return player == 1 ? (mesum + nums[st] > hesum) : (mesum < hesum + nums[st]); 
		}

		if (player == 1){
			return !canWin(nums, st + 1, end, mesum + nums[st], hesum, 2) ||
				!canWin(nums, st, end - 1, mesum + nums[end], hesum, 2); 
		}

		return !canWin(nums, st + 1, end, mesum, hesum + nums[st], 1) ||
			!canWin(nums, st, end - 1, mesum, hesum + nums[end], 1);
	}
}; 

// mesum is dynamic
class Solution3 {
public:
	bool PredictTheWinner(vector<int>& nums) {
		if (nums.size() == 1) // for case nums = {0}
			return true;

		int n = nums.size();
		return canWin(nums, 0, n - 1, 0, 0, 1);
	}

	bool canWin(vector<int>& nums, int st, int end, int mesum, int hesum, int player){
		if (st == end)
			return mesum + nums[st] > hesum;

		return !canWin(nums, st + 1, end, hesum, mesum + nums[st], player==1?2:1) ||
			!canWin(nums, st, end - 1, hesum, mesum + nums[end], player==1?2:1);
	}
};


class Solution4 {
public:
    bool PredictTheWinner(vector<int>& nums) {
		unordered_map<int, unordered_map<int, bool>> m; 
		return dfs(nums, 0, nums.size() - 1, 0, 0, m, 0); 
	}

	bool dfs(vector<int>& nums, int i, int j, int curpScore, int anotherpScore, unordered_map<int, unordered_map<int, bool>>& m, int curpl){
		if (i > j)
			return (curpScore > anotherpScore) || (curpScore == anotherpScore && curpl == 0); 

		int n = nums.size(), idx = i*n + j; 
		if (m.count(idx) && m[idx].count(curpScore))
			return m[idx][curpScore]; 

		bool res = (!dfs(nums, i + 1, j, anotherpScore, curpScore + nums[i], m, !curpl)) | (!dfs(nums, i, j - 1, anotherpScore, curpScore + nums[j], m, !curpl)); 

		m[idx][curpScore] = res; 
		return res; 
	}
};

// best solution
class Solution5 {
public:
	bool PredictTheWinner(vector<int>& nums) {
		unordered_map<int, unordered_map<int, int>> m; 
		return dfs(nums, 0, nums.size() - 1, m) >= 0; 
	}

	int dfs(vector<int>& nums, int i, int j, unordered_map<int, unordered_map<int, int>>& m){
		if (i > j)
			return 0; 

		if (m.count(i) && m[i].count(j))
			return m[i][j]; 

		int r = max(nums[i] - dfs(nums, i + 1, j, m), nums[j] - dfs(nums, i, j - 1, m)); 
		return r;
	}
}; 


class Solution6{
public:
	int PredictTheWinner(vector<int>& nums) {
		int n = nums.size(); 
		vector<vector<int>> dp(n, vector<int>(n, 0)); 
		for (int j = 0; j < n; ++j){
			for (int i = j; i >= 0; --i){
				if (i == j)
					dp[i][j] = nums[i];
				else if (i == j - 1)
					dp[i][j] = max(nums[i], nums[j]);
				else{
					int r1 = nums[i] + min(dp[i + 2][j], dp[i + 1][j - 1]),
						r2 = nums[j] + min(dp[i][j - 2], dp[i + 1][j - 1]);

					dp[i][j] = max(r1, r2); 
				}
			}
		}
		
		return dp[0][n - 1]; 
	}
};

class Solution7{
public:
	bool PredictTheWinner(vector<int>& nums) {
		int n = nums.size();
		return win(nums, 0, n - 1) > 0; 
	}

	int win(vector<int>& nums, int l, int r){
		if (l == r) return nums[l]; 
		return max(nums[l] - win(nums, l + 1, r), nums[r] - win(nums, l, r - 1)); 
	}
}; 


class Solution8{
public:
	bool PredictTheWinner(vector<int>& nums) {
		return win(nums, 0, nums.size() - 1) > 0; 
	}
	int win(vector<int>& nums, int i, int j){
		if (i == j) return nums[i]; 
		if (i > j) return 0; 
		return max(nums[i] - win(nums, i + 1, j), nums[j] - win(nums, i, j - 1)); 
	}
}; 



int main(){
	Solution6 a; 
	Solution7 a2; 

	vector<int> b = { 1, 5, 2 }; 
	vector<int> b2 = { 0 };

	cout << a.PredictTheWinner(b) << endl;
	cout << a2.PredictTheWinner(b) << endl;


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

