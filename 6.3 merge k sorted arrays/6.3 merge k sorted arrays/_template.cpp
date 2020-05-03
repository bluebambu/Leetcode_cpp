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


// amz audible 面试题， 与linkedlist稍微有点不同。 heap中存 iterator， 在不知道iterator属于哪个array的情况下， 
// 判断iterator到末尾的条件我不会写。 这是我找到的 stackoverflow的答案



// Use the std::vector::front and std::vector::back to get a reference to the data in the first and last positions.
// 
// Reference is a keyword here because you could efficiently check the address of your iterating item and the address of the respective front / back references.
// In your example you take the item by value not reference so this prehaps wouldn't work, take in consideration this example that'd work with this method:
// 
// for (auto& item : myVector) // take item by reference
// {
// 	std::cout << item;
// 	if (&item == &myVector.back())
// 		std::cout << "(last element) " << std::endl;
// 	else if (&item == &myVector.front())
// 		std::cout << "(first element)" << std::endl;
// }
// 
// If the object overloads the address of operator & (though it's considered a bad practice) you might want to use std::addressof instead.
// 
// 	This method won't work however for the std::vector<bool> specialization since it optimizes the vector to store booleans efficiently with bits, and
// since we cannot have references to bits, all references taken out this data structure is a proxy object not exactly tied to the address of the internal data.

class Solution {
public:
	vector<int> kmerge(vector<vector<int>> vecs){
		for (auto& v : vecs)
			sort(v.begin(), v.end()); 

		typedef vector<int*> vpp; 

		struct comp{
			bool operator()(const vpp& a, const vpp& b){
				return *(a[0]) > *(b[0]);
			}
		};

		priority_queue<vpp, vector<vpp>, comp> pq; 

		for (int i = 0; i < vecs.size(); ++i){
			pq.push({ &vecs[i][0], &(vecs[i][vecs[i].size()-1]) }); 
		}

		vector<int> res; 

		while (!pq.empty()){
			vpp f = pq.top(); 
			pq.pop(); 
			int *curp = f[0], *end = f[1]; 
			res.push_back(*curp); 

			if (curp + 1 != end)
				pq.push({ curp + 1, end }); 
		}

		return res; 
	}
};


class Solution2 {
public:
	vector<int> kmerge(vector<vector<int>> vecs){
		for (auto& v : vecs)
			sort(v.begin(), v.end()); 

		typedef vector<int> VI; 
		auto comp = [=](VI& a, VI& b){
			return vecs[a[0]][a[1]] > vecs[b[0]][b[1]];
		}; 
		
		priority_queue<VI, vector<VI>, decltype(comp)> pq(comp); 

		for (int i = 0; i < vecs.size(); ++i){
			if (vecs[i].size() > 0)
				pq.push({ i, 0 });
		}

		vector<int> res; 
		while (!pq.empty()){
			VI f = pq.top(); 
			pq.pop(); 

			int id = f[0], iid = f[1]; 
			res.push_back(vecs[id][iid]); 
			if (iid + 1 < vecs[id].size())
				pq.push({ id, iid + 1 }); 
		}

		return res; 
	}
};


int main() {
	Solution2 a;

	vector<vector<int>> data = {
		{1,3,4,6,8}, 
		{2,3,4,8,9}, 
		{7,8,9,10}
	};

	auto c = a.kmerge(data); 

	for (auto i : c)
		cout << i << " "; 
	cout << endl; 

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






