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


// passed, hashmap, 2 pointers 	 , beats 23% 
// 这道题给我们一个字符串，让我们求最多有两个不同字符的最长子串。那么我们首先想到的是用哈希表来做，
// 哈希表记录每个字符的出现次数，然后如果哈希表中的映射数量超过两个的时候，我们需要删掉一个映射，比
// 如此时哈希表中e有2个，c有1个，此时把b也存入了哈希表，那么就有三对映射了，这时我们的left是0，先从e
// 开始，映射值减1，此时e还有1个，不删除，left自增1。这是哈希表里还有三对映射，此时left是1，那么到c了
// ，映射值减1，此时e映射为0，将e从哈希表中删除，left自增1，然后我们更新结果为i - left + 1，以此类推
// 直至遍历完整个字符串，参见代码如下：
class Solution {
public:
	int lengthOfLongestSubstringTwoDistinct(string s) {
		if (s.size() < 2)
			return s.size();
		unordered_map<char, int> winmap;
		int i = 0, j = 1;
		int res = 0;
		winmap[s[i]]++;
		for (; j < s.size(); ++j){
			if (winmap.find(s[j]) != winmap.end()) { // pre-existed
				winmap[s[j]]++;
			}
			else if (winmap.size() < 2)
				winmap[s[j]]++;
			else{
				while (i < j && winmap.size() == 2){
					winmap[s[i]]--;
					if (winmap[s[i]] == 0)
						winmap.erase(s[i]);
					++i;
				}
				winmap[s[j]]++;
			}
			res = max(res, j - i + 1);
		}
		return res;
	}
};

class Solution2 {
public:
	int lengthOfLongestSubstringTwoDistinct(string s) {
		if (s.size() < 2)
			return s.size(); 
		unordered_map<char, int> charmap; 
		int i = 0, j = 1; 
		int res = 0; 
		charmap[s[i]]=i;

		for (; j < s.size(); ++j){
			if (charmap.find(s[j]) != charmap.end()){
				res = max(res, j - i + 1); 
				charmap[s[j]] = j;
			}
			else if (charmap.size() < 2){
				charmap[s[j]] = j; 
				res = max(res, j - i + 1); 
			}
			else{
				while (i < j && charmap.size() == 2){
					if (i < charmap[s[i]])
						++i;
					else
						charmap.erase(s[i++]); // 这里必须是 i++ , 因为删除 s[i]之后， s[i]不能再留在window里面 
				}
				charmap[s[j]] = j; 
			}
		}
		return res; 
	}
};


class Solution3 {
public:
	string lengthOfLongestSubstringTwoDistinct(string s) {
		unordered_map<char, int> d;

		int i = 0, j = 0, cnt = 0, head, len = INT_MIN;
		while (j < s.size()){
			if (d[s[j]] == 0)
				++cnt;
			++d[s[j]];
			++j;
			while (cnt > 2){
				--d[s[i]];
				if (d[s[i]] == 0)
					cnt -= 1;
				++i;
			}

			if (len < j - i){
				head = i;
				len = j - i;
			}
		}

		return len == INT_MIN ? "" : s.substr(head, len);
	}
};


class Solution4 {
public:
	int lengthOfLongestSubstringTwoDistinct(string s) {
		if (s.size() <= 2)
			return s.size(); 
		unordered_map<char, int> m; 

		int i = 0, j = 0, total = 0, n = s.size(); 
		int head=-1, len=INT_MIN; 
		while (1){
			for (; j < n; ++j){
				char c = s[j]; 
				if (m[c] == 0 && total == 2)
					break;
				if (m[c] == 0){
					++total; 
				}
				++m[c]; 
				if (len < j - i + 1){
					len = j - i + 1; 
					head = i; 
				}
			}
			if (j==n) break;

			for (; i < j; ++i){
				if (total == 1){
					break;
				}
				char c = s[i]; 
				m[c]--; 
				if (m[c] == 0)
					--total; 
			}
		}

		return head == -1 ? 0 : len; 
	}
};

class Solution5 {
public:
	int lengthOfLongestSubstringTwoDistinct(string s) {
		if (s.size() < 2)
			return s.size(); 
		unordered_map<char, int> m; 

		int i = 0, j = 0, total = 0, head = -1, len = 0, n = s.size(); 
		while (1){
			for (; j < n; ++j){
				char c = s[j]; 
				if (m[c] == 0 && total == 2)
					break;
				if (m[c] == 0)
					++total; 
				m[c] += 1; 
				len = max(len, j - i + 1); 
			}
			if (j == n) return len; 

			for (; i < j; ++i){
				char c = s[i]; 
				if (total==1)
					break;
				m[c] -= 1; 
				if (m[c] == 0)
					--total; 
			}
		}

		return len; 
	}
}; 

class Solution6 {
public:
	int lengthOfLongestSubstringTwoDistinct(string s) {
		unordered_map<char, int> m; 

		int i = 0, j = 0, total = 0, len = 0, n = s.size(); 
		while (1){
			for (; j < n; ++j){
				char c = s[j]; 
				if (total==2 && m[c]==0)
					break;
				if (m[c] == 0)
					++total; 
				m[c] += 1; 
				len = max(len, j - i + 1); 
			}

			for (; i < j; ++i){
				if (total==1)
					break;
				char c = s[i]; 
				m[c] -= 1; 
				if (m[c] == 0)
					--total; 
			}

			if (j == n) return len; 
		}
		return len; 
	}
}; 

int main() {
	Solution3 a; 
	Solution6 a2; 
	string b = "ecebeeecccca";
	string bb = "ccccccccccccccccc";
	string bbb = "aac";
	cout << a.lengthOfLongestSubstringTwoDistinct(b)<< endl; 
	cout << a2.lengthOfLongestSubstringTwoDistinct(b)<< endl; 
}

