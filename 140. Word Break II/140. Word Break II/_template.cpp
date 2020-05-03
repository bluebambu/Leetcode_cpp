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
// �������֮ǰ�ǵ�Word Break ��ִʾ����չ���ǵ���ֻ�������жϸ������ַ����ܷ񱻲�ֳ��ֵ��еĴʣ��������Ӵ����Ѷȣ�������������п��Բ�ֳɵ������
// ������Ŀ�и���������ʾ��������DFS����·�����⣬���ǲ���һ���brute force�����Ǳ�����м�֦�Ż�����Ϊ���չ���OJ�����һ��test case���Ǿ޳��ޱȵģ�������
// ��Time Limit Exceeded����ô��ν��м�֦�Ż��أ����Բμ�����ˮ�е���Ĳ��ͣ�����һ��һλ����possible������possible[i] = true��ʾ��[i, n]�������н⣬nΪs��
// ���ȣ����ĳ������֮ǰ���ж����޽⣬�´�ѭ��ʱ�ͻ�����������䣬�Ӷ�������������ʱ�䣬�μ��������£�
// 
//
//										  catsanddog
//											 / | \
//										   c  ... cat
// 										  /			\
// 										 at			..sand....		  ��������³������ظ������ ������dp �� ��֦
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


// ��ʵpath ����Ҫ�� vector<string> ����ֱ���ڹ�����ת���ɳ�string
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
				out.append(word).append(" ");	// path ֱ��ת��
				int oldSize = res.size();
				wordBreakDFS(s, wordDict, i + 1, possible, out, res);
				if (res.size() == oldSize) possible[i + 1] = false;	   // һ�־����дdp�ķ����� size���䡣    
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

