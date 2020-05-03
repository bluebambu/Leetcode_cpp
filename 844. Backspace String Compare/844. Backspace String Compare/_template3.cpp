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

vector<vector<int>> dirs = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };
typedef pair<int, int> PII;
typedef vector<int> VI; 
typedef vector<vector<int>> VVI; 


// wrong ans!
class Solution {
public:
    bool backspaceCompare(string S, string T) {
		int i = S.size() - 1, j = T.size() - 1; 
		while (i >= 0 && j >= 0){
			while (i>=0 && S[i] == '#')
				i = max(i - 2, -1); 
			while (j>=0 && T[j] == '#')
				j = max(j - 2, -1); 
			if (i == -1 && j == -1) break; 
			if (i == -1 || j == -1) return false; 
			if (S[i] != T[j])
				return false; 
			--i, --j; 
		}
		return true; 
    }
};


class Solution2 {
public:
	bool backspaceCompare(string S, string T) {
		int cnt1 = 0, cnt2 = 0; 
		int i = S.size() - 1, j = T.size() - 1; 
		while (1){
			while (i >= 0 && S[i] == '#'){
				while (S[i] == '#')
					++cnt1, --i;
				while (cnt1 && S[i] != '#')
					--cnt1, --i;
			}
			while (j >= 0 && T[j] == '#'){
				while (T[j] == '#')
					++cnt2, --j;
				while (cnt2 && T[j] != '#')
					--cnt2, --j;
			}
			i = max(i, -1); 
			j = max(j, -1); 

			if (i==-1 && j==-1) break;
			if (i == -1 || j == -1) return false; 
			if (S[i] != T[j]) return false; 
			--i, --j; 
		}
		return true; 
	}
}; 

class Solution3{
public:
	bool backspaceCompare(string S, string T){
		int cnt1 = 0, cnt2 = 0; 
		int i = S.size() - 1, j = T.size() - 1; 
		while (1){
			while (i >= 0 && (cnt1 > 0 || S[i] == '#')){
				cnt1 += S[i--] == '#' ? 1 : -1; 
			}
			while (j >= 0 && (cnt2 > 0 || T[j] == '#')){
				cnt2 += T[j--] == '#' ? 1 : -1; 
			}
			if (i == -1 && j == -1)return true; 
			if (i == -1 || j == -1) return false;
			if (S[i] != T[j]) return false; 
			--i, --j; 
		}
		return true; 
	}
};


int main(){
	Solution3 a;

	cout << a.backspaceCompare(	"bxj##tw", "bxo#j##tw") << endl; 
	cout << a.backspaceCompare(	"bbbxjtw", "bbb#xjtw") << endl; 
	cout << a.backspaceCompare("a##c", "c#d#") << endl; 
	cout << a.backspaceCompare("ab##", "c#d#") << endl; 


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

