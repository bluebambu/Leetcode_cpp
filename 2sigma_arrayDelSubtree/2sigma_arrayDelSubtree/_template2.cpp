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


struct node{
	int parent; 
	int value; 
	bool valid; 
	bool visited; 
	node(int x, int y) :parent(x), value(y), valid(true), visited(false) {}
};

bool checkDel(vector<node>& arr, int i, int& n);

void del(vector<node>& arr, int i, int& size){
	for (int j = 0; j < arr.size(); ++j){
		arr[j].visited = false; 
	}

	if (arr[i].valid == false){
		return; 
	}
	arr[i].valid = false; 
	arr[i].visited = true;
	--size; 

	for (int j = 0; j < arr.size(); ++j){
		if (arr[j].visited == false)
			checkDel(arr, j, size); 
	}
}


bool checkDel(vector<node>& arr, int i, int& size){
	if (arr[i].visited){
		return !arr[i].valid; 
	}
	if (arr[i].parent == -1){
		arr[i].visited = true; 
		return !arr[i].valid; 
	}
	if (arr[i].valid == false){
		arr[i].visited = true; 
		return true; 
	}

	int parent = arr[i].parent; 
	arr[i].visited = true; 
	if (checkDel(arr, parent, size)){
		arr[i].valid = false;
		--size;
		return true;
	}
	else
		return false;
}



class Solution2{
public:
	void delTree(vector<node>& arr, int& size){
		for (int i = 0; i < arr.size(); ++i){
			if (arr[i].visited == false){
				checkAndDel(arr, i, size); 
			}
		}
	}

	// true -> invalid, false -> valid
	bool checkAndDel(vector<node>& arr, int cur, int& size){
		if (cur == -1){
			return false; 
		}
		//if (arr[cur].valid == false){
		//	return true; 
		//}
		if (arr[cur].visited == true){
			return !arr[cur].valid; 
		}

		bool parentState = checkAndDel(arr, arr[cur].parent, size); 
		if (parentState == true){
			arr[cur].valid = false; 
			--size;
		}
		arr[cur].visited = true; 
		return !arr[cur].valid; 
	}
};

class Solution3{
public:
	void delTree(vector<node>& arr, int i, int& size){
		arr[i].valid = false; 
		size -= 1; 

		for (int j = 0; j < arr.size(); ++j){
			if (arr[j].visited == false)
				checkAndDel(arr, j, size); 
		}
	}

	// true - del, false - not del
	bool checkAndDel(vector<node>& arr, int cur, int& size){
		if (cur == -1)
			return false; 
		if (arr[cur].visited)
			return !arr[cur].valid; 
		if (arr[cur].valid == false){
			return true; 
		}

		bool parentState = checkAndDel(arr, arr[cur].parent, size); 
		if (parentState == true){
			arr[cur].valid = false; 
			--size; 
		}
		arr[cur].visited = true; 
		return !arr[cur].valid; 
	}
};




int main(){
	vector<node> arr; 
	arr.push_back(node(-1, 0)); 
	arr.push_back(node(5, 1)); 
	arr.push_back(node(0,  2)); 
	arr.push_back(node(2,  3)); 
	arr.push_back(node(1,  4)); 
	arr.push_back(node(7,  5)); 
	arr.push_back(node(3,  6)); 
	arr.push_back(node(-1,  7)); 

	// int n = arr.size(); 
	// del(arr, 0, n); 
	// for (auto i : arr){
	// 	cout << i.parent << " " << i.value << " " << i.valid << " " << i.visited << endl; 
	// }
	// cout << "size: " << n<<endl; 

	// 7 5 1 4, 0 2 3 6

	// arr[2].valid = false; 
	int size = arr.size(); 

	Solution3 sln; 
	sln.delTree(arr, 10, size); 

	for (auto i : arr){
		cout << i.parent << " " << i.value << " " << i.valid << " " << i.visited << endl; 
	}

	cout << "size: " << size <<endl; 

}

