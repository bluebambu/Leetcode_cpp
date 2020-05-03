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
// ����������һ���ַ������������������������ͬ�ַ�����Ӵ�����ô���������뵽�����ù�ϣ��������
// ��ϣ���¼ÿ���ַ��ĳ��ִ�����Ȼ�������ϣ���е�ӳ����������������ʱ��������Ҫɾ��һ��ӳ�䣬��
// ���ʱ��ϣ����e��2����c��1������ʱ��bҲ�����˹�ϣ����ô��������ӳ���ˣ���ʱ���ǵ�left��0���ȴ�e
// ��ʼ��ӳ��ֵ��1����ʱe����1������ɾ����left����1�����ǹ�ϣ���ﻹ������ӳ�䣬��ʱleft��1����ô��c��
// ��ӳ��ֵ��1����ʱeӳ��Ϊ0����e�ӹ�ϣ����ɾ����left����1��Ȼ�����Ǹ��½��Ϊi - left + 1���Դ�����
// ֱ�������������ַ������μ��������£�
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
						charmap.erase(s[i++]); // ��������� i++ , ��Ϊɾ�� s[i]֮�� s[i]����������window���� 
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

