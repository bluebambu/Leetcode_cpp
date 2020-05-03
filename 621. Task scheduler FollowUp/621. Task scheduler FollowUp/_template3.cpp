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
 
//task scheduler一个经典的followup就是 如果tasks很多很多  但是cooldown time很小 如何优化空间复杂度到 O(cooldown time)注意这里顺序是不能变的（就是说如果cooldown内有重复 的元素，就只添加 '_' 来消除重复。 就是一个sliding window ).
//刚才有美国同学面了phone说面试官问这个followup他没答上来!!后来我想了想发现。。我也不会lul 搜了下地里没看到靠谱的代码啊
//请教！ 面试官给的提示是用queue


class Solution {
public:
	string task(string t, int n){
		queue<char> q; 
		unordered_set<char> v; 

		string res; 
		for (int i = 0; i < t.size(); ++i){
			char c = t[i]; 
			if (q.size() == n+1){
				char f = q.front(); 
				q.pop(); 
				if (f != '*')
					v.erase(f); 
			}

			if (v.count(c)){
				res.push_back('*'); 
				q.push('*'); 
				--i; 
			}
			else{
				res.push_back(c); 
				q.push(c);
				v.insert(c); 
			}
		}

		return res; 
	}
};



int main(){
	Solution a;

	vector<int> b = { 4, 1, -9, 0, INT_MAX };

	cout << a.task("AADBSDABBDS", 7) << endl; 


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

