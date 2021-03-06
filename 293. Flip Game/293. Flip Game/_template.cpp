// _template.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;

inline int exchg(int &a, int &b)  { int c = a; a = b; b = c; }
inline int log2(int N){ return log10(N) / log10(2); }
inline float min(float a, float b) { return a<b ? a : b; }


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
		for (int i = 0; i<n; ++i){
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


// You are playing the following Flip Game with your friend: Given a string that contains only these two characters : +and - , you and your friend take turns to flip two consecutive "++" into "--".The game ends when a person can no longer make a move and therefore the other person will be the winner.
// 
// Write a function to compute all possible states of the string after one valid move.
// 
// For example, given s = "++++", after one move, it may become one of the following states :
// 
// [
// 	"--++",
// 	"+--+",
// 	"++--"
// ]
// 
// If there is no valid move, return an empty list[].
// 




class Solution {
public:
	vector<string> generatePossibleNextMoves(string s) {
		vector<string> res; 
		for (int i = 1; i < s.size(); ++i){
			if (s[i] == '+' && s[i - 1] == '+')
				res.push_back(s.substr(0, i - 1) + "--" + s.substr(i + 1)); 
		}
		return res; 
	}
};






int main()
{
	Solution a;

	//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
	3       8
	1    4   7    9

	*/

	a.flatten(tree);


}

