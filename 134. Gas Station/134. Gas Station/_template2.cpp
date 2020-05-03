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
	int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
		vector<int> diff;
		int n = gas.size(); 
		int total = 0; 
		for (int i = 0; i < n; ++i){
			diff.push_back(gas[i] - cost[i]);
			total += diff.back(); 
		}
		if (total < 0) 
			return -1; 

		prt1Layer(diff); 

		int curMax = diff[0], preMax, curMin = diff[0], preMin, start=0; 
		int maxSt = 0, minSt = 0; 
		int res = INT_MIN; 

		for (int i = 1; i < n; ++i){
			preMax = curMax; 
			preMin = curMin; 

			if (preMax < 0){
				curMax = diff[i]; 
				maxSt = i; 
			}
			else{
				curMax = preMax + diff[i]; 
				// maxSt not changed. 
			}

			if (preMin > 0){
				curMin = diff[i]; 
				minSt = (i+1)%n; 
				// minSt always changed. 
			}
			else{
				curMin = preMin + diff[i]; 
				minSt = (i + 1) % n; 
				// minSt always changed. 
			}

			int curOpt = max(curMax, total - curMin); 
			if (res < curOpt){
				res = curOpt; 
				start = curOpt == curMax ? maxSt : minSt; 
			}
		}

		return start; 
	}
};

class Solution2 {
public:
	int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
		int n = gas.size(); 
		vector<int> diff(n, 0); 
		for (int i = 0; i < n; ++i)
			diff[i] = gas[i] - cost[i]; 

		int total = 0, locMax = 0, glbMax = 0, locMin = 0, glbMin = 0; 
		int locMaxSt, glbMaxSt, locMinEnd, glbMinEnd; 
		for (int i = 0; i < n; ++i){
			total += diff[i]; 

			if (locMax < 0){
				locMax = diff[i]; 
				locMaxSt = i; 
			}
			else{
				locMax += diff[i]; 
			}

			if (locMax > glbMax){
				glbMax = locMax; 
				glbMaxSt = locMaxSt; 
			}


			if (locMin > 0){
				locMin = diff[i]; 
				// locMinEnd always change! 
				locMinEnd = (i + 1) % n; 
			}
			else{
				locMin += diff[i]; 
				locMinEnd = (i + 1) % n; 
			}

			if (locMin < glbMin){
				glbMin = locMin; 
				glbMinEnd = locMinEnd; 
			}
		}

		if (total < 0) return -1; 
		if (glbMax > total - glbMin)
			return glbMaxSt;
		else
			return glbMinEnd; 
	}
}; 


// not finished. 
class Solution3 {
public:
	int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
		vector<int> netgas; 
		for (int i = 0; i < gas.size(); ++i){
			netgas.push_back(gas[i] - cost[i]); 
		}

		int tot = accumulate(netgas.begin(), netgas.end(), 0) ; 
		if (tot < 0) return false;

		int maxgas = netgas[0], mingas = netgas[0], l_start, l_end; 
		int g_max = maxgas, g_min = mingas, g_max_start = 0, g_min_end = 0; 
		for (int i = 1; i < netgas.size(); ++i){
			if (maxgas > 0){
				maxgas += netgas[i]; 
				if (maxgas > g_max){
					g_max = maxgas; 
					g_max_start = l_start; 
				}
			}
			else{
				maxgas = netgas[i]; 
				l_start = i; 
			}

			if (mingas < 0){
				mingas += netgas[i]; 
				if (mingas < g_min){
					g_min = mingas; 
					g_min_end = i; 
				}
			}
			else{
				mingas = netgas[i]; 
				if (mingas < g_min){
					g_min = mingas; 
					g_min_end = i; 
				}
			}
		}
	}
};


int main(){
	Solution a; 
	Solution2 a2; 

	vector<int> c = { 4, 2, -10, 6 }; 
	vector<int> d = { 2, 1, -5, 3 }; 
	vector<int> b = { 2, 1, -5, 3 }; 

	vector<int> cc2 = { 1, 2, 3, 4, 5 };
	vector<int> dd2 = { 3, 4, 5, 1, 2 }; 

	vector<int> cc = { 5, 8, 2, 8 }; 
	vector<int> dd = { 6, 5, 6, 6 }; 

	cout << a.canCompleteCircuit(cc, dd) << endl; 
	cout << a2.canCompleteCircuit(cc, dd) << endl; 


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

