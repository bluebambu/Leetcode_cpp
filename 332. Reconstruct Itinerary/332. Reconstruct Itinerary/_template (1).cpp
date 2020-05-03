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


// Given a list of airline tickets represented by pairs of departure and arrival airports[from, to], 
// reconstruct the itinerary in order.All of the tickets belong to a man who departs from JFK.Thus, 
// the itinerary must begin with JFK.

// Note:
// If there are multiple valid itineraries, you should return the itinerary that has the smallest 
// lexical order when read as a single string.For example, the itinerary["JFK", "LGA"] has a 
// smaller lexical order than["JFK", "LGB"].

// All airports are represented by three capital letters(IATA code).
// You may assume all tickets form at least one valid itinerary.

// Example 1 :
// tickets = [["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]]
// Return["JFK", "MUC", "LHR", "SFO", "SJC"].
// Example 2 :
// tickets = [["JFK", "SFO"], ["JFK", "ATL"], ["SFO", "ATL"], ["ATL", "JFK"], ["ATL", "SFO"]]
// Return["JFK", "ATL", "JFK", "SFO", "ATL", "SFO"].
// Another possible reconstruction is["JFK", "SFO", "ATL", "JFK", "ATL", "SFO"].But it is larger in lexical order.

// my answer, did not pass. this solution did not traverse all the vertex
class Solution {
public:
	vector<string> findItinerary(vector<pair<string, string>> tickets) {
		unordered_map<string, set<string>> g; 
		for (auto p : tickets){
			g[p.first].insert(p.second);
		}

		unordered_set<string> vstedEdge; 

		vector<string> res; 
		
		helper("JFK", g, vstedEdge, res); 

		return res; 
	}

	void helper(string cur, unordered_map<string, set<string>>& g, unordered_set<string>& vEdge, vector<string>& res){
		res.push_back(cur);
		for (string next : g[cur]){
			string edge = cur + next; 
			if (vEdge.count(edge)!=0)
				continue;

			vEdge.insert(edge); 
			helper(next, g, vEdge, res);
			break;
		}
	}

};


class Solution2 {
public:
	vector<string> findItinerary(vector<pair<string, string>> tickets) {
		unordered_map<string, multiset<string>> g; 
		for (auto i : tickets){
			g[i.first].insert(i.second);
		}

		vector<string> res; 

		helper("JFK", g, res); 

		return reverse(res.begin(), res.end());
		// or : return vector<string>(res.rbegin(), res.rend()); 
	}

	void helper(string cur, unordered_map<string, multiset<string>>& g, vector<string>& res){
		while (g[cur].size()){
			string next = *(g[cur].begin()); 
			g[cur].erase(g[cur].begin()); 
			helper(next, g, res);
		}
		res.push_back(cur); 
	}
};

// pass 
class Solution {
public:
	vector<string> findItinerary(vector<pair<string, string>> tickets) {
		unordered_map<string, map<string, int>> g;
		for (auto t : tickets){
			g[t.first][t.second] += 1;
		}

		vector<string> res;
		dfs("JFK", g, res);
		return vector<string>(res.rbegin(), res.rend());
	}

	void dfs(string cur, unordered_map<string, map<string, int>>& g, vector<string>&res){
		for (auto& nxt : g[cur]){
			if (g[cur][nxt.first] > 0){
				g[cur][nxt.first] -= 1;
				dfs(nxt.first, g, res);
			}
		}
		res.push_back(cur);
	}
};


class Solution {
public:
	vector<string> findItinerary(vector<pair<string, string>> tickets) {
		unordered_map<string, map<string, int>> g;
		for (auto t : tickets){
			g[t.first][t.second] += 1;
		}

		
	}
}; 





int main() {
	Solution a;

	vector<pair<string, string>> tickets = { { "JFK", "SFO" }, { "JFK", "ATL" }, { "SFO", "ATL" }, { "ATL", "JFK" }, { "ATL", "SFO" } }; 
	vector<string> b = a.findItinerary(tickets);

	for (int i = 0; i < b.size(); ++i){
		cout << b[i] << " ";
	}

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

