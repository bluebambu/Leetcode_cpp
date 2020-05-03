// _template4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <assert.h>
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


class AllOne {
public:
	struct Bucket{ int val; unordered_set<string> keys; };
	list<Bucket> cntsList; 
	unordered_map<string, list<Bucket>::iterator> key_iter; 

	AllOne() {
		
	}

	/** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
	void inc(string key) {
		if (key_iter.count(key) == 0){
			if (cntsList.empty() || cntsList.begin()->val != 1)
				cntsList.insert(cntsList.begin(), { 1, {} }); 
			cntsList.begin()->keys.insert(key); 
			key_iter[key] = cntsList.begin(); 
		}
		else{
			int oldcnt = key_iter[key]->val; 
			auto nxt = next(key_iter[key]), cur = key_iter[key]; 
			if (nxt==cntsList.end() || nxt->val != oldcnt + 1)
				cntsList.insert(nxt, { oldcnt + 1, {} }); 
			next(cur)->keys.insert(key); 
			key_iter[key] = next(cur); 
			cur->keys.erase(key); 
			if (cur->keys.empty())
				cntsList.erase(cur); 
		}
	}

	/** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
	void dec(string key) {
		if (key_iter.count(key) == 0) return; 
		int oldcnt = key_iter[key]->val; 
		auto cur = key_iter[key], pre=cur; 
		if (oldcnt == 1){
			cur->keys.erase(key); 
			if (cur->keys.empty()){
				cntsList.erase(cur);
			}
			key_iter.erase(key);
		}
		else{
			if (cur == cntsList.begin() || prev(cur)->val != oldcnt - 1)
				cntsList.insert(cur, { oldcnt - 1, {} }); 
			pre = prev(cur); 
			pre->keys.insert(key); 
			key_iter[key] = pre; 
			cur->keys.erase(key); 
			if (cur->keys.empty())
				cntsList.erase(cur); 
		}
	}

	/** Returns one of the keys with maximal value. */
	string getMaxKey() {
		if (cntsList.empty())
			return "";
		return *(prev(cntsList.end())->keys.begin()); 
	}

	/** Returns one of the keys with Minimal value. */
	string getMinKey() {
		if (cntsList.empty())
			return "";
		return *(cntsList.begin()->keys.begin()); 
	}
};


int main(){
	AllOne a; 
	a.inc("abc"); 
	a.inc("abc"); 
	a.inc("abc"); 
	a.inc("def"); 
	a.inc("abc"); 
	a.inc("def"); 
	a.dec("abc"); 

	assert(a.getMaxKey() == "abc"); 
	assert(a.getMinKey() == "def"); 



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

