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


struct TreeNode {
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
class SnakeGame {
public:
	/** Initialize your data structure here.
	@param width - screen width
	@param height - screen height
	@param food - A list of food positions
	E.g food = [[1,1], [1,0]] means the first food is positioned at [1,1], the second is at [1,0]. */
	int screen_width, screen_height; 
	deque<PII> snake; 
	vector<PII> foods; 
	int foodId; 
	
	SnakeGame(int width, int height, vector<pair<int, int>> food):foods(food) {
		screen_height = height, screen_width = width; 
		snake.push_back({ 0, 0 }); 
		foodId = 0; 
	}

	PII nextPos(string direction){
		switch (direction[0]){
		case 'U': return{ snake[0].first - 1, snake[0].second }; 
		case 'L': return{ snake[0].first, snake[0].second-1 }; 
		case 'D': return{ snake[0].first + 1, snake[0].second }; 
		case 'R': return{ snake[0].first, snake[0].second+1 }; 
		}
	}
	/** Moves the snake.
	@param direction - 'U' = Up, 'L' = Left, 'R' = Right, 'D' = Down
	@return The game's score after the move. Return -1 if game over.
	Game over when snake crosses the screen boundary or bites its body. */
	int move(string direction) {
		PII next = nextPos(direction); 
		int x = next.first, y = next.second; 
		if (x < 0 || x >= screen_height || y < 0 || y >= screen_width)
			return -1; 
		for (int i = 0; i < snake.size() - 1; ++i){
			if (x == snake[i].first && y == snake[i].second)
				return -1; 
		}

		if (foodId < foods.size() &&  (x == foods[foodId].first && y == foods[foodId].second)){
			snake.push_front(foods[foodId++]);
		}
		else{
			snake.pop_back(); 
			snake.push_front(next); 
		}
		
		return snake.size() - 1; 
	}
};


class SnakeGame2 {
public:

	SnakeGame2(int width, int height, vector<pair<int, int>> food ){
		
	}

	int move(string cmd){

	}
};


int main(){
	vector<PII> f = { { 1, 2 }, { 0, 1 } }; 
	SnakeGame a(3, 2, f); 
	cout<<a.move("R"); 
	cout<<a.move("D"); 
	cout<<a.move("R"); 
	cout<<a.move("U"); 
	cout<<a.move("L"); 
	cout<<a.move("U"); 
}

