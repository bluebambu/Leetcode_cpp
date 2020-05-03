// _template.cpp : Defines the entry point for the console application.
//
#include <stdafx.h>

#include <iostream>
#include <cassert>
#include <functional>
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
#include <ctime>
#include <random>

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
// 第二题是设计一个stack，除了实现普通stack的push和pop之外，还有max，min，most frequent number，average，和median。
// average很简单，记录sum就行。min和max就是按照leetcode原题来做。most frenquent number我是按照leetcode上least frequent 
// used cache那道题的方法做的，用一个list来记录所有数，list上的每个节点记录一个frequency和所有这个frequency的数字。再用一
// 个map来快速找到数字在list上的位置。medium我觉得最复杂，因为数字是有可能被pop的。做法有点像leetcode上的sliding window median。
// 除了用两个heap来记录所有数字，还需要记录哪些数字被删除了。每次删除一个数字，不需要立马从heap里去删除，而是记录下来，
// 当这个数字出现在heap顶端的时候，我们再删除。最后因为时间不够了，所以没有具体说删除的做法。



class SuperStack {
	stack<int> stk; 
	stack<int> minStk; 
	stack<int> maxStk; 
	int sum; 

	//get mode
	unordered_map<int, int> kf; 
	unordered_map<int, list<int>> fkl;
	unordered_map<int, list<int>::iterator> kit; 
	int maxFreq; 
	stack<int> maxFrStk; 

	//get median
	multiset<int, greater<int>> right; // greater<int> is [5,4,3,2,1] 
	multiset<int, less<int>> left; // less<int> is [1,2,3,4,5]

public:
	SuperStack() :maxFreq(0){}

	void push(int i){
		stk.push(i); 
		
		if (minStk.empty() || minStk.top() > i)
			minStk.push(i);
		else
			minStk.push(minStk.top());

		if (maxStk.empty() || maxStk.top() < i)
			maxStk.push(i);
		else
			maxStk.push(maxStk.top());

		pushForMode(i); 
		pushForMedian(i); 
	}

	void prnt(){
		stack<int> cp = stk; 
		unordered_map<int, int> cnt; 
		cout << "orig stack: "; 
		while (cp.size()){
			cout << cp.top() << " "; 
			cnt[cp.top()] += 1; 
			cp.pop(); 
		}
		cout << endl;
		cout << endl; 
		mapprt(cnt); 

		cout << "right: ";
		prt1Layer(right); 
		cout << "left: ";
		prt1Layer(left); 

	}

	void pop(){
		if (stk.size() >= 1){
			popForMode();
			popForMedian(); 
			stk.pop();
		}
	}

	void pushForMedian(int i){
		right.insert(i); 
		left.insert(*(right.begin())); 
		right.erase(right.begin()); 
		if (left.size() > right.size()){
			right.insert(*(left.begin())); 
			left.erase(left.begin()); 
		}
	}

	void popForMedian(){
		int toPop = stk.top(); 
		if (left.count(toPop)){
			left.erase(left.find(toPop)); 
			if (right.size() > left.size() + 1){
				left.insert(*(right.begin())); 
				right.erase(right.begin()); 
			}
		}
		else{
			// this is wrong! erase will erase ALL toPop elements!!
			right.erase(right.find(toPop)); 
			if (left.size() > right.size()){
				right.insert(*(left.begin())); 
				left.erase(left.begin()); 
			}
		}
	}

	double getMedian(){
		return (stk.size() % 2) ? (*(right.begin())) : ((*(right.begin()) + *(left.begin())) / 2.0); 
	}

	void pushForMode(int i){
		if (kf.count(i) == 0){
			kf[i] = 1;
			fkl[1].push_back(i);
			kit[i] = --fkl[1].end(); 
			if (maxFreq < 1)
				maxFreq = kf[i]; 
			maxFrStk.push(fkl[maxFreq].back()); 
			return; 
		}

		fkl[kf[i]].erase(kit[i]); 
		kf[i] += 1; 
		fkl[kf[i]].push_back(i); 
		kit[i] = --(fkl[kf[i]].end()); 
		if (maxFreq < kf[i])
			maxFreq = kf[i]; 
		maxFrStk.push(fkl[maxFreq].back()); 
	}


	void popForMode(){
		int key = stk.top(); 
		fkl[kf[key]].erase(kit[key]); 
		kf[key] -= 1; 
		fkl[kf[key]].push_back(key); 
		kit[key] = --(fkl[kf[key]].end()); 

		maxFrStk.pop(); 
		maxFreq = kf[maxFrStk.top()];
	}

