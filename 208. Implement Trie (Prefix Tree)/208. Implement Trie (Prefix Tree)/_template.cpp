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
// ��ĸ���Ĳ��루Insert����ɾ���� Delete���Ͳ��ң�Find�����ǳ��򵥣���һ��һ��ѭ�����ɣ�����i ��ѭ���ҵ�ǰi ����ĸ����Ӧ
// ��������Ȼ�������Ӧ�Ĳ�����ʵ�������ĸ������������������鱣�棨��̬�����ڴ棩���ɣ���ȻҲ���Կ���̬��ָ�����ͣ���̬
// �����ڴ棩�����ڽ��Զ��ӵ�ָ��һ�������ַ�����
// 
// 1����ÿ����㿪һ����ĸ����С�����飬��Ӧ���±��Ƕ�������ʾ����ĸ����������������Ӷ�Ӧ�ڴ������ϵ�λ�ã�����ţ�
// 
// 2����ÿ������һ��������һ��˳���¼ÿ��������˭��
// 
// 3��ʹ����������ֵܱ�ʾ����¼�������
// 
// ���ַ����������ص㡣��һ����ʵ�֣���ʵ�ʵĿռ�Ҫ��ϴ󣻵ڶ��֣�����ʵ�֣��ռ�Ҫ����Խ�С�����ȽϷ�ʱ�������֣��ռ�Ҫ����С��
// ����Է�ʱ�Ҳ���д��

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
			if (tmp->letters[idx]==nullptr)	// ע����һ�У���
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

