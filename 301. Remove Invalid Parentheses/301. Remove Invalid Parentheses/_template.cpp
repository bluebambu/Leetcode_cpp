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
#include <unordered_set>

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

// passed, but very slow, 11.94% cpp， 300ms
class Solution
{
public:
	vector<string> removeInvalidParentheses(string s) {
		queue<string> q; 
		q.push(s); 
		unordered_set<string> visited; 
		bool flag = false; 
		vector<string> res; 

		if (isValid(s)){
			res.push_back(s); 
			return res; 
		}

		while (!q.empty() && !flag){
			int n = q.size(); 

			for (int i = 0; i < n; ++i){
				string cur = q.front(); 
				q.pop(); 

				for (int j = 0; j < cur.size(); ++j){
					string tmp = cur;
					tmp.erase(j,1); 
					if (visited.find(tmp)!=visited.end()) // visited 必须record所有的变形， 而并不是只有valid的变形， 否则 unvalid的变形也会有重复入queue的情况
						continue;; 
					visited.insert(tmp); 

					if (isValid(tmp)){
						flag = true; 
						res.push_back(tmp);  
					}
					else if (!isValid(tmp))
						q.push(tmp); 

					while (j + 1 < cur.size() && cur[j] == cur[j + 1])
						++j; 
				}
			}	
		}
		return res; 
	}

	bool isValid(string& s){
		int cnt = 0; 
		for (int i = 0; i < s.size(); ++i){
			if (s[i] == '(')
				cnt++;
			if (s[i] == ')')
				--cnt; 
			if (cnt < 0)
				return false; 
		}
		return cnt == 0; 
	}

};


// this one is faster, 100ms 
class Solution2 {
public:
	vector<string> removeInvalidParentheses(string s) {
		vector<string> result;
		if (s == ""){
			result.push_back(s);
			return result;
		}
		/*** use the visited to record the visited string ***/
		unordered_set<string> visited;
		/*** use the deque to do the BFS ***/
		deque<string> queue;
		queue.push_back(s);
		visited.insert(s);
		bool found = false;
		while (!queue.empty()){
			string temp = queue.front();
			queue.pop_front();
			if (check(temp)){
				result.push_back(temp);
				found = true;
			}

			/*** if found, stop to increase the level depth ***/
			if (found)  continue;
			for (int i = 0; i < temp.size(); i++){
				if (temp[i] != '(' && temp[i] != ')') continue;
				string str = temp.substr(0, i) + temp.substr(i + 1);
				if (visited.find(str) == visited.end()){
					queue.push_back(str);
					visited.insert(str);
				}
			}
		}
		return result;
	}

	bool check(string s){
		int count = 0;
		for (int i = 0; i < s.size(); i++){
			char c = s[i];
			if (c == '(') count++;
			if (c == ')') {
				if (count == 0)    return false;
				count--;
			}
		}
		return count == 0;
	}
};



// passsAC
class Solution4 {
public:
	vector<string> removeInvalidParentheses(string s) {
		vector<string> res; 
		queue<string> q; 
		unordered_set<string> visited; 
		q.push(s); 
		bool flag = false; 

		while (!q.empty()){
			int sz = q.size(); 
			for (int i = 0; i < sz; ++i){
				string cur = q.front(); 
				q.pop(); 

				if (isValid(cur)){
					res.push_back(cur); 
					flag = true;
				}
				
				for (int j = 0; j < cur.size(); ++j){
					if (cur[j] != '(' && cur[j] != ')')
						continue;
					string next = cur.substr(0, j) + cur.substr(j + 1); 
					if (visited.count(next) == 0){
						visited.insert(next); 
						q.push(next);
					}
				}
			}
			if (flag)
				break;
		}

		return res; 
	}

	bool isValid(string s){
		int left = 0; 
		for (int i = 0; i < s.size(); ++i){
			if (s[i] == '(')
				left += 1;
			else if (s[i] == ')')
				left -= 1; 
			if (left < 0)
				return false;
		}
		return left == 0; 
	}
};


// super solution! dietPepsi
class Solution5 {
public:
	vector<string> res;
	string p; 
	Solution5() :p({ '(', ')' }) {}

