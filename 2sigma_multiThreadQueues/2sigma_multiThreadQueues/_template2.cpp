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
#include <thread>
#include <mutex>

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
mutex mu;

stringstream s1("1 5 10"), s2("2 6 11"), s3("3 7 12");

const double dist = 6; 

vector<pair<int, int>> res; 

void process(list<double>& q1, list<double>& q2, int value, vector<pair<int, int>>& res){
	for (double it : q2){
		if (abs(it - value) <= dist){
			res.push_back({ it, value });
		} else if (it - value > dist)  
			// for >2 threads, here you can not break when  it - value < -1*dist, 
			// because you might have very small numbers remaining in the queue
			break;
	}
}

void dropAbd(vector<list<double>>& pool, int id){
	cout << "dropAbd No: " << id << endl; 
	while (!pool[id].empty()){
		cout << "pool[id] size: " << pool[id].size() << endl; 
		bool flag = false; 
		
		for (int i = 0; i < pool.size(); ++i){
			if (i != id){
				if (pool[i].empty() || abs(pool[i].back() - pool[id].front()) <= dist)
					flag = true;
			}
		}

		if (flag)
			break;
		else
			pool[id].pop_front(); 
	}
}

void Thread(int id, vector<list<double>>& pool, stringstream* s){
	while (s->rdbuf()->in_avail()){
		double cur; 
		*s >> cur; 

		lock_guard<mutex> l(mu); 

		cout << "lock thread " << id << " thrd_id: "<<this_thread::get_id() << endl; 
		pool[id].push_back(cur);

		cout << "\nprint pool: \n"; 
		prt2Layer(pool);

		dropAbd(pool, id);  // need to drop unnecessary elem first. 

		for (int i = 0; i < pool.size(); ++i){
			if (i != id){
				process(pool[id], pool[i], cur, res); 
			}
		}

		cout << "\nprint pool: \n"; 
		prt2Layer(pool);
		cout << "\n ========== \n"; 
	}
}



int main(){
	int n = 3; 
	vector<thread> tpool; 
	vector<list<double>> pool(n); 
	vector<stringstream*> sstrvec; 

	sstrvec.push_back(&s1); 
	sstrvec.push_back(&s2); 
	sstrvec.push_back(&s3); 

	for (int i = 0; i < n; ++i){
		tpool.push_back(thread(Thread, i, ref(pool), ref(sstrvec[i]))); 
	}

	for (int i = 0; i < n; ++i){
		tpool[i].join(); 
	}

	for (auto i : res){
		cout << i.first << "-" << i.second << endl; 
	}

	cout << "size: " << res.size() << endl; 
}