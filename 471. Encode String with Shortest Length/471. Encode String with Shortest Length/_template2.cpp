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
	unordered_map<string, string> v; 

	string encode(string s) {
		if (v.count(s))
			return v[s]; 

		string res; 
		pair<int,string> rpts = numOfRepeat(s); 
		if (rpts.first>1){
			string repeatComp = encode(rpts.second); 
			int rptsRealLen = (repeatComp.size() + 2 + to_string(rpts.first).size()); 
			res = rptsRealLen < s.size() ? to_string(rpts.first) + "[" + repeatComp + "]" : s; 
		}
		else{
			res = s; 
		}

		for (int i = 1; i < s.size(); ++i){
			string left = encode(s.substr(0, i)), right = encode(s.substr(i));
			if (left.size() + right.size() < res.size())
				res = left + right; 
		}

		v[s] = res; 
		return res; 
	}

	pair<int, string> numOfRepeat(string s){
		if (s.size() < 2)
			return{ s.size(), s };

		string ss = s + s; 
		int n = s.size(); 
		int i; 
		for (i = 1; i < ss.size(); ++i){
			string sub = ss.substr(i, n); 
			if (sub == s)
				break;
		}

		return{ n / i, s.substr(0, i) };
	}
};

// pass ans
class Solution2 {
public:
	unordered_map<string, string> m; 

	string encode(string s) {
		if (s.size() < 5)
			return s; 

		if (m.count(s))
			return m[s]; 
		
		int len = s.size(); 
		string res = s; ;
		for (int i = 0; i < s.size()-1; ++i){
			string cur = s.substr(0, i + 1); 
			int n = 1, j=i+1; 

			while (1){
				string rest = encode(s.substr(j)); 
				string mid = encode(cur); 
				int curl = n == 1 ? mid.size() + rest.size() : to_string(n).size() + 2 + mid.size() + rest.size(); 
				if (curl < len){
					len = curl; 
					res = n == 1 ? cur + rest : to_string(n) + "[" + mid + "]" + rest; 
				}

				if (j + cur.size() <= s.size() && cur == s.substr(j, cur.size())){
					j += cur.size(); n += 1; 
				}else
					break;
			}
		}
		m[s] = res; 
		return res; 
	}
}; 

// pass, just slow
class Solution3 {
public:
	unordered_map<string, string> m;
	string encode(string s) {
		if (m.count(s))
			return m[s]; 

		int n = s.size(); 
		string res = s;
		int encodeLen = s.size(); 

		// 2[.....] pattern first
		for (int i = 1; i < n; ++i){
			if (n%i == 0){
				int cnt = n / i; 
				string sub = s.substr(0, i); 
				string combined;
				for (int j = 0; j < cnt; ++j) combined += sub;
				if (combined == s){
					string synth = to_string(cnt) + '[' + encode(sub) + ']'; 
					if (synth.size() < encodeLen){
						encodeLen = synth.size(); 
						res = synth; 
					}
				}
			}
		}

		// 2[..]3[..] pattern next. 
		for (int i = 1; i < n; ++i){
			string pre = s.substr(0, i), tail = s.substr(i); 
			string combined = encode(pre) + encode(tail); 
			if (combined.size() < encodeLen){
				encodeLen = combined.size(); 
				res = combined; 
			}
		}

		m[s] = res; 
		return res; 
	}
};



int main(){
	Solution a; 
	Solution3 a2; 

	string s1 = "aabcaabcd",
		s2 = "abbbabbbcabbbabbbc",
		s3 = "aaaaaaaaaabbbaaaaabbb"; 
	cout << a.encode(s3) << endl; 
	cout << a2.encode(s3) << endl;



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

