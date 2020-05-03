// _template4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

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

typedef vector<int> VI; 
typedef vector<VI> VVI; 
typedef pair<int, int> PII; 

VVI dirs = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } }; 


class Solution {
public:
	struct info{
		char c; 
		string state; 
		vector<char> depend;
		info(char x, string y, vector<char> z) :c(x), state(y), depend(z) {}
	}; 
	map<char, int> charMap(vector<info> infos){
		unordered_map<char, vector<char>> depMap; 
		unordered_map<char, vector<char>> infoMap; 
		unordered_map<char, string> stateMap; 
		unordered_map<char, int> outdegree; 
		for (auto& i : infos){
			infoMap[i.c] = i.depend; 
			for (char pre : i.depend)
				depMap[pre].push_back(i.c); 
			outdegree[i.c] = i.depend.size(); 
			stateMap[i.c] = i.state; 
		}

		queue<char> q; 
		map<char, int> res; 
		for (char c : outdegree)
			if (!outdegree[c]){
				res[c] = stoi(stateMap[c])
				q.push(c); 
			}


		while (!q.empty()){
			char f = q.front(); 
			q.pop(); 

			for (char nxt : depMap[f]){
				--outdegree[nxt]; 
				if (outdegree[nxt] == 0){
					calc(infoMap, nxt, res); 
					q.push(nxt); 
				}
			}
		}

		return res;
	}
};

class Solution {
public:
	struct info{
		char c;
		string state;
		vector<char> depend;
		info(char x, string y, vector<char> z) :c(x), state(y), depend(z) {}
	};

	unordered_map<char, vector<char>> depMap; 
	unordered_map<char, string> stateMap;
	unordered_map<char, int> resMap;
	map<char, int> charMap(vector<info> infos){
		for (auto&i : infos){
			depMap[i.c] = i.depend; 
			stateMap[i.c] = i.state; 
		}
		unordered_map<char, bool> processed; 
		for (int i = 0; i < infos.size(); ++i){
			if (!processed[infos[i].c]){
				dfs(infos[i].c, processed); 
			}
		}
	}

	void dfs(char c, unordered_map<char, bool>& processed){
		vector<char>& depen = depMap[c];
		for (char pre : depen){
			if (!processed[pre]){
				dfs(pre, processed); 
			}
		}
		resMap[c] = calc(c, stateMap); 
		processed[c] = true; 
	}
}; 


int main(){
	Solution a;

	vector<int> b = { 1, 2, 3, 4, 5 }; 



	//TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6,
		new TreeNode(3, new TreeNode(1),
						new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
						new TreeNode(9,
		                               new TreeNode(10),
		                               nullptr)));
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

