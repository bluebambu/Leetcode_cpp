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
#include <string>

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
// A character in UTF8 can be from 1 to 4 bytes long, subjected to the following rules :

// For 1 - byte character, the first bit is a 0, followed by its unicode code.
// For n - bytes character, the first n - bits are all one's, the n+1 bit is 0, followed by n-1 bytes 
// with most significant 2 bits being 10.

// This is how the UTF - 8 encoding would work :

// Char.number range | UTF - 8 octet sequence
// (hexadecimal) | (binary)
// -------------------- + -------------------------------------------- -
// 0000 0000 - 0000 007F | 0xxxxxxx
// 0000 0080 - 0000 07FF | 110xxxxx 10xxxxxx
// 0000 0800 - 0000 FFFF | 1110xxxx 10xxxxxx 10xxxxxx
// 0001 0000 - 0010 FFFF | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
// Given an array of integers representing the data, return whether it is a valid utf - 8 encoding.

// Note:
// The input is an array of integers.Only the least significant 8 bits of each integer is used to store the data.
// This means each integer represents only 1 byte of data.


// 注意： vector<int> 可能代表 多个连续的 utf8 字符，而不是一个。 
class Solution {
public:
	bool validUtf8(vector<int>& data) {
		int n = data.size(); 
		int cnt = 0; 

		for (auto d : data){
			if (cnt == 0){
				if ((d >> 5) == 0b110)
					cnt = 1;
				else if ((d >> 4) == 0b1110)
					cnt = 2;
				else if ((d >> 3) == 0b11110)
					cnt = 3;
				else if ((d >> 7))
					return false; 
			}
			else{
				if ((d >> 6) != 0b10)
					return false; 
				--cnt; 
			}
		}

		return cnt == 0;// 防止最后一个utf8 的 10xxx后缀数量不对. 
	}
};



int main()
{
	Solution a;
	vector<int> b = {197, 130, 1}; 

	cout << a.validUtf8(b); 

}

