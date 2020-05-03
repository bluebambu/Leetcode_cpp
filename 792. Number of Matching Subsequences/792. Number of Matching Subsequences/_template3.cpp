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
typedef vector<int> VI; 
typedef vector<vector<int>> VVI; 

// TLE
class Solution {
public:
	int numMatchingSubseq(string S, vector<string>& words) {
		int n = words.size();; 
		if (n == 0 || S.empty())
			return 0; 
		vector<int> w_idx(n, 0); 

		int cnt = 0; 
		for (char c: S){
			for (int i = 0; i < n; ++i){
				string cur_w = words[i]; 
				int cur_i = w_idx[i]; 
				if (cur_i < cur_w.size() && cur_w[cur_i]==c){
					w_idx[i] += 1; 
					if (w_idx[i] == cur_w.size())
						++cnt; 
				}
			}
		}
		return cnt; 
	}
};

class Solution2 {
public:
	int numMatchingSubseq(string S, vector<string>& words) {
		unordered_map<char, vector<int>> idx_map; 
		for (int i = 0; i < S.size(); ++i){
			idx_map[S[i]].push_back(i); 
		}

		int res = 0; 
		for (auto& w : words){
			int last_pos = -1; 
			bool isgood = true; 
			for (char c : w){
				vector<int>& cur_map = idx_map[c]; 
				auto iter = upper_bound(cur_map.begin(), cur_map.end(), last_pos); 
				if (iter == cur_map.end()){
					isgood = false; 
					break;
				}
				last_pos = *iter; 
			}
			if (isgood)
				++res; 
		}

		return res; 
	}
 }; 


class Solution3 {
public:
	int numMatchingSubseq(string S, vector<string>& words) {
		unordered_map<char, vector<int>> m; 
		int cnt = 0; 
		for (int i = 0; i < S.size(); ++i) m[S[i]].push_back(i); 

		for (int i = 0; i < words.size(); ++i){
			string cur = words[i]; 
			int i = 0, si = -1; 
			bool success = true; 
			for (; i < cur.size(); ++i){
				vector<int>& posv = m[cur[i]]; 
				auto iter = upper_bound(posv.begin(), posv.end(), si); 
				if (iter == posv.end()){
					success = false; 
					break;
				}
				si = *iter; 
			}
			if (success){
				cnt += 1; 
			}
		}

		return cnt; 
	}
};

int main(){
	Solution a;
	Solution2 a2;

	string s = "abcde"; 
	vector<string> words = {
		"a",
		"bb",
		"acd",
		"ace"
	};

	cout << a.numMatchingSubseq(s, words) << endl; 
	cout << a2.numMatchingSubseq(s, words) << endl; 


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

