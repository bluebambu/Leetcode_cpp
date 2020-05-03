// _template.cpp : Defines the entry point for the console application.
//
#include <stdafx.h>

#include <functional>
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
class MedianFinder {
public:
	priority_queue<int, vector<int>, greater<int>> minheap; 
	priority_queue<int, vector<int>, less<int>> maxheap; 
	int n; 

	/** initialize your data structure here. */
	MedianFinder():n(0) {

	}

	void addNum(int num) {
		minheap.push(num); 
		maxheap.push(minheap.top()); 
		minheap.pop(); 
		if (maxheap.size() > minheap.size() + 1){
			minheap.push(maxheap.top()); 
			maxheap.pop(); 
		}
		++n; 
	}

	double findMedian() {
		if (n == 0)
			return 0; 
		
		return (n % 2) ? maxheap.top() : ((maxheap.top() + minheap.top()) / 2.0);
	}
};

/**
* Your MedianFinder object will be instantiated and called as such:
* MedianFinder obj = new MedianFinder();
* obj.addNum(num);
* double param_2 = obj.findMedian();
*/

// not find median, but find the 1/5 element. 
class MedianFinder_extend {
public:
	priority_queue<double, vector<double>, greater<double>> minheap; 
	priority_queue<double, vector<double>, less<double>> maxheap; 

	double ratio;
	int n; 
	/** initialize your data structure here. */
	MedianFinder_extend(double x):ratio(x), n(0) {
		
	}

	void addNum(double num) {
		minheap.push(num); 
		maxheap.push(minheap.top()); 
		minheap.pop(); 
		if (minheap.size() < ratio*(maxheap.size() + minheap.size())){
			minheap.push(maxheap.top()); 
			maxheap.pop(); 
		}
		++n; 
	}

	double findMedian() {
		if (n == 0)
			return 0;
		return minheap.top();
	}
};


int main(){ 
	MedianFinder_extend a(0.7); 

	a.addNum(-1);
	a.addNum(-2); 
	a.addNum(-3); 
	a.addNum(-4); 
	a.addNum(-5); 
	a.addNum(-6);
	a.addNum(-7); 
	a.addNum(-8); 
	a.addNum(-9); 
	a.addNum(-10); 
	cout << a.findMedian(); 


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

