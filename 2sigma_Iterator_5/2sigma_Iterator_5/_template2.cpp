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




class RandomIterator {
public:
	int cnt;
	RandomIterator(){ cnt = 0;  }

	virtual ~RandomIterator() {}

	// return next value
	virtual int next(){
		++cnt; 
		return rand()%100; 
	}
	// check if there is next value
	virtual bool hasNext(){
		return cnt<1000000; 
	}
	virtual void remove(){}
};


class ModFiveIterator : public RandomIterator{
	bool flag;  // this flag is for the case when usr call hasNext() multiple times: iter.hasNext(); iter.hasNext();  so that you don't have to update the random number inside. 
	int res; 
public:
	// ctor is necessary!! cuz flag and res need to be initialized
	ModFiveIterator() :RandomIterator(), flag(false), res(0) {}

	bool hasNext(){
		if (!flag){
			res = RandomIterator::next(); 

			// do you want 0 as an answer? ask the interviewer! 
			while (RandomIterator::hasNext() && (res % 5))
				res = RandomIterator::next(); 
			flag = true; 
			return !(res%5); // for the case that RandomIterator is used up...
		}
		return true; 
	}

	int next(){
		hasNext(); 
		flag = false; 
		return res; 
	}
};


class ModFiveIterator2 : public RandomIterator{
public:
	int res; 
	bool hasRes; 

	ModFiveIterator2() :res(0), hasRes(false) {}

	bool hasNext(){
		if (RandomIterator::hasNext() == false)
			return false; 

		if (hasRes)
			return true; 

		while (RandomIterator::hasNext()){
			res = RandomIterator::next(); 
			if (res%5==0)
				break;
		}
		hasRes = (res % 5) ? false : true; 
		return hasRes; 
	}

	int next(){
		hasNext();
		hasRes = false; 
		return res; 
	}
};



int main(){
	srand(time(NULL)); 

	ModFiveIterator2 iter; 
	map<int, int> m; 

	for (int i = 0; i < 100000; ++i)
		if (iter.hasNext() )
			m[iter.next()] += 1;

	mapprt(m); 

	vector<int> b = { 4, 1, -9, 0, INT_MAX }; 


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

