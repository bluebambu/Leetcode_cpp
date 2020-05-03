// _template.cpp : Defines the entry point for the console application.
//
#include <stdafx.h>

#include <iostream>
#include <functional>
#include <bitset>
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

vector<vector<int>> dirs = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };
typedef pair<int, int> PII;
typedef vector<long long> VI; 
typedef vector<vector<long long>> VVI; 


// TLE
class Solution {
public:
	int numMusicPlaylists(int N, int L, int K) {
		vector<long long> path; 
		vector<long long> nextpos(N+1, 0); 
		unordered_map<int, int> used; 
		int cnt = 0; 
		dfs(N, L, K, path, nextpos, cnt, used); 
		return cnt; 
	}

	void dfs(int N, int L, int K, VI& path, VI& nextpos, int& cnt, unordered_map<int, int>& used){
		if (path.size() == L){
			if (used.size() == N)
				cnt += 1;
			return; 
		}

		for (int i = 1; i <= N; ++i){
			if (nextpos[i] <= path.size()){
				int old = nextpos[i]; 
				nextpos[i] = path.size() + K + 1; 
				path.push_back(i); 
				used[i] += 1; 
				dfs(N, L, K, path, nextpos, cnt, used); 
				path.pop_back(); 
				nextpos[i] = old; 
				used[i] -= 1; 
				if (used[i] == 0)
					used.erase(i); 
			}
		}
	}
};


// pass
long long mod = 1e9 + 7; 

class Solution2 {
public:
	int numMusicPlaylists(int N, int L, int K) {
		VVI dp(N + 1, VI(L + 1, 0)); 
		dp[1][1] = N; 
		
		for (int j = 1; j <= L; ++j){
			for (int i = 1; i <= N; ++i){
				if (i==1 && j==1)
					continue;
				long long choose_new_song = (dp[i - 1][j - 1] * (N - (i - 1))) % mod;
				long long choose_old_song = (i <= K ? 0 : (dp[i][j - 1] * (i - K))%mod); 
				dp[i][j] = (choose_old_song + choose_new_song )%mod;
			}
		}

		prt2Layer(dp); 

		return (int)dp[N][L]; 
	}
}; 




int main(){
	Solution2 a;

	cout << a.numMusicPlaylists(3, 3, 1) << endl; 
	cout << a.numMusicPlaylists(2, 3, 0) << endl; 
	cout << a.numMusicPlaylists(2, 3, 1) << endl; 
	cout << a.numMusicPlaylists(16, 16, 4) << endl; 


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

