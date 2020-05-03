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
#include <functional>

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

// cannot pass test
class MaxStack {
public:
    /** initialize your data structure here. */
	stack<int> data, maxstk; 
	unordered_map<int, vector<int>> val_status; 
    MaxStack() {
		
    }
    
    void push(int x) {
		if (data.empty()){
			data.push(x); 
			maxstk.push(x); 
			val_status[x].push_back(1); 
		}
		else{
			data.push(x); 
			if (maxstk.empty())
				maxstk.push(x); 
			else
				maxstk.push(max(maxstk.top(), x));
			val_status[x].push_back(1); 
		}
    }
    
    int pop() {
		int top = data.top(); 
		data.pop(); 
		maxstk.pop(); 
		while (!val_status[top].empty() && val_status[top].back() == 0)
			val_status[top].pop_back(); 
		val_status[top].pop_back(); 
		return top;
    }
    
    int top() {
		return data.top(); 
    }
    
    int peekMax() {
		return maxstk.top(); 
    }
    
    int popMax() {
		int top = maxstk.top(); 
		if (data.top() == top){
			data.pop(); 
			maxstk.pop(); 
			while (!val_status[top].empty() && val_status[top].back() == 0)
				val_status[top].pop_back();
			val_status[top].pop_back();
		}
		else{
			for (int i = val_status[top].size() - 1; i >= 0; --i){
				if (val_status[top][i] == 1){
					val_status[top][i] = 0; 
					break;
				}
			}
			maxstk.pop(); 
		}
		return top; 
    }
};


// pass
class MaxStack2 {
public:
	stack<int> data, maxstk; 
    MaxStack2() { }
    
    void push(int x) {
		data.push(x); 
		if (maxstk.empty() || maxstk.top() <= x)
			maxstk.push(x); 
    }
    
    int pop() {
		int top = data.top(); 
		if (top == maxstk.top())
			maxstk.pop(); 
		data.pop(); 
		return top; 
    }
    
    int top() {
		return data.top(); 
    }
    
    int peekMax() {
		return maxstk.top(); 
    }
    
    int popMax() {
		stack<int> helper; 
		while (!data.empty() && data.top() < maxstk.top()){
			helper.push(data.top()); 
			data.pop(); 
		}
		int maxtop = maxstk.top(); 
		data.pop(); 
		maxstk.pop(); 
		while (!helper.empty()){
			push(helper.top()); 
			helper.pop(); 
		}
		return maxtop; 
    }
};


class MaxStack3 {
public:
	list<int> stk; 
	map<int, vector<list<int>::iterator>, std::greater<int>> val_2_iter; 

    MaxStack3(){}
    
    void push(int x) {
		stk.push_back(x); 
		val_2_iter[x].push_back(prev(stk.end())); 
    }
    
    int pop() {
		int top = stk.back(); 
		val_2_iter[top].pop_back(); 
		stk.pop_back(); 
		if (val_2_iter[top].empty())
			val_2_iter.erase(top); 
		return top; 
    }
    
    int top() {
		return stk.back(); 
    }
    
    int peekMax() {
		return  val_2_iter.begin()->first; 
    }
    
    int popMax() {
		list<int>::iterator iter = *prev((val_2_iter.begin()->second).end());
		int r = (*iter); 
		stk.erase(iter); 
		val_2_iter.begin()->second.pop_back(); 
		if (val_2_iter.begin()->second.empty())
			val_2_iter.erase(val_2_iter.begin()); 
		return r; 
    }
};

class MaxStack4 {
public:
	MaxStack3(){}
	list<int> stk; 
	map<int,vector<list<int>::iterator>> sorted; 
	void push(int x) {
		stk.push_back(x); 
		sorted[x].push_back(prev(stk.end())); 
	}

	int pop(){
		int tail = stk.back(); 
		stk.pop_back(); 
		sorted[tail].pop_back(); 
		if (sorted[tail].empty())
			sorted.erase(tail); 
	}

	int popMax(){
		int maxv = prev(sorted.end())->first; 
		auto iter = prev(sorted.end())->second.back(); 
		stk.erase(iter); 
		prev(sorted.end())->second.pop_back();
		if (sorted[maxv].empty())
			sorted.erase(maxv); 
		return maxv; 
	}
};


int main(){
	MaxStack3 a; 

	a.push(-2); 
	a.popMax(); 
	a.push(-45);
	a.push(-82);
	a.push(29);
	a.pop();
	a.peekMax();
	a.push(40);
	a.pop();
	a.pop();
	a.push(66); 
	a.peekMax(); 
	a.peekMax(); 
	a.push(-61); 
	a.peekMax(); 
	a.push(98); 
	a.peekMax(); 


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

