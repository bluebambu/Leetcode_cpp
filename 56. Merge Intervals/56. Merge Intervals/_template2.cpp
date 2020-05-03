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

// Given a collection of intervals, merge all overlapping intervals.

// For example,
// Given[1, 3], [2, 6], [8, 10], [15, 18],
// return[1, 6], [8, 10], [15, 18].


struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};


class Solution {
public:
	vector<Interval> merge(vector<Interval>& intervals) {
		typedef pair<int, bool> PIB; 
		vector<PIB> termPtrs; 
		for (auto i : intervals){
			termPtrs.push_back({ i.start, true }); 
			termPtrs.push_back({ i.end, false }); 
		}

		sort(termPtrs.begin(), termPtrs.end(), [](PIB& a, PIB& b){
			return a.first<b.first || (a.first == b.first && a.second>b.second); 
		}); 

		vector<Interval> res; 
		int cum = 0; 
		int start, end; 
		for (int i = 0; i < termPtrs.size(); ++i){
			if (cum == 0 && termPtrs[i].second){
				start = termPtrs[i].first; 
			}
			
			if (termPtrs[i].second)
				cum += 1;
			else
				cum -= 1; 

			if (cum == 0 && termPtrs[i].second == false){
				end = termPtrs[i].first; 
				res.push_back(Interval(start, end)); 
				start = 0; 
				end = 0; 
			}
		}
		return res; 
	}
};


class Solution2 {
public:
	vector<Interval> merge(vector<Interval>& intervals) {
		map<int, int> terminals; 
		for (auto& i : intervals){
			terminals[i.start] += 1; 
			terminals[i.end] -= 1; 
		}

		vector<Interval> res; 
		int levels = 0, start; 
		for (auto& p : terminals){
			int x = p.first, cnt = p.second; 
			if (levels == 0)
				start = x; 
			levels += cnt; 
			if (levels == 0){
				res.push_back(Interval(start, x)); 
			}
		}

		return res; 
	}
}; 


int main(){
	Solution a; 

	vector<int> b = { 4, 1, -9, 0, INT_MAX }; 

	Interval c(1, 3), d(2, 6), e(8, 10), f(15, 18); 

	vector<Interval> v; v.push_back(c); v.push_back(d); v.push_back(e); v.push_back(f); 

	auto g = a.merge(v); 

	for (auto i : g){
		cout << i.start << " " << i.end << endl; 
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

