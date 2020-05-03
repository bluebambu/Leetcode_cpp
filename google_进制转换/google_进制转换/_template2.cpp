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
	string convert(string a, int base1, int base2){
		string res; 

		while (a.size() > 0){
			pair<string, string> r = div(a, base1, base2); 
			res = r.first + res; 
			a = r.second; 
		}

		return res; 
	}

	pair<string,string> div(string& a, int base1, int base2){
		string d, m; 
		int curSum = 0; 
		int mod; 
		for (int i = 0; i < a.size(); ++i){
			int cur = c2i(a[i]); 
			curSum = base1*curSum + cur; 
			int quot = curSum / base2; 
			mod = curSum%base2;
			curSum = mod; 
			d.push_back(i2c(quot)); 
		}

		string t = ""; 
		t.push_back(i2c(mod)); 
		m = t; 

		while (d.size() > 0 && d[0] == '0')
			d = d.substr(1); 

		return{m , d }; 
	}

	int c2i(char c){
		if (isdigit(c))
			return c - '0';
		else
			return c - 'A' + 10; 
	}

	char i2c(int i){
		if (i < 10)
			return '0' + i;
		else
			return 'A' + i - 10; 
	}
};

class Solution2 {
public:
	string convert(string a, int base1, int base2){
		string res; 
		while (!a.empty()){
			auto tmp = div(a, base1, base2); 
			res.push_back(i2c(tmp.second)); 
			a = tmp.first; 
		}

		reverse(res.begin(), res.end());
		return res; 
	}

	pair<string, int> div(string a, int base1, int base2){
		string divres; 
		int mod = 0; 
		int middle = 0; 
		for (int i = 0; i < a.size(); ++i){
			int j = i; 
			while (j < a.size()){
				middle = add(middle, a[j], base1); 
				if (middle < base2)
					divres.push_back('0'); 
				else
					break;
				++j; 
			}
			i = j; 

			int cur_r = middle / base2;;
			mod = middle%base2;
			divres.push_back(i2c(cur_r)); 
			middle = mod; 
		}

		int i = 0;
		for (; i < divres.size(); ++i)
			if (divres[i] != '0')
				break;

		return{ divres.substr(i), mod }; 
	}
	

	long long add(long long orig, char c, int base){
		if (isdigit(c))
			return orig*base + c - '0';
		else
			return orig*base + c - 'a' + 10; 
	}

	char i2c(int v){
		if (v < 10)
			return '0' + v;
		else
			return 'a' + v - 10; 
	}

}; 


class Solution3 {
public:
	char i2c(int v){
		if (v < 10)
			return '0' + v;
		else
			return 'a' + v - 10; 
	}
	int c2i(char c){
		if (isdigit(c)) return c - '0'; 
		return c - 'a' + 10; 
	}

	string convert(string a, int base1, int base2){
		string res; 
		while (a != ""){
			auto cur = div(a, base1, base2); 
			cout << cur.first << " " << cur.second << endl; 
			res.push_back(i2c(cur.second)); 
			a = cur.first; 
		}
		reverse(res.begin(), res.end()); 
		return res; 
	}
	pair<string, int> div(string a, int b1, int b2){
		string q; 
		int cur_num = 0;

		for (int i = 0; i < a.size(); ++i){
			cur_num = cur_num*b1 + c2i(a[i]); 
			if (cur_num < b2)
				q.push_back('0'); 
			else{
				q.push_back(i2c(cur_num/b2));
				cur_num = cur_num%b2; 
			}
		}

		int j = 0; 
		while (j < q.size() && q[j] == '0') ++j; 

		return{ q.substr(j), cur_num }; 
	}
};


int main(){
	Solution a; 
	Solution3 a2; 

	cout << a.convert("12345", 6, 8) << endl; 
	cout << "=========\n";
	cout << a2.convert("12345", 6, 8) << endl; 

	vector<int> b = { 4, 1, -9, 0, INT_MAX }; 


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

