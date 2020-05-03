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
	string crackSafe(int n, int k, int start) {
		string res, path; 
		unordered_set<string> v; 

		for (int i = 0; i < n; ++i){
			path.push_back('0'+ start); 
		}
		res.append(path.begin(), path.end()); 
		v.insert(path); 

		dfs(n, k, path, res, v); 
		return res; 
	}

	bool dfs(int n, int k, string& path, string& res, unordered_set<string>& v){
		bool allVisited = true; 
		for (int i = 0; i < k; ++i){
			string pathCp = path; 
			pathCp = pathCp.substr(1) + to_string(i); 
			if (v.count(pathCp)){
				continue;			
			}
			else{
				allVisited = false; 
				v.insert(pathCp); 
				res.push_back('0' + i); 
				if (!dfs(n, k, pathCp, res, v)){
					res.pop_back(); 
					v.erase(pathCp); 
				}
				else
					return true; 
			}
		}

		if (allVisited)
			return v.size() == pow(k, n); 

		return false; 
	}
};

class Solution2 {
public:
	string crackSafe(int n, int k) {
		string res;
		for (int i = 0; i < n; ++i)
			res.push_back('0');

		unordered_set<string> v;
		v.insert(res);

		if (dfs(res, v, n, k))
			return res;
		else
			return "NONE"; 
	}

	bool dfs(string& res, unordered_set<string>& v, int n, int k){
		if (v.size() == pow(k, n))
			return true; 

		int l = res.size(); 
		string tail = res.substr(l - n, n);
		for (int i = 0; i < k; ++i){
			char c = '0' + i; 
			string cur = tail + c; 
			if (!v.count(cur)){
				v.insert(cur); 
				res.push_back(c); 
				if (dfs(res, v, n, k))
					return true; 
				else{
					v.erase(cur); 
					res.pop_back(); 
				}
			}
		}

		return false; 
	}
}; 


class Solution3 {
public:
	string crackSafe(int n, int k) {
		string res(n, '0'); 
		unordered_set<string> v; 
		v.insert(res);

		dfs(n, k, v, res, res);
		return res; 
	}
	bool dfs(int n, int k, unordered_set<string>& v, string cur, string& res){
		if (v.size() == pow(k, n))
			return true; 
		for (int i = 0; i < k; ++i){
			string nxt = cur.substr(1) + char('0' + i); 
			if (!v.count(nxt)){
				res.push_back('0' + i); 
				v.insert(nxt); 
				if (dfs(n, k, v, nxt, res))
					return true; 
				else{
					res.pop_back(); 
					v.erase(nxt); 
				}
			}
		}
		return false; 
	}
};



int main(){
	Solution3 a; 

	cout << a.crackSafe(2, 100).size() << endl; 
	//cout << a.crackSafe(2, 10, 1).size() << endl; 
	//cout << a.crackSafe(2, 10, 2).size() << endl; 

	Solution2 b; 
	cout << b.crackSafe(2, 10).size()  << endl; 

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

