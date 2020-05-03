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


class Solution {
public:
	string pushDominoes(string dominoes) {
		if (dominoes.empty())
			return ""; 

		int n = dominoes.size(); 
		vector<int> st(n, -1);
		bool isR = false; 
		int cnt = 0; 
		for (int i = 0; i < n; ++i){
			if (dominoes[i] == 'R'){
				cnt = 1; 
				isR = true; 
				st[i] = cnt; 
			}
			else if (dominoes[i] == '.' && isR){
				cnt += 1; 
				dominoes[i] = 'R'; 
				st[i] = cnt; 
			}
			else
				isR = false; 
		}

		cnt = 0; 
		bool isL = false; 
		for (int i = n - 1; i >= 0; --i){
			if (dominoes[i] == 'L' || isL){
				if (dominoes[i] == 'L'){
					cnt = 0;
					isL = true;
				}

				cnt += 1; 
				dominoes[i] = 'L'; 
				if (i > 0){
					if (cnt == st[i - 1]){
						isL = false; 
						continue;
					}
					if (cnt == st[i - 1] - 1){
						isL = false; 
						dominoes[i - 1] = '.'; 
						continue;
					}
				}
			}
		}

		return dominoes; 
	}
};

// this is a better solution. pass. 
class Solution2 {
public:
	string pushDominoes(string dominoes) {
		dominoes = "L" + dominoes + "R"; 
		char prev = 'L'; 
		int idprev = 0; 
		string res; 
		for (int i = 1; i < dominoes.size(); ++i){
			char c = dominoes[i]; 
			if (c == '.')
				continue;

			if (c == 'L'){
				if (prev == 'L'){
					int cnt = i - idprev; 
					for (; cnt > 0; --cnt) res.push_back('L'); 
				}
				else if (prev == 'R'){
					int cnt = i - idprev; 
					for (int i = 0; i < (cnt-1) / 2; ++i) res.push_back('R');
					if ((cnt-1) % 2 ) res.push_back('.'); 
					for (int i = 0; i < (cnt-1) / 2; ++i) res.push_back('L');
					res.push_back('L'); 
				}
				prev = c; 
				idprev = i; 
			}
			else if (c == 'R'){
				if (prev == 'L'){
					int cnt = i - idprev; 
					for (; cnt > 1; --cnt) res.push_back('.'); 
					res.push_back('R'); 
				}
				else if (prev == 'R'){
					int cnt = i - idprev; 
					for (; cnt > 0; --cnt) res.push_back('R'); 
				}
				prev = c; 
				idprev = i; 
			}
		}

		res.pop_back(); 
		return res; 
	}
}; 

class Solution3 {
public:
	string pushDominoes(string dominoes) {
		dominoes = "L" + dominoes + "R"; 
		int i = 0, j = 1; 
		string res; 
		for (; j < dominoes.size(); ++j){
			if (dominoes[i] == 'L' && dominoes[j] == 'R'){
				res.append(string(j - i-1, '.')); 
				res.push_back('R');
			}
			else if (dominoes[i] == 'L' && dominoes[j] == 'L'){
				res.append(string(j - i-1, 'L'));
				res.push_back('L'); 
			}
			else if (dominoes[i] == 'R'&&dominoes[j] == 'L'){
				int len = j - i - 1; 
				res.append(string(len / 2, 'R')); 
				res.append(string(len % 2, '.')); 
				res.append(string(len / 2, 'L')); 
				res.push_back('L'); 
			}
			else if (dominoes[i] == 'R'&&dominoes[j] == 'R'){
				res.append(string(j-i-1, 'R'));
				res.push_back('R'); 
			}
			if (dominoes[j] != '.')
				i = j;
		}
		res.pop_back(); 
		return res; 
	}
}; 


int main(){
	Solution a; 
	Solution3 a2; 

	cout << a.pushDominoes(".L.R...LR..L..") << endl; 
	cout << a.pushDominoes("RR.L") << endl; 
	cout << a.pushDominoes("RL") << endl; 
	cout << a.pushDominoes(".") << endl; 
	cout << a.pushDominoes("L") << endl; 

	cout << endl << endl; 
	cout << a2.pushDominoes(".L.R...LR..L..") << endl; 
	cout << a2.pushDominoes("RR.L") << endl; 
	cout << a2.pushDominoes("RL") << endl; 
	cout << a2.pushDominoes(".") << endl; 
	cout << a2.pushDominoes("L") << endl; 

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

