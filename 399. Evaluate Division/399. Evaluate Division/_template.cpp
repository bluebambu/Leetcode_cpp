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
#include <set>
#include <map>
#include <utility>
#include <sstream>
#include <string>
#include <time.h>

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

// Equations are given in the format A / B = k, where A and B are variables 
// represented as strings, and k is a real number(floating point number).Given 
// some queries, return the answers.If the answer does not exist, return  - 1.0.

// Example:
// Given a / b = 2.0, b / c = 3.0.
// queries are : a / c = ? , b / a = ? , a / e = ? , a / a = ? , x / x = ? .
// return [6.0, 0.5, -1.0, 1.0, -1.0].

// The input is : vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries , whereequations.size() == values.size(), and the values are positive.This represents the equations.Return vector<double>.
// According to the example above :

// equations = [["a", "b"], ["b", "c"]],
// values = [2.0, 3.0],
// queries = [["a", "c"], ["b", "a"], ["a", "e"], ["a", "a"], ["x", "x"]].

// 可以看作图， a/b=3 , 可以写成图的两条边， a->b=3, b->a=1/3. 然后再图搜索加上memorization就应该可以
// 邻接矩阵的表示法， 感觉还是 unordered_map<string, unordered_map<string, double>> 更好。 链表的效率太低了。 


// 我自己的解法， 最后终于接受了...... 太多corner case了。比较慢， beats 7%。。。。 
// 考虑的点，比如 a/b==0, 比如 a->b->c->d->a, 还有 a/a， 等等
class Solution {
public:

	vector<double> calcEquation(vector<pair<string, string>> equations, 
								vector<double>& values, 
								vector<pair<string, string>> queries ) 
	{
		// 核心思想就是， memorization可以当做整个graph的一部分不断地添加上去
		unordered_map<string, unordered_map<string, double>> g; 

		for (int i = 0; i < equations.size(); ++i){
			string dividend = equations[i].first, divisor = equations[i].second; 

			// 一个除法式子的正反， 再加上除数，被除数自己相除的情况
			g[dividend][divisor] = values[i]; 
			g[divisor][dividend] = values[i] != 0.0 ? 1.0 / values[i] : DBL_MAX; 
			g[dividend][dividend] = 1.0; 
			g[divisor][divisor] = 1.0;
		}

		vector<double> res; 
		unordered_set<string> hist; // 这个是用来每次query 记录 路径的

		for (int i = 0; i < queries.size(); ++i){
			// 每一次query， history需要清空
			hist.clear(); 
			// 对 query 进行dfs 深搜， 有valid结果返回数字， 否则返回 DBL_MAx. 
			double tmp = helper(queries[i].first, queries[i].second, hist, g);
			if (tmp != DBL_MAX)
				res.push_back(tmp);
			else
				res.push_back(-1.0); 
		}

		return res; 
	}

	
	double helper(string cur,
		string target,
		unordered_set<string>& hist,
		unordered_map<string, unordered_map<string, double>>& g // memorization 直接写入graph
		){

		if (g.find(cur) != g.end() && g[cur].find(target) != g[cur].end()){
			// 仔细想一下，任何情况都能用这个式子做结尾， 包括 a->a 的情况。 
			return g[cur][target];
		}

		// 如果路径中出现过cur， 返回invalid。 a->b->c->d->a, 死循环， 应该返回 invalid， 即 dblmax
		if (hist.count(cur) != 0)
			return DBL_MAX; 

		hist.insert(cur); 

		double res = DBL_MAX; 

		for (auto a : g[cur]){
			if (hist.count(a.first) == 0){					
				double tmp = helper(a.first, target, hist, g); 
				if (tmp != DBL_MAX)
					// 这里要记得把当前阶段除法结果带进去。 
					res = g[cur][a.first] * tmp; 
			}
		}

		// 我本来是想把invalid 结果也加入进 graph的， 但这样会出现bug， 比如本来 a 到 z 是没有连接的， 但如果写成 a->z = dblmax, 
		// then z->a=0, 这会在接下来的搜索中产生错误的结果。 所以我还是在这里做了个判断， 尽量不产生invalid的结果到graph里面。 
		if (res != DBL_MAX){
			g[cur][target] = res;
			g[target][cur] = 1.0 / res;
		}

		return res; 
	}
};

// bfs, 好写一些。 3ms. bidirectional bfs should be better. 
class Solution2 {
public:
	vector<double> calcEquation(vector<pair<string, string>> equations,
		vector<double>& values,
		vector<pair<string, string>> queries)
	{
		unordered_map<string, unordered_map<string, double>> g; 
		for (int i = 0; i < values.size(); ++i){
			g[equations[i].first][equations[i].second] = values[i];
			g[equations[i].second][equations[i].first] = 1.0 / values[i];
		}

		vector<double> res; 

		struct node{
			string symbol; 
			double val; 
			node(string x, double y) :symbol(x), val(y){}
		};

		for (int i = 0; i < queries.size(); ++i){
			queue<node> q;
			unordered_set<string> hist; 
			bool flag = true; 

			string head = queries[i].first, tail = queries[i].second;
			q.push(node(head, 1.0)); 
			hist.insert(head); 

			while (q.size() && flag){
				int n = q.size(); 
				for (int j = 0; j < n && flag ; ++j){
					string cur = q.front().symbol; 
					double base = q.front().val; 
					q.pop(); 

					for (auto next : g[cur]){
						string nxstr = next.first; 
						double ratio = next.second; 

						if (nxstr == tail){
							res.push_back(base*ratio);
							flag = false; 
							break; 
						}
						if (hist.count(nxstr) == 0){
							q.push(node(nxstr, base*ratio)); 
							hist.insert(nxstr);
							g[head][nxstr] = base*ratio; 
							g[nxstr][head] = 1.0 / (base*ratio);
						}
					}
				}
			}
			if (flag)
				res.push_back(-1.0);
		}

		return res; 
	}
};

