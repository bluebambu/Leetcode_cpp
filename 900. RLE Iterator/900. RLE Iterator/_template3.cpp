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


// 4/9 tests passed
class RLEIterator {
public:
	int curId, rem; 
	vector<int> core; 
    RLEIterator(vector<int> A) {
		core = A; 
		curId = 1; 
		rem = A[0]; 
    }
    
    int next(int n) {
		while (n > 0){
			while (rem == 0){
				curId += 2; 
				if (curId < core.size())
					rem = core[curId - 1]; 
				else 
					break;
			}
			--n; 
			--rem; 
		}
        
		if (curId >= core.size())
			return -1; 

		return core[curId]; 
    }
};

// pass
class RLEIterator2 {
public:
	int curId, rem;
	vector<int> core;
	RLEIterator2(vector<int> A) {
		core = A;
		curId = 1;
		rem = A[0];
	}

	int next(int n) {
		if (n <= rem){
			rem -= n; 
			return core[curId]; 
		}
		else{
			n -= rem; 
			curId += 2; 
			if (curId < core.size())
				rem = core[curId - 1];
			else{
				rem = 0; 
				return -1; 
			}

			return next(n);
		}
	}
}; 


int main(){
	vector<int> b = { 3, 8, 0, 9, 2, 5 }; 

	RLEIterator2 a(b); 

	cout << a.next(2) << endl; 
	cout << a.next(1) << endl; 
	cout << a.next(1) << endl; 
	cout << a.next(2) << endl; 


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

