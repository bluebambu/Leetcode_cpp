// _template.cpp : Defines the entry point for the console application.
//
#include <stdafx.h>

#include <iostream>
#include <functional>
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
#include <fstream>
#include <random>
#include <ctime>

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
	void external(int RAM, string fname) {
		ifstream ifstr(fname); 

		int out_fid = 1; 
		string line; 
		while (getline(ifstr, line)){
			ofstream ofstr(to_string(out_fid) + ".txt"); 
			for (int i = 0; i < RAM; ++i){
				ofstr << line << endl; 
				if (!getline(ifstr, line))
					break; 
			}
			++out_fid; 
		}

		for (int i = 1; i < out_fid; ++i){
			string cur_f = to_string(i) + ".txt"; 
			ifstream ifstr(cur_f); 
			vector<string> arr; 
			string line; 
			while (getline(ifstr, line)){
				arr.push_back(line); 
			}
			sort(arr.begin(), arr.end()); 
			ofstream ofstr(cur_f); 
			for (auto& a : arr){
				ofstr << a << endl; 
			}
		}

		priority_queue<string, vector<string>, greater<string>> minheap; 

		// use heap to reduce all the files and make into a full one. 

	}

	void prepare(string fname){
		ofstream of(fname); 

		int N = 1000; 
		for (int i = 0; i < N; ++i){
			for (int j = 0; j < 7; ++j){
				of << char('a' + rand()%26); 
			}
			of << endl; 
		}
	}
};








int main(){
	srand(time(NULL)); 

	string fname = "big_data.txt"; 
	Solution a; 

	vector<int> b = { 4, 1, -9, 0, INT_MAX }; 

	a.prepare(fname);
	a.external(90, fname); 

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

