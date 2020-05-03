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

template <typename T>
void vprt(vector<T> v){
	for (auto i : v)
		cout << v << " ";
	cout << endl;
}

template <typename T>
void vvprt(vector<vector<T>> v){
	for (auto i : v){
		for (auto j : i){
			cout << j << " ";
		}
		cout << endl;
	}
	cout << endl;
}

template <typename C>
void setprt(C v){
	for (auto i : v)
		cout << i << " ";
	cout << endl;
}

template <typename C>
void mapprt(C v){
	for (auto i : v)
		cout << i.first << " " << i.second << endl;
	cout << endl;
}
////////////////////////////////////////////////////////////////


// brute force
class Solution2 {
public:
	int strStr(string haystack, string needle) {
		if (haystack.size() < needle.size())
			return -1; 

		for (int ii = 0; ii < haystack.size(); ++ii){
			if (haystack[ii] == needle[0]){
				int i = ii; 
				int j; 

				for (j = 1; j < needle.size() && i + j < haystack.size(); ++j){
					if (needle[j] != haystack[i + j]){
						break;	
					}
				}

				if (j == needle.size() && i + j <= haystack.size()){
					return ii; 
				}
			}
		}
		
		return -1; 
	}
};


// rabin-karp
class Solution {
public:
	vector<int> strStr(string haystack, string needle) {
		vector<int> res;
		int R = 31;
		long long M = 1000000000000000003L;
		int n = needle.size();

		long long patternHash = hash(needle, 0, n, R, M);

		int hayHash;
		for (int i = 0; i + n < haystack.size(); ++i){
			if (i == 0){
				hayHash = hash(haystack, 0, n, R, M);
			}
			else{
				// hayHash = (hayHash - ((haystack[i - 1] - 'a') * pow(R, n - 1)))*R + (haystack[i] - 'a'); 
				hayHash = (hayHash*R%M + M - long long((haystack[i - 1] - 'a') * pow(R, n)) % M + (haystack[i + n - 1] - 'a')) % M;
			}

			if (hayHash == patternHash){
				if (needle == haystack.substr(i, n))
					res.push_back(i);
			}
		}

		return res;
	}

	long long hash(string str, int i, int len, int R, long long M){
		long long res = 0;
		for (int j = 0; j < len; ++j){
			res = (R*res + str[i + j] - 'a') % M;
		}
		return res;
	}
};




int main()
{
	Solution a;

	auto b = a.strStr("wefjlkasjfljkwe", "kas"); 

	setprt(b);
	

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

