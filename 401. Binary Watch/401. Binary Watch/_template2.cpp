// _template.cpp : Defines the entry point for the console application.
//
#include <stdafx.h>

#include <iostream>
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
// A binary watch has 4 LEDs on the top which represent the hours (0-11), and the 6 LEDs on the bottom represent the minutes (0-59).

// Each LED represents a zero or one, with the least significant bit on the right.

// For example, the above binary watch reads "3:25".

// Given a non-negative integer n which represents the number of LEDs that are currently on, return all possible times the watch could represent.

// Example:

// Input: n = 1
// Return: ["1:00", "2:00", "4:00", "8:00", "0:01", "0:02", "0:04", "0:08", "0:16", "0:32"]


// pass
class Solution {
public:
	vector<string> readBinaryWatch(int num) {
		vector<int> mins = { 480, 240, 120, 60, 32, 16, 8, 4, 2, 1 }; 

		vector<int> res; 
		vector<bool> visited(10, false); 
		dfs(0, 0, num, mins, 0, visited, res); 

		return convert(res); 
	}

	void dfs(int id, int cnt, int total, vector<int>& mins, int path, vector<bool>& visited, vector<int>& res){
		if (cnt > total || path >= 12*60)
			return; 
		if (path == 60){
			prt1Layer(visited); 
			cout << "cnt: " << cnt << endl; 
			cout << id << endl; 
			cout << "===============\n";
		}
		if (cnt == total && validate(visited, mins)){
			res.push_back(path); 
			return; 
		}
		

		for (int i = id; i < mins.size(); ++i){
			if (visited[i] == false){
				visited[i] = true; 
				dfs(i + 1, cnt+1, total, mins, path + mins[i], visited, res); 
				visited[i] = false; 
			}
		}
	}

	bool validate(vector<bool>& v, vector<int>& mins){
		int cum = 0; 
		for (int i = 0; i < 4; ++i){
			if (v[i]){
				cum += mins[i]; 
				if (cum >= 12 * 60)
					return false;
			}
		}

		cum = 0; 
		for (int i = 4; i < mins.size(); ++i){
			if (v[i]){
				cum += mins[i]; 
				if (cum >= 60)
					return false; 
			}
		}
		return true; 
	}

	vector<string> convert(vector<int>& res){
		vector<string> vs; 

		for (int i = 0; i < res.size(); ++i){
			int t = res[i]; 
			int h = t / 60, m = t % 60; 
			
			string s = to_string(h) + ":" + (m < 10 ? "0" : "") + to_string(m); 
			vs.push_back(s); 
		}

		sort(vs.begin(), vs.end());
		return vs; 
	}
};


// bitset
class Solution2 {
public:
	vector<string> readBinaryWatch(int num) {
		vector<string> res; 
		for (int h = 0; h < 12; ++h){
			for (int m = 0; m < 60; ++m){
				if (bitset<10>(h << 6 | m).count() == num){
					res.push_back(to_string(h) + ":" + (m>9 ? "" : "0") + to_string(m)); 
				}
			}
		}
		return res;
	}
};


class Solution3 {
public:
	vector<string> readBinaryWatch(int num) {
		
	}
}; 



int main(){
	Solution2 a; 

	vector<int> b = { 4, 1, -9, 0, INT_MAX }; 

	prt1Layer(a.readBinaryWatch(4)); 


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

