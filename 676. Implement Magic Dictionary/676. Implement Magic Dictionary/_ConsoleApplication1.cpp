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

class Trie {
public:
	class TrieNode {
	public:
		// Initialize your data structure here.
		TrieNode() :isWord(false), letters(26, nullptr) {}

		vector<TrieNode*> letters;
		bool isWord;
		string word;
	};

	Trie() {
		root = new TrieNode();
	}

	// Inserts a word into the trie.
	void insert(string word) {
		TrieNode* tmp = root; 
		for (int i = 0; i < word.size(); ++i){
			int idx = word[i] - 'a'; 
			if (tmp->letters[idx]==nullptr)	
				tmp->letters[idx] = new TrieNode(); 
			tmp = tmp->letters[idx]; 
		}
		tmp->isWord = true; 
	}

	// Returns if the word is in the trie.
	bool search(string word) {
		TrieNode* tmp = root; 
		for (int i = 0; i < word.size(); ++i){
			int idx = word[i] - 'a'; 
			if (tmp->letters[idx] == nullptr)
				return false; 
			tmp = tmp->letters[idx]; 
		}
		return tmp->isWord; 
	}

	bool match(string& word, int modn){
		return match(root, word, 0, modn); 
	}
	bool match(TrieNode* n, string& s, int i, int modn){
		if (!n) return false; 
		if (i == s.size()) return modn == 0 && n->isWord;

		int idx = s[i] - 'a'; 
		bool res = false; 
		if (n->letters[idx])
			res |= match(n->letters[idx], s, i + 1, modn); 
		if (res) return true;

		auto& p = n->letters; 
		for (int j = 0; j < p.size(); ++j){
			if (j != idx && modn > 0 && n->letters[j]){
				res |= match(n->letters[j], s, i + 1, modn - 1); 
			}
			if (res) return true; 
		}

		return false; 
	}

private:
	TrieNode* root;
};




class MagicDictionary {
public:
	Trie trie; 
    /** Initialize your data structure here. */
    MagicDictionary():trie() {
		 
    }
    
    /** Build a dictionary through a list of words */
    void buildDict(vector<string> dict) {
		for (auto& s : dict) trie.insert(s); 
    }
    
    /** Returns if there is any word in the trie that equals to the given word after modifying exactly one character */
    bool search(string word) {
		return trie.match(word, 2); 
    }
};


class MagicDictionary2 {
	struct Trie2{
		struct node{
			vector<node*> childs; 
			bool isWord; 
			string word; 
			node() :childs(26) {}
		};

		node* root; 
		Trie2() :root(new node) {}
		bool insert(string& s){
			try{
			node *p = root; 
			for (int i = 0; i < s.size(); ++i){
				int idx = s[i] - 'a'; 
				if (p->childs[idx] == nullptr)
					p->childs[idx] = new node; 
				p = p->childs[idx]; 
			}
			p->isWord = true; 
			p->word = s; 
			return true; 
			}
			catch (exception& e){
				cerr << e.what() << endl; 
				return false; 
			}
		}

		bool search(const string& w){
			return srch(root, w, 0, 1); 
		}
		bool srch(node* n, const string& w, int i, int k){
			for (; i < w.size(); ++i){
				int idx = w[i] - 'a'; 
				if (n->childs[idx] == nullptr){
					if (k == 0) return false; 
					for (int j = 0; j < 26; ++j){
						if (n->childs[j] && srch(n->childs[j], w, i+1, k-1)){
							return true; 
						}
					}
					return false; 
				}
				n = n->childs[idx]
			}

			return k == 0 && n->isWord; 
		}
	};

public:
	Trie2 trie; 
    /** Initialize your data structure here. */
    MagicDictionary():trie() {
		 
    }
    
    /** Build a dictionary through a list of words */
    void buildDict(vector<string> dict) {
		for (auto& s : dict) trie.insert(s); 
    }
    
    /** Returns if there is any word in the trie that equals to the given word after modifying exactly one character */
    bool search(string word) {
		return trie.match(word, 2); 
    }
};


int main(){
	MagicDictionary a; 

	vector<string> d = { "hello", "leetcode" }; 

	a.buildDict(d); 
	cout << a.search("hello") << endl; 
	cout << a.search("hhllo") << endl; 
	cout << a.search("hell") << endl; 
	cout << a.search("leetcoded") << endl; 
	cout << a.search("leetcoxf") << endl; 


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

