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
// 有 N 件物品和一个容量为 V 的背包。放入第 i 件物品耗费的费用是 Ci，得到的
// 价值是 Wi。求解将哪些物品装入背包可使价值总和最大。

class backpack_1{
public:
	int maxval(vector<int>& c, vector<int>& w, int v){
		// dp[i][j] = max(dp[i-1][j], dp[i-1][j-ci]+wi)
		int n = c.size(); 
		vector<vector<int>> dp(n + 1, vector<int>(v + 1, 0)); 

		for (int i = 1; i < n; ++i){
			for (int j = 1; j < v + 1; ++j){ // optimized 方法可以从 V->c[i]， 但是朴素方法必须从 v->0， 因为状态要传递下去
				if (j >= c[i])
					dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - c[i]] + w[i]);
				else // if j<c[i], no updates but status need to be recorded. 
					dp[i][j] = dp[i - 1][j]; 
			}
		}

		return dp[n][v]; 
	}
};


class backpack_1_optimized {
public:
	int maxval(vector<int>& c, vector<int>& w, int v){
		// dp[i][j] = max(dp[i-1][j], dp[i-1][j-ci]+wi)
		int n = c.size();
		vector<int> dp(v + 1, 0); 

		for (int i = 0; i < n; ++i){
			for (int j = v; j >= c[i]; --j){
				dp[j] = max(dp[j], dp[j - c[i]] + w[i]); 
			}
		}

		return dp[v]; 
	}
};

// 我们看到的求最优解的背包问题题目中，事实上有两种不太相同的问法。有的题目
// 要求“恰好装满背包”时的最优解，有的题目则并没有要求必须把背包装满。一种区别
// 这两种问法的实现方法是在初始化的时候有所不同。
// 如果是第一种问法，要求恰好装满背包，那么在初始化时除了 F[0] 为 0，其它
// F[1::V] 均设为 −infi，这样就可以保证最终得到的 F[V] 是一种恰好装满背包的最优解。
// 如果并没有要求必须把背包装满，而是只希望价格尽量大，初始化时应该将 F[0::V]
// 全部设为 0。

//////////////////////////////////////////////
// 有 N 种物品和一个容量为 V 的背包，每种物品都有无限件可用。放入第 i 种物品
// 的费用是 Ci，价值是 Wi。求解：将哪些物品装入背包，可使这些物品的耗费的费用总
// 和不超过背包容量，且价值总和最大

class backpack_2 {
public:
	int maxval(vector<int>& c, vector<int>& w, int v){
		// dp[i][j] = max( dp[i-1][j], max( dp[i-1][j-k*ci]+k*wi ) )
		// equals to: dp[i][j] = max( dp[i-1][j-k*ci]+k*wi ) for 0<= k <=j

		int n = c.size(); 
		vector<vector<int>> dp(n + 1, vector<int>(v + 1, 0)); 

		for (int i = 1; i < n + 1; ++i){
			for (int j = 1; j < v + 1; ++j){
				for (int k = 0; j - k*c[i] >= 0; ++k){
					dp[i][j] = max(dp[i-1][j], dp[i-1][j-k*c[i]]+k*w[i]);
				}
			}
		}

		return dp[n][v]; 
	}
};
class backpack_2_optimized {
public:
	int maxval(vector<int>& c, vector<int>& w, int v){
		// 直接从 1 推出 2 的 n方 逻辑， 不是特别直观。 
		// 我觉得更好的是理解另一个等价的dp 推导式： dp[i][j] = max( dp[i-1][j], dp[i][j-c[i]]+w[i])
		// 即本次 i 循环的 dp[i][j] 可以由 dp[i][j-c[i]] 得到， 因为 i 元素可以选择多次。 
		int n = c.size(); 

		vector<int> dp(v + 1, 0); 
		for (int i = 0; i < n; ++i){
			for (int j = c[i]; j < v + 1; ++j){
				dp[j] = max(dp[j], dp[j - c[i]] + w[i]); 
			}
		}
		return dp[v]; 
	}
};


// 有 N 种物品和一个容量为 V 的背包。第 i 种物品最多有 Mi 件可用，每件耗费的
// 空间是 Ci，价值是 Wi。求解将哪些物品装入背包可使这些物品的耗费的空间总和不超
// 过背包容量，且价值总和最大

class backpack_3 {
public:
	int maxval(vector<int>& c, 
		vector<int>& w, 
		vector<int>& M,
		int v
		){
		int n = c.size(); 

		vector<vector<int>> dp(n + 1, vector<int>(v + 1, 0)); 

		for (int i = 1; i < n + 1; ++i){
			for (int j = 1; j < v + 1; ++j){
				for (int k = 0; j - k*c[i] >= 0 && k <= M[i]; ++k){
					dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - k*c[i]] + w[i]); 
				}
			}
		}
		return dp[n][v]; 
	}
};
class backpack_3_optimized {
public:
	// seems too complicated to me....
	int maxval(vector<int>& c,
		vector<int>& w,
		vector<int>& M,
		int v
		){
		int n = c.size();
	}
};


// 二维费用的背包问题是指：对于每件物品，具有两种不同的费用，选择这件物品必
// 须同时付出这两种费用。对于每种费用都有一个可付出的最大值（背包容量）。问怎样
// 选择物品可以得到最大的价值。
// 设第 i 件物品所需的两种费用分别为 Ci 和 Di。两种费用可付出的最大值（也即两
// 种背包容量）分别为 V 和 U。物品的价值为 Wi

class backpack_4 {
public:
	int maxval(vector<int>& c,
		vector<int>& d,
		vector<int>& w,
		int v, int u
		){
		int n = c.size(); 

		vector<vector<vector<int>>> dp(n + 1,
			vector<vector<int>>(v + 1,
			vector<int>(u + 1, 0))); 

		for (int i = 1; i < n + 1; ++i){
			for (int j = 0; j < v + 1; ++j){
				for (int k = 0; k < u + 1;; ++u){
					if (j < c[i] || k < d[i])
						dp[i][j][k] = dp[i - 1][j][k]; 
					else{
						dp[i][j][k] = max(dp[i - 1][j][k], dp[i - 1][j - c[i]][k - d[i]] + w[i]); 
					}
				}
			}
		}

		return dp[n][u][v]; 
	}
};
class backpack_4_optimized {
public:
	int maxval(vector<int>& c,
		vector<int>& d,
		vector<int>& w,
		int v, int u
		){
		int n = c.size();

		vector<vector<int>> dp(v + 1, vector<int>(u + 1, 0)); 
		// dp[i + 1][j][k] = max(dp[i][j][k], dp[i][j - s*c[i]][k - s*d[i]] + s*w[i]);
		for (int i = 0; i < n; ++i){
			for (int j = v; j >= c[i]; --j){
				for (int k = u; u >= d[i]; --k){
					dp[j][k] = max(dp[j][k], dp[j - c[i]][k - d[i]] + w[i]); 
				}
			}
		}

		return dp[u][v]; 
	}
};

// 二维完全背包？？？


int main(){


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