	int getMode(){ 
		return maxFrStk.top(); 
	}

	double realMedian(){
		stack<int> cp = stk; 
		vector<int> scores; 
		while (cp.size()){
			scores.push_back(cp.top()); 
			cp.pop(); 
		}
		double median;
		size_t size = scores.size();

		sort(scores.begin(), scores.end());

		if (size % 2 == 0)
		{
			median = (scores[size / 2 - 1] + scores[size / 2]) / 2.0;
		}
		else
		{
			median = scores[size / 2];
		}

		return median;
	}

};

template<typename T>
class SuperStack2{
public:
	vector<T> origStk, minStk, maxStk; 
	T sum; 

	// mode
	unordered_map<T, int> kf; 
	unordered_map<int, list<T>> fks; 
	unordered_map<T, typename list<T>::iterator> kit; 
	vector<T> modeStk; 

	// median
	multiset<T, less<T>> left, right; 

	void push(T i){
		if (minStk.empty() || minStk.back() > i)
			minStk.push_back(i);
		else
			minStk.push_back(minStk.back()); 

		if (maxStk.empty() || maxStk.back() < i)
			maxStk.push_back(i);
		else
			maxStk.push_back(maxStk.back()); 
		
		// avg
		sum += i; 

		// mode
		if (kf.count(i))
			fks[kf[i]].erase(kit[i]); 
		kf[i] += 1; 
		fks[kf[i]].push_back(i); 
		kit[i] = --fks[kf[i]].end(); 
		if (modeStk.empty() || modeStk.back() < kf[i])
			modeStk.push_back(i);
		else
			modeStk.push_back(modeStk.back()); 

		// median
		left.insert(i); 
		right.insert(*(--left.end())); 
		left.erase(--left.end()); 
		if (right.size() > left.size()){
			left.insert(*(right.begin())); 
			right.erase(right.begin()); 
		}

		// orig
		origStk.push_back(i); 
	}

	void pop(){
		if (!origStk.empty()){
			//min max
			minStk.pop_back();
			maxStk.pop_back();

			//avg
			sum -= origStk.back();

			//mode
			int toPop = origStk.back();
			fks[kf[toPop]].erase(kit[toPop]);
			kf[toPop] -= 1;
			fks[kf[toPop]].push_back(toPop);
			kit[toPop] = --fks[kf[toPop]].end();
			modeStk.pop_back();

			//median
			if (left.count(toPop)){
				left.erase(left.find(toPop));
				if (left.size() < right.size()){
					left.insert(*(right.begin()));
					right.erase(right.begin());
				}
			}
			else{
				right.erase(right.find(toPop));
				if (right.size() < left.size() - 1){
					right.insert(*(--left.end()));
					left.erase(--left.end());
				}
			}

			//orig
			origStk.pop_back(); 
		}
	}

	T getMin(){ return minStk.back(); }
	T getMax(){ return maxStk.back(); }
	T getAvg(){ return sum / origStk.size();  }
	T getMode(){ return modeStk.back();  }
	T getMedian(){
		if (origStk.size() % 2){
			return *(--left.end()); 
		}
		else{
			return (*(--left.end()) + *(right.begin())) / 2.0; 
		}
	}

	T realMode(){
		unordered_map<T, int> cnt; 
		int m = 0;
		T n; 
		for (int i = 0; i < origStk.size(); ++i){
			cnt[origStk[i]] += 1; 
			if (m < cnt[origStk[i]]){
				m = cnt[origStk[i]];
				n = origStk[i];
			}
		}
		return n; 
	}

	void prnt(){
		prt1Layer(origStk); 
	}
};






int main(){
	srand(time(NULL)); 

	SuperStack2<double> s; 
	for (int i = 0; i < 100; ++i){
		int j = rand()%30; 
		s.push(j); 
		cout << j << endl; 
		cout << "print: "; 
		s.prnt(); 
		cout << "min: "<<s.getMin() << endl; 
		cout << "max: "<<s.getMax() << endl; 
		cout << "avg: "<<s.getAvg() << endl; 
		cout << "mode: "<<s.getMode() << endl; 
		cout << "median " << s.getMedian() << endl; 
		cout << "real mode " << s.realMode() << endl; 

		//assert(s.getMedian() == s.realMedian()); 

		if (rand()%2)
			s.pop();

		cout << "================\n\n"; 

	}


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

