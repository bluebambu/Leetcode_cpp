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
		cout << i << endl;
	cout << endl;
}

template <typename C>
void mapprt(C v){
	for (auto i : v)
		cout << i.first << " " << i.second << endl;
	cout << endl;
}
////////////////////////////////////////////////////////////////
// Given a string that contains only digits 0 - 9 and a target value, return all possibilities to add binary operators(not unary) + , -, or * between the digits so they evaluate to the target value.
// Examples:
// "123", 6 ->["1+2+3", "1*2*3"]
// "232", 8 ->["2*3+2", "2+3*2"]
// "105", 5 ->["1*0+5", "10-5"]
// "00", 0 ->["0+0", "0-0", "0*0"]
// "3456237490", 9191 ->[]


// Hard to process cases: "1+23*45"!!
// this solution should be very slow..... Speeding by string.str() to get chunk of numbers;
// failed, too complicated!!!! 
class Solution2 {
public:
	vector<string> addOperators(string num, int target) {
		vector<string> res; 
		if (num == "")
			return res; 

		string tmp; 
		tmp.push_back(num[0]);
		int vtmp = num[0] - '0'; 

		dfs(num, 1, target, tmp, vtmp, res, "", vtmp); 
		return res; 
	}

	void dfs(string& str, 
		int idx, 
		int target,
		string tmp, 
		int vtmp, 
		vector<string>& res,  
		string lastOp, 
		int lastNum
		){
		if (idx == str.size() && vtmp == target){
			res.push_back(tmp);
			return; 
		}

		if (idx == str.size() && vtmp != target){
			return; 
		}

		char scur = str[idx]; 
		int vcur = scur - '0';

		dfs(str, idx + 1, target, tmp + "+" + scur, vtmp + vcur, res, "+", vcur);
		dfs(str, idx + 1, target, tmp + "-" + scur, vtmp - vcur, res, "-", vcur);

		if (lastOp == "+"){
			dfs(str, idx + 1, target, tmp + "*" + scur, vtmp - lastNum + (vcur - 1)*lastNum, res, lastOp, lastNum*vcur);
			if (lastNum != 0);
				//dfs(str, idx+1, target, tmp+scur, )
		}
	}
};


// std solution. Pass AC. 
class Solution {
public:
	vector<string> addOperators(string num, int target) {
		int n = num.size(); 
		vector<string> res; 

		// 第一个substr， i是长度！
		for (int i = 1; i <= n; ++i){
			// 第一个 substr 也要查 0 
			if (i > 1 && num[0] == '0')
				continue;
			string head = num.substr(0, i);
			// first operator can be regarded as "+" !!!
			dfs(num, i, target, res, head, stoll(head), "+", stoll(head));
		}
		return res; 
	}

	// long long vtmp & last Val!!! 因为是中间算出来的值，有可能比 int target 大， 可能出界
	void dfs(string& num, int i, long long target, vector<string>& res, string stmp, long long vtmp, string lastOp, long long lastVal){
		if (i == num.size() && vtmp == target){
			res.push_back(stmp);
			return;
		}
		// close dfs.
		if (i == num.size())
			return; 

		for (int j = 0; i + j < num.size(); ++j){
			// substr head is not 0xxx. 
			if (j > 0 && num[i] == '0')
				return; 

			string scur = num.substr(i, j + 1);
			auto icur = stoll(scur); 

			dfs(num, i + j + 1, target, res, stmp + "+" + scur, vtmp + icur, "+", icur);
			dfs(num, i + j + 1, target, res, stmp + "-" + scur, vtmp - icur, "-", icur);
			if (lastOp == "+")
				dfs(num, i + j + 1, target, res, stmp + "*" + scur, vtmp + (icur-1)*lastVal, lastOp, icur*lastVal);
			else if (lastOp == "-")
				dfs(num, i + j + 1, target, res, stmp + "*" + scur, vtmp - (icur-1)*lastVal, lastOp, icur*lastVal);
		}
	}
};




class Solution3 {
public:
	vector<string> addOperators(string num, int target) {
		// 12-3*45*23-023*23*23
		vector<string> res; 
		dfs(num, 0, target, "", 0, 0, '+', res); 

		return res; 
	}

	void dfs( string num, int cur, int target, string path, long long vpath, int lastNum, char lastOp, vector<string>& res ){
		if (cur == num.size()){
			if (vpath == target)
				res.push_back(path); 
			return; 
		}
		
		for (int i = cur; i < num.size(); ++i){
			string left = num.substr(cur, i - cur + 1), right = num.substr(i + 1); 
			if (left.size()>1 && left[0] == '0')
				continue;

			long long lnum = stol(left); 

			if (cur==0)
				dfs(num, i + 1, target, path + left, vpath + lnum, lnum, '+', res);

			if (cur>0){
				dfs(num, i + 1, target, path + "+" + left, vpath + lnum, lnum, '+', res);
				dfs(num, i + 1, target, path + "-" + left, vpath - lnum, lnum, '-', res);
				if (lastOp == '+')
					dfs(num, i + 1, target, path + "*" + left, vpath + (lnum - 1)*lastNum, lastNum*lnum, '+', res);
				else if (lastOp == '-'){
					dfs(num, i + 1, target, path + "*" + left, vpath - (lnum - 1)*lastNum, lastNum*lnum, '-', res);
				}
			}
		}
	}
};



