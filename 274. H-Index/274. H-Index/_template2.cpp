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

class Solution {
public:
	int hIndex(vector<int>& citations) {
		if (citations.empty())
			return 0; 

		sort(citations.begin(), citations.end(), greater<int>()); 

		for (int i = 0; i < citations.size(); ++i){
			if (i+1 > citations[i])
				return i; 
		}
	}
};


class Solution2{
public:
	int hIndex(vector<int> citations){
		int n = citations.size(); 
		if (n == 0)
			return 0; 
		vector<int> citMap(n + 1, 0); 

		for (auto i : citations){
			if (i >= n)
				citMap[n] += 1;
			else
				citMap[i] += 1; 
		}

		int cites = 0; 
		for (int i = n; i >= 0; --i){
			cites += citMap[i]; 
			if (cites >= i)
				return i; 
		}
	}
};


class Solution3{
public:
	int hIndex(vector<int> citations){
		sort(citations.rbegin(), citations.rend()); 
		for (int i = 1; i <= citations.size(); ++i){
			if (i > citations[i-1])
				return i-1 ; 
		}

		return citations.size(); 
	}
}; 

// passed
class Solution4{
public:
	int hIndex(vector<int>& citations){
		int n = citations.size(); 
		vector<int> m(n + 1, 0); 
		for (auto c : citations){
			if (c >= n)
				m[n] += 1;
			else
				m[c] += 1; 
		}

		int cntsum = 0;
		for (int cite=n; cite>=0; --cite){
			cntsum += m[cite]; 
			if (cntsum >= cite)
				return cite; 
		}

		return -1; 
	}
};

// pass
class Solution5 {
public:
	int hIndex(vector<int>& citations){
		int n = citations.size(); 
		vector<int> cit_paper(n + 1, 0); 
		for (auto& c : citations){
			if (c >= n)
				cit_paper[n] += 1;
			else
				cit_paper[c] += 1; 
		}

		int h = 0, res=0; 
		for (int i = cit_paper.size() - 1; i > 0; --i){
			h += cit_paper[i]; 
			if (h >= i){
				res = i; // shall not be  res=h;  
				break;
			}
		}
		return res; 
	}
};


int main(){
	Solution2 a; 
	Solution5 a2; 

	vector<int> b = { 3, 0, 6, 1, 5 }; 
	vector<int> c = { 0, 0, 4, 4}; 

	cout << a.hIndex(c) << endl; 
	cout << a2.hIndex(c) << endl; 


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

