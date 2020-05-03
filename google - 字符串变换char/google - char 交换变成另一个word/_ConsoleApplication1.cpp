// _template4.cpp : Defines the entry point for the console application.
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

typedef vector<int> VI; 
typedef vector<VI> VVI; 
typedef pair<int, int> PII; 

VVI dirs = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } }; 


class Solution {
public:
	vector<vector<char>> exch(string s, string target){
		if (s.size() != target.size()) return{};
		unordered_map<char, char> g; 
		unordered_map<char, int> indegree; 
		for (int i = 0; i < s.size(); ++i){
			if (s[i] != target[i]){
				if (g.count(s[i]) && g[s[i]] != target[i])
					return{};
				if (g[s[i]] == target[i])
					continue;
				g[s[i]] = target[i]; 
				indegree[s[i]]; 
				indegree[target[i]] += 1; 
			}
		}
		
		queue<char> q; 
		for (auto& p : indegree){
			char c = p.first; 
			if (p.second == 0){
				q.push(c); 
			}
		}
		
		vector<vector<char>> res; 
		int terminal = 0; 
		while (!q.empty()){
			char f = q.front(); 
			q.pop();;

			if (g.count(f) == 0){
				++terminal; 
				continue;
			}

			char nxt = g[f]; 
			--indegree[nxt]; 
			res.push_back({ f, nxt }); 
			if (indegree[nxt] == 0){
				q.push(nxt); 
			}
		}
		if (res.size() != indegree.size() - terminal){
			return{};//processCycle(g, indegree);
		}
		reverse(res.begin(), res.end()); 
		return res; 
	}
};


class Solution2 {
public:
	vector<vector<char>> exch(string s, string t){
		if (s.size() != t.size()) return{}; 

		unordered_map<char, char> map; 
		unordered_map<char, int> indegree; 
		for (int i = 0; i < s.size(); ++i){
			char a = s[i], b = t[i]; 
			if (map.count(a) && map[a] != b)
				return{}; 
			if (a == b)
				map[a] = a; 
			if (map.count(a) == 0){
				map[a] = b;
				indegree[b] += 1; 
				indegree[a]; 
			}
		}

		for (auto iter = map.begin(); iter != map.end();){
			if (iter->first == iter->second){
				iter = map.erase(iter); 
			}
			else
				++iter; 
		}

		queue<char> q; 
		for (auto& p : indegree)
			if (p.second == 0)
				q.push(p.first); 

		int processed_nodes = 0; 
		vector<vector<char>> res; 

		while (!q.empty()){
			char f = q.front(); 
			q.pop(); 
			processed_nodes += 1; 
			if (map.count(f)==0)
				continue;

			res.push_back({ f, map[f] }); 


			auto& nxtc = map[f];
			--indegree[nxtc];
			if (indegree[nxtc] == 0){
				q.push(nxtc);
			}
		}

		if (processed_nodes != indegree.size()){
			// here is circle
			// advance_to_process_circle(map, res); 
			cout << "Cycle!\n"; 
			return{};
		}

		return res; 
	}
}; 


class Solution3 {
public:
	vector<vector<char>> exch(string s, string t){
		unordered_map<char, char> cmap; 
		unordered_map<char, int> indegree; 
		for (int i = 0; i < s.size(); ++i){
			char a = s[i], b = t[i]; 
			if (cmap.count(a)){
				if (cmap[a] != b)
					return false; 
				continue;
			}
			if (a == b){
				cmap[a] = b; 
			}
			else{
				cmap[a] = b;
				indegree[b] += 1; 
				indegree[a]; 
			}
		}

		for (auto iter = cmap.begin(); iter != cmap.end();){
			if (iter->first == iter->second)
				iter = cmap.erase(iter);
			else
				++iter; 
		}

		queue<char> q; 
		for (auto& p : indegree){
			if (p.second == 0)
				q.push(p.first); 
		}

		int processed_nodes = 0; 
		vector<vector<char>> res; 

		while (!q.empty()){
			char f = q.front(); 
			q.pop(); 
			++processed_nodes; 
			if (cmap.count(f) == 0)
				continue;

			char nxt = cmap[f]; 
			res.push_back({ f, nxt }); 
			--indegree[nxt]; 
			if (indegree[nxt] == 0)
				q.push(nxt); 
		}

		if (indegree.size() != processed_nodes){
		// circle
			return{}; 
		}
		
		return res;;
	}
};


int main(){
	Solution2 a;

	string s1 = "abc", s2 = "bca"; 
	auto b = a.exch(s1, s2); 
	prt2Layer(b);

	s1 = "abcd", s2 = "accc"; 
	b = a.exch(s1, s2); 
	prt2Layer(b);

	s1 = "aab", s2 = "acd"; 
	b = a.exch(s1, s2); 
	prt2Layer(b);

	s1 = "aaaa", s2 = "bbbb"; 
	b = a.exch(s1, s2); 
	prt2Layer(b);

	s1 = "abcd", s2 = "efgh"; 
	b = a.exch(s1, s2); 
	prt2Layer(b);


	//TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6,
		new TreeNode(3, new TreeNode(1),
						new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
						new TreeNode(9,
		                               new TreeNode(10),
		                               nullptr)));
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

