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

vector<string> parse(string str, char delimiter){
	istringstream ss(str);
	vector<string> res; 
	string token; 

	while (std::getline(ss, token, delimiter)) {
		res.push_back(token);
	}

	return res; 
}

////////////////////////////////////////////////////////////////
// Given the running logs of n functions that are executed in a nonpreemptive single threaded CPU, find the exclusive time of these functions. 
// Each function has a unique id, start from 0 to n-1. A function may be called recursively or by another function.
// A log is a string has this format : function_id:start_or_end:timestamp. For example, "0:start:0" means function 0 starts from the very beginning of time 0. "0:end:0" means function 0 ends to the very end of time 0. 
// Exclusive time of a function is defined as the time spent within this function, the time spent by calling other functions should not be considered as this function's exclusive time. You should return the exclusive time of each function sorted by their function id.
// Example 1:
// Input:
// n = 2
// logs = 
// ["0:start:0",
//  "1:start:2",
//  "1:end:5",
//  "0:end:6"]
// Output:[3, 4]
// Explanation:
// Function 0 starts at time 0, then it executes 2 units of time and reaches the end of time 1. 
// Now function 0 calls function 1, function 1 starts at time 2, executes 4 units of time and end at time 5.
// Function 0 is running again at time 6, and also end at the time 6, thus executes 1 unit of time. 
// So function 0 totally execute 2 + 1 = 3 units of time, and function 1 totally execute 4 units of time.

// Note:
// Input logs will be sorted by timestamp, NOT log id.
// Your output should be sorted by function id, which means the 0th element of your output corresponds to the exclusive time of function 0.
// Two functions won't start or end at the same time.
// Functions could be called recursively, and will always end.
// 1 <= n <= 100


// passAC
/*
a bit hard!! 

consider >3-layer recursion

[												]
	[				]			[			]
		[		]						[]

to get the real duration of each recurtion, you need to know its net duration, and the *total duration of previous recurtion*!!!!

So you have to track the *net* and *total* duration for each layer!!!!!!!


HERE I use {id, time, previous recurtion duration} as the elem of stack. 
So  net duration == endTime - startTime + 1 - (previous total duration) 

*/
class Solution {
public:
	vector<int> exclusiveTime(int n, vector<string>& logs) {
		vector<int> res(n, 0); 
		vector<vector<int>> st; 

		for (int i = 0; i < logs.size(); ++i){
			vector<string> cur = parse(logs[i], ':');
			int id = stoi(cur[0]); 
			string cmd = cur[1]; 
			int time = stoi(cur[2]); 

			if (cmd == "start"){
				st.push_back(vector<int>({ id, time, 0 })); 
			}
			else{
				int totaldur = time - st.back().at(1) + 1; 
				int realdur = totaldur - st.back().at(2); 
				res[id] += realdur; 
				st.pop_back(); 
				if (!st.empty()){
					st.back().at(2) += totaldur; 
				}
			}
		}
		
		return res; 
	}
};







int main(){
	Solution a;

	vector<int> b = { 7, 2, 5, 10, INT_MAX };

	vector<string> logs = { "0:start:0", "1:start:2", "1:end:5", "0:end:6" }; 
	
	vector<string> logs2 = { "0:start:0", "0:start:1", "0:start:2", "0:end:3", "0:end:4", "0:end:5" }; 

	auto c = a.exclusiveTime(1, logs2); 

	prt1Layer(c); 


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

