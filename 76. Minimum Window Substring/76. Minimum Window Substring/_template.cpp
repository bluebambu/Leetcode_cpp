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


//////////////////////////////////////////////////////////////////////////
// Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

// For example,
// S = "ADOBECODEBANC"
// T = "ABC"
// Minimum window is "BANC".

// Note:
// If there is no such window in S that covers all characters in T, return the empty string "".

// If there are multiple such windows, you are guaranteed that there will always be only one unique minimum window in S.



// pass AC
// Key point: map<char, int> and int count together to determine the expanding end. 
// the skill to use while() loop to perform two pointers strat. 
// not easy to do! 

class Solution {
public:
	string minWindow(string s, string t) {
		if (s.size() < t.size())
			return "";
		unordered_map<char, int> m; 

		for (int i = 0; i < t.size(); ++i)
			++m[t[i]]; 

		int i = 0, j = 0, count = 0, minlen = s.size(); 
		string res; 

		while (j < s.size()){
			if (m.count(s[j]) == 0){
				++j;
				continue;
			}

			--m[s[j]]; 
			if (m[s[j]] >= 0) ++count; 

			while (count == t.size() && i<=j){
				if (m.count(s[i]) != 0){
					if (j - i + 1 <= minlen){
						minlen = j - i + 1; 
						res = s.substr(i, minlen);
					}

					++m[s[i]]; 
					if (m[s[i]] > 0) --count; 
				}
				++i; 
			}

			++j;
		}

		return res; 
	}
};



class Solution2 {
public:
	string minWindow(string s, string t) {
		unordered_map<char, int> d; 
		for (auto i : t)
			d[i] += 1; 
		unordered_map<char, int> stat; 

		// [i, j], cnt, 
		int i = 0, j = 0, cnt = d.size(); 
		char misschar; 
		vector<int> res({ -1, int(s.size())}); 
		while (i < s.size()){
			while (i < s.size() && cnt >0 ){
				if (d.count(s[i]))
					d[s[i]] -= 1; 
				if (d.count(s[i]) && d[s[i]] == 0)
					cnt -= 1; 
				++i; 
			}
			--i; 
			if (cnt==0)
				res = ((res[1] - res[0]) > i - j) ? vector<int>({ j, i }) : res;
			else 
				break;

			while (j <= i && cnt == 0){
				if (d.count(s[j]))
					d[s[j]] += 1; 
				if (d.count(s[j]) && d[s[j]] > 0)
					cnt += 1; 
				++j;
			}

			if (cnt>0)
				res = ((res[1] - res[0]) > i - j + 1) ? vector<int>({ j - 1, i }) : res;
			else
				break;

			++i; 
		}

		return res[0]==-1 ? "" : s.substr(res[0], res[1] - res[0] + 1); 
	}
}; 

// wrong ans
class Solution3 {
public:
	string minWindow(string s, string t) {
		// [ , ) 
		unordered_map<char, int> d; 
		for (auto i : t) d[i] += 1; 

		int i = 0, j = 0, cnt = t.size(), head = 0, l = INT_MAX; 
		while (j < s.size()){
			if (d[s[j]] > 0){
				cnt -= 1; 
			}
			d[s[j]] -= 1;
			++j; 
			while (cnt == 0){
				if (l > j - i){
					head = i; 
					l = j - i; 
				}
				if (d[s[i]] == 0){
					cnt++; 
				}
				d[s[i]]++;
				++i; 
			}
		}
		return l == INT_MAX ? "" : s.substr(head, l); 
	}
}; 


class Solution4 {
public:
	string minWindow(string s, string t) {
		unordered_map<char, int> d; 
		for (auto i : t) d[i] += 1; 

		int i = 0, j = 0, cnt = t.size(), len = INT_MAX, head; 
		while (j < s.size()){
			if (d.count(s[j])){
				if (d[s[j]]>0)
					cnt -= 1;
				d[s[j]] -= 1; 
			}
			++j; 
			while (cnt == 0){
				if (len > j - i){
					head = i; 
					len = j - i; 
				}
				if (d.count(s[i])){
					d[s[i]] += 1; 
					if (d[s[i]]>0)
						cnt += 1;
				}
				++i; 
			}
		}
		return len == INT_MAX ? "" : s.substr(head, len); 
	}
}; 


