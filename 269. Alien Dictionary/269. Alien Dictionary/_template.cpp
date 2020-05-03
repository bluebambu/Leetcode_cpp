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


template <typename T>
void tprt(T v){
	for (auto i : v)
		cout << v << " ";
	cout << endl; 
}


// There is a new alien language which uses the latin alphabet.However, the order among letters are unknown to you.You receive a list of non - empty words from the dictionary, where words are sorted lexicographically by the rules of this new language.Derive the order of letters in this language.

// Example 1:
// Given the following words in dictionary,

// [
// 	"wrt",
// 	"wrf",
// 	"er",
// 	"ett",
// 	"rftt"
// ]
// The correct order is : "wertf".

// Example 2 :
// Given the following words in dictionary,

// [
// 	"z",
// 	"x"
// ]
// The correct order is : "zx".

// Example 3 :
// Given the following words in dictionary,

// [
// 	"z",
// 	"x",
// 	"z"
// ]
// The order is invalid, so return "".

// Note:
// You may assume all letters are in lowercase.
// You may assume that if a is a prefix of b, then a must appear before b in the given dictionary.
// If the order is invalid, return an empty string.
// There may be multiple valid order of letters, return any one of them is fine.


// 我自己的版本，不是很完美， 不过勉强可用。 用的是princeton algo topo sort 的框架。
class Solution {
public:
	string alienOrder(vector<string>& words) {
		unordered_map<char, unordered_set<char>> g;
		unordered_set<char> all;
		genG(words, g, all);

		// print //
		for (auto aa : g){
			cout << aa.first << ": ";
			for (auto bb : aa.second){
				cout << bb << ", ";
			}
			cout << endl;
		}

		cout << "all: "; 
		for (auto i : all)
			cout << i << " ";
		cout << endl; 
		// print //

		string res;
		unordered_set<char> visited;

		for (char a : all){
			
			if (visited.count(a) == 0){
				// 因为要测是否有环， 所以每次dfs都要额外再用一个hashtable来记录这一条路径是否会遇到同一个元素两次
				unordered_set<char> isCycle;
				bool flag = false; // 遇到环之后的flag
				helper(a, g, visited, res, isCycle, flag);

				if (flag)
					return "";
			}
		}
		return res;
	}

	void helper(char cur,
		unordered_map<char, unordered_set<char>>& g,
		unordered_set<char>& visited,
		string& res,
		unordered_set<char>& isCycle,
		bool& flag){

		if (flag == true)
			return;

		visited.insert(cur);
		isCycle.insert(cur);
		for (auto next : g[cur]){
			// 要特别注意， 环的检测要放在这里， 而不是for loop 上面。 check {"z","x","z"} example. 
			if (isCycle.count(next)){
				flag = true;
				return;
			}

			if (visited.count(next) == 0){
				helper(next, g, visited, res, isCycle, flag);
			}
		}
		res.push_back(cur);
	}


	void genG(vector<string>& words,
		unordered_map<char, unordered_set<char>>& g,
		unordered_set<char>& all){

		int n = words.size();

		// 图的生成其实比较讲究。 我本来想按照 j 来loop， 每次只比较同一位上面的字母， 但发现太麻烦了， 
		// 太多corner case。 所以还是按照 i 来 loop， 每次只比较上下两条string， 这样方便很多， 思路清晰
		// 注意 i<n-1， 因为只比较上下两条， 最后一条不需要遍历到。 不过all 的生成还是要求要遍历到最后一条string
		// 所以我在all 的处理上冗余了一些..... 
		for (int i = 0; i < n-1; ++i){
			for (int j = 0; j < words[i].size(); ++j){
				all.insert(words[i][j]);
			}

			int n1 = words[i].size(), n2 = words[i + 1].size(), minN = min(n1, n2);
			for (int j = 0; j < minN; ++j){
				if (words[i][j] != words[i + 1][j]){
					// 只要有不同， 就不再需要再接下去找了。 
					g[words[i][j]].insert(words[i + 1][j]);
					break;;
				}
			}


		}

		for (int j = 0; j < words[n-1].size(); ++j){
			all.insert(words[n-1][j]);
		}
	}
};


