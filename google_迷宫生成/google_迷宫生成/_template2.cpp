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

// wall: 0-up, 1-right, 2-down, 3-left

class Cell{
public:
	vector<bool> walls; 
	bool isVisited; 
	int status;

	Cell() :walls(4, true), isVisited(false), status(0) {}
};

vector<vector<int>> dirs = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } }; 

typedef pair<int, int> PII; 

class Maze{
public:
	int rows, cols; 
	vector<vector<Cell>> core; 

	Maze(int x, int y) :rows(x), cols(y), core(x, vector<Cell>(y)) {
		srand(time(NULL)); 
	}

	void genMaze(){
		gen(0, 0); 

		core[0][0].walls[0] = false; 
		core.back().back().walls[2] = false; 
	}

	bool allvisited(int x, int y){
		bool res = true; 
		for (auto d : dirs){
			int xx = x + d[0], yy = y + d[1]; 
			if (xx >= 0 && xx < rows && yy >= 0 && yy < cols)
				res &= core[xx][yy].isVisited; 
		}
		return res;
	}

	void prntVisitedStatus(){
		for (int i = 0; i < rows; ++i){
			for (int j = 0; j < cols; ++j){
				cout << core[i][j].isVisited << " "; 
			}
			cout << endl; 
		}
		cout << endl; 
	}

	void gen(int x, int y){
		prntVisitedStatus(); 

		core[x][y].isVisited = true; 

		while(!allvisited(x,y)){
			int idx = rand() % 4; 
			vector<int> d = dirs[idx]; 
			int nx = x + d[0], ny = y + d[1]; 
			if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && core[nx][ny].isVisited == false){
				(core[x][y].walls)[idx] = false; 
				(core[nx][ny].walls)[(idx + 2) % 4] = false; 
				gen(nx, ny); 
			}
		}
	}

	void prnt(){
		for (int i = 0; i < rows; ++i){
			for (int j = 0; j < cols; ++j){
				cout << "["; 
				prt1Layer(core[i][j].walls); 
				cout << "]"; 
			}
			cout << endl; 
		}

		prntVisitedStatus(); 
	}
};


class Maze2{
public:
	void prntVisitedStatus(){
		for (int i = 0; i < rows; ++i){
			for (int j = 0; j < cols; ++j){
				cout << core[i][j].status << " "; 
			}
			cout << endl; 
		}
		cout << endl; 
	}

	void prnt(){
		for (int i = 0; i < rows; ++i){
			for (int j = 0; j < cols; ++j){
				cout << "[";
				prt1Layer(core[i][j].walls);
				cout << "]";
			}
			cout << endl;
		}

		prntVisitedStatus(); 
	}

	int rows, cols; 
	vector<vector<Cell>> core; 

	Maze2(int x, int y) :rows(x), cols(y), core(x, vector<Cell>(y)) {
		srand(time(NULL)); 
	}

	void genMaze(){
		int x = rand() % rows, y = rand() % cols; 
		vector<PII> toVisit; 
		toVisit.push_back({ x, y }); 

		while (!toVisit.empty()){
			int n = toVisit.size(); 
			int r = rand() % n; 
			x = toVisit[r].first, y = toVisit[r].second; 
			core[x][y].status = 1;
			toVisit.erase(find(toVisit.begin(), toVisit.end(), toVisit[r])); 

			vector<PII> neibVisited; 

			for (auto d : dirs){
				int i = x + d[0], j = y + d[1]; 
				if (i >= 0 && i < rows&&j >= 0 && j < cols){
					if (core[i][j].status == 0){
						toVisit.push_back({ i, j }); 
						core[i][j].status = 2;
					}
					else if (core[i][j].status == 1){
						neibVisited.push_back({ i, j }); 
					}
				}
			}

			if (neibVisited.empty())
				continue;

			r = rand() % (neibVisited.size()); 
			PII vis = neibVisited[r]; 
			vector<int> dd = { vis.first - x, vis.second - y }; 
			if (dd == dirs[0]){
				core[x][y].walls[1] = false; 
				core[vis.first][vis.second].walls[3] = false; 
			}
			if (dd == dirs[1]){
				core[x][y].walls[3] = false; 
				core[vis.first][vis.second].walls[1] = false; 
			}
			if (dd == dirs[2]){
				core[x][y].walls[2] = false; 
				core[vis.first][vis.second].walls[0] = false; 
			}
			if (dd == dirs[3]){
				core[x][y].walls[0] = false; 
				core[vis.first][vis.second].walls[2] = false; 
			}
		}


	}

};




int main(){
	//Maze a(10, 10); 
	//a.genMaze(); 

	//a.prnt(); 

	Maze2 b(10, 10); 
	b.genMaze(); 
	b.prnt(); 



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