class Solution5 {
public:
	string minWindow(string s, string t) {
		unordered_map<char, int> d; 
		for (auto i : t) d[i]++; 

		int i = 0, j = 0, cnt = t.size(), head, len = INT_MAX; 
		while (j < s.size()){
			if (d[s[j]] > 0){
				cnt -= 1;
			}
			d[s[j]] -= 1; 
			++j; 
			while (cnt == 0){
				if (len > j - i){
					head = i; 
					len = j - i; 
				}
				d[s[i]]++; 
				if (d[s[i]] > 0)
					++cnt; 
				++i; 
			}
		}

		return len == INT_MAX ? "" : s.substr(head, len); 
	}
}; 

class Solution6 {
public:
	string minWindow(string s, string t) {
		unordered_map<char, int> m; 
		for (auto c : t)
			m[c] += 1; 

		int i = 0, j = 0, n = s.size(), total = m.size(); 
		int head=-1, len=INT_MAX; 
		while (1){
			for (; j < n; ++j){
				char c = s[j]; 
				if (m.count(c)){
					if ((--m[c]) == 0){
						if ((--total) == 0){
							// this part is not necessary!!!!
							//if (len > j - i + 1){
							//	len = j - i + 1; 
							//	head = i; 
							//}
							break;
						}
					}
				}
			}
			if (j == n) break;

			for (; i <= j; ++i){
				char c = s[i]; 
				if (m.count(c)){
					if ((m[c]++) == 0){
						total += 1; 
						if (len > j - i + 1){
							len = j - i + 1;
							head = i;
						}
						++i, ++j; 
						break;
					}
				}
			}
		}
		
		return head == -1 ? "" : s.substr(head, len);
	}
}; 


// this is wrong ans!!!!!
class Solution7 {
public:
	string minWindow(string s, string t) {
		unordered_map<char, int> m; 
		for (auto& c : t) m[c] += 1; 

		int i = 0, j = 0, head = -1, len = INT_MAX, n = s.size(); 
		int total = m.size(); 
		while (1){
			while (j < n){
				char c = s[j]; 
				if (m.count(c)){
					m[c] -= 1; 
					++j; // keep [ , ) range 
					if (m[c] == 0){
						total -= 1; 
						if (total == 0 && len>j-i){
							break; 
						}
					}
				}
				else
					++j; 
			}

			while (i < j){
				char c = s[i]; 
				if (m.count(c)){
					if (m[c]==0 && total==0){
						total += 1; 
						m[c] += 1;
						if (len > j - i){
							head = i; 
							len = j - i; 
							++i;
							break; 
						}
					}
					m[c] += 1; 
				}
				++i;
			}

			if (j==n) break;
		}

		return head == -1 ? "" : s.substr(head, len);
	}

}; 


// pass
class Solution8 {
public:
	string minWindow(string s, string t) {
		unordered_map<char, int> m; 
		for (auto c : t) m[c] += 1; 

		int i = 0, j = 0, head = -1, len = INT_MAX, total = m.size(), n = s.size(); 
		while (1){
			for (; j < n; ++j){
				char c = s[j]; 
				if (total == 0)
					break;
				if (m.count(c)){
					m[c] -= 1;
					if (m[c] == 0)
						total -= 1;
				}
			}

			for (; i < j; ++i){
				char c = s[i]; 
				if (m.count(c)){
					if (m[c] == 0){
						if (total==0 && len > j - i){
							len = j - i;
							head = i;
						}
						++i;
						m[c] += 1; 
						total += 1; 
						break;
					}
					m[c] += 1;
				}
			}

			if (j==n) break;
		}

		return head == -1 ? "" : s.substr(head, len);
	}
}; 

int main() {
	Solution5 a; 
	Solution8 a2; 

	string S = "ab"; 
	string T = "b"; 
	string S2 = "ADOBECODEBANC"; 
	string T2 = "ABC";

	cout << a.minWindow(S, T) << endl; 
	cout << a2.minWindow(S, T) << endl; 
	cout << a.minWindow(S2, T2) << endl; 
	cout << a2.minWindow(S2, T2) << endl; 
	cout << a.minWindow("a", "ab") << endl; 
	cout << a2.minWindow("a", "ab") << endl; 


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

