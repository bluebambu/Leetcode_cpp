// _template4.cpp : Defines the entry point for the console application.
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

typedef vector<int> VI; 
typedef vector<VI> VVI; 
typedef pair<int, int> PII; 

VVI dirs = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } }; 

class Solution {
public:
    int slidingPuzzle(vector<vector<int>>& board) {
		string state; 
		for (auto& i : board){
			for (int j : i){
				state.push_back('0' + j); 
			}
		}

		int step = 0; 
		queue<string> q;; 
		unordered_set<string> v; 
		q.push(state); v.insert(state); 
		string finalstate = "123450"; 

		while (!q.empty()){
			int sz = q.size(); 

			for (int k = 0; k < sz; ++k){
				string f = q.front();
				q.pop();
				if (f == finalstate) return step; 

				int idx = find(f.begin(), f.end(), '0') - f.begin();
				if (idx + 1 != state.size() && idx + 1 != 3){
					swap(f[idx], f[idx + 1]);
					if (!v.count(f)){
						v.insert(f);
						q.push(f);
					}
					swap(f[idx], f[idx + 1]);
				}
				if (idx - 1 != -1 && idx - 1 != 2){
					swap(f[idx], f[idx - 1]);
					if (!v.count(f)){
						v.insert(f);
						q.push(f);
					}
					swap(f[idx], f[idx - 1]);
				}
				if (idx + 3 < f.size()){
					swap(f[idx], f[idx + 3]);
					if (!v.count(f)){
						v.insert(f);
						q.push(f);
					}
					swap(f[idx], f[idx + 3]);
				}
				if (idx - 3 < f.size()){
					swap(f[idx], f[idx - 3]);
					if (!v.count(f)){
						v.insert(f);
						q.push(f);
					}
					swap(f[idx], f[idx - 3]);
				}
			}
			++step; 
		}

		return -1; 
    }
};

// pass 100%
class Solution2 {
public:
	int slidingPuzzle(vector<vector<int>>& board) {
		queue<pair<VVI, int>> q; 
		unordered_set<string> v; 
		q.push({ board, 0 });
		v.insert(encode(board)); 
		VVI finalstate = { { 1, 2, 3 }, { 4, 5, 0 } }; 

		while (!q.empty()){
			auto cur = q.front().first; 
			int step = q.front().second; 
			q.pop(); 
			if (cur == finalstate) return step; 

			vector<int> zeroPos = findzero(cur); 
			int x = zeroPos[0], y = zeroPos[1]; 
			for (auto d : dirs){
				int xx = x + d[0], yy = y + d[1]; 
				if (xx >= 0 && xx < 2 && yy >= 0 && yy < 3){
					swap(cur[x][y], cur[xx][yy]); 
					string code = encode(cur); 
					if (v.count(code) == 0){
						v.insert(code); 
						q.push({ cur, step + 1 }); 
					}
					swap(cur[x][y], cur[xx][yy]); 
				}
			}
		}
		return -1; 
	}

	string encode(VVI& board){
		string res; 
		for (auto& i : board)
			for (auto& j : i)
				res.push_back('0' + j); 
		return res; 
	}

	vector<int> findzero(VVI& b){
		for (int i = 0; i < b.size(); ++i){
			for (int j = 0; j < b[i].size(); ++j){
				if (b[i][j] == 0)
					return{ i, j }; 
			}
		}
		return{}; 
	}
};


int main(){
	Solution a;
	Solution2 a2;

	vector<vector<int>> d = { { 4, 1, 2 }, { 5, 0, 3 } }; 

	cout << a.slidingPuzzle(d) << endl; 
	cout << a2.slidingPuzzle(d) << endl; 



	//TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6,
		new TreeNode(3, new TreeNode(1),
						new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
						new TreeNode(9,
		                               new TreeNode(10),
		                               nullptr)));
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

