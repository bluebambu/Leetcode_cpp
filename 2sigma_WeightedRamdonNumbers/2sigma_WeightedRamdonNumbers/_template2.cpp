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
#include <random>
#include <ctime>

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




class Solution2 {
public:
	vector<int> cumProb; 
	vector<string> items; 
	int sum; 

	Solution2(vector<pair<string, int>> data):sum(0){
		int start = 0; 
		for (int i = 0; i < data.size(); ++i){
			items.push_back(data[i].first); 
			start += data[i].second; 
			cumProb.push_back(start); 
		}
		sum = start; 
	}

	string weightedRandom(){
		int rnum = rand() % sum + 1;  // make the result between [1, sum]. So for example, first number correspond to [1,2,3,..,n]. 0 is not in range. 
		int left = 0, right = cumProb.size() - 1; // [a,b]. for some reason, [a,b) is not easy
		while (left < right){
			int mid = left + (right - left) / 2; 
			if (cumProb[mid] < rnum)
				left = mid + 1;
			else
				right = mid; 
		}
		return items[left]; 
	}
};


class Solution {
public:
	int sum; 
	map<int, string> tm; 

	Solution(vector<pair<string, int>> data) :sum(0){
		int cum = 0; 
		for (auto p : data){
			cum += p.second; 
			tm[cum] = p.first; 
		}
		sum = cum; 
	}

	string weightedRandom(){
		int rnum = rand() % sum + 1; 
		return (tm.lower_bound(rnum))->second; 
	}
}; 

int main(){
	srand(time(NULL)); 

	vector<pair<string, int>> a = { { "ab", 2 }, { "cd", 4 }, { "de", 6 } };
	Solution b(a); 

	unordered_map<string, int> m; 

	for (int i = 0; i < 100000; ++i){
		m[b.weightedRandom()] += 1; 
	}

	mapprt(m); 
	
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

