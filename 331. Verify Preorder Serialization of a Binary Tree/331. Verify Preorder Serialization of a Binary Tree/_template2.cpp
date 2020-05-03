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

class Solution {
public:
	string next(string& s, int& i){
		int j = i; 
		while (j < s.size() && s[j] != ',') ++j; 
		string res = s.substr(i, j - i); 
		i = j + 1; 
		return res; 
	}

	bool isValidSerialization(string preorder) {
		stack<bool> st; 
		st.push(true); 
		int i = 0; 

		while (!st.empty() || i==preorder.size()){
			string cur = next(preorder, i); 
			if (cur == "#"){
				st.pop(); 
			}
			else{
				st.push(true); 
			}
		}

		return st.empty() && i == preorder.size()+1; 
	}
};


// pass
class Solution2 {
public:
	string next(string& s, int& i){
		int j = i;
		while (j < s.size() && s[j] != ',') ++j;
		string res = s.substr(i, j - i);
		i = j + 1;
		return res;
	}

	bool isValidSerialization(string preorder) {
		preorder.push_back(',');
		int cnt = 1;
		int i = 0;
		while (i < preorder.size()){
			string cur = next(preorder, i);
			if (cur == "#")
				cnt -= 1;
			else
				cnt += 1;

			if (cnt < 0 || (cnt == 0 && cur == "#" && i < preorder.size()))
				return false;
		}
		return cnt == 0;
	}
};


class Solution3 {
public:
	string next(string& s, int& i){
		int j = i;
		while (j < s.size() && s[j] != ',') ++j;
		string res = s.substr(i, j - i);
		i = j + 1;
		return res;
	}

	bool isValidSerialization(string preorder) {
		int cnt = 1; 
		int i = 0; 
		while (i < preorder.size()){
			string cur = next(preorder, i); 
			cnt -= 1; 
			if (cnt < 0) return false; 
			if (cur != "#")
				cnt += 2;
		}
		return cnt == 0; 
	}
}; 

class Solution4{
public:
	bool isValidSerialization(string preorder) {
		int i = 0;
		return valid(preorder, i) && i >= preorder.size(); 
	}
	bool valid(string& s, int& i){
		if (i >= s.size())
			return false; 

		int j = i + 1; 
		while (j < s.size() && s[j] != ',') ++j; 
		string cur = s.substr(i, j - i); 
		i = j + 1; 
		if (cur == "#"){
			return true; 
		}

		return valid(s, i) && valid(s, i); 
	}
}; 

int main(){
	Solution4 a; 

	cout << a.isValidSerialization("1,#, #, 1") << endl; 
	cout << a.isValidSerialization("1,#") << endl; 
	cout << a.isValidSerialization("9,3,4,#,#,1,#,#,2,#,6,#,#") << endl; 

	vector<int> b = { 4, 1, -9, 0, INT_MAX }; 


	//TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
		3       8
	1    4   7    9
	auto


	///////////////////////////
	*/ start = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	cout << endl << microseconds << " microseconds elapsed..." << endl;
}