	void helper(string& s, int si, int sj, int rev){
		int stn = 0;
		for (int i = si; i < s.size(); i++){
			if (s[i] == p[rev]) stn++;
			else if (s[i] == p[1 - rev]) stn--;
			if (stn < 0){
				for (int j = sj; j <= i; j++){
					if (s[j] == p[1 - rev] && (j == sj || s[j - 1] != p[1 - rev])){
						string t = s.substr(0, j) + s.substr(j + 1);
						helper(t, i, i, rev);
					}
				}
				return;
			}
		}
		string rs = s;
		reverse(rs.begin(), rs.end());
		if (p[rev] == '('){
			helper(rs, 0, 0, 1 - rev);
		}
		else{
			res.push_back(rs);
		}
	}

public:
	vector<string> removeInvalidParentheses(string s) {
		res.clear();
		helper(s, 0, 0, 0);
		return res;
	}
};


// basic dfs, there will be duplicates. 
class Solution6 {
public:
	vector<string> removeInvalidParentheses(string s) {
		vector<string> res; 
		pair<char, char> order({ '(', ')' }); 
		helper(s, order, res);
		return res;
	}

	void helper(string s, pair<char, char> order, vector<string>& res){
		int i = 0, leftCnt = 0; 
		for (; i < s.size(); ++i){
			if (s[i] == order.first)
				++leftCnt;
			else if (s[i] == order.second)
				--leftCnt; 
			if (leftCnt < 0){
				for (int j = 0; j <= i; ++j){
					if (s[j] == order.second && (j == 0 || s[j - 1] != order.second)){
						string next = s.substr(0, j) + s.substr(j + 1); 
						helper(next, order, res); 
					}
				}
				return; 
			}
		}
		string t = s; 
		reverse(t.begin(), t.end());
		if (order.first == '('){
			helper(t, make_pair(')', '('), res);
		}
		else{
			res.push_back(t); 
		}
	}
};

																			  
// passAC
class Solution7 {
public:
	vector<string> removeInvalidParentheses(string s) {
		vector<string> res; 
		helper(s, 0, 0, res, { '(', ')' }); 
		return res; 
	}

	void helper(string& s, int last_i, int last_j, vector<string>& res, vector<char> order){
		int leftCnt = 0; 
		for (int i = 0; i < s.size(); ++i){
			if (s[i] == order[0])
				++leftCnt;
			else if (s[i] == order[1])
				--leftCnt; 
			if (leftCnt < 0){
				for (int j = last_j; j <= i; ++j){
					if (s[j] == order[1] && (j == last_j || s[j - 1] != order[1])){
						string next = s.substr(0, j) + s.substr(j + 1); 
						helper(next, 0, j, res, order); // pass i into it also works!
					}
				}
				return; 
			}
		}
		string t = s; 
		reverse(t.begin(), t.end());
		if (order[0] == '(')
			helper(t, 0, 0, res, { ')', '(' });
		else
			res.push_back(t);
	}
}; 

class Solution8 {
public:
	vector<string> removeInvalidParentheses(string s) {
		vector<string> res; 
		int minLen = -1; 
		bool isFound = false;
		queue<string> q;
		q.push(s);

		while (!q.empty()){
			int sz = q.size();
			for (int k = 0; k < sz; ++k){
				string tmp = q.front();
				q.pop();

				for (int i = 0; i < tmp.size(); ++i){
					string next = tmp.substr(0, i) + tmp.substr(i + 1);
					if (good(next)){
						isFound = true;
						if (minLen == -1)
							minLen = next.size();
						if (next.size() == minLen)
							res.push_back(next);
					}
					q.push(next); 
				}
			}

			if (isFound)
				break;
		}
		return res; 
	}

	bool good(string s){
		int left = 0, right = 0; 
		for (auto i : s){
			if (i == '(')
				++left; 
			if (i == ')')
				++right; 

			if (right > left)
				return false; 
		}
		return left == right; 
	}
};


class Solution9 {
public:
	vector<string> removeInvalidParentheses(string s) {
		queue<string> q; 
		bool finished = false; 
		q.push(s); 

		unordered_set<string> res; 
		while (!q.empty()){
			int sz = q.size(); 
			for (int i = 0; i < sz; ++i){
				string f = q.front(); 
				q.pop(); 

				if (good(f)){
					res.insert(f); 
					finished = true; 
					continue;
				}

				if (finished)
					continue;

				for (int j = 0; j < f.size(); ++j){
					string next = f.substr(0, j) + f.substr(j + 1); 
					q.push(next); 
				}
			}

			if (finished)
				break;
		}

		return vector<string>(res.begin(), res.end()); 
	}

