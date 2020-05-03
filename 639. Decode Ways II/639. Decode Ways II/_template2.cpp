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
//  A message containing letters from A-Z is being encoded to numbers using the following mapping way: 
//  'A' -> 1
//  'B' -> 2
//  ...
//  'Z' -> 26
//  Beyond that, now the encoded string can also contain the character '*', which can be treated as one of the numbers from 1 to 9. 
//  Given the encoded message containing digits and the character '*', return the total number of ways to decode it. 
//  Also, since the answer may be very large, you should return the output mod 109 + 7. 
//  Example 1:
//  Input: "*"
//  Output: 9
//  Explanation: The encoded message can be decoded to the string: "A", "B", "C", "D", "E", "F", "G", "H", "I".

//  Example 2:
//  Input: "1*"
//  Output: 9 + 9 = 18

//  Note:
//  The length of the input string will fit in range [1, 105].
//  The input string will only contain the character '*' and digits '0' - '9'.




// should be correct, but shows RunTime error......  probably recursion explode the stack....... 
// next time use DP to do this. 
class Solution {
public:
	int M; 
	Solution() :M(1000000007) {}

	int numDecodings(string s) {
		unordered_map<string, int> map; 
		unordered_map<int, int> answers; 

		// 1byte string "2" and 2-bytes string "23" should be excluded each other, for example
		// "**" should exclude "AA" case, only contain "Z" ( value > 10 ) like case; 

		// "0*", "01", "06", "60" are all different!!
		map["0"] = 0; 
		for (int i = 1; i <= 9; ++i)
			map[to_string(i)] = 1; 
		map["*"] = 9; 

		for (int i = 1; i <= 9; ++i)
			map[string(1,'0') + to_string(i)] = 0; 
		map["00"] = 0; 
		map["**"] = 15; 
		map["*0"] = 2; 
		for (int i = 1; i <= 6; ++i)
			map[string(1,'*') + to_string(i)] = 2;
		for (int i = 7; i <= 9; ++i)
			map[string(1,'*') + to_string(i)] = 1;
		map["0*"] = 0; 
		map["1*"] = 9; 
		map["2*"] = 6; 
		for (int i = 3; i <= 9; ++i)
			map[to_string(i) + string(1,'*')] = 0;
		
		return rec(s, s.size() - 1, map, answers); 
	}

	int rec(string& s, int n, unordered_map<string, int>& map, unordered_map<int, int>& ans){
		if (n < -1)
			return 0; 
		if (n == -1)
			return 1; 
		if (n == 0)
			return map[string(1,s[n])]; 
		if (ans.count(n))
			return ans[n]; 

		// even though the result will be %M, here p, pp, res still need to be long long !!!!
		long long p = rec(s, n - 1, map, ans); 
		long long pp = rec(s, n - 2, map, ans); 

		long long res = 0; 
		res += p*map[string(1,s[n])]; 

		if (n - 2 >= -1){
			if (s[n] == '*' || s[n - 1] == '*'){
				res += pp * map[string(1,s[n - 1]) + string(1,s[n])]; 
			}
			else{
				res += pp * (stoi(s.substr(n - 1, 2)) > 26 || stoi(s.substr(n - 1, 2)) < 10 ? 0 : 1); 
			}
		}

		res %= M; 
		ans[n] = res; 

		return res; 
	}
};


// pass AC
// it is very recommended to split into 3x3 situations: '0', '*', '1-9'
class Solution2 {
public:
	int M;
	Solution2() :M(1000000007) {}

	int numDecodings(string s) {
		vector<long long> dp(s.size() + 1, 0);
		dp[0] = 1;

		// dp[i] = dp[i-1]*f(i) + dp[i-2]*f(i-1 -> i); 
		for (int i = 1; i < dp.size(); ++i){
			if (s[i - 1] == '0'){
				if (i < 2)
					dp[i] = 0;
				else if (s[i - 2] == '0' || s[i - 2]>'2')
					dp[i] = 0;
				else if (s[i - 2] == '1' || s[i - 2] == '2')
					dp[i] = dp[i - 2];
				else
					dp[i] = 2 * dp[i - 2]; 
			}
			else if (s[i - 1] == '*'){
				if (i < 2)
					dp[i] = 9;
				else if (s[i - 2] == '0')
					dp[i] = dp[i - 1] * 9;
				else if (s[i - 2] == '*')
					dp[i] = dp[i - 1] * 9 + dp[i - 2] * 15;
				else
					dp[i] = dp[i - 1] * 9 + dp[i - 2] * (s[i - 2]>'2' ? 0 : (s[i - 2] == '1' ? 9 : 6)); 
			}
			else{ // s[i-1] == " 1 - 9 "
				if (i < 2)
					dp[i] = 1;
				else if (s[i - 2] == '0')
					dp[i] = dp[i - 1];
				else if (s[i - 2] == '*')
					dp[i] = dp[i - 1] + dp[i - 2] * (s[i - 1]>'6' ? 1 : 2); 
				else {
					dp[i] = dp[i - 1] + dp[i - 2] * (stoi(s.substr(i - 2, 2)) > 26 ? 0 : 1);
				}
			}
			dp[i] %= M; 
		}

		return dp.back(); 
	}
};




int main(){
	Solution2 a;

	vector<int> b = { 7, 2, 5, 10, INT_MAX };

	Solution c; 
	string s = "1003"; 

	cout << a.numDecodings(s)<<endl; 
	cout << c.numDecodings(s)<<endl; 
	//  **********1111111111

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