// bfs by me
class Solution2 {
public:
	string alienOrder(vector<string>& words) {
		unordered_set<char> allch; 
		for (auto w : words)
			allch.insert(w.begin(), w.end());

		unordered_map<char, unordered_set<char>> g; 
		for (size_t i = 0; i < words.size() - 1; ++i){
			size_t mn = min(words[i].size(), words[i + 1].size()); 
			size_t j = 0;
			for (; j < mn; ++j){
				if (words[i][j] != words[i + 1][j]){
					g[words[i][j]].insert(words[i + 1][j]);
					break;
				}
			}
			if (j == mn && words[i].size() > words[i + 1].size())
				return ""; 
		}

		unordered_map<char, int> in; 
		for (auto p : g)
			for (auto c : p.second)
				in[c] += 1;

		queue<char> q; 
		for (auto i : allch) // 要从 allch 遍历， 而不是从 in 遍历。 因为  indegree 为零的点根本不在 in 里面!:
			if (in.count(i)==0)
				q.push(i); 

		////////////////////
		cout << "graph: \n"; 
		for (auto i : g){
			cout << i.first << ": ";
			for (auto j : i.second){
				cout << j << ", ";
			}
			cout << endl; 
		}

		cout << "\n\nin: \n"; 
		for (auto i : in)
			cout << i.first << ": " << i.second << endl; 
		cout << endl; 


		cout << "allch: \n"; 
		set<char> s(allch.begin(), allch.end());
		for (auto i : s)
			cout << i ;
		cout << endl; 
		/////////////////////////


		string res; 

		while (!q.empty()){
			char tmp = q.front(); 
			q.pop(); 

			if (g.count(tmp)){
				for (auto next : g[tmp]){
					--in[next];

					// 这句话不需要的， 因为达不到！！ 有环的情况下，并不是 indegree会成负， 而是在环的地方 bfs 断掉结束
					// 从而无法遍历所有的点。 所以最后return的值是 allch 和 res 的size 的比较！！！！： 
					if (in[next] < 0)
						return "";

					if (in[next] == 0){
						q.push(next);
					}
				}
			}

			res.push_back(tmp); 
		}

		/////////////////
		cout << "res: \n"; 
		sort(res.begin(), res.end());
		cout << res << endl; 
		////////////////`

		// return res; 会出错。 写上下面这一句就过了。
		// 出错的例子是这个。  { "ri", "xz", "qxf", "jhsguaw", "dztqrbwbm", "dhdqfb", "jdv", "fcgfsilnb", "ooby" };
		return  res.size() == allch.size() ? res : ""; 
	}
};


// practice
class Solution3 {
public:
	string alienOrder(vector<string>& words) {
		unordered_set<char> allch; 
		for (auto i : words)
			allch.insert(i.begin(), i.end()); 

		unordered_map<char, unordered_set<char>> g; 
		for (size_t i = 0; i < words.size() - 1; ++i){
			size_t mn = min(words[i].size(), words[i + 1].size()); 
			for (size_t j = 0; j < mn; ++j){
				if (words[i][j] != words[i + 1][j]){
					g[words[i][j]].insert(words[i + 1][j]); 
					break; 
				}
			}
		}

		unordered_map<char, int> in; 
		for (auto i : g)
			for (auto j : i.second)
				++in[j]; 

		queue<char> q; 
		for (auto c : allch){
			if (in.count(c) == 0){
				q.push(c);
			}
		}

		string res; 

		while (q.size()){
			char frt = q.front(); 
			q.pop(); 

			for (auto next : g[frt]){
				--in[next]; 
				if (in[next] == 0){
					q.push(next);
				}
			}

			res.push_back(frt);
		}
		
		return res.size() == allch.size() ? res : ""; 
		

	}

};


//
class Solution4 {
public:
    string alienOrder(vector<string>& words) {
		unordered_map<char, unordered_set<char>> g; 
		unordered_map<char, int> indegree; 
		int n = words.size(); 
		for (int i = 0; i < n ; ++i){
			for (int j = 0; j < words[i].size(); ++j)
				g[words[i][j]]; 

			for (int j = 0; i<n-1 && j < min(words[i].size(), words[i + 1].size()); ++j){
				if (words[i][j] != words[i + 1][j]){
					g[words[i][j]].insert(words[i + 1][j]);
					// indegree[words[i + 1][j]] += 1;  this is Wrong!!!!
					break;
				}
			}
		}

		for (auto p : g){
			for (auto i : p.second){
				indegree[i] += 1; 
			}
		}

		for (auto p : g){
			for (auto i : p.second){
				cout << p.first << " " << i << endl; 
			}
		}

		cout << endl << endl; 

		for (auto p : indegree)
			cout << p.first << " " << p.second << endl; 

		queue<char> q; 
		unordered_set<char> v; 
		string res; 
		for (auto p : g){
			char cur = p.first; 
			if (indegree[cur] == 0){
				q.push(cur); 
				v.insert(cur);
				res.push_back(cur); 
			}
		}

		while (!q.empty()){
			char f = q.front(); 
			q.pop(); 

			for (char next : g[f]){
				indegree[next] -= 1; 
				if (indegree[next] == 0){
					q.push(next); 
					v.insert(next); 
					res.push_back(next); 
				}
			}
		}

		return res.size()==g.size() ? res : ""; 
    }
};

int main() {
	Solution4 aa;

	vector<string> words = {
		"wrt",
		"wrf",
		"er",
		"ett",
		"rftt"
	}; 

	vector<string> w3 = { "za", "zb", "ca", "cb" }; 

	vector<string> w2 = { "ri",  // has rings inside!!!!
						  "xz", 
						  "qxf", 
						  "jhsguaw", 
						  "dztqrbwbm", 
						  "dhdqfb", 
						  "jdv", 
						  "fcgfsilnb", 
						  "ooby" };

	auto bb = aa.alienOrder(w3); 

	cout << "result: " << bb << endl; 

}

