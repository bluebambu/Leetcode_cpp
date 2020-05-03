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


class Solution {
public:
    int lengthOfLongestSubstring(string s) {
		unordered_map<char, int> d; 

		int i = 0, j = 0, head, len = INT_MIN; 
		while (j < s.size()){
			d[s[j]]++; 
			j++; 
			while (d[s[j-1]] == 2){
				d[s[i]]--; 
				++i; 
			}
			len = max(len, j - i); 
		}
		return len == INT_MIN ? 0 : len; 
    }
};


class Solution2 {
public:
	int lengthOfLongestSubstring(string s) {
		vector<bool> v(26, false); 
		int i = 0, j = 0, len = 0, n = s.size(); 
		while (1){
			for (; j < n; ++j){
				char c = s[j]; 
				if (v[c-'a'])
					break;
				v[c-'a'] = true; 
				len = max(len, j - i + 1); 
			}

			if (j == n) return len; 

			for (; i < j; ++i){
				if (s[i] == s[j]){
					v[s[i]-'a'] = false; 
					++i; 
					break;
				}
				v[s[i]-'a'] = false; 
			}

		}
		return len;
	}
}; 

int main(){
	Solution a; 
	Solution2 a2; 

	string s = "abcabcbb"; 
	string s2 = "bbbbb"; 
	string s3 = "abc"; 

	cout << a.lengthOfLongestSubstring(s) << endl; 
	cout << a2.lengthOfLongestSubstring(s) << endl; 


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

