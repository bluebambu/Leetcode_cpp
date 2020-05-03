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

// wrong ans! Because each boat can only take at most 2 people!!!!!
// this is for taking n people !!!
class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
		sort(people.begin(), people.end()); 
		int i = 0, j = people.size() - 1; 
		int res = 1, rem = limit; 
		while (i <= j){
			int a = people[i], b = people[j]; 
			if (rem >= people[j]){
				rem -= people[j]; 
				--j; 
				if (i>j)
					break;
			}
			if (rem >= people[i]){
				rem -= people[i]; 
				++i; 
			}
			else{
				res += 1; 
				rem = limit;
			}
		}
		return res; 
    }
};

class Solution2 {
public:
	int numRescueBoats(vector<int>& people, int limit) {
		sort(people.begin(), people.end()); 
		int i = 0, j = people.size() - 1; 
		int res = 1, rem = limit, cnt = 2;
		while (i <= j){
			int a = people[i], b = people[j]; 
			if (rem >= people[j]){
				rem -= people[j]; 
				--j; 
				--cnt; 
				if (i>j)
					break;
			}
			if (rem >= people[i]){
				rem -= people[i]; 
				++i; 
				--cnt; 
			}
			
			if (i > j)
				break;

			if(cnt==0 || rem < people[i]){
				res += 1; 
				rem = limit;
				cnt = 2; 
			}
		}
		return res; 
	}
}; 

// pass
class Solution3 {
public:
	int numRescueBoats(vector<int>& people, int limit) {
		sort(people.begin(), people.end()); 
		int i = 0, j = people.size() - 1; 
		int res = 0;
		for (; i <= j; --j, ++res){
			if (people[i] + people[j] <= limit)
				++i; 
		}
		return res; 
	}
};


//
class Solution4 {
public:
	int numRescueBoats(vector<int>& people, int limit) {
		sort(people.begin(), people.end()); 
		int n = 0; 
		int i = 0, j = people.size() - 1; 
		while (i <= j){
			int c = limit; 
			c -= people[j]; 
			--j; 
			++n; 
			if (c >= people[i]) ++i; 
		}
		return n; 
	}
};

//at most k people 
class Solution4 {
public:
	int numRescueBoats(vector<int>& people, int limit) {
	}
}; 



int main(){
	Solution3 a;
	Solution4 a2;

	vector<int> b = { 3, 5, 3, 4 }; 
	vector<int> b2 = { 3,2,3,2,2}; 
	vector<int> b3 = { 2, 49, 10, 7, 11, 41, 47, 2, 22, 6, 13, 12, 33, 18, 10, 26, 2, 6, 50, 10 }; 

	cout << a.numRescueBoats(b3, 50) << endl; 
	cout << a2.numRescueBoats(b3, 50) << endl; 


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

