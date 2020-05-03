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

typedef pair<int, int> PII;
typedef vector<int> VI; 
typedef vector<vector<int>> VVI; 

class Robot{
public:
	bool move(); 
	void turnLeft(); 
	void turnRight(); 
	void clean(); 
};

vector<vector<int>> dirs = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } }; 

// problem not stated clearly. 
class Solution {
public:
	int cleanRoom(Robot& robot){
		unordered_map<string, bool> visited; 
		dfs(robot, visited, 0, 0, 0); 
	}

	void dfs(Robot& robot, unordered_map<string, bool>& v, int dir, int x, int y){
		robot.clean();
		v[to_string(x) + '_' + to_string(y)] = true; 

		for (int i = 0; i < 4; ++i){
			dir += 1; 
			dir %= 4; 
			robot.turnLeft(); 

			int xx = x + dirs[dir][0], yy = y + dirs[dir][1];
			if (v.count(to_string(xx) + '_' + to_string(yy)) == 0 && robot.move()){
				dfs(robot, v, dir, xx, yy);
			}
		}

		robot.turnLeft(); 
		robot.turnLeft(); 
		robot.move(); 
		robot.turnLeft(); 
		robot.turnLeft(); 
	}
};


// good ans on leetcode, java
// class Solution10 {
// public:
//     unordered_map<int, unordered_map<int, int>> data;
//     int x=0;
//     int y=0;
//     int dx[4]={1, 0, -1, 0};
//     int dy[4]={0, 1, 0, -1};
//     int dir=0;
//     void cleanRoom(Robot& robot) {
//         if(data[x][y]==1){
//             return;
//         }
//         data[x][y]=1;
//         robot.clean();
//         for(int i=0; i<4; i++){
//             if(robot.move()){
//                 x+=dx[dir];
//                 y+=dy[dir];
//                 cleanRoom(robot);
//                 robot.turnRight();
//                 robot.turnRight();
//                 robot.move();
//                 robot.turnRight();
//                 robot.turnRight();
//                 x-=dx[dir];
//                 y-=dy[dir];
//             }
//             robot.turnRight();
//             dir=(dir+1)%4;
//         }
//     }
// };


// direction: 0->right, 1->down, 2->left бн.
class Solution3 {
public:
	int i = 0, j = 0;
	int direction = 0;
	unordered_map<int, unordered_map<int, bool>> map;

	void cleanRoom(Robot& robot) {
		robot.clean();
		map[i][j] = true;
		for (int ii = 0; ii < 4; ++ii){
			vector<int> next_pos = nextPos();
			int next_i = next_pos[0], next_j = next_pos[1];
			if (map[next_i][next_j] == false && robot.move()){
				i = next_i, j = next_j + j;
				cleanRoom(robot);
			}
			robot.turnRight();
			direction = (direction + 1) % 4;
		}
		back_track(robot);
	}

	void back_track(Robot& robot){
		robot.turnRight(); 
		robot.turnRight(); 
		robot.move(); 
		robot.turnRight(); 
		robot.turnRight(); 
	}

	vector<int> nextPos(){
		int ii = i, jj = j;
		switch (direction){
		case 0: jj = j + 1; break;
		case 1: ii = i + 1; break;
		case 2: jj = j - j; break;
		case 3: ii = i - 1; break;
		}
		return{ ii, jj };
	}
};


// pass, 32%
class Solution2 {
public:
	//  0
	//3   1
	//  2
    void cleanRoom(Robot& robot) {
		int d = 0; 
		unordered_map<int, unordered_map<int, int>> v; 
		v[0][0] = 1;
		dfs(robot, d, 0, 0, v); 
    }
	void dfs(Robot& robot, int dir, int x, int y, unordered_map<int, unordered_map<int, int>>& v){
		robot.clean(); 

		for (int i=0; i<4; ++i){
			vector<int> pos = calc(x, y, dir); 
			int xx = pos[0], yy = pos[1]; 
			if (v[xx][yy]){
				robot.turnRight(); 
				dir = (dir + 1) % 4; 
				continue; 
			}
			if (robot.move()){
				v[xx][yy] = 1; 
				dfs(robot, dir, xx, yy, v); 
			}
			robot.turnRight();
			dir = (dir + 1) % 4;
		}

		robot.turnRight(); 
		robot.turnRight(); 
		robot.move(); 
		robot.turnRight(); 
		robot.turnRight(); 
	}

	vector<int> calc(int x, int y, int d){
		switch (d){
		case 0: return{ x - 1, y };
		case 1: return{ x, y + 1 };
		case 2: return{ x + 1, y };
		case 3: return{ x, y - 1 };
		}
		return{}; 
	}
};



int main(){
	Solution2 a2;

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

