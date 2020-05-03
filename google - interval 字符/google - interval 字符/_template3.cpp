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


class Solution {
public:
	vector<pair<vector<int>, string>>  interval(vector<vector<int>> interval, string chars){
		struct point{
			int x; 
			bool isStart; 
			char letter; 
			point(int a, bool b, char c) :x(a), isStart(b), letter(c) {}
		};

		int n = interval.size(); 
		vector<point> points; 
		for (int i = 0; i < n; ++i){
			points.push_back(point(interval[i][0], true, chars[i]));
			points.push_back(point(interval[i][1], false, chars[i]));
		}

		sort(points.begin(), points.end(), [](point& a, point& b){
			return a.x < b.x; 
		}); 

		unordered_set<char> letters; 
		vector<pair<vector<int>, string>> res; 
		int pre = points[0].x; letters.insert(points[0].letter); 
		for (int i = 1; i < points.size(); ++i){
			string cur = string(letters.begin(), letters.end()); 
			res.push_back({ { pre, points[i].x }, cur }); 
			if (points[i].isStart){
				letters.insert(points[i].letter);
			}
			else{
				letters.erase(points[i].letter); 
			}
		}

		return res; 
	}
};

class Solution2 {
public:
	vector<pair<vector<int>, string>> interval(vector<vector<int>> interval, string chars){
		int n = interval.size(); 
		map<int, pair<bool, char>> points; 
		for (int i = 0; i < n; ++i){
			points[interval[i][0]] = { interval[i][1], chars[i] }; 
		}

		vector<pair<vector<int>, string>> res; 
		unordered_set<char> letters; 
		for (auto iter = points.begin(); iter != prev(points.end()); ++iter){
			int pos = iter->first; 
			bool flag = iter->second.first; 
			char letter = iter->second.second; 
			if (flag)
				letters.insert(letter);
			else
				letters.erase(letter); 

			res.push_back({ { pos, next(iter)->first }, string(letters.begin(), letters.end()) }); 
		}

		return res; 
	}
}; 



int main(){
	Solution a;

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

