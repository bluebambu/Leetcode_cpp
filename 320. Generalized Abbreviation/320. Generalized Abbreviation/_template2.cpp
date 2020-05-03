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
// Write a function to generate the generalized abbreviations of a word.

// Example:

// Given word = "word", return the following list(order does not matter) :

// ["word", "1ord", "w1rd", "wo1d", "wor1", "2rd", "w2d", "wo2", "1o1d", "1or1", "w1r1", "1o2", "2r1", "3d", "w3", "4"]


// pass AC
class Solution {
public:
	vector<string> generateAbbreviations(string word) {
		vector<string> res; 
		if (word.empty()){
			res.push_back("");  // this is very important, to make sure [abc]d, after generating 'abc', make sure the for loop is entered correctly. 
			return res; 
		}

		for (int i = 0; i < word.size(); ++i){
			string left = (i == 0 ? "" : to_string(i));
			for (auto right : generateAbbreviations(word.substr(i+1))){
				res.push_back(left + word[i] + right); 
			}
		}
		
		res.push_back(to_string(word.size())); 
		return res; 
	}
};


// pass AC
class Solution2 {
public:
	vector<string> generateAbbreviations(string word) {
		vector<string> res; 
		dfs(word, 0, 0, "", res); 
		return res; 
	}

	void dfs(string& word, int cur, int cnt, string path, vector<string>& res){
		if (cur == word.size()){
			if (cnt > 0){
				path += to_string(cnt); 
			}
			res.push_back(path); 
			return; 
		}

		//choose to abbr word[pos], but not abbr right now.
		dfs(word, cur + 1, cnt + 1, path, res); 
		//choose not to abbr word[pos], but abbr prev CNT chars.
		dfs(word, cur + 1, 0, path + (cnt==0 ? "" : to_string(cnt)) + word[cur], res); 
	}
};



// wrong ans
class Solution3 {
public:
	vector<string> generateAbbreviations(string word) {
		vector<string> res = dfs(word); 

		vector<string> res2; 
		for (auto& s : res){
			for (int i = 0; i < s.size(); ++i){
				if (isdigit(s[i])){
					int j = i + 1, sum = stoi(string()+s[i]); 
					while (j < s.size() && isdigit(s[j])) ++j, sum += stoi(string()+s[j]); 
					if (j==i+1)
						continue;
					else{
						
					}
				}
			}
		}
	}

	vector<string> dfs(string word){
		if (word.empty())
			return{""}; 

		vector<string> res; 
		for (int start = 0; start <= word.size(); ++start){
			if (start == 0)
				res.push_back(word); 
			else{
				string x = word.substr(start); 
				vector<string> sub = dfs(x); 
				for (auto& s : sub)
					res.push_back(to_string(start) + s); 
			}
		}
		return res; 
	}
}; 



class Solution4 {
public:
	vector<string> generateAbbreviations(string word) {
		if (word.empty())
			return{ "" }; 
		vector<string> res; 
		for (int i = 0; i < word.size(); ++i){
			string num = i == 0 ? "" : to_string(i); 
			string sub = word.substr(i + 1); 
			for (auto s : generateAbbreviations(sub)){
				res.push_back(num + word[i] + s); 
			}
		}
		res.push_back(to_string(word.size())); 
		return res; 
	}
}; 

class Solution5 {
public:
	vector<string> generateAbbreviations(string word) {
		vector<string> res; 
		dfs(word, 0, "", res); 
		return res; 
	}

	void dfs(string& word, int start, string path, vector<string>& res){
		for (int len = 0; len <= word.size() - start; ++len){
			string num = len == 0 ? "" : to_string(len); 
			int next_idx = start + len; 
			if (next_idx == word.size()){
				res.push_back(path + num); 
				return;; 
			}
			dfs(word, next_idx + 1, path + num + word[next_idx], res); 
		}
	}
}; 

int main(){
	Solution5 a; 

	vector<int> b = { 4, 1, -9, 0, INT_MAX }; 

	prt1Layer(a.generateAbbreviations("word")); 


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

