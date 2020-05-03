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

// Given an absolute path for a file(Unix - style), simplify it.
// For example,
// path = "/home/", = > "/home"
// path = "/a/./b/../../c/", = > "/c"

// Corner Cases :

// Did you consider the case where path = "/../" ?
// In this case, you should return "/".
// Another corner case is the path might contain multiple slashes '/' together, such as "/home//foo/".
// In this case, you should ignore redundant slashes and return "/home/foo".

// corner case is too tricky: "/..." , "//.//", "/.", "/a//c//b"
// finally accept it. 
class Solution {
public:
	string simplifyPath(string path) {
		vector<string> stk;
		if (path.size() == 1)
			return path;

		for (int i = 1; i < path.size();)	{
			int j = i;
			for (; j < path.size() && path[j] != '/'; ++j);
			string substr = path.substr(i, j - i + 1);

			if (substr == "./" || substr == "/" || substr == "."){ // "." is specific for the last subpath
			}
			else if (substr == "../" || substr == ".."){  // ".." is specific for the last subpat
				if (stk.size())
					stk.pop_back();
			}
			else{
				stk.push_back(substr);
			}
			i = j + 1;
		}

		string res = "/";
		for (string s : stk){
			res += s;
		}

		for (int i = res.size() - 1; i > 0 && (res[i] == '/'); --i){
			res.pop_back();
		}

		return res;
	}
};

class Solution2 {
public:
	string simplifyPath(string path) {
		deque<string> stk; 
		path = "." + path + "/"; 

		for (int i = 0; i < path.size(); ++i){
			int j = i; 
			for (; j < path.size() && path[j] != '/'; ++j); 

			if (j==i)
				continue;

			string cur = path.substr(i, j - i + 1); 

			i = j; 

			if (cur == "./" || (cur == "../" && stk.empty()))
				continue;
			if (cur == "../")
				stk.pop_back();
			else
				stk.push_back(cur); 
		}

		string res = "/"; 
		while (!stk.empty()){
			res.append(stk.front()); 
			stk.pop_front(); 
		}
		if (res.size()>1)
			res.pop_back();
		return res; 
	}
}; 

class Solution3 {
public:
	string simplifyPath(string path) {
		if (path.back() != '/') // "/a/b//c//d/../."
			path.push_back('/');
		int i = path.size() - 1;
		int back_num = 0;
		string r;
		while (i >= 0){
			int j = i - 1;
			while (j >= 0 && path[j] != '/') --j;
			if (j < 0) break;
			string cur = path.substr(j + 1, i - j);
			i = j;
			if (cur == "../"){
				back_num += 1;
			}
			else if (cur == "./" || cur == "/") // "/a/b//c//d"
				continue;
			else if (back_num>0){
				--back_num;
			}
			else{
				r = cur + r;
			}
		}
		return "/" + r.substr(0, r.size() - 1);
	}
};

int main() {
	Solution3 a;

	string p = "/a/./b/../../c/"; 
	string p2 = "/home/"; 
	string p3 = "/a/../../b/./c/"; 
	string p4 = "/a/../../../";

	cout << a.simplifyPath(p4) << endl; 

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

