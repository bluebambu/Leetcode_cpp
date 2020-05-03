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
// 1.	第一轮两题，都是在白板上写。白人哥哥先问了word search，给你一个字典，
// 再给你一个长单词，让你找长单词里所有在字典里的substr。
//
//
// 假设字典里的单词平均长度是m，那么trie树的深度也就是m啦，所以根本不可能找一个特别长的substring。
// 你可以假设这道题target word长度特别长，like one million, 而字典里的单词都特别短。搜索的复杂度肯定不会是one million*one million啊

// 解法：不要insert target string到trie，应该insert dictionary中所有单词。然后遍历target string，注意在search的时候不需要用java substring method和Stringbuilder。
// search(TrieNode node, String targetString, int index), index是递增的。从targetString.charAt(index)作为开始，向后面搜。


struct node{
	bool isWord; 
	string word;
	vector<node*> childs; 

	// by default isWord is false; 
	node(): isWord(false), childs(26, nullptr){}
};

class Trie{
	node* root; 
public:
	Trie() :root(new node) {
		root->isWord = true; // is "" included?? 
	}

	void insert(string str){
		node* p = root; 
		for (int i = 0; i < str.size(); ++i){
			char cur = str[i];	
			int pos = cur - 'a'; 
			if ((p->childs)[pos] == nullptr) // this statement is important!!!!!
				(p->childs)[pos] = new node; 
			p = (p->childs)[pos]; 
		}
		p->isWord = true; 
	}

	bool find(string str){
		node* p = root; 
		for (int i = 0; i < str.size(); ++i){
			int pos = str[i] - 'a'; 
			p = (p->childs)[pos]; 

			// root is always valid, so this condition should be put here. 
			if (p == nullptr)
				return false; 
		}
		return p->isWord; 
	}

	vector<string> search_substr(string str, int start){
		vector<string> res; 
		node* p = root; 
		for (int i = start; i < str.size(); ++i){
			int pos = str[i] - 'a'; 
			p = (p->childs)[pos]; 
			if (p == nullptr)
				return res; 
			if (p->isWord)
				res.push_back(str.substr(start, i - start + 1)); 
		}

		return res;
	}
};


class Solution {
public:
	vector<string> wordSearch_1(string word, set<string> dict){
		if (dict.empty())
			return {}; 
		if (word.empty())
			return (dict.count("") ? vector<string>({""}) : vector<string>({})); 

		vector<string> res; 

		int n = word.size(); 
		for (int i = 0; i < n; ++i){
			for (int j = 0; j <= n; ++j){
				string sub = word.substr(i, j); 
				if (dict.count(sub))
					res.push_back(sub); 
			}
		}
		return res; 
	}
	// complexity: word len = n, O(n^2)

	// this is the best solution. 
	vector<string> wordSearch_2(string word, vector<string> dict){
		Trie trie; 
		for (string i : dict){
			trie.insert(i); 
		}

		vector<string> res; 
		for (int i = 0; i < word.size(); ++i){
			vector<string> tmp = trie.search_substr(word, i); 
			res.insert(res.end(), tmp.begin(), tmp.end()); 
		}
		return res; 
	}
};


class Trie2{
	node* root; 
public:
	Trie2() :root(new node) {}

	void insert(string str){
		node* p = root; 
		for (int i = 0; i < str.size(); ++i){
			int pos = str[i] - 'a'; 
			if (p->childs[pos] == nullptr)
				p->childs[pos] = new node(); 
			p = p->childs[pos]; 
		}
		p->isWord = true;
		p->word = str; 
	}

	set<string> srch(string& str, int start){
		node* p = root; 
		set<string> res; 
		for (int i = start; i < str.size() ; ++i){
			int pos = str[i] - 'a'; 
			p = p->childs[pos]; 
			if (p==nullptr)
				break;
			if (p->isWord) // p=p->child[i] first, then check p->isWord. Otherwise, last word will be neglected. 
				res.insert(p->word); 
		}
		return res;
	}

	set<string> findSubstr(string& str){
		set<string> res; 
		for (int i = 0; i < str.size(); ++i){
			auto tmp = srch(str, i); 
			res.insert(tmp.begin(), tmp.end()); 
		}
		return res; 
	}

};

class Trie3{
public:
	node* root; 
	
	Trie3() :root(new node) {}

	void insert(string str){
		node* it = root; 
		for (int i = 0; i < str.size(); ++i){
			int pos = str[i] - 'a'; 
			if (it->childs[pos] == nullptr)
				it->childs[pos] = new node; 
			it = it->childs[pos]; 
		}
		it->isWord = true; 
		it->word = str; 
	}

	unordered_set<string> search(string& str, int start){
		unordered_set<string> res; 
		node* it = root; 
		for (int i = start; i < str.size(); ++i){
			int pos = str[i] - 'a'; 
			it = it->childs[pos]; 
			if (it==nullptr)
				break;
			if (it->isWord)
				res.insert(it->word); 
		}
		return res; 
	}	unordered_set<string> allSub(string& str){
		unordered_set<string> res; 
		for (int i = 0; i < str.size(); ++i){
			auto cur = search(str, i); 
			res.insert(cur.begin(), cur.end()); 
		}
		return res; 
	}
};


int main(){

	vector<int> b = { 4, 1, -9, 0, INT_MAX }; 

	Trie3 c; 
	vector<string> d = {
		"ab",
		"abc",
		"bcd",
		"dfg",
		"dfgsj",
		"fgh", 
		"ha", 
		"zzz",
		"zzzz"
	}; 

	for (auto i : d)
		c.insert(i); 

	string f = "abcabcdbcdfgbcdbfghsjjfgsjhaabczzzababczz"; 

	auto m = c.allSub(f); 
	prt1Layer(m); 


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

