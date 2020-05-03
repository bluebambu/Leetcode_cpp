// _template.cpp : Defines the entry point for the console application.
//
#include <stdafx.h>

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



class GOL {
public:
	// 1 life around -> flip,  0,2 lives around -> keep
	void gol1d(vector<int>& arr){
		if (arr.size() < 3)
			return;

		// state code: 
		//{
		//	0: 0->0,
		//	1: 1->1,
		//	2: 0->1,
		//	3: 1->0
		//}

		int n = arr.size(); 
		for (int i = 0; i < n; ++i){
			int prev = (i - 1 + n) % n, next = (i + 1 + n) % n; 
			int life_around = 0; 
			if (arr[prev] == 1 || arr[prev] == 3)
				++life_around; 
			if (arr[next] == 1 || arr[next] == 3)
				++life_around; 
			if (life_around == 1)
				arr[i] = (arr[i] == 0 ? 2 : 3); 
			else
				arr[i] = (arr[i] == 0 ? 0 : 1); 
		}

		for (int i = 0; i < n; ++i)
			arr[i] = ((arr[i] == 1 || arr[i] == 2) ? 1 : 0);
	}

	void gol2d(vector<vector<int>>& mtrx){
		if (mtrx.size() < 2 || mtrx[0].size() < 2)
			return; 
		// state code: 
		//{
		//	0: 0->0, b00
		//	1: 1->1, b01
		//	2: 0->1, b10
		//	3: 1->0, b11
		//}

		int n = mtrx.size(), m = mtrx[0].size(); 
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				// 8 directions
				int life_around = 0; 
				for (int k = 0; k<3; ++k){
					for (int l = 0; l < 3; ++l){
						int x = (i - 1 + k + n) % n, y = (j - 1 + l + m) % m; 
						if (x != i || y != j){
							//cout << "i, j: " << i << j << endl; 
							//cout << "x, y: " << x << y << endl; 
							life_around += (mtrx[x][y]%2); 
						}
					}
				}

				if (mtrx[i][j] % 2){
					if (life_around < 2 || life_around>3)
						mtrx[i][j] = 3;
				}
				else{
					if (life_around == 3)
						mtrx[i][j] = 2;
				}
			}
		}

		//prt2Layer(mtrx); 

		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				mtrx[i][j] = ((mtrx[i][j] == 2 || mtrx[i][j] == 1) ? 1 : 0); 
			}
		}
	}
};


int main(){
	GOL game; 

	vector<int> b = { 1, 0, 0, 0, 1, 1, 0, 1, 0, 1 }; 

	game.gol1d(b); 
	prt1Layer(b); 
	game.gol1d(b); 
	prt1Layer(b); 

	cout << endl << endl << endl; 

	vector<vector<int>> c = {
		{ 0, 0, 0, 0 },
		{ 0, 0, 1, 1 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 0, 0 },
	}; 


	game.gol2d(c); 
	prt2Layer(c); 
	game.gol2d(c); 
	prt2Layer(c); 

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

