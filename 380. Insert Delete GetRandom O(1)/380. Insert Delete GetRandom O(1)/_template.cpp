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
#include <unordered_set>
#include <set>
#include <map>
#include <utility>
#include <sstream>
#include <string>

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

template <typename T>
void vprt(vector<T> v){
	for (auto i : v)
		cout << v << " ";
	cout << endl; 
}

template <typename T>
void vvprt(vector<vector<T>> v){
	for (auto i : v){
		for (auto j : i){
			cout << j << " "; 
		}
		cout << endl;
	}
	cout << endl; 
}



// Design a data structure that supports all following operations in average O(1) time.

// insert(val) : Inserts an item val to the set if not already present.
// remove(val) : Removes an item val from the set if present.
// getRandom : Returns a random element from current set of elements.Each element must have the same probability of being returned.
// Example:
// // Init an empty set.
// RandomizedSet randomSet = new RandomizedSet();

// // Inserts 1 to the set. Returns true as 1 was inserted successfully.
// randomSet.insert(1);

// // Returns false as 2 does not exist in the set.
// randomSet.remove(2);

// // Inserts 2 to the set, returns true. Set now contains [1,2].
// randomSet.insert(2);

// // getRandom should return either 1 or 2 randomly.
// randomSet.getRandom();

// // Removes 1 from the set, returns true. Set now contains [2].
// randomSet.remove(1);

// // 2 was already in the set, so return false.
// randomSet.insert(2);

// // Since 2 is the only number in the set, getRandom always return 2.
// randomSet.getRandom();


// pass AC. Key point: vector + hashtable, remove-> swap elem with tail elem, then pop_back . 
class RandomizedSet {
public:

	unordered_map<int, int> um; 
	vector<int> vec; 

	/** Initialize your data structure here. */
	RandomizedSet() {

	}

	/** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
	bool insert(int val) {
		if (um.count(val)){
			return false; 
		}

		int v_sz = vec.size(); 
		vec.push_back(val); 
		um[val] = v_sz; 
		return true; 
	}

	/** Removes a value from the set. Returns true if the set contained the specified element. */
	bool remove(int val) {
		if (um.count(val) == 0){
			return false;
		}

		int orig_idx = um[val], v_sz = vec.size(), tail_val = vec[v_sz - 1];
		vec[orig_idx] = tail_val; 

		vec.pop_back(); 
		um[tail_val] = orig_idx; 
		um.erase(val); 													
		return true; 
	}

	/** Get a random element from the set. */
	int getRandom() {
		int randID = rand() % (vec.size()); 
		return vec[randID]; 
	}
};


class RandomizedSet2 {
public:
	vector<int> vec; 
	unordered_map<int, int> hash; 

	RandomizedSet2() {

	}

	bool insert(int val) {
		if (hash.count(val)){
			return false; 
		}
		vec.push_back(val); 
		hash[val] = vec.size() - 1; 
		return true; 
	}

	bool remove(int val) {
		if (hash.count(val) == 0){
			return false; 
		}
		int pos = hash[val]; 
		swap(vec[pos], vec[vec.size() - 1]); 
		hash[vec[pos]] = pos;
		vec.pop_back(); 
		hash.erase(val); 
		return true; 
	}

	int getRandom() {
		int r = rand() % vec.size(); 
		return vec[r]; 
	}
};


int main()
{
	RandomizedSet a;

	//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
	3       8
	1    4   7    9
	*/

	a.insert(1); 
	a.remove(1);
	a.insert(-1);
	a.remove(1);
	cout << a.getRandom();
	cout << a.getRandom();
	cout << a.getRandom();


}

