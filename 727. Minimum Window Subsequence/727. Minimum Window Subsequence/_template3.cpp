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

// wrong ans, cuz this only checks the appearance of each char, but lack the char order of subsequence. 
class Solution {
public:
    string minWindow(string S, string T) {
		unordered_map<char, int> m; 
		for (char c : T) m[c] += 1; 
		int tot = m.size(), i = 0, j = 0; 
		int res = INT_MAX, start, len; 
		while (1){
			for (; j < S.size(); ++j){
				if (tot == 0)
					break;
				char c = S[j];
				if (m.count(c)){
					m[c] -= 1;
					if (m[c] == 0)
						tot -= 1;
				}
			}

			if (tot != 0) break;

			for (; i < j; ++i){
				if (tot>0)
					break;
				char c = S[i]; 
				if (m.count(c)){
					m[c] += 1; 
					if (m[c] > 0){
						tot += 1; 
						if (res > j - i){
							res = j - i;
							start = i; 
						}
					}
				}
			}
		}

		return S.substr(start, res); 
    }
};


// pass, 88.8%
class Solution2 {
public:
	string minWindow(string S, string T) {
		int i = 0, j = 0, k = 0; 
		int start, len; 
		unordered_map<char, int> m; 
		int res = INT_MAX; 
		while (1){
			for (; j < S.size(); ++j){
				if (k==T.size())
					break;

				char c = S[j]; 
				if (c == T[k])
					++k; 
			}

			if (k!=T.size()) break;

			--k; 
			for (i = j - 1; i >= 0; --i){
				char c = S[i]; 
				if (c == T[k])
					--k; 
				if (k==-1)
					break;
			}

			if (res > j - i){
				res = j - i; 
				start = i; 
			}

			i += 1, j = i, k = 0; 
		}

		return res==INT_MAX ? "" : S.substr(start, res); 
	}
}; 


class Solution3 {
public:
	string minWindow(string S, string T) {
		string res; 
		int len = S.size(); 
		int i = 0; 
		while (true){
			// going left to right
			int j = 0; int k = i; 
			while (j < T.size() && k < S.size()){
				if (T[j] == S[k])
					++k, ++j;
				else
					++k; 
			}

			// end of going
			if (k == S.size() && j < T.size()) break;;

			// going right to left
			int kk = k-1; 
			while (kk >= i && j >= 0){
				if (T[j] == S[kk])
					--j, --kk;
				else
					--kk; 
			}
			if (len > k - kk - 1){
				len = k - kk - 1; 
				res = S.substr(kk + 1, len); 
			}
			i = kk + 2; 
		}
		return res; 
	}
};


int main(){
	Solution2 a;

	string s = "abcdebdde", t = "bde"; 
	string s2 = "abxbxycdbedebdde", t2 = "bde"; 

	cout << a.minWindow(s, t) << endl; 
	cout << a.minWindow(s2, t2) << endl; 


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

