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


// pass
typedef pair<vector<int>::iterator, vector<int>::iterator> PII; 
typedef pair<vector<vector<int>>::iterator, vector<vector<int>>::iterator> PVIVI; 

class Vector2D {
public:
	PVIVI vecP; 
	PII elemP; 

	Vector2D(vector<vector<int>>& vec2d) {
			vecP = { vec2d.begin(), vec2d.end() };
			if (vecP.first != vecP.second)
				elemP = { vecP.first->begin(), vecP.first->end() };
	}

	int next() {
		if (hasNext()){
			int res = *(elemP.first);
			++elemP.first;
			return res;
		}
		else
			throw runtime_error(" "); 
	}

	bool hasNext() {
		while (vecP.first != vecP.second && elemP.first == elemP.second){
			vecP.first = vecP.first + 1; 
			if (vecP.first==vecP.second)
				break;
			elemP.first = vecP.first->begin(); 
			elemP.second = vecP.first->end(); 
		}
		return vecP.first != vecP.second; 
	}
};

/**
* Your Vector2D object will be instantiated and called as such:
* Vector2D i(vec2d);
* while (i.hasNext()) cout << i.next();
*/
// pass
class Vector2D2 {
public:
	int x, y; 
	vector<vector<int>>* pv2d; 

	Vector2D2(vector<vector<int>>& vec2d) {
		pv2d = &vec2d; 
		x = 0, y = 0; 
	}

	int next() {
		if (hasNext()){
			return (*pv2d)[x][y++]; 
		}
		else
			throw runtime_error("err"); 
	}

	bool hasNext(){
		while (x < pv2d->size() && y >= (*pv2d)[x].size()){
			++x; 
			y = 0; 
		}
		return x < pv2d->size(); 
	}
}; 

class Vector2D3 {
public:
	Vector2D3(vector<vector<int>>& vec2d) {
	}
}; 

int main(){

	vector<int> b = { 4, 1, -9, 0}; 
	vector<int> c = { 1,2}; 
	vector<int> d = { }; 
	vector<int> e = { 5,6,7,8,9}; 

	vector<vector<int>> f = {d};

	Vector2D a(f);

	while (a.hasNext())
		cout << a.next() << endl; 

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

