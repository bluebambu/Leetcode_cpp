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

// pass
long long M = 1e9 + 7; 
class Solution {
public:
    int rectangleArea(vector<vector<int>>& rectangles) {
		if (rectangles.size() == 0)
			return 0; 

		vector<vector<int>> verticals; 
		for (auto& rec : rectangles){
			verticals.push_back({ rec[0], rec[1], rec[3], 1 }); 
			verticals.push_back({ rec[2], rec[1], rec[3], -1 }); 
		}
		sort(verticals.begin(), verticals.end()); 

		map<int, int> y; 
		int prex = verticals[0][0]; 
		long long res = 0; 
		for (int i = 0; i < verticals.size(); ++i){
			auto& cur = verticals[i]; 
			long long ylen = calcYlen(y);
			if (cur[3]==1){
				y[cur[1]]++, y[cur[2]]--; 
			}
			else if (cur[3] == -1){
				y[cur[1]]--, y[cur[2]]++;
			}

			if (i > 0){
				res = (res + (ylen * (cur[0] - prex)) % M) % M;
				prex = cur[0]; 
			}
		}

		return res; 
    }

	long long calcYlen(map<int, int>& y){
		int cnt = 0, start = -1, end = -1; 
		long long res = 0; 
		for (auto& p : y){
			int ypos = p.first, ycnt = p.second; 
			if (ycnt != 0){
				if (cnt == 0)
					start = ypos; 
				cnt += ycnt; 
				if (cnt == 0){
					res += ypos - start; 
				}
			}
		}
		return res; 
	}
};

// not considering super big number. 
class Solution2 {
public:
	int rectangleArea(vector<vector<int>>& rectangles) {
		// [x1, y1, x2, y2]
		struct edge{
			int x, y0, y1; 
			bool flag; 
			edge(int a, int b, int c, bool d) :x(a), y0(b), y1(c), flag(d) {}
		};
		vector<edge> edges; 
		for (auto& rec : rectangles){
			edges.push_back(edge(rec[0], rec[1], rec[3], 1)); 
			edges.push_back(edge(rec[2], rec[1], rec[3], 0)); 
		}
		sort(edges.begin(), edges.end(), [](edge a, edge b){
			return a.x < b.x; 
		}); 

		map<int, int> terminals; 
		int prex = edges[0].x; 
		terminals[edges[0].y0] += 1, terminals[edges[0].y1] -= 1; 
		int res = 0; 

		for (int i = 1; i < edges.size(); ++i){
			int preY = calc(terminals); 
			int xdelta = edges[i].x - prex; 
			res += xdelta * preY; 
			prex = edges[i].x; 
			if (edges[i].flag == 1){
				terminals[edges[i].y0] += 1;
				terminals[edges[i].y1] -= 1;
			}
			else{
				terminals[edges[i].y0] -= 1;
				terminals[edges[i].y1] += 1;
			}
		}

		return res; 
	}

	int calc(map<int, int>& ytermnl){
		int res = 0, start, levels = 0; 
		for (auto& p : ytermnl){
			if (p.second != 0){
				if (levels == 0)
					start = p.first;
				levels += p.second;
				if (levels == 0){
					res += p.first - start; 
				}
			}
		}
		return res; 
	}
}; 


class Solution3 {
public:
	int rectangleArea(vector<vector<int>>& rectangles) {
		
	}
}; 

int main(){
	Solution a;
	Solution2 a2;

	vector<vector<int>> b = {
		{0,0,2,2}, 
		{1,0,2,3}, 
		{1,0,3,1}, 
	}; 

	cout << a.rectangleArea(b) << endl; 
	cout << a2.rectangleArea(b) << endl; 

	vector<vector<int>> c = {
		{ 0, 0, 1000000000, 1000000000 }
	}; 

	cout << a.rectangleArea(c) << endl; 
	cout << a2.rectangleArea(c) << endl; 

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

