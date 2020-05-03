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
#include <unordered_set>
#include <string>
#include <queue>	 
#include <set>
#include <stack>

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

/*
Given a set of words(without duplicates), find all word squares you can build from them.

A sequence of words forms a valid word square if the kth row and column read the exact same string, where 0 ¡Ü k < max(numRows, numColumns).

For example, the word sequence["ball", "area", "lead", "lady"] forms a word square because each word reads the same both horizontally and vertically.

b a l l
a r e a
l e a d
l a d y

Note :

There are at least 1 and at most 1000 words.
All words will have the exact same length.
Word length is at least 1 and at most 5.
Each word contains only lowercase English alphabet a - z.
*/

class Solution
{
public:
	vector<vector<string>> wordSquares(vector<string> words) {
		vector<vector<string>> res; 
		unordered_map<string, unordered_set<string>> trie; 

		// caution: i < size, not i<=size
		for (int i = 0; i <= words[0].size(); ++i){
			for (string str : words){
				trie[str.substr(0, i)].insert(str); 
			}
		}

		// print trie
		for (auto a : trie){
			cout << a.first << "->:"; 
			for (auto b : a.second)
				cout << b << " ";
			cout << endl;
		}

		int len = words[0].size(); 
		vector<vector<char>> sq(len, vector<char>(len)); 

		helper(0, len, sq, trie, res);
		return res; 
	}

	void helper(int i, int n, vector<vector<char>>& sq, unordered_map<string, 
		unordered_set<string>>& trie, vector<vector<string>>& res){
		
		if (i == n){
			vector<string> out; 
			for (int j = 0; j < n; ++j)
				out.push_back(string(sq[j].begin(), sq[j].end())); 
			res.push_back(out); 
			return; 
		}

		string key = string(sq[i].begin(), sq[i].begin() + i); 

		/*
			w a l l
			a x y y
			l y
			l y

		*/
		for (string str : trie[key]){
			sq[i][i] = str[i]; 
			int j = i + 1; 
			for (; j < n; ++j){
				sq[i][j] = str[j]; 
				sq[j][i] = str[j]; 
				if (!trie.count(string(sq[j].begin(), sq[j].begin() + i + 1)))
					break; 
			}
			if (j == n)
				helper(i + 1, n, sq, trie, res); 
		}
	}

};




class Solution2 {
public:
	struct TrieNode {
		vector<int> indexs;
		vector<TrieNode*> children;
		TrieNode() : children(26, nullptr) {}
	};

	TrieNode* buildTrie(vector<string>& words) {
		TrieNode *root = new TrieNode();
		for (int i = 0; i < words.size(); ++i) {
			TrieNode *t = root;
			for (int j = 0; j < words[i].size(); ++j) {
				if (!t->children[words[i][j] - 'a']) {
					t->children[words[i][j] - 'a'] = new TrieNode();
				}
				t = t->children[words[i][j] - 'a'];
				t->indexs.push_back(i);
			}
		}
		return root;
	}

	vector<vector<string>> wordSquares(vector<string>& words) {
		TrieNode *root = buildTrie(words);
		vector<string> out(words[0].size());
		vector<vector<string>> res;
		for (string word : words) {
			out[0] = word;
			helper(words, 1, root, out, res);
		}
		return res;
	}

	void helper(vector<string>& words, int level, TrieNode* root, vector<string>& out, vector<vector<string>>& res) {
		if (level >= words[0].size()) {
			res.push_back(out);
			return;
		}
		string str = "";
		for (int i = 0; i < level; ++i) {
			str += out[i][level];
		}
		TrieNode *t = root;
		for (int i = 0; i < str.size(); ++i) {
			if (!t->children[str[i] - 'a']) return;
			t = t->children[str[i] - 'a'];
		}
		for (int idx : t->indexs) {
			out[level] = words[idx];
			helper(words, level + 1, root, out, res);
		}
	}
};



int main() {
	Solution a;

	auto d = a.wordSquares(vector<string>({"area","lead","wall","lady","ball"}));

	for (auto e : d){
		for (auto f : e){
			cout << f << " ";
		}
		cout << endl; 
	}
}

