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

class Solution {
public:
	int minFlipsMonoIncr(string S) {
		int n = S.size(); 
		vector<int> end_zero(n + 1, INT_MAX), end_one(n+1, INT_MAX); 
		end_one[0] = 0, end_zero[0] = 0; 
		
		for (int i = 1; i <= n; ++i){
			char c = S[i - 1];
			end_zero[i] = end_zero[i - 1] + (c != '0'); 
			end_one[i] = min(end_zero[i - 1] + (c!= '1'), end_one[i - 1] + (c!= '1')); 
		}

		prt1Layer(end_zero); 
		prt1Layer(end_one); 

		return min(end_zero[n], end_one[n]); 
	}
};


class Solution2 {
public:
	int minFlipsMonoIncr(string S) {
		int n = S.size(); 
		int end_one= 0, end_zero= 0; 
		
		for (int i = 1; i <= n; ++i){
			char c = S[i - 1];
			end_one = min(end_zero + (c != '1'), end_one + (c != '1'));
			end_zero = end_zero + (c != '0'); 
		}

		return min(end_one, end_zero); 
	}
};


class Solution3 {
public:
	int minFlipsMonoIncr(string S) {
					
	}
};


int main(){
	Solution2 a;

	string s = "00110"; 
	string s2 = "00011000"; 

	cout << a.minFlipsMonoIncr(s2) << endl; 


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

