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
#include <string> 
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


class MergeSort{
public:
	vector<int> aux; 

	void sort(vector<int>& vec){
		for (int sz = 1; sz < vec.size(); sz *= 2){
			for (int j = 0; j + sz < vec.size(); j += 2 * sz){
				merge(vec, j, j + sz, min(j + 2 * sz, vec.size())); 
			}
		}
	}

	// merge 函数直接利用辅助数组， 接受 start, mid, end 三个index，并且直接操作 vec&， 效率很高。
	void merge(vector<int>& vec, int start, int mid, int end){
		aux = vec; 

		int i = start, j = mid; 
		for (int k = start; k < end; ++k){
			if (i >= mid){
				vec[k] = aux[j++];		
			}
			else if (j >= end){
				vec[k] = aux[i++];
			}
			else if (aux[i] > aux[j]){
				vec[k] = aux[j++];
			}
			else{
				vec[k] = aux[i++]; 
			}
		}
	}
	
};

int main()
{
	MergeSort a; 

	vector<int> b = { 5, 7, 2, 9, 1, 99 }; 

	a.sort(b); 

	for (auto i : b)
		cout << i << " "; 



}