	bool good(string s){
		int cnt = 0; 
		for (int i = 0; i < s.size(); ++i){
			if (s[i] == '(')
				cnt += 1;
			else if (s[i] == ')')
				cnt -= 1; 

			if (cnt < 0)
				return false; 
		}
		return true; 
	}
};


// wrong ans; 
class Solution10 {
public:
	vector<string> removeInvalidParentheses(string s) {
		vector<string> res; 
		dfs(s, res, 0, true); 
		return res; 
	}
	void dfs(string s, vector<string>& res, int i, bool flag){
		// cout << s << endl; 
		int score = 0; 
		vector<int> rpPos; 
		for (; i < s.size(); ++i){
			if (s[i] == '('){
				score += 1;
			}
			else if (s[i] == ')'){
				score -= 1; 
				rpPos.push_back(i); 
			}

			if (score < 0){
				while (!rpPos.empty()){
					int p = rpPos.back(); 
					string striped = s.substr(0, p) + s.substr(p + 1); 
					rpPos.pop_back(); 
					dfs(striped, res, i, flag); 
					while (!rpPos.empty() && rpPos.back() == p - 1){
						rpPos.pop_back(); 
						p -= 1; 
					}
				}
				return; 
			}
		}

		if (score == 0 && flag)
			res.push_back(s); 
		else if(score > 0){
			reverse(s.begin(), s.end()); 
			for (int j = 0; j < s.size(); ++j){
				if (s[j] == '(')
					s[j] = ')';
				else if (s[j] == ')')
					s[j] = '('; 
			}
			dfs(s, res, 0, !flag); 
		}
		else if (!flag){
			reverse(s.begin(), s.end()); 
			for (int j = 0; j < s.size(); ++j){
				if (s[j] == '(')
					s[j] = ')';
				else if (s[j] == ')')
					s[j] = '('; 
			}
			res.push_back(s); 
		}
	}
};


// wrong
class Solution11 {
public:
	vector<string> removeInvalidParentheses(string s) {
		vector<string> res;
		dfs(s, res, 0, true);
		return res;
	}
	void dfs(string s, vector<string>& res, int i, bool flag){
		int score = 0; 
		int orig_i = i; 
		for (; i < s.size(); ++i){
			switch (s[i]){
			case '(': score += 1; break;
			case ')': score -= 1; break;
			}

			if (score < 0){
				for (int j = i; j >= orig_i; --j){
					if (j<i && s[j] == s[j+1])
						continue;
					if (s[j] == ')'){
						string proc = s.substr(0, j) + s.substr(j + 1); 
						dfs(proc, res, j-1, flag); 
					}
				}
				return; 
			}
		}

		string reversed(s.rbegin(), s.rend()); 
		for (int j = 0; j < reversed.size(); ++j){
			switch (reversed[j]){
			case '(':reversed[j] = ')'; break;
			case ')':reversed[j] = '('; break;
			}
		}
		
		if (score == 0 && !flag) res.push_back(reversed); 
		else dfs(reversed, res, 0, !flag); 
	}
};


// pass
class Solution12 {
public:
	vector<string> removeInvalidParentheses(string s) {
		vector<string> res; 
		dfs(s, res, 0, 0, true); 
		return res; 
	}
	void dfs(string s, vector<string>& res, int i, int last_j, bool flag){
		int score = 0; 
		for (; i < s.size(); ++i){
			switch (s[i]){
			case '(': score += 1; break;
			case ')': score -= 1; break;
			}

			if (score < 0){
				for (int j = i; j >= last_j; --j){
					if (j > last_j && s[j] == s[j - 1]) continue;
					if (s[j] == ')'){
						string proc = s.substr(0, j) + s.substr(j + 1); 
						dfs(proc, res, i, j, flag); 
					}
				}
				return; 
			}
		}

		if (score == 0 && flag) res.push_back(s); 
		else{
			string reversed(s.rbegin(), s.rend()); 
			for (int j = 0; j < reversed.size(); ++j){
				switch (reversed[j]){
				case '(':reversed[j] = ')'; break;
				case ')':reversed[j] = '('; break;
				}
			}

			if (score > 0)
				dfs(reversed, res, 0, 0, !flag);
			else
				res.push_back(reversed); 
		}
	}
};


int main() {
	Solution12 a;

	string str = "()))()))";//")()(()))))))(()())()((((" will bloat the memory
	string str2 = ")()(()))))))(()"; 
	string str3 = "(r(()()("; 
	string str4 = "()r)r)"; 

	vector<string> b = a.removeInvalidParentheses(str3); 

	for (string& i : b)
		cout << i << endl;

}

