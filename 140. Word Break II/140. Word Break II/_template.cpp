// _template.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>
#include <string>
#include <unordered_set>

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


// Given a string s and a dictionary of words dict, add spaces in s to construct a sentence where each word is a valid dictionary word.
// 
// Return all such possible sentences.
// 
// For example, given
// s = "catsanddog",
// dict = ["cat", "cats", "and", "sand", "dog"].
// 
// A solution is["cats and dog", "cat sand dog"].


// 
// 这道题是之前那道Word Break 拆分词句的拓展，那道题只让我们判断给定的字符串能否被拆分成字典中的词，而这道题加大了难度，让我们求出所有可以拆分成的情况，
// 就像题目中给的例子所示。可以用DFS的套路来解题，但是不是一般的brute force，我们必须进行剪枝优化，因为按照惯例OJ的最后一个test case都是巨长无比的，很容易
// 就Time Limit Exceeded。那么如何进行剪枝优化呢，可以参见网友水中的鱼的博客，定义一个一位数组possible，其中possible[i] = true表示在[i, n]区间上有解，n为s的
// 长度，如果某个区间之前被判定了无解，下次循环时就会跳过这个区间，从而大大减少了运行时间，参见代码如下：
// 
//
//										  catsanddog
//											 / | \
//										   c  ... cat
// 										  /			\
// 										 at			..sand....		  这种情况下出现了重复情况， 可以用dp 来 剪枝
// 										/
// 									  ..sand...
class Solution
{
public:
	vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
		vector<string> res; 
		if (s.empty())
			return res; 
		vector<string> path; 
		vector<bool> dp(s.size() + 1, true); 
		dfs(s, 0, path, res, dp, wordDict);
		return res; 
	}

	bool dfs(string& s, int start, vector<string>& path, vector<string>& res, vector<bool>& dp, unordered_set<string>& wordDict){
		if (dp[start] == false)
			return false; 
		if (start == s.size()){
			string tmp; 
			for (auto& str : path)
				tmp += str + " "; 
			tmp.pop_back(); 
			res.push_back(tmp); 
			return true; 
		}

		bool temp = false; 
		for (int i = start; i < s.size(); ++i){
			string tmp = s.substr(start, i - start + 1); 
			if (wordDict.find(tmp) != wordDict.end() && dp[i + 1]){
				path.push_back(tmp); 
				temp |= dfs(s, i + 1, path, res, dp, wordDict); 
				path.pop_back(); 
			}
		}
		dp[start] = temp; 
		return temp; 
	}

};


// 其实path 不需要是 vector<string> 可以直接在过程中转换成长string
class Solution2 {
public:
	vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
		vector<string> res;
		string out;
		vector<bool> possible(s.size() + 1, true);
		wordBreakDFS(s, wordDict, 0, possible, out, res);
		return res;
	}
	void wordBreakDFS(string &s, unordered_set<string> &wordDict, int start, vector<bool> &possible, string &out, vector<string> &res) {
		if (start == s.size()) {
			res.push_back(out.substr(0, out.size() - 1));
			return;
		}
		for (int i = start; i < s.size(); ++i) {
			string word = s.substr(start, i - start + 1);
			if (wordDict.find(word) != wordDict.end() && possible[i + 1]) {
				out.append(word).append(" ");	// path 直接转换
				int oldSize = res.size();
				wordBreakDFS(s, wordDict, i + 1, possible, out, res);
				if (res.size() == oldSize) possible[i + 1] = false;	   // 一种经典的写dp的方法。 size不变。    
				out.resize(out.size() - word.size() - 1);
			}
		}
	}
};

int main()
{
	Solution a;

	string s = "catsanddog";
	unordered_set<string> dict = { "cat", "cats", "and", "sand", "dog" };

	auto b = a.wordBreak(s, dict); 

	for (auto i : b)
		cout << i << endl; 





}