vector<vector<int>> dirs{ { 0, -1 }, { 0, 1 }, { 1, 0 }, { -1, 0 } };
typedef pair<int, int> PII;


// my own solution, not that perfect
class Solution4 {
public:
	vector<string> addOperators(string num, int target) {
		vector<string> res;
		dfs(num, 0, '+', 0, 0, "", target, res);
		return res;
	}

	void dfs(string str, int id, char op, long long tot, long long pre, string path, int target, vector<string>& res){
		if (id == str.size()){
			if (tot == target)
				res.push_back(path.substr(1));
			return;
		}

		for (int i = id + 1; i <= str.size(); ++i){
			if (str[id] == '0' && i > id + 1)
				return;

			string cur = str.substr(id, i - id);
			long long num = stoll(cur);
			long long curTot = tot;
			long long curPre = pre;

			switch (op){
			case '+': curTot += num; curPre = num; break;
			case '-': curTot -= num; curPre = -num; break;
			case '*': curTot += (num - 1)*curPre; curPre *= num; break;
			}

			string curPath = path + op + cur;

			// must be here, otherwise result will be multiply 3 times. 
			if (i == str.size()) {
				if (curTot == target){
					res.push_back(curPath.substr(1));
				}
				return;
			}

			dfs(str, i, '+', curTot, curPre, curPath, target, res);
			dfs(str, i, '-', curTot, curPre, curPath, target, res);
			dfs(str, i, '*', curTot, curPre, curPath, target, res);
		}
	}
};


// best solution
class Solution5 {
public:
	vector<string> addOperators(string num, int target) {
		vector<string> res;
		dfs(num, 0, 0, 0, "", target, res);
		return res;
	}

	void dfs(string& num, int i, long long pre, long long tot, string path, int target, vector<string>& res){
		if (i == num.size()){
			if (tot == target)
				res.push_back(path);
			return;
		}

		for (int j = i; j < num.size(); ++j){
			if (j > i && num[i] == '0')
				return;

			string cur = num.substr(i, j - i + 1);
			long long curV = stoll(cur);

			if (i == 0)
				dfs(num, j + 1, curV, curV, cur, target, res);
			else{
				dfs(num, j + 1, curV, tot + curV, path + '+' + cur, target, res);
				dfs(num, j + 1, -curV, tot - curV, path + '-' + cur, target, res);
				dfs(num, j + 1, pre*curV, tot + (curV - 1)*pre, path + '*' + cur, target, res);
			}
		}
	}
};


class Solution6 {
public:
	vector<string> addOperators(string num, int target) {
		vector<string> res; 
		dfs(num, 0, "", 0, 0, target, res);
		return res; 
	}

	void dfs(string& num, int i, string path, long long pre, long long tot, int target, vector<string>& res){
		if (i == num.size()){
			if (tot == target)
				res.push_back(path); 
			return; 
		}

		for (int j = i; j < num.size(); ++j){
			string cur = num.substr(i, j - i + 1); 
			long long c = stoll(cur); 

			if (i == 0)
				dfs(num, j + 1, cur, c, c, target, res); 
			else{
				dfs(num, j + 1, path + "+" + cur, c, tot + c, target, res); 
				dfs(num, j + 1, path + "-" + cur, -c, tot - c, target, res);
				dfs(num, j + 1, path + "*" + cur, pre*c, tot + (c - 1)*pre, target, res); 
			}
		}
	}
};


class Solution7 {
public:
	vector<string> addOperators(string num, int target) {
		vector<string> res; 
		process(num, 0, target, 0, 0, "", res); 
		return res; 
	}

	void process(string& num, int i, int target, int sum, int last, string path, vector<string>& res){
		if (i == num.size()){
			if (sum == target){
				res.push_back(path); 
			}
			return; 
		}

		for (int j = i + 1; j <= num.size(); ++j){
			string sub = num.substr(i, j - i); 
			int cur = stoll(sub); 
			if (i == 0){
				process(num, j, target + cur, cur, path + "+" + sub, res); 
			}
			else{
				process(num, j, target + cur, cur, path + "+" + sub, res); 
				process(num, j, target - cur, -1*cur, path + "-" + sub, res); 
				process(num, j, target + last*(cur-1), last*cur, path + "*" + sub, res); 
			}
		}
	}
};


