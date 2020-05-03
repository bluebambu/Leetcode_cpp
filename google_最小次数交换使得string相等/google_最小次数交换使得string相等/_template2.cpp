// _template.cpp : Defines the entry point for the console application.
//
#include <stdafx.h>

#include <iostream>
#include <random>
#include <iterator>
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
	int minSwap(string std, string toswap){
		vector<int> orderMap(26, 0); 
		for (int i = 0; i < std.size(); ++i){
			orderMap[std[i] - 'a'] = i; 
		}

		vector<int> toswapArr; 
		for (int i = 0; i < toswap.size(); ++i){
			toswapArr.push_back(orderMap[toswap[i] - 'a']); 
		}

		// now it becomes how to make toswapArr sorted with min steps. 

		// we need a visited array to avoid repeating search
		vector<bool> visited(toswapArr.size(), false); 

		int res = 0; 
		for (int i = 0; i < toswapArr.size(); ++i){
			if (!visited[i]){
				int j = i; 
				int startpos = j; 

				// be careful to set how repeating loop starts and ends...
				int ringSz = 1;  // if there is no ring, just single number, ring size should be 1
				while (1){ // while(1) loop is equal to  do{}while() loop. 
					visited[j] = true; 
					if (toswapArr[j]==startpos)
						break;
					j = toswapArr[j]; 
					++ringSz; 
				}

				res += ringSz - 1; 
			}
		}
		return res; 
	}

	int minSwap2(string std, string str){
		if (std == str)
			return 0; 

		int left = 0, right = std.size() - 1; 
		while (left < right && std[left] == str[left]) ++left; 
		while (left < right && std[right] == str[right]) --right; 

		int j = right; 
		while (j > left && str[j] != std[left]) --j; 
		swap(str[left], str[j]); 
		int r_res = 1 + minSwap2(std.substr(left + 1), str.substr(left + 1));
		swap(str[left], str[j]); 

		int i = left; 
		while (i < right && str[i] != std[right]) ++i; 
		swap(str[right], str[i]); 
		int l_res = 1 + minSwap2(std.substr(left, right-left), str.substr(left, right-left));
		swap(str[right], str[i]); 

		return min(r_res, l_res); 
	}
};



int main(){
	Solution a; 

	string bb = "abcdefghijk"; 
	string b = "abcdefghijk"; 
	for (int i = 0; i < 10; ++i){
		random_device rd; 
		mt19937 g(rd()); 

		shuffle(b.begin(), b.end(), g); 
		cout << bb << endl << b << endl; 
		cout << a.minSwap(bb, b) << endl;
		cout << a.minSwap2(bb,b) << endl<<endl;
	}


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

