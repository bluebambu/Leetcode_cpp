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

// pass, w/ string
class Codec {
public:
	// Encodes a tree to a single string.
	string serialize(TreeNode* root) {
		if (!root)
			return "#"; 
		return to_string(root->val) + "," + serialize(root->left) + "," + serialize(root->right); 
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) {
		int i = 0; 
		return des(data, i); 
	}

	TreeNode* des(string& data, int& i){
		if (data[i] == '#'){
			i += 2; // VERY IMPORTANT!!!!
			return nullptr; 
		}

		int j = i; 
		for (; j < data.size() && data[j] != ','; ++j); 
		TreeNode *root = new TreeNode(stoi(data.substr(i, j - i))); 
		i = j + 1; 
		TreeNode *left = des(data, i);
		TreeNode *right = des(data, i);

		root->left = left, root->right = right; 
		return root; 
	}
};

class Codec2 {
public:
	// Encodes a tree to a single string.
	string serialize(TreeNode* root) {
		ostringstream oss; 
		helper(root, oss); 
		return oss.str();
	}
	void helper(TreeNode* node, ostringstream& oss){
		if (!node){
			oss << "# ";
			return; 
		}
		oss << to_string(node->val) << " "; 
		helper(node->left, oss); 
		helper(node->right, oss); 
	}

	TreeNode* deserialize(string data){
		istringstream iss(data); 
		return helper2(iss); 
	}
	TreeNode* helper2(istringstream& iss){
		string cur; 
		iss >> cur; 
		if (cur == "#")
			return nullptr; 
		TreeNode*root = new TreeNode(stoi(cur)); 
		TreeNode*left = helper2(iss);
		TreeNode*right = helper2(iss);
		root->left = left; root->right = right;
		return root; 
	}
};

// pass
class Codec3 {
public:
	// Encodes a tree to a single string.
	string serialize(TreeNode* root) {
		ostringstream oss;
		helper(root, oss);
		return oss.str();
	}
	void helper(TreeNode* root, ostringstream& oss){
		queue<TreeNode*> que; 
		que.push(root); 

		while (!que.empty()){
			TreeNode* front = que.front(); 
			que.pop(); 

			if (front)
				oss << front->val << " ";
			else
				oss << "# "; 

			if (front){
				que.push(front->left); 
				que.push(front->right);
			}
		}
	}

	TreeNode* deserialize(string data){
		if (data == "# ")
			return nullptr; 
		istringstream iss(data);
		return helper2(iss); 
	}
	TreeNode* helper2(istringstream& iss){
		string h; 
		iss >> h; 
		TreeNode*root = new TreeNode(stoi(h)); 
		queue<TreeNode*> que; 
		que.push(root); 

		while (!que.empty()){
			TreeNode* front = que.front(); 
			que.pop(); 

			iss >> h; 
			if (h == "#")
				front->left = nullptr; 
			else{
				front->left = new TreeNode(stoi(h)); 
				que.push(front->left); 
			}

			iss >> h; 
			if (h == "#")
				front->right = nullptr; 
			else{
				front->right = new TreeNode(stoi(h)); 
				que.push(front->right); 
			}
		}

		return root; 
	}
};



class Codec4 {
public:
	string serialize(TreeNode* root) {
		if (!root)
			return "#"; 
		return to_string(root->val) + "," + serialize(root->left) + "," + serialize(root->right);
	}

	TreeNode* deserialize(string data) {
		int i = 0; 
		return helper(data,i); 
	}

	TreeNode* helper(string& data, int& st){
		int i = st; 
		while (i < data.size() && data[i] != ',') ++i; 
		string cur = data.substr(st, i - st); 
		if (cur == "#"){
			st = i + 1; 
			return nullptr; 
		}

		TreeNode *cn = new TreeNode(stoi(cur)); 
		st = i + 1; 
		cn->left = helper(data, st); 
		cn->right = helper(data, st); 

		return cn; 
	}
};

class Codec5 {
public:
	string serialize(TreeNode* root) {
		ostringstream oss; 
		h(root, oss); 
		return oss.str(); 
	}
	void h(TreeNode* node, ostringstream& oss){
		if (!node){
			oss << "# ";
			return; 
		}
		oss << to_string(node->val)<<" ";
		h(node->left, oss); 
		h(node->right, oss); 
	}

	TreeNode* deserialize(string s){
		istringstream iss(s); 
		return h2(iss); 
	} 
	TreeNode* h2(istringstream& iss){
		string cur; 
		iss >> cur; 
		if (cur == "#")
			return nullptr; 
		TreeNode *n = new TreeNode(stoi(cur)); 
		n->left = h2(iss); 
		n->right = h2(iss); 
		return n; 
	}
}; 


// pass AC. 
class Codec6 {
public:
	string serialize(TreeNode* root) {
		if (!root)
			return "#"; 
		return to_string(root->val) + "," + serialize(root->left) + "," + serialize(root->right); 
	}

	TreeNode* deserialize(string& s){
		int i = 0; 
		while (i < s.size() && s[i] != ',') ++i; 
		string first = s.substr(0, i);

		s = i==s.size() ? "" : s.substr(i + 1); // important!!!

		if (first == "#")
			return nullptr; 

		TreeNode* cur = new TreeNode(stoi(first)); 
		
		cur->left = deserialize(s); 
		cur->right = deserialize(s); 

		return cur; 
	}
}; 

class Codec7{
public:
	string serialize(TreeNode* root){
		if (!root)
			return "#"; 
		return to_string(root->val) + ',' + serialize(root->left) + ',' + serialize(root->right);
	}

	TreeNode* deserialize(string& s){
		int i = 0; 
		return des(s, i); 
	}
	TreeNode* des(string&s, int& i){
		int j = i + 1; 
		while (j < s.size() && s[j] != ',') ++j; 
		string cur = s.substr(i, j - i); 
		i = j + 1;
		if (cur == "#"){
			return nullptr; 
		}

		TreeNode* n = new TreeNode(stoi(cur)); 
		n->left = des(s, i); 
		n->right = des(s, i); 

		return n; 
	}
};


class Codec8{
public:
	string serialize(TreeNode* root){
		if (!root) return "#"; 
		return to_string(root->val) + "," + serialize(root->left) + "," + serialize(root->right); 
	}
	TreeNode* deserialize(string& s){
		int i = 0; 
		return dfs(s, i); 
	}
	TreeNode* dfs(string& s, int& i){
		int j = i + 1; 
		while (j < s.size() && s[j] != ',') ++j; 
		string cur = s.substr(i, j - i); 
		i = j + 1; 
		if (cur == "#") return nullptr; 
		TreeNode* c = new TreeNode; 
		c->val = stoi(cur); 
		c->left = dfs(s, i); 
		c->right = dfs(s, i); 
		return c; 
	}
};



int main(){
	Codec6 a; 

	//TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, nullptr,
									new TreeNode(8, new TreeNode(7),
													nullptr));
	/*      6
		3       8
	1    4   7    9
	*/

	string c =  a.serialize(tree); 
	cout << c << endl; 

	auto d = a.deserialize(c); 
	print(d); 



	///////////////////////////
	auto start = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	cout << endl << microseconds << " microseconds elapsed..." << endl;
}

