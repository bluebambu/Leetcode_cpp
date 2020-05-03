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


// pass
class Solution {
public:
    int maxVacationDays(vector<vector<int>>& flights, vector<vector<int>>& days) {
		if (flights.empty() || flights[0].empty() || days.empty() || days[0].empty())
			return 0; 

		int n = flights.size(), k = days[0].size(); 
		vector<int> weekData(n, -1);

		for (auto xx : weekData) {
			cout << xx << ' ';
		}
		cout << endl;

		for (int i = 0; i < k; ++i){
			vector<int> oldWeekData(weekData);
			if (i == 0){
				for (int cur = 0; cur < n; ++cur){
					if (flights[0][cur] || cur == 0){
						weekData[cur] = days[cur][0]; 
					}
				}
			}
			else{
				for (int pre = 0; pre < n; ++pre){
					for (int cur = 0; cur < n; ++cur){
						// oldWeekData[pre]>=0 is to make sure invalid path are excluded. 
						if ((flights[pre][cur] || pre == cur) && oldWeekData[pre]>=0){
							weekData[cur] = max(weekData[cur], oldWeekData[pre] + days[cur][i]); 
						}
					}
				}
			}


		for (auto xx : weekData) {
			cout << xx << ' ';
		}
		cout << endl;

		}

		int r = INT_MIN; 
		for (int i : weekData)
			r = max(r, i); 

		return r; 
    }
};


class Solution2 {
public:
	int maxVacationDays(vector<vector<int>>& flights, vector<vector<int>>& days) {
		
	}
}; 


int main(){
	Solution a; 

	vector<vector<int>> 
		flights = { { 0, 1, 1 }, { 1, 0, 1 }, { 1, 1, 0 } },
		days = { { 7, 0, 0 }, { 0, 7, 0 }, { 0, 0, 7 } };

	vector<vector<int>> 
		flights2 = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
		days2 = { { 1, 1, 1 }, { 7, 7, 7 }, { 7, 7, 7 } };

	vector<vector<int>> 
		flights3 = { { 0, 1, 1 }, { 1, 0, 1 }, { 1, 1, 0 } },
		days3 = { { 1, 3, 1 }, { 6, 0, 3 }, { 3, 3, 3 } };

	cout << a.maxVacationDays(flights3, days3) << endl; 
	

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

