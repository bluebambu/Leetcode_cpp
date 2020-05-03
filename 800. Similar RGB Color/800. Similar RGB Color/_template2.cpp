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


class Solution {
public:
	string similarRGB(string color) {
		string res; 
		int min = INT_MAX; 
		color = color.substr(1); 
		for (char a = prev(color[0]); a <= next(color[0]); a = next(a)){
			for (char b = prev(color[2]); b <= next(color[2]); b = next(b)){
				for (char c = prev(color[4]); c <= next(color[4]); c = next(c)){
					string cand = string() + a + a + b + b + c + c; 
					if (abs(dist(cand, color)) < min){
						min = abs(dist(cand, color));
						res = cand; 
					}
				}
			}
		}

		return "#" + res; 
	}

	char prev(char c){
		if (c == '0')
			return c;
		else if (c == 'a')
			return '9';
		else
			return c - 1; 
	}

	char next(char c){
		if (c == 'F')
			return c;
		else if (c == '9')
			return 'a';
		else
			return c + 1; 
	}

	int dist(string a, string b){
		return -(unitDist(a.substr(0, 2), b.substr(0, 2))) - (unitDist(a.substr(2, 2), b.substr(2, 2))) - (unitDist(a.substr(4, 2), b.substr(4, 2)));
	}

	int unitDist(string a, string b){
		// ab->xy, dist^2
		int x = sixteen(a[0]) * 16 + sixteen(a[1]); 
		int y = sixteen(b[0]) * 16 + sixteen(b[1]); 

		return (x - y)*(x - y); 
	}

	int sixteen(char c){
		if (c >= '0' && c <= '9')
			return c - '0';
		else
			return c - 'a' + 10; 
	}

};


class Solution2 {
public:
	string similarRGB(string color) {
		return "#" + closest(color.substr(1, 2)) + closest(color.substr(3, 2)) + closest(color.substr(5, 2)); 
	}
	string closest(string hex){
		string dec_2_hex = "0123456789abcdef"; 
		string res; 
		int dec_num = stoi(hex, nullptr, 16); 
		int num1 = dec_num / 17; 
		if (dec_num % 17 > 8) ++num1; 
		return string() + dec_2_hex[num1] + dec_2_hex[num1]; 
	}
}; 


int main(){
	Solution2 a; 

	cout << a.similarRGB("#09f166") << endl;


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

