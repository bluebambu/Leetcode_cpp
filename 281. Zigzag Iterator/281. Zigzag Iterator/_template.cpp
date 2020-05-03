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

// Given two 1d vectors, implement an iterator to return their elements alternately.
// 
// For example, given two 1d vectors:
// 
// v1 = [1, 2]
// v2 = [3, 4, 5, 6]
// 
// By calling next repeatedly until hasNext returns false, the order of elements returned by next should be : [1, 3, 2, 4, 5, 6].
// 
// Follow up : What if you are given k 1d vectors ? How well can your code be extended to such cases ?
// 
// Clarification for the follow up question - Update(2015 - 09 - 18) :
// The "Zigzag" order is not clearly defined and is ambiguous for k > 2 cases.If "Zigzag" does not look right to you, replace "Zigzag" with "Cyclic".For example, given the following input :
// 
// [1, 2, 3]
// [4, 5, 6, 7]
// [8, 9]
// 
// It should return[1, 4, 8, 2, 5, 9, 3, 6, 7].





// pass
class ZigzagIterator {
public:

	typedef vector<int>::iterator VIT; 
	typedef pair<VIT, VIT> PIT; 

	queue<PIT> q; 

	ZigzagIterator(vector<int>& v1, vector<int>& v2) {
		
		if (!v1.empty())
			q.push(make_pair(v1.begin(), v1.end())); 
		if (!v2.empty())
			q.push(make_pair(v2.begin(), v2.end())); 
	}

	int next() {
		PIT tmp = q.front(); 
		q.pop(); 
		if (tmp.first + 1 != tmp.second)
			q.push(make_pair(tmp.first + 1, tmp.second)); 
		return *tmp.first; 
	}

	bool hasNext() {
		return !q.empty(); 
	}
};

/**
* Your ZigzagIterator object will be instantiated and called as such:
* ZigzagIterator i(v1, v2);
* while (i.hasNext()) cout << i.next();
*/

// passed
class ZigzagIterator2 {
public:

	typedef vector<int>::iterator VIT; 
	queue<pair<VIT, VIT>> que; 

	ZigzagIterator2(vector<int>& v1, vector<int>& v2){
		if (!v1.empty()) que.push({ v1.begin(), v1.end() }); 
		if (!v2.empty()) que.push({ v2.begin(), v2.end() }); 
	}

	int next() {
		if (!hasNext())
			return INT_MIN; 

		auto f = que.front(); 
		que.pop(); 

		VIT cur = f.first, end = f.second; 
		if (cur + 1 != end)
			que.push({cur + 1, end});
		return *cur; 
	}

	bool hasNext() {
		return !que.empty(); 
	}
};


// Wrong ans.  consider case: 
// {1,2,3,4,5}
// {1,2,3}
// {1,2}
// when id comes to pos under 5, hasNext() still returns true, but infact there is no valid elem there anymore. 
class ZigzagIterator3 {
public:
	int id; 
	int maxid; 
	vector<int> *a1, *a2; 

	ZigzagIterator3(vector<int>& v1, vector<int>& v2){
		a1 = &v1;  a2 = &v2;
		int m = max(v1.size(), v2.size()); 
		maxid = 2 * m; 
		id = 0; 
	}

	int next(){
		if (hasNext()){
			int x, y;
			vector<int>* cur;
			while (1) {
				x = id % 2, y = id / 2;
				cur = x ? a2 : a1;
				if (y >= maxid)
					return INT_MIN; 

				if (y >= cur->size()){
					++id;
					continue;
				}
				else
					break;
			}
			++id;
			return (*cur)[y];
		}
	}

	bool hasNext(){
		return id < maxid; 
	}
}; 

// passed 
class ZigzagIterator4 {
public:
	vector<vector<int>*> core; 
	int i, j; 
	int n; 
	ZigzagIterator4(vector<int>& v1, vector<int>& v2) {
		core.push_back(&v1); 
		core.push_back(&v2); 
		n = 2; 
		i = n - 1, j = -1;
	}

	bool hasNext(){
		int ii=i, jj=j; 
		while (true){
			ii = (ii + 1) % n; 
			if (ii == 0)
				jj += 1; 
			if (jj<core[ii]->size() || ii==i)
				break;
		}

		return jj < core[ii]->size(); 
	}

	int next(){
		if (hasNext()){
			while (true){
				i = (i + 1) % n;
				if (i == 0)
					j += 1;
				if (j < core[i]->size())
					break;
			}
			return core[i]->at(j); 
		}
	}
}; 
		

class ZigzagIterator5 {
public:
	vector<vector<int>*> core; 
	int i, j; 
	int n; 
	ZigzagIterator5(vector<int>& v1, vector<int>& v2) {
		core.push_back(&v1); 
		core.push_back(&v2); 
		n = 2; 
		i = n - 1, j = -1;
	}

	bool hasNext(){
		int ii = (i + 1) % n, jj = (ii == 0 ? j + 1 : j );
		int cnt = 0; 
		while (cnt < n){
			if (jj<core[ii]->size())
				break;
			ii = (ii + 1) % n, jj = (ii == 0 ? jj + 1 : jj );
			cnt += 1; 
		}

		return !(cnt == n);
	}

	int next(){
		if (hasNext()){
			while (true){
				i = (i + 1) % n;
				if (i == 0)
					j += 1;
				if (j < core[i]->size())
					break;
			}
			return core[i]->at(j); 
		}
	}
}; 

class ZigzagIterator6 {
public:
	vector<vector<int>> core;
	int i, j; 
	ZigzagIterator6(vector<vector<int>> mtx) :core(mtx){
		i = 0, j = 0; 
	}

	bool hasNext(){
		if (i == core.size())
			++j, i = 0;

		int prei = i; 

		while (true){
			if (i < core.size() && j < core[i].size())
				return true; 
			++i; 
			if (i == core.size())
				++j, i = 0;
			if (i == prei)
				return false; 
		}
		return false; 
	}

	int next(){
		int r = core[i][j]; 
		++i; 
		return r;
	}
};

int main() {
	vector<int> b = { 1, 2, 3, 4, 5 }; 
	vector<int> c = { 2}; 
	vector<int> d = { -1, -2}; 
	vector<vector<int>> m; m.push_back(b); m.push_back(c); m.push_back(d); 
	ZigzagIterator5 a(b,c); 
	ZigzagIterator6 a2(m); 

	while (a.hasNext())
		cout << a.next() << endl; 

	cout << "======================\n"; 
	while (a2.hasNext())
		cout << a2.next() << endl; 

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

