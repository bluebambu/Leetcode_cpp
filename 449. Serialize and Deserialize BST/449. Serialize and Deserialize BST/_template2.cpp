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
// Serialization is the process of converting a data structure or object into a 
// sequence of bits so that it can be stored in a file or memory buffer, or 
// transmitted across a network connection link to be reconstructed later in
// the same or another computer environment.

// Design an algorithm to serialize and deserialize a binary search tree.There 
// is no restriction on how your serialization / deserialization algorithm should 
// work.You just need to ensure that a binary search tree can be serialized to a 
// string and this string can be deserialized to the original tree structure.

// The encoded string should be as compact as possible.

// Note: Do not use class member / global / static variables to store states.Your 
// serialize and deserialize algorithms should be stateless.


// solve as it is a normal binary tree
class Codec {
public:
	// Encodes a tree to a single string.
	string serialize(TreeNode* root) {
		ostringstream oss; 
		out(root, oss); 
		return oss.str(); 
	}

	void out(TreeNode* node, ostringstream& oss){
		if (!node){
			oss << "# "; 
			return; 
		}
		oss << node->val << " "; 
		out(node->left, oss); 
		out(node->right, oss); 
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) {
		istringstream iss(data); 
		return in(iss); 
	}

	TreeNode* in(istringstream& iss){
		string cur; 
		iss >> cur; 
		if (cur == "#")
			return nullptr; 

		TreeNode* c = new TreeNode(stoi(cur)); 
		c->left = in(iss); 
		c->right = in(iss); 
		return c; 
	}
};


// solve as it is BST
// pass AC
class Codec2 {
public:
	// Encodes a tree to a single string.
	string serialize(TreeNode* root) {
		ostringstream oss; 
		out(root, oss); 
		return oss.str(); 
	}

	void out(TreeNode* node, ostringstream& oss){
		if (!node){
			return; 
		}
		oss << node->val << " "; 
		out(node->left, oss); 
		out(node->right, oss); 
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) {
		istringstream iss(data); 
		return in(iss, INT_MAX, INT_MIN); 
	}

	TreeNode* in(istringstream& iss, int up, int down){
		streampos p_orig = iss.tellg(); // record pos in stringstream
		string cur; 
		iss >> cur; 
		if (cur.empty())
			return nullptr; 
		
		if (stoi(cur) > up){
			iss.seekg(p_orig); // reset pos in stringstream
			return nullptr;
		}

		TreeNode* n = new TreeNode(stoi(cur)); 
		n->left = in(iss, stoi(cur), down); 
		n->right = in(iss, up, stoi(cur)); 
		return n; 
	}
};


// best solution: C style codes, very fast! Cast INT into char[4]. 
class Codecc {
public:

	// Encodes a tree to a single string.
	string serialize(TreeNode* root) {
		string order;
		inorderDFS(root, order);
		return order;
	}

	inline void inorderDFS(TreeNode* root, string& order) {
		if (!root) return;
		char buf[4];
		memcpy(buf, &(root->val), sizeof(int)); //burn the int into 4 chars
		for (int i = 0; i < 4; i++) order.push_back(buf[i]);
		inorderDFS(root->left, order);
		inorderDFS(root->right, order);
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) {
		int pos = 0;
		return reconstruct(data, pos, INT_MIN, INT_MAX);
	}

	inline TreeNode* reconstruct(const string& buffer, int& pos, int minValue, int maxValue) {
		if (pos >= buffer.size()) return NULL; //using pos to check whether buffer ends is better than using char* directly.

		int value;
		memcpy(&value, &buffer[pos], sizeof(int));
		if (value < minValue || value > maxValue) return NULL;

		TreeNode* node = new TreeNode(value);
		pos += sizeof(int);
		node->left = reconstruct(buffer, pos, minValue, value);
		node->right = reconstruct(buffer, pos, value, maxValue);
		return node;
	}
};


// queue iteration solution, layer traverse
class Codeccc {
public:
	// Encodes a tree to a single string.
	string serialize(TreeNode* root) {
		queue<TreeNode*> que; 
		ostringstream oss; 
		que.push(root); 
		string cur(to_string(root->val)); 
		oss << cur << " ";
		while (!que.empty()){
			TreeNode* tmp = que.front(); 
			que.pop(); 

			if (tmp->left){
				oss << to_string(tmp->left->val) << " "; 
				que.push(tmp->left); 
			}
			else
				oss << "# ";

			if (tmp->right){
				oss << to_string(tmp->right->val) << " "; 
				que.push(tmp->right); 
			}
			else
				oss << "# ";
		}

		return oss.str(); 
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) {
		istringstream iss(data); 
		string cur;
		iss >> cur; 
		TreeNode* root = new TreeNode(stoi(cur)); 
		queue<TreeNode*> que; 
		que.push(root); 

		while (!que.empty()){
			TreeNode* tmp = que.front(); 
			que.pop(); 

			if (iss.rdbuf()->in_avail()==0)
				break;
			iss >> cur; 
			if (cur != "#"){
				TreeNode* le = new TreeNode(stoi(cur)); 
				tmp->left = le; 
				que.push(le); 
			}

			if (iss.rdbuf()->in_avail()==0)
				break;
			iss >> cur; 
			if (cur != "#"){
				TreeNode* ri = new TreeNode(stoi(cur)); 
				tmp->right = ri; 
				que.push(ri); 
			}
		}

		return root; 
	}
};


class Codec3 {
public:
	string serialize(TreeNode* root) {
		string r; 
		r += to_string(root->val); 
		if (root->left)
			r += "," + serialize(root->left); 
		if (root->right)
			r += "," + serialize(root->right); 
		return r;
	}

	TreeNode* deserialize(string& s){
		int i = 0; 
		return dfs(s, i);
	}
	TreeNode* dfs(string&s, int& i){
		int j = i + 1;
		while (j < s.size() && s[j] != ',') ++j; 
		string cur = s.substr(i, j - i); 
		TreeNode *c = new TreeNode(stoi(cur)); 
		i = j + 1; 
		j = i + 1; 
		while (j < s.size() && s[j] != ',') ++j; 
		if (j >= s.size()) return c; 
		string next = s.substr(i, j - i); 
		if (stoi(next) > stoi(cur)){
			return c; 
		}
		c->left = dfs(s, i); 
		c->right = dfs(s, i); 
		return c; 
	}
}; 


int main(){

	vector<int> b = { 4, 1, -9, 0, INT_MAX }; 


	//TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
		3       8
	1    4   7    9
	*/

	Codec3 c; 
	auto s = c.serialize(tree); 
	cout << s << endl; 
	c.deserialize(s); 


	///////////////////////////
	auto start = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	cout << endl << microseconds << " microseconds elapsed..." << endl;
}

