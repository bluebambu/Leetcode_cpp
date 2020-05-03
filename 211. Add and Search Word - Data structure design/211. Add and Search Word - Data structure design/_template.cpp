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

template <typename T>
void vprt(vector<T> v){
	for (auto i : v)
		cout << v << " ";
	cout << endl;
}

template <typename T>
void vvprt(vector<vector<T>> v){
	for (auto i : v){
		for (auto j : i){
			cout << j << " ";
		}
		cout << endl;
	}
	cout << endl;
}

template <typename C>
void setprt(C v){
	for (auto i : v)
		cout << i << " ";
	cout << endl;
}

template <typename C>
void mapprt(C v){
	for (auto i : v)
		cout << i.first << " " << i.second << endl;
	cout << endl;
}
////////////////////////////////////////////////////////////////
// Design a data structure that supports the following two operations :
// void addWord(word)
// bool search(word)

// search(word) can search a literal word or a regular expression string containing only letters 
// a - z or ..A.means it can represent any one letter.

// For example :
// addWord("bad")
// addWord("dad")
// addWord("mad")
// search("pad") -> false
// search("bad") -> true
// search(".ad") -> true
// search("b..") -> true


// pass AC
// About Trie, the first node has multiple children, the last node has none children. Take care of 
// how to express the trie!!!
class WordDictionary {
private:
	struct node{
		vector<node*> childs; 
		bool isWord; 
		node() :isWord(false), childs(26, nullptr) {}
	};

public:

	node* root; 
	/** Initialize your data structure here. */
	WordDictionary() {
		root = new node(); 
	}

	/** Adds a word into the data structure. */
	void addWord(string word) {
		node* p = root; 
		for (int i = 0; i < word.size(); ++i){
			int idx = word[i] - 'a';
			if (p->childs[idx] == nullptr){
				p->childs[idx] = new node; 
			}

			p = p->childs[idx]; 

			if (i + 1 == word.size())
				p->isWord = true; 
		}
	}

	/** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
	bool search(string word) {
		node* p = root; 
		return helper(p, word, 0); 
	}
	bool helper(node* p, string word, int n){
		if (!p)
			return false; 
		if (n==word.size())
			return p->isWord; 

		if (word[n] == '.'){
			for (int i = 0; i < p->childs.size(); ++i){
				if (p->childs[i]){
					if(helper(p->childs[i], word, n + 1)) 
						return true; 
				}
			}
			return false; 
		}

		return helper(p->childs[word[n] - 'a'], word, n + 1);
	}
};

/**
* Your WordDictionary object will be instantiated and called as such:
* WordDictionary obj = new WordDictionary();
* obj.addWord(word);
* bool param_2 = obj.search(word);
*/

class WordDict {
private:
	struct node{
		vector<node*> childs; 
		bool isWord; 
		node() :childs(26, nullptr), isWord(false){}
	};

	node* root; 

public:
	WordDict() :root(new node) {}; 

	void addWord(string word){
		node* p = root; 
		for (auto c : word){
			if (p->childs[c - 'a'] == nullptr)
				p->childs[c - 'a'] = new node; 
			p = p->childs[c - 'a']; 
		}
		p->isWord = true; 
	}

	bool searchWord(string word){
		return helper(root, word, 0); 
	}
	bool helper(node* node, string& word, int idx){
		if (!node)
			return false; 
		if (idx == word.size())
			return node->isWord; 

		if (word[idx] == '.'){
			for (auto p : node->childs){
				if (p){
					if (helper(p, word, idx + 1))
						return true; 
				}
			}
		}
	}
};

namespace TEST3{

	struct node2{
		bool isWord; 
		vector<TEST3::node2*> childs; 
		node2() :isWord(false), childs(26, nullptr) {}
	};

	class WordDictionary4 {
	public:
		node2* root; 
		/** Initialize your data structure here. */
		WordDictionary4() {
			root = new node2; 
		}

		/** Adds a word into the data structure. */
		void addWord(string word) {
			node2* p = root; 
			for (int i = 0; i < word.size(); ++i){
				int id = word[i] - 'a'; 
				if (p->childs[id] == nullptr)
					p->childs[id] = new node2; 
				p = p->childs[id]; 
			}
			p->isWord = true; 
		}

		/** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
		bool search(string word) {
			if (word.empty())
				return true; 

			node2* p = root; 
			return h(word, 0, p); 
		}
		bool h(string& w, int i, node2* p){
			if (i == w.size())
				return p->isWord; 

			int id = w[i] - 'a'; 
			if (w[i] == '.'){
				for (node2* next : (p->childs)){
					if (next && h(w, i + 1, next))
						return true; 
				}
				return false; 
			}
			else{
				if (p->childs[id] == nullptr)
					return false; 
				return h(w, i + 1, p->childs[id]); 
			}
		}
	};
}


namespace TEST4{

	struct node2{
		bool isWord; 
		vector<node2*> childs; 
		node2() :isWord(false), childs(26, nullptr) {}
	};

	class WordDictionary4 {
	public:
		node2 *root; 
		WordDictionary4() :root(new node2()) {}

		void addWord(string word) {
			node2 *p = root; 
			int i = 0, n = word.size(); 
			for (; i < n; ++i){
				int idx = word[i] - 'a'; 
				if (p->childs[idx] == nullptr)
					p->childs[idx] = new node2(); 
				p = p->childs[idx]; 
			}
			p->isWord = true; 
		}

		bool search(string word) {
			return search(word, 0, root); 
		}
		bool search(string& w, int i, node2* nd){
			if (!nd)
				return false; 
			if (i == w.size())
				return nd->isWord; 

			char c = w[i]; 
			if (c != '.'){
				int idx = c - 'a'; 
				return search(w, i + 1, nd->childs[idx]); 
			}
			else{
				for (int j = 0; j < 26; ++j){
					if (search(w, i + 1, nd->childs[j]))
						return true; 
				}
				return false; 
			}
		}
	};
}

namespace TEST5{
	struct node2{
		bool isWord;
		vector<node2*> childs;
		node2() :isWord(false), childs(26, nullptr) {}
	};

	class WordDictionary4 {
	public:
		node2 *root;
		WordDictionary4() :root(new node2()) {}

		void addWord(string word) {
			node2*p = root; 
			for (auto c : word){
				int idx = c - 'a'; 
				if (p->childs[idx] == nullptr)
					p->childs[idx] = new node2(); 
				p = p->childs[idx];
			}
			p->isWord = true; 
		}
		bool search(string word) {
			return dfs(root, word, 0); 
		}
		bool dfs(node2* n, string& s, int i){
			if (i == s.size()) return n->isWord; 
			if (!n) return false; 
			if (s[i] != '.')
				return dfs(n->childs[s[i] - 'a'], s, i + 1); 
			else{
				for (int j = 0; j < n->childs.size(); ++j){
					node2 *nxt = n->childs[j]; 
					if (dfs(nxt, s, i + 1))
						return true; 
				}
				return false; 
			}
		}
	};
}

int main() {
	TEST4::WordDictionary4 a;

	a.addWord("bad"); 
	a.addWord("mad"); 
	a.addWord("dad"); 
	a.addWord("dae"); 

	cout << a.search("..d") << endl; 
	cout << a.search("z..") << endl; 
	cout << a.search("...") << endl; 
	cout << a.search("..e") << endl; 
	cout << a.search("...e") << endl; 

	//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
	3       8
	1    4   7    9

	*/


}

