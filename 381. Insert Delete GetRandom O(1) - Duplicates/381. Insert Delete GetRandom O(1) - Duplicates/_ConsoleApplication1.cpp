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

// wrong
class RandomizedCollection2 {
public:
	RandomizedCollection2() { } 
	vector<vector<int>> vec; 
	unordered_map<int, int> hash; 
	bool insert(int val) {
		if (hash.count(val)){
			int pos = hash[val]; 
			vec[pos][1] += 1; 
			return true; 
		}

		vec.push_back({val, 1});
		hash[val] = vec.size() - 1; 
		return true; 
	}

	bool remove(int val) {
		if (hash.count(val) == 0){
			return false; 
		}
		int pos = hash[val]; 
		vec[pos][1] -= 1; 
		if (vec[pos][1] == 0){
			swap(vec[pos], vec[vec.size() - 1]); 
			hash[vec[pos][0]] = pos; 
			vec.pop_back(); 
			hash.erase(val); 
		}
		return true; 
	}

	int getRandom() {
		return 1; 
	}
};


// wrong
class RandomizedCollection3 {
public:
	RandomizedCollection3(){}
	unordered_map<int, vector<int>> hash; 
	vector<int> vec; 
	bool insert(int val) {
		vec.push_back(val); 
		hash[val].push_back(vec.size() - 1); 
		return true; 
	}

	bool remove(int val) {
		if (hash.count(val) == 0)
			return false; 
		int pos = hash[val].back(); 
		int replace = vec.back(); 
		if (replace == val){
			hash[val].pop_back();
			vec.pop_back();
			if (hash[val].empty())
				hash.erase(val);
			return true; 
		}
		swap(vec[pos], vec[vec.size() - 1]); 
		hash[val].pop_back();
		vec.pop_back();
		hash[replace].pop_back(); 
		hash[replace].push_back(pos); 
		return true; 
	}

	int getRandom(){
		return vec[rand() % vec.size()]; 
	}
};


// pass 73%
class RandomizedCollection {
public:
	vector<int> v;
	unordered_map<int, unordered_set<int>> m;
	RandomizedCollection(){}

	bool insert(int val) {
		v.push_back(val);
		m[val].insert(v.size() - 1);
		return true;
	}

	bool remove(int val) {
		if (m.count(val) == 0)
			return false;
		int pos = *m[val].begin();
		if (pos == v.size() - 1){
			m[val].erase(m[val].begin());
			v.pop_back(); 
			if (m[val].empty())
				m.erase(val);
			return true; 
		}
		m[val].erase(m[val].begin());
		if (m[val].empty())
			m.erase(val);
		int o_val = v.back(), o_pos = v.size() - 1;
		v[pos] = o_val;
		v.pop_back();
		if (m.count(o_val)){
			m[o_val].erase(o_pos);
			m[o_val].insert(pos);
		}
		return true;
	}

	int getRandom(){
		return v[rand() % v.size()];
	}
};


int main(){
	RandomizedCollection a;

	cout<<a.insert(0);
	cout<<a.remove(0); 
	cout<<a.insert(-1);
	cout<<a.remove(0);


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

