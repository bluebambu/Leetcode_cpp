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
// 给一个扫地机器人，还有三个function：
// move(), which returns boolean value
// turn_left(k), which make robot turns left k times.
// turn_right(k), which make robot turns right k times.
// Design an algorithm to make robot clean up all room.Timecomplexity, linear in term of room space.


typedef pair<int, int> PII; 

class Matrix{
	int n; 
	int m; 
	vector<vector<int>>& core; 
	int r_init_x, r_init_y; 

public:
	Matrix(vector<vector<int>>& x) :n(x.size()), m(x[0].size()), core(x),r_init_x(0), r_init_y(0) {}

	void setRobotInit(int i, int j){
		r_init_x = i; 
		r_init_y = j;
	}

	bool can(int i, int j){
		int x = i + r_init_x, y = j + r_init_y; 
		return x >= 0 && y >= 0 && x < n && y < m && core[x][y] != 1; 
	}

	void clean(int i, int j){
		int x = i + r_init_x, y = j + r_init_y; 
		core[x][y] = 2; 
		cout << "["<<x << " " << y <<"]"<< endl; 

		prt2Layer(core); 
	}

	void backtrack(int i, int j){
		int x = i + r_init_x, y = j + r_init_y; 
		core[x][y] = 3; 
		prt2Layer(core); 
	}
};


class Robot {
public:
	int i, j; 
	// dir: up,right,down,left, 0, 1, 2, 3
	int direction; 
	Matrix& mtx; 
	map<PII, int> visited;

	explicit Robot(Matrix& y) :i(0), j(0), direction(1), mtx(y) {}

	PII alongDirection1StepPos(){
		int x, y; 
		if (direction % 2){
			x = i; 
			y = j + (direction == 1 ? 1 : -1); 
		}
		else{
			x = i + (direction == 2 ? 1 : -1); 
			y = j; 
		}
		return{ x, y };
	}

	bool move(){ 
		PII nextPos = alongDirection1StepPos(); 
		int x = nextPos.first, y = nextPos.second; 
		if (!mtx.can(x,y))
			return false; 

		i = x; 
		j = y;
		return true; 
	}

	void clean(){
		mtx.clean(i, j); 
	}

	void turn90(){
		direction = (direction + 1) % 4;
	}; 

	// dir: up,right,down,left, 0, 1, 2, 3
	void broomAll(){
		dfs2(visited); 
	}

	void dfs2(map<PII, int>& visited){
		visited[{i,j}] = 1;
		clean(); 

		for (int k = 0; k < 4; ++k){ // left, straight, right, backward
			int x, y;
			x = alongDirection1StepPos().first, y = alongDirection1StepPos().second;

			if (!visited[{x, y}] && (move()))
				dfs(visited);

			turn90(); 
		}

		turn90(); turn90(); 
		move(); 
		turn90(); turn90(); 
	}

	void dfs(map<PII, int>& visited){
		visited[{i, j}] = 1; 
		clean(); 

		for (int k = 0; k < 4; ++k){
			turn90(); 
			int x, y; 
			x = alongDirection1StepPos().first, y = alongDirection1StepPos().second;
			
			if (visited[{x, y}]) 
				continue;
			if (!move())
				continue;

			dfs(visited); 
		}
		turn90(); turn90(); 
		move(); 
		turn90(); turn90(); 
	}
};


int main(){
	vector < vector<int>> a = {
		{ 0, 1, 1, 0, 1, 0 },
		{ 1, 1, 1, 0, 1, 0 },
		{ 0, 0, 0, 0, 1, 0 },
		{ 0, 0, 1, 0, 0, 0 },
		{ 0, 1, 1, 0, 1, 0 },
		{ 0, 0, 1, 0, 1, 0 },
	}; // 6x6

	vector < vector<int>> a2 = {
		{ 0, 1, 1, 0, 1, 0 },
		{ 1, 1, 1, 0, 1, 0 },
		{ 0, 0, 1, 0, 1, 0 },
		{ 0, 0, 1, 0, 0, 0 },
		{ 0, 1, 1, 0, 1, 0 },
		{ 0, 0, 0, 0, 0, 0 },
	}; // 6x6


	Matrix b(a2); 
	Robot c(b); 
	b.setRobotInit(5, 3); 
	c.broomAll();
}

