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


struct TreeNode {
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
	string rearrangeString(string s, int k) {
		vector<int> cnt(26, 0); 
		for (auto c : s)
			cnt[c - 'a'] += 1; 

		vector<int> lastPos(26, 0); 

		string res = "";
		int len = s.size(); 
		for (int i = 0; i < len; ++i){
			int nxtElem = findNxtElem(cnt, lastPos, i); 
			if (nxtElem == -1)
				return ""; 
			cnt[nxtElem]--; 
			lastPos[nxtElem] = i + k; 
			res.push_back('a' + nxtElem); 
		}
		return res; 
	}

	int findNxtElem(vector<int>& cnt, vector<int>& lastPos, int curPos){
		int nextElem = -1; 
		int maxCnt = -1; 
		for (int i = 0; i < cnt.size(); ++i){
			if (cnt[i]>0 && cnt[i] > maxCnt && lastPos[i] <= curPos){
				maxCnt = cnt[i]; 
				nextElem = i; 
			}
		}
		return nextElem; 
	}
};


// wrong ans
class Solution2 {
public:
	string rearrangeString(string s, int k) {
		unordered_map<char, int> char_cnt, char_pos; 
		for (auto c : s) char_cnt[c] += 1, char_pos[c] = 0;
		vector<pair<char, int>> vec; 
		for (auto& p : char_cnt)	vec.push_back(p);
		sort(vec.begin(), vec.end(), [](pair<char, int>& a, pair<char, int>& b){
			return a.second > b.second; 
		}); 

		string res; 
		while (res.size() < s.size()){
			bool goodstatus = false; 
			for (int i = 0; i < vec.size(); ++i){
				char c = vec[i].first; 
				if (vec[i].second>0 && char_pos[c] <= res.size()){
					res.push_back(c); 
					vec[i].second -= 1; 
					char_pos[c] = res.size() + k-1; 
					goodstatus = true; 
					break;
				}
			}
			if (!goodstatus) return ""; 
		}
		return res;
	}
};


class Solution3 {
public:
	string rearrangeString(string s, int k) {
		unordered_map<char, int> char_cnt; 
		for (auto c : s) char_cnt[c] += 1; 
		
	}
};; 


int main(){
	Solution a; 
	Solution2 a2; 

	cout << a.rearrangeString("aaaabbbbcccefg", 2) << endl; 
	cout << a2.rearrangeString("aabbcc", 2)<<endl; 


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

