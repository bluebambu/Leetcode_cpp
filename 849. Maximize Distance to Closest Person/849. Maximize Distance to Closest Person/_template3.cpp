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

vector<vector<int>> dirs = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };
typedef pair<int, int> PII;
typedef vector<int> VI; 
typedef vector<vector<int>> VVI; 


// pass , 22.7%
class Solution {
public:
    int maxDistToClosest(vector<int>& seats) {
		vector<int> pos; 
		for (int i = 0; i < seats.size(); ++i){
			if (seats[i] == 1)
				pos.push_back(i); 
		}

		int maxDist = pos[0]*2; 
		int maxGapStart = -1; 
		int i; 
		for (i = 0; i < pos.size() - 1; ++i){
			int nxt = i + 1; 
			if (pos[nxt] - pos[i] > maxDist){
				maxDist = pos[nxt] - pos[i]; 
				maxGapStart = pos[i]; 
			}
		}
		if (seats.size() - pos.back() - 1 > maxDist / 2){
			maxDist = 2 * (seats.size() - pos.back() - 1); 
		}
		return maxDist / 2; 
    }
};

class Solution2 {
public:
	int maxDistToClosest(vector<int>& seats) {
		int maxdist = -1;
		int i = -1, j = 0;
		for (; j < seats.size(); ++j){
			if (seats[j] == 1){
				if (i == -1) maxdist = max(maxdist, j - i - 1);
				else maxdist = max(maxdist, (j - i) / 2);
				i = j;
			}
		}
		maxdist = max(maxdist, int(seats.size()) - i - 1);
		return maxdist;
	}
};


int main(){
		vector<int> v1 = { 1, 0, 0, 0, 1, 0, 1 },
		v2 = { 1, 0, 0, 0 },
		v3 = { 0, 0, 0, 0, 1, 0, 0 },
		v4 = { 0, 0, 1, 0, 0, 1, 0, 0, 0, 0 },
		v5 = { 0, 1, 1, 1, 0, 0, 1, 0, 0 }; 

	Solution2 a; 
	cout << a.maxDistToClosest(v1) << endl;
	cout << a.maxDistToClosest(v2) << endl;
	cout << a.maxDistToClosest(v3) << endl;
	cout << a.maxDistToClosest(v4) << endl;
	cout << a.maxDistToClosest(v5) << endl;




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