int main() {
	Solution6 a;

	string b = "3456237490";

	vector<string> c = a.addOperators(b, 97); 

	for (auto i : c)
		cout << i << endl; 

	//set<string> v1(c.begin(), c.end()); 
	// { "1+2+3+4+5+6+7+8+9", "1+2+3+4+5-6*7+8*9", "1+2+3+4-5+67-8*9", "1+2+3+4-5*6+7*8+9", "1+2+3+4-5*6-7+8*9", "1+2+3-4*5+6*7+8+9", "1+2+3-4*5-6+7*8+9", "1+2+3-4*5-6-7+8*9", "1+2+3*4+5+6*7-8-9", "1+2+3*4*5+6*7-8*9", "1+2+3*4*5-6-7-8-9", "1+2+34-5-6-7+8-9", "1+2-3+4*5+6*7-8-9", "1+2-3+45+6-7-8+9", "1+2-3+45-6+7+8-9", "1+2-3-4-5*6+7+8*9", "1+2-3-45-6+7*8*9", "1+2-3*4+5*6+7+8+9", "1+2-3*4+56+7+8*9", "1+2-3*4-5+6*7+8+9", "1+2-3*4-5-6+7*8+9", "1+2-3*4-5-6-7+8*9", "1+2-3*4*5-6+7*8*9", "1+2-34+5+6+7*8+9", "1+2-34+5+6-7+8*9", "1+2*3+4*5-6+7+8+9", "1+2*3*4+5+6+7+8-9", "1+2*3*4-5*6+7*8-9", "1+2*34+5+67-8*9", "1+23*4+5*6-78-9", "1-2+3+4*5*6-78-9", "1-2+3*4*5+6-7*8*9", "1-2+34+5+6-7+8+9", "1-2-3+4+5+67-8*9", "1-2-3+45+67-8*9", "1-2-3*4+5+6+7*8-9", "1-2-34-5+6+7+8*9", "1-2*3+4+5+6*7+8-9", "1-2*3+4+5-6+7*8-9", "1-2*3+4*5+6+7+8+9", "1-2*3+4*5-6*7+8*9", "1-2*3-4+5*6+7+8+9", "1-2*3-4+56+7+8*9", "1-2*3-4-5+6*7+8+9", "1-2*3-4-5-6+7*8+9", "1-2*3-4-5-6-7+8*9", "1-2*3-45+67*8+9", "1-2*34+5+67-8*9", "1-23-4+5*6*7+8+9", "1*2+3+4+5*6+7+8-9", "1*2+3+4-5+6*7+8-9", "1*2+3+4-5-6+7*8-9", "1*2+3+45-67+8+9", "1*2+3-45+6+7+8*9", "1*2+3*4*5-6*7+8+9", "1*2+34+5-6-7+8-9", "1*2+34-5+6+7-8-9", "1*2+34-56+7*8-9", "1*2-3+4*5*6-78+9", "1*2-3*4*5+67*8+9", "1*2-34+5*6+7*8-9", "1*2-34*5+6*7-89", "1*2*3+4+5+6+7+8+9", "1*2*3+4+5-6*7+8*9", "1*2*3+4-5+67-8*9", "1*2*3+4-5*6+7*8+9", "1*2*3+4-5*6-7+8*9", "1*2*3-4*5+6*7+8+9", "1*2*3-4*5-6+7*8+9", "1*2*3-4*5-6-7+8*9", "1*2*3*4+5+6-7+8+9", "1*2*3*4*5-6-78+9", "1*2*34-5+6-7-8-9", "1*23+4*5-6+7-8+9", "12+3*4+5+6-7+8+9", "12+3*4*5-6-78+9", "12+34+5-6*7-8*9", "12+34-5*6-7-8*9", "12-3+4*5+6-7+8+9", "12-3+45+6-7-89", "12-3-4+5*6-7+8+9", "12-3-4-56+7*8*9", "12-3*4+5+67-8*9", "12*3+4+5+6-7-8+9", "12*3+4+5-6+7+8-9", "12*3-4-5-6+7+8+9", "12*3*4-5*6-78+9" };

	//set<string> v2 = { "1*2*3*4*5-6-78+9", "1*2*3*4+5+6-7+8+9", "1*2*3+4+5+6+7+8+9", "1*2*3+4+5-6*7+8*9", "1*2*3+4-5*6+7*8+9", "1*2*3+4-5*6-7+8*9", "1*2*3-4*5+6*7+8+9", "1*2*3-4*5-6+7*8+9", "1*2*3-4*5-6-7+8*9", "1*2*3-45+67+8+9", "1*2*34+56-7-8*9", "1*2*34-5+6-7-8-9", "1*2+3*4-56+78+9", "1*2+3+4+5*6+7+8-9", "1*2+3+4-5+6*7+8-9", "1*2+3+4-5-6+7*8-9", "1*2+3+45+67-8*9", "1*2+3-45+6+7+8*9", "1*2+34+5-6-7+8+9", "1*2+34+56-7*8+9", "1*2+34-5+6+7-8+9", "1*2+34-56+7*8+9", "1*2+34-56-7+8*9", "1*2-3*4+5+67-8-9", "1*2-3+4-5-6*7+89", "1*2-3-4*5+67+8-9", "1*2-3-4+56-7-8+9", "1*2-34+5*6+7*8-9", "1*23+4*5-6+7-8+9", "1*23-4-56-7+89", "1+2*3*4*5+6+7-89", "1+2*3*4+5*6+7-8-9", "1+2*3*4-5+6*7-8-9", "1+2*3+4*5*6+7-89", "1+2*3+4*5-6+7+8+9", "1+2*3-4-5-6*7+89", "1+2*34-5*6+7+8-9", "1+2+3*4*5+6-7-8-9", "1+2+3*4+5+6*7-8-9", "1+2+3*45-6-78-9", "1+2+3+4+5+6+7+8+9", "1+2+3+4+5-6*7+8*9", "1+2+3+4-5*6+7*8+9", "1+2+3+4-5*6-7+8*9", "1+2+3-4*5+6*7+8+9", "1+2+3-4*5-6+7*8+9", "1+2+3-4*5-6-7+8*9", "1+2+3-45+67+8+9", "1+2-3*4*5+6+7+89", "1+2-3*4+5*6+7+8+9", "1+2-3*4-5+6*7+8+9", "1+2-3*4-5-6+7*8+9", "1+2-3*4-5-6-7+8*9", "1+2-3+4*5+6*7-8-9", "1+2-3+45+6-7-8+9", "1+2-3+45-6+7+8-9", "1+2-3-4-5*6+7+8*9", "1+2-3-45-6+7+89", "1+2-34+5+6+7*8+9", "1+2-34+5+6-7+8*9", "1+2-34-5-6+78+9", "1+23*4+5-6-7*8+9", "1+23*4-5-6*7+8-9", "1+23*4-56+7-8+9", "1+23+4+5+6+7+8-9", "1+23+4-5*6+7*8-9", "1+23+4-5-67+89", "1+23-4*5+6*7+8-9", "1+23-4*5-6+7*8-9", "1+23-4-5+6+7+8+9", "1+23-4-5-6*7+8*9", "1+23-45+67+8-9", "1-2*3*4+5-6+78-9", "1-2*3*4-5-6+7+8*9", "1-2*3+4*5+6+7+8+9", "1-2*3+4*5-6*7+8*9", "1-2*3+4+5+6*7+8-9", "1-2*3+4+5-6+7*8-9", "1-2*3+4+56+7-8-9", "1-2*3+45-67+8*9", "1-2*3-4+5*6+7+8+9", "1-2*3-4-5+6*7+8+9", "1-2*3-4-5-6+7*8+9", "1-2*3-4-5-6-7+8*9", "1-2*34+5*6-7+89", "1-2+3*4*5-6-7+8-9", "1-2+3+4-5*6+78-9", "1-2+3+45+6-7+8-9", "1-2+3-4*5-6+78-9", "1-2+3-45+6-7+89", "1-2-3*4+5+6+7*8-9", "1-2-3*4-5-6+78-9", "1-2-3+4-5+67-8-9", "1-2-3+45-6-7+8+9", "1-2-34+5+6+78-9", "1-2-34+56+7+8+9", "1-2-34-5+6+7+8*9", "1-23*4+5+6*7+89", "1-23+4*5-6*7+89", "1-23+4-5+67-8+9", "1-23+45-67+89", "1-23-4+5+67+8-9", "1-23-4-5-6-7+89", "12*3*4-5*6-78+9", "12*3+4+5+6-7-8+9", "12*3+4+5-6+7+8-9", "12*3-4-5-6+7+8+9", "12*3-4-56+78-9", "12+3*4+5+6-7+8+9", "12+3*45-6-7-89", "12+3+4-56-7+89", "12+3-4*5+67-8-9", "12+3-45+6+78-9", "12+34-5-6-7+8+9", "12-3*4*5+6+78+9", "12-3*4-5+67-8-9", "12-3+4*5+6-7+8+9", "12-3+4+56-7-8-9", "12-3-4+5*6-7+8+9", "12-3-4-56+7+89", "12-3-45-6+78+9" };

	//cout << endl << "================\n"; 
	//cout << c.size() << "  --  " << v2.size() << endl; 
	//cout << endl << "================\n"; 
	//for (auto i : v1){
	//	if (v2.count(i) == 0)
	//		cout << i << endl;
	//}
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

