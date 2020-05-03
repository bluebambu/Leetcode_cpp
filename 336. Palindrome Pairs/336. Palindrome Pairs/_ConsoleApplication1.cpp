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
    vector<vector<int>> palindromePairs(vector<string>& words) {
		unordered_map<string, int> revers_2_id; 
		for (int i=0; i<words.size(); ++i){
			string p = words[i]; 
			reverse(p.begin(), p.end()); 
			revers_2_id[p] = i; 
		}
		set<vector<int>> res; 
		for (int i = 0; i < words.size(); ++i){
			string& cur = words[i]; 
			for (int j = 0; j <= cur.size(); ++j){
				string left = cur.substr(0, j),
					right = cur.substr(j); 
				if (revers_2_id.count(left) && isPalin(right) && revers_2_id[left] != i)
					res.insert({ i, revers_2_id[left] }); 
				if (revers_2_id.count(right) && isPalin(left)&& revers_2_id[right] != i)
					res.insert({ revers_2_id[right], i }); 
			}
		}
		return VVI(res.begin(), res.end());
    }
	bool isPalin(string s){
		int i = 0, j = s.size() - 1; 
		while (i < j)
			if (s[i++] != s[j--]) return false; 
		return true; 
	}
};


int main(){
	Solution a;

	vector<string> d = { "abcd", "dcba", "lls", "s", "sssll" }; 
	auto c = a.palindromePairs(d); 

	prt2Layer(c); 


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

