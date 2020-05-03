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

typedef pair<int, int> Interval; 

class Solution {
public:
	vector<Interval> intersection(vector<Interval> va, vector<Interval> vb){
		typedef pair<int, int> PII; 
		vector<PII> pts; 

		for (auto i : va){
			pts.push_back({ i.first, 1 });
			pts.push_back({ i.second, -1 });
		}
		for (auto i : vb){
			pts.push_back({i.first, 1}); 
			pts.push_back({i.second, -1}); 
		}

		sort(pts.begin(), pts.end()); 

		vector<Interval> res; 
		int start=-1, end=-1, cum=0; 
		for (int i = 0; i < pts.size(); ++i){
			cum += pts[i].second; 
			if (cum == 2 && pts[i].second == 1)
					start = pts[i].first; 

			if (cum == 1 && pts[i].second == -1){
				end = pts[i].first; 
				res.push_back({ start, end }); 
			}
		}
		return res; 
	}
};


class Solution2 {
public:
	vector<Interval> intersection(vector<Interval> va, vector<Interval> vb){
		map<int, int> terminals; 
		for (auto& i : va){
			terminals[i.first] += 1; 
			terminals[i.second] -= 1; 
		}
		for (auto& i : vb){
			terminals[i.first] += 1; 
			terminals[i.second] -= 1; 
		}

		int overlaps = 0; 
		vector<Interval> res; 
		for (auto iter=++terminals.begin(); iter!=terminals.end(); ++iter){
			if (iter->second < 0 && prev(iter)->second>0){
				res.push_back({ prev(iter)->first, iter->first }); 
			}
		}
		return res; 
	}
};


int main(){
	Solution a; 

	vector<Interval> b = { { 0, 2 }, { 7, 10 } }; 
	vector<Interval> c = { { 1, 3 }, { 5, 8 }, { 9, 11 } }; 

	auto d = a.intersection(b, c); 

	for (auto i : d){
		cout << i.first << " " << i.second << endl; 
	}


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

