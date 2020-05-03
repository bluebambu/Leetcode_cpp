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
	double minmaxGasDist(vector<int>& stations, int K) {
		double left = 0, right = maxRange(stations); 
		while ( fabs(right - left) > 0.000001 ){
			double mid = left + (right - left) / 2; 
			cout << left << " <> " << right << " <> " << mid << endl; 
			if (sep(stations, mid) > K)
				left = mid;
			else
				right = mid; 
		}
		return left; 
	}

	double maxRange(vector<int>& v){
		double r = 0;
		for (int i = 1; i < v.size(); ++i){
			r = max(double(v[i]-v[i-1]), r); 
		}
		return r; 
	}

	int sep(vector<int>& v, double range){
		int n = 0; 
		for (int i = 1; i < v.size(); ++i){
			double gap = v[i] - v[i - 1]; 
			n += int(gap / range ) ;
			cout << '\t' << gap << " <> " << int(gap / range)  << endl; 
		}
		return n; 
	}
};


class Solution2 {
public:
	double minmaxGasDist(vector<int>& stations, int K) {
		double delta = 1e-6; 
		double left = 0, right = max(stations); 
		while (left + delta < right){
			double mid = left + (right - left) / 2.0;
			if (try(stations, mid)<=K)
				right = mid;
			else
				left = mid; 
		}
		return right; 
	}

	int try(vector<int>& sts, double gap){
		int cnt = 0; 
		for (int i = 0; i < sts.size(); ++i){
			cnt += double(sts) / gap; 
		}
		return cnt; 
	}
}; 


int main(){
	Solution a; 

	vector<int> stations = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }; 
	vector<int> stations2 = { 23, 24, 36, 39, 46, 56, 57, 65, 84, 98 }; 
	int K = 9; 

	cout << a.minmaxGasDist(stations2, 1) << endl; 


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

