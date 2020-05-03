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




struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

// pass
class Solution {
public:
	vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
		vector<Interval> res; 
		int i = 0; 
		bool headInserted = false; 
		if (intervals.size() == 0 || newInterval.start <= intervals[0].start){
			res.push_back(newInterval); 
			headInserted = true; 
		}
		else{
			res.push_back(intervals[0]);
			i = 1; 
		}

		for (; i < intervals.size(); ++i){
			if (!headInserted){
				if ( newInterval.start <= intervals[i].start && newInterval.start > res.back().start){
					if (newInterval.start > res.back().end)
						res.push_back(newInterval);
					else
						res.back().end = max(newInterval.end, res.back().end); 
					headInserted = true; 
				}

			}
			if (intervals[i].start > res.back().end)
				res.push_back(intervals[i]);
			else
				res.back().end = max(intervals[i].end, res.back().end);
		}

		if (!headInserted){
			if (newInterval.start > res.back().end)
				res.push_back(newInterval);
			else
				res.back().end = max(newInterval.end, res.back().end);
			headInserted = true;
		}

		return res; 

	}
};

class Solution2 {
public:
	vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
		map<int, int> terminals; 
		for (auto& i : intervals){
			terminals[i.start] += 1; 
			terminals[i.end] -= 1; 
		}
		terminals[newInterval.start] += 1; 
		terminals[newInterval.end] -= 1; 

		int cnt = 0, start; 
		vector<Interval> res; 
		for (auto& p : terminals){
			if (cnt == 0)
				start = p.first; 
			cnt += p.second; 
			if (cnt == 0)
				res.push_back(Interval(start, p.first)); 
		}
		return res; 
	}
}; 



int main(){
	Solution a; 

	Interval b(0, 3), c(6, 7), d(8, 10); 
	vector<Interval> e; 
	e.push_back(b); 
	e.push_back(c); 
	e.push_back(d); 
	Interval f(4, 5); 

	auto g = a.insert(e, f);

	for (auto x : g){
		cout << x.start << " " << x.end << endl; 
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

