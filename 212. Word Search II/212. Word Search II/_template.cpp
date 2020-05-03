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
// 
// [LeetCode] Word Search II ��������֮��
// 
// 
// 
// Given a 2D board and a list of words from the dictionary, find all words in the board.
// 
// Each word must be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or 
// vertically neighboring.The same letter cell may not be used more than once in a word.
// 
// For example,
// Given words = ["oath", "pea", "eat", "rain"] and board =
// 
// [
// 	['o', 'a', 'a', 'n'],
// 	['e', 't', 'a', 'e'],
// 	['i', 'h', 'k', 'r'],
// 	['i', 'f', 'l', 'v']
// ]
// 
// Return["eat", "oath"].
// 
// Note:
// You may assume that all inputs are consist of lowercase letters a - z.
// 
// click to show hint.
// 
// You would need to optimize your backtracking to pass the larger test.Could you stop backtracking earlier ?
// 
// If the current candidate does not exist in all words' prefix, you could stop backtracking immediately. What kind of data structure 
// could answer such query efficiently? Does a hash table work? Why or why not? How about a Trie? If you would like to learn how to 
// implement a basic trie, please work on this problem: Implement Trie (Prefix Tree) first.
// 
// 
// 
// ���������֮ǰ�ǵ�Word Search ���������Ļ���������Щ��չ��֮ǰ�Ǹ�һ���������ж��Ƿ���ڣ������Ǹ���һ�ѵ��ʣ��÷������д��ڵĵ��ʣ�
// ��������ʼ���µļ���Сʱ�ڣ���brute force�ǿ���ͨ��OJ�ģ�������֮ǰ����Ļ����϶��һ��forѭ�����ѣ����Ǻ�����������ʵ���뿼����
// ������Ӧ�ã����Լ���һ�������test case��������brute force�޷�ͨ����ǿ�����Ǳ���Ҫ���ֵ�������⡣LeetCode���й��ֵ������⻹�� 
// Implement Trie(Prefix Tree) ʵ���ֵ���(ǰ׺��)��Add and Search Word - Data structure design ��ӺͲ��ҵ��� - ���ݽṹ��ƣ�
// ��ô������������ֻҪʵ���ֵ����е�insert���ܾ����ˣ����ҵ��ʺ�ǰ׺��û�б�Ҫ�ˣ�Ȼ��DFS��˼·��֮ǰ�ǵ�Word Search ��������������ͬ����μ��������£�
// 

// passed, 
// 
class TrieNode{
public:
	bool isword;
	vector<TrieNode*> child;

	TrieNode() :isword(false), child(26, nullptr) {}
};

class Trie{	  // ���õķ����ǰ� isword ���� string�� ������string�� ��������ÿһ��track char ��
public:
	TrieNode* root;

	Trie() :root(new TrieNode()) {}

	void insert(string str){
		TrieNode* tmp = root;
		for (int i = 0; i < str.size(); ++i){
			int idx = str[i] - 'a';
			if (tmp->child[idx] == nullptr)
				tmp->child[idx] = new TrieNode();
			tmp = tmp->child[idx];
		}
		tmp->isword = true;
	}
};

class Solution {
public:
	vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
		unordered_set<string> res;
		if (words.empty() || board.empty() || board[0].empty())
			return vector<string>();

		Trie T;
		for (auto& str : words)
			T.insert(str);

		vector<vector<bool>> map(board.size(), vector<bool>(board[0].size(), false));
		string path;
		for (int i = 0; i < board.size(); ++i){
			for (int j = 0; j < board[0].size(); ++j){
				dfs(board, i, j, T.root->child[board[i][j] - 'a'], path, map, res);
			}
		}
		return vector<string>(res.begin(), res.end());
	}

	void dfs(vector<vector<char>>& board, int i, int j, TrieNode* node, string& path, vector<vector<bool>>& map, unordered_set<string>& res){
		if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size() || node == nullptr)
			return;

		if (map[i][j])
			return;

		if (node->isword){
			path.push_back(board[i][j]);
			res.insert(path);
			path.pop_back();
			// return; 		   
			// ���ﲻ��д return, ��Ϊ����˵��� words �� ��aaa���� ��aaab���� ����trie���棬 
			// aaa��isword��aaab�Ķ���true�� �����return��䣬����Զ�����ܵ��� aaab�� ��Ϊ���� aaa return �ˣ�����
		}

		map[i][j] = true;
		path.push_back(board[i][j]);

		if (i + 1 < board.size())
			dfs(board, i + 1, j, node->child[board[i + 1][j] - 'a'], path, map, res);
		if (j + 1 < board[0].size())
			dfs(board, i, j + 1, node->child[board[i][j + 1] - 'a'], path, map, res);
		if (i - 1 >= 0)
			dfs(board, i - 1, j, node->child[board[i - 1][j] - 'a'], path, map, res);
		if (j - 1 >= 0)
			dfs(board, i, j - 1, node->child[board[i][j - 1] - 'a'], path, map, res);

		map[i][j] = false;
		path.pop_back();

	}
};


vector<vector<int>> dirs = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };

class Solution2 {
public:
	struct node{
		vector<node*> child; 
		bool isword; 
		string word; 
	};

	struct Trie{
		node *root; 
		void insert(string s){}
	};

	vector<string> wordSearch(vector<vector<char>>& board, vector<string>& words){
		Trie t; 
		for (auto& s : words)  t.insert(s); 
		int n = board.size(), m = board[0].size(); 
		vector<string> res; 
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				char c = board[i][j]; 
				if (t.root->child[c]){
					dfs(board, i, j, t.root->child[c], res); 
				}
			}
		}

		return res; 
	}

	void dfs(vector<vector<char>>& board, int i, int j, node* p, vector<string>& res){
		int n = board.size(), m = board[0].size(); 
		if (p->isword){
			res.push_back(p->word); 
		}

		for (auto& d : dirs){
			int x = i + d[0], y = j + d[1]; 
			if (x >= 0 && x < n&&y >= 0 && y < m&&p->child[board[x][y]]){
				dfs(board, x, y, p->child[board[x][y]], res); 
			}
		}
	}
};


int main()
{
	Solution a;



}

