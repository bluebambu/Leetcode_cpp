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

// passed
// 字母树的插入（Insert）、删除（ Delete）和查找（Find）都非常简单，用一个一重循环即可，即第i 次循环找到前i 个字母所对应
// 的子树，然后进行相应的操作。实现这棵字母树，我们用最常见的数组保存（静态开辟内存）即可，当然也可以开动态的指针类型（动态
// 开辟内存）。至于结点对儿子的指向，一般有三种方法：
// 
// 1、对每个结点开一个字母集大小的数组，对应的下标是儿子所表示的字母，内容则是这个儿子对应在大数组上的位置，即标号；
// 
// 2、对每个结点挂一个链表，按一定顺序记录每个儿子是谁；
// 
// 3、使用左儿子右兄弟表示法记录这棵树。
// 
// 三种方法，各有特点。第一种易实现，但实际的空间要求较大；第二种，较易实现，空间要求相对较小，但比较费时；第三种，空间要求最小，
// 但相对费时且不易写。

class TrieNode {
public:
	// Initialize your data structure here.
	TrieNode():isWord(false), letters(26, nullptr) {}

	vector<TrieNode*> letters;		
	bool isWord; 
};

class Trie {
public:
	Trie() {
		root = new TrieNode();
	}

	// Inserts a word into the trie.
	void insert(string word) {
		TrieNode* tmp = root; 
		for (int i = 0; i < word.size(); ++i){
			int idx = word[i] - 'a'; 
			if (tmp->letters[idx]==nullptr)	// 注意这一行！！
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

	// Returns if there is any word in the trie
	// that starts with the given prefix.
	bool startsWith(string prefix) {
		TrieNode* tmp = root;
		for (int i = 0; i < prefix.size(); ++i){
			int idx = prefix[i] - 'a';
			if (tmp->letters[idx] == nullptr)
				return false;
			tmp = tmp->letters[idx];
		}
		return tmp->isWord || tmp->letters.size(); 
	}

private:
	TrieNode* root;
};

// Your Trie object will be instantiated and called as such:
// Trie trie;
// trie.insert("somestring");
// trie.search("key");



int main()
{
	Solution a;

	//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
	3       8
	1    4   7    9

	*/

	a.flatten(tree);


}

