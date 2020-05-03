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

// 
// You are playing the following Flip Game with your friend: Given a string that contains only these two characters : +and - , you and your friend take turns to flip two consecutive "++" into "--".The game ends when a person can no longer make a move and therefore the other person will be the winner.
// 
// Write a function to determine if the starting player can guarantee a win.
// 
// For example, given s = "++++", return true.The starting player can guarantee a win by flipping the middle "++" to become "+--+".
// 
// Follow up :
// Derive your algorithm's runtime complexity. 


// pass 复杂度 这样的代码复杂度是O（n！），如果输入是一个长度为N的"+++++...+++"，
// T(N)=T(N-2)+T(N-3)+(T(2)+T(N-4))+(T(3)+T(N-5))+....+(T(N-5)+T(3))+(T(N-4)+T(2))+T(N-3)+T(N-2) = 2(T(2)+T(3) +..T(N-2))<N*T(N-2) = N(N-2)(N-4)..3*2 < n!
class Solution {
public:
	bool canWin(string s) {
		for (int i = 1; i < s.size(); ++i){
			if (s[i] == '+' && s[i - 1] == '+' && !canWin(s.substr(0, i - 1) + "--" + s.substr(i + 1)))
				return true;
		}
		return false;
	}
};




// faster, use memorization	  , 复杂度 貌似是 n2
class Solution4 {
public:

	unordered_map<string, bool> m; 

	bool canWin(string s) {
		if (m.find(s) != m.end())
			return m[s]; 

		for (int i = 1; i < s.size(); ++i){
			if (s[i] == '+' && s[i - 1] == '+' && !canWin(s.substr(0, i - 1) + "--" + s.substr(i + 1))){
				m[s] = true; 
				return true;
			}
		}
		m[s] = false; 
		return false; 
	}
};



class Solution2 {
public:
	unordered_map<string, bool> m;
	bool canWin(string& s) {
		for (int i = 1; i < s.size(); ++i){
			if (s[i] == '+'&&s[i - 1] == '+'){
				s[i] = '-', s[i - 1] = '-'; 
				if (!canWin(s)){
					s[i] = '+', s[i - 1] = '+'; // don't forget here. 
					return true;
				}
				s[i] = '+', s[i - 1] = '+'; 
			}
		}
		return false; 
	}
}; 



int main() {
	Solution2 a;

	string s = "++++"; 
	cout << a.canWin(s) << endl; 

	//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
	3       8
	1    4   7    9

	*/



}

