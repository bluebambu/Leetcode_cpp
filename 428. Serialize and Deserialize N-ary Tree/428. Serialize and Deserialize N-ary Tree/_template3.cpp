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



class Node {
public:
	int val = NULL;
	vector<Node*> children;

	Node() {}

	Node(int _val, vector<Node*> _children) {
		val = _val;
		children = _children;
	}
};

// pass
class Codec {
public:

	// Encodes a tree to a single string.
	string serialize(Node* root) {
		if (!root)
			return ""; 

		string res = "(" + to_string(root->val);
		for (int i = 0; i < root->children.size(); ++i)
			res += serialize(root->children[i]); 
		res += ")"; 
		return res; 
	}

	// Decodes your encoded data to tree.
	Node* deserialize(string data) {
		if (data == "")
			return nullptr; 

		int i = 0; 
		return helper(data, i); 
	}

	Node* helper(string& data, int& i){
		int j = i; 
		i += 1; 
		while (i < data.size() && data[i] != '(' && data[i] !=')') ++i; 

		string c = data.substr(j + 1, i - j - 1); 
		Node* cur = new Node(stoi(c), {}); 

		if (data[i] == ')'){
			++i;
			return cur; 
		}

		while (i < data.size() && data[i] == '('){
			Node* child = helper(data, i);
			cur->children.push_back(child); 
		}

		++i; 
		return cur; 
	}
};


class Codec3 {
public:
	string serialize(Node* root) {
		if (!root)return "#"; 
		string res; 
		int n = root->children.size(); 
		res = " " + to_string(root->val) + " " + to_string(n); 
		for (auto c : root->children)
			res += serialize(c); 
		return res; 
	}

	Node* deserialize(string& s){
		int i = 0; 
		return decode(s, i); 
	}
	Node* decode(string& s, int& i){
		if (i >= s.size()) return nullptr; 
		int j = i + 1; 
		while (j < s.size() && s[j] != ' ') ++j; 
		string cur_val = s.substr(i, j - i); 
		i = j; 
		j = i + 1; 
		while (j < s.size() && s[j] != ' ') ++j; 
		string child_n = s.substr(i, j - i); 
		int cnt = stoi(child_n);
		i = j; 

		Node *cur = new Node; 
		cur->val = stoi(cur_val); 
		while (cnt--){
			cur->children.push_back(decode(s, i)); 
		}

		return cur; 
	}
};


class Codec4 {
public:
	string serialize(Node* root) {
		string res; 
		res += to_string(root->val) + " " + to_string(root->children.size()) + " "; 
		for (Node* c : root->children){
			res += serialize(c); 
		}
		return res; 
	}

	Node* deserialize(string& s){
		int i = 0; 
		return d(s, i); 
	}
	Node* d(string& s, int& i){
		int j = i + 1; 
		while (j < s.size() && s[j] != ' ') ++j; 
		string v = s.substr(i, j - i); 
		i = j+1; 
		j = i + 1; 
		while (j < s.size() && s[j] != ' ') ++j; 
		string cnt = s.substr(i, j - i); 
		i = j+1; 
		Node *cur = new Node; 
		cur->val = stoi(v); 
		for (int k = 0; k < stoi(cnt); ++k){
			cur->children.push_back(d(s, i)); 
		}
		return cur; 
	}
};


class Codec5 {
public:
	string serialize(Node* root) {
		string res; 
		res = to_string(root) + " " + to_string(root->children.size()) + " "; 
		for (int i = 0; i < root->children.size(); ++i)
			res += serialize(root->children[i]); 
		return res; 
	}

	Node* deserialize(string& s){
		int i = 0; 
		return dfs(s, i); 
	}
	Node* dfs(string& s, int& i){
		if (i >= s.size()) return nullptr; 
		int j = i + 1;
		while (j < s.size() && s[j] != ' ') ++j; 
		string v = s.substr(i, j - i); 
		i = j + 1; 
		j = i + 1;
		while (j < s.size() && s[j] != ' ') ++j; 
		string n = s.substr(i, j - i); 
		int nc = stoi(n); 
		i = j + 1; 
		Node *cur = new Node; 
		cur->val = stoi(v); 
		for (int k = 0; k < nc; ++k){
			cur->children.push_back(dfs(s, i)); 
		}
		return cur; 
	}
};
		
void prnt(Node *r){
	if (!r) return; 
	cout << r->val << "("; 
	for (auto c : r->children){
		prnt(c); 
	}
	cout << ")"; 
}

int main(){
	Node* tree = new Node(1, {}),
		*a = new Node(2, {}),
		*b = new Node(3, {}),
		*c = new Node(4, {}),
		*d = new Node(5, {}),
		*e = new Node(6, {}),
		*f = new Node(7, {}),
		*g = new Node(8, {}),
		*h = new Node(9, {}); 

	(e->children).push_back(f); 
	(e->children).push_back(g);
	(e->children).push_back(h);
	
	(b->children).push_back(c);
	
	(a->children).push_back(b);
	(a->children).push_back(d);
	(a->children).push_back(e);

	/*
	a -> b -> c
	  -> d
	  -> e -> f
		   -> g
		   -> h
	*/

	Codec4 s; 

	auto s1 = s.serialize(a); 
	cout << s1 << endl; 

	auto r = s.deserialize(s1); 
	prnt(r); 


	///////////////////////////
	auto start = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	cout << endl << microseconds << " microseconds elapsed..." << endl;
}