// pass
class Solution3 {
public:
	vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
		unordered_map<string, unordered_map<string, double>> g; 
		int n = equations.size(); 
		for (int i = 0; i < n; ++i){
			g[equations[i].first][equations[i].second] = values[i]; 
			g[equations[i].second][equations[i].first] = 1.0/values[i]; 
		}
		
		unordered_map<string, unordered_map<string, double>> buf; 
		vector<double> res; 
		for (auto p : queries){
			unordered_set<string> v; 
			string st = p.first, ed = p.second; 
			if (st == ed){
				if (g.count(st))
					res.push_back(1.0);
				else
					res.push_back(-1.0); 
				continue;
			}

			bool found = false; 
			double r = dfs(g, st, ed, 1.0, v); 
			buf[st][ed] = r; 
			res.push_back(r); 
		}

		return res; 
	}

	typedef unordered_map<string, unordered_map<string, double>> GRAPH; 

	double dfs(GRAPH& g, string st, string ed, double path, unordered_set<string>& v){
		v.insert(st); 

		for (auto& p : g[st]){
			string next = p.first; 
			if (!v.count(next)){
				if (next == ed)
					return path * g[st][ed]; 
				double cur = dfs(g, next, ed, path*g[st][next], v); 
				if (cur != -1)
					return cur; 
			}
		}
		return -1; 
	}
};

class Solution4 {
public:
	vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
		int n = equations.size(); 
		unordered_map<string, unordered_map<string, double>> dict; 
		for (int i = 0; i < n; ++i){
			dict[equations[i].first][equations[i].second] = values[i]; 
			if (values[i]!=0)
				dict[equations[i].second][equations[i].first] = 1.0/values[i];
		}

		vector<double> res; 
		for (auto& p : queries){
			string start = p.first, end = p.second; 
			unordered_set<string> v; 
			bool isFinish = false; 
			if (start == end && dict.count(start)){
				res.push_back(1.0); 
				continue;; 
			}

			queue<pair<string, double>> q; 
			double curRes = -1; 
			q.push({ start, 1.0 }); 
			v.insert(start); 

			while (!q.empty()){
				auto f = q.front(); 
				q.pop(); 
				string curW = f.first; 
				double curV = f.second; 

				for (auto& nxt : dict[curW]){
					string nxtW = nxt.first; 
					double nxtV = nxt.second; 
					if (nxtW == end){
						isFinish = true; 
						curRes = curV*nxtV; 
						break;
					}
					if (!v.count(nxtW)){
						v.insert(nxtW); 
						q.push({ nxtW, curV*nxtV }); 
					}
				}
				if (isFinish)
					break;
			}

			if (!isFinish)
				res.push_back(-1);
			else{
				dict[start][end] = curRes; 
				res.push_back(curRes); 
			}
		}
		return res; 
	}
}; 

class Solution5 {
public:
	vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
		unordered_map<string, unordered_map<string, double>> dict; 
		int n = equations.size(); 
		for (int i = 0; i < n; ++i){
			dict[equations[i].first][equations[i].second] = values[i]; 
			if (values[i]!=0)
				dict[equations[i].second][equations[i].first] = 1.0/values[i];
		}

		vector<double> res; 
		for (auto& q : queries){
			double curRes = -1.0; 
			unordered_set<string> v; 
			v.insert(q.first);
			dfs(dict, q.first, q.second, 1.0, curRes, v); 
			dict[q.first][q.second] = curRes; 
			res.push_back(curRes); 
		}
		return res; 
	}
	void dfs(unordered_map<string, unordered_map<string, double>>& dict, string& cur, string& target, double curV, double& curRes, unordered_set<string>& v){
		if (cur == target && dict.count(cur)){
			curRes = curV; 
			return; 
		}
		
		for (auto& nxt : dict[cur]){
			string nxtW = nxt.first; 
			double nxtV = nxt.second; 
			if (!v.count(nxtW)){
				v.insert(nxtW); 
				dfs(dict, nxtW, target, curV*nxtV, curRes, v); 
			}
		}
	}
}; 


int main() {
	vector<pair<string, string>> equations = { { "x1", "x2" }, { "x2", "x3" }, { "x1", "x4" }, { "x2", "x5" } };
	vector<double> values					= { 3.0,				0.5,		3.4,				5.6 };
	vector<pair<string, string>> queries = { { "x2", "x4" }, { "x1", "x5" }, { "x1", "x3" }, { "x5", "x5" }, { "x5", "x1" }, 
											 { "x3", "x4" }, { "x4", "x3" }, { "x6", "x6" }, {"x0", "x0"}};

	Solution a; 
	auto b = a.calcEquation(equations, values, queries); 
	for (auto c : b)
		cout << c << "  ";
	cout << endl << endl; 

	Solution2 a2; 
	auto b2 = a2.calcEquation(equations, values, queries); 
	for (auto c2 : b2)
		cout << c2 << "  ";
	cout << endl << endl; 

	Solution5 a3; 
	auto b3 = a3.calcEquation(equations, values, queries); 
	for (auto c3 : b3)
		cout << c3 << "  ";
	cout << endl << endl; 
}

