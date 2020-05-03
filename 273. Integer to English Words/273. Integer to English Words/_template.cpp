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
		cout << i << " ";
	cout << endl;
}

template <typename C>
void mapprt(C v){
	for (auto i : v)
		cout << i.first << " " << i.second << endl;
	cout << endl;
}
////////////////////////////////////////////////////////////////
// 
// Pick One


// Convert a non - negative integer to its english words representation.Given input is guaranteed to be less than 231 - 1.
// For example,
// 123 -> "One Hundred Twenty Three"
// 12345 -> "Twelve Thousand Three Hundred Forty Five"
// 1234567 -> "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"


vector<string> v1 = { "", "thousand", "million", "billion" },
v2 = { "", "one", "two", "three", "four" },
v3 = { "twenty", "thirty", "forty" };

class Solution {
public:
	string procBlwThnd(int n){
		if (n >= 1000)
			return "Wrong number > 1000!\n"; 

		string hundr = v2[n / 100] + " hundred "; 
		n %= 100; 
		
		if (n < 20)
			return hundr + v2[n];
		else{
			string tens = v3[n / 10]; 
			string dec = v2[n % 10]; 
			return hundr + tens + dec; 
		}
	}

	string numberToWords(int num) {
		string res; 
		int thnds = 0; 
		
		while (num > 0){
			int blw_thnd = num % 1000; 

			res = procBlwThnd(blw_thnd) + v1[thnds] + res; 

			num /= 1000;

			thnds += 1; 
		}
	}
};

// not fully right
class Solution2 {
public:
	string numberToWords(int num) {
		if (!num) return ""; 

		map<int, string> n_str; 
		n_str[1000000000] = "Billion"; 
		n_str[1000000] = "Million"; 
		n_str[1000] = "Thousand"; 
		n_str[100] = "Hundred"; 
		n_str[90] = "Ninety"; 
		n_str[80] = "Eighty"; 
		n_str[70] = "Seventy"; 
		n_str[60] = "Sixty"; 
		n_str[50] = "Fifty"; 
		n_str[40] = "Forty"; 
		n_str[30] = "Thirty"; 
		n_str[20] = "Twenty"; 
		n_str[10] = "Ten"; 
		n_str[9] = "Nine"; 
		n_str[8] = "Eight"; 
		n_str[7] = "Seven"; 
		n_str[6] = "Six"; 
		n_str[5] = "Five"; 
		n_str[4] = "Four"; 
		n_str[3] = "Three"; 
		n_str[2] = "Two"; 
		n_str[1] = "One"; 

		return decode(num, n_str); 
	}

	string decode(int num, map<int, string>& n_str){
		if (!num) return ""; 
		if (n_str.count(num)) return n_str[num]; 

		for (auto iter = n_str.rbegin(); iter != n_str.rend(); ++iter){
			auto p = *iter; 
			int scale = p.first; 
			if (num < scale) continue;

			int div = num / scale, mod = num%scale; 
			string res = (div == 1 ? "" : decode(div, n_str)) + " " + p.second + " " + decode(mod, n_str);
			return res; 
		}

		return ""; 
	}
}; 


vector<string> thousands = { " ", "Thousand ", "Million ", "Billion " },
below_100 = { " ", " ", "Twenty ", "Thirty ", "Forty ", "Fifty ", "Sixty ", "Seventy ", "Eighty ", "Ninety " },
below_20 = { 
	" ", "One ", "Two ", "Three ", "Four ", "Five ", "Six ", "Seven ", "Eight ", "Nine ", 
	"Ten ", "Eleven ", "Twelve ", "Thirteen ", "Fourteen ", "Fifteen ", "Sixteen ", "Seventeen ", "Eighteen ", "Nineteen " };

class Solution3 {
public:
	string numberToWords(int num) {

		string res; 
		int thousands_idx = 0; 
		while (num){
			int below_1000 = num % 1000, above_1000 = num / 1000; 
			res = proc_below_1000(below_1000) + thousands[thousands_idx] + res; 
			num = above_1000; 
			++thousands_idx; 
		}
		return res; 
	}

	string proc_below_1000(int num){
		int hundred = num / 100,
			rem = num % 100; 
		string res; 
		if (hundred){
			res = proc_below_1000(hundred) + "Hundred "; 
		}

		if (rem < 20)
			res += below_20[rem]; 
		else{
			res += below_100[rem / 10] + below_20[rem % 10]; 
		}

		return res; 
	}
}; 

// wrong ans; 
class Solution4 {
public:
	typedef vector<pair<int, string>> dict;
	string numberToWords(int num) {
		dict _1000map{
			{ 1000, "thousand" },
			{ 1000000, "million" },
			{ 1000000000, "billion" }
		}, _100map{
			{ 30, "thirty" },
			{ 40, "forty" },
			{ 50, "fifty" },
			{ 60, "sixty" },
			{ 70, "seventy" },
			{ 80, "eighty" },
			{ 90, "ninety" }
		}, _20map{
			{ 1, "one" },
			{ 2, "two" },
			{ 3, "three" }
			};

			///////////////////////////////////////////////////
			string res; 
			for (int i = 2; i >= 0; --i){
				string _1000str = _1000map[i].second;
				int _1000base = _1000map[i].first, 
					_1000val = num / _1000base, _1000mod = num%_1000base; 
				if (_1000val > 0){
					res = under_1000_str(_1000val, _100map, _20map) + _1000str + res; 
				}
				num = _1000mod; 
			}

			return res; 
	}

	string under_1000_str(int num, dict& _100map, dict& _20map){
		string res; 
		int _100cnt = num / 100, below_100 = num % 100; 
		if (_100cnt > 0){
			res = _20map[_100cnt].second + " hundreds" + res; 
		}

		for (int i = _100map.size() - 1; i >= 0; --i){
			int base = _100map[i].first;
			string str = _100map[i].second; 

		}
		return ""; 
	}
}; 


typedef vector<pair<int, string>> dict;
dict above1000 = {
	{ 1000000000, "billion" },
	{ 1000000, "million" },
	{ 1000, "thousand" },
	{ 1, "" },
};
vector<string> tens = { "", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety" };
vector<string> below20 = { " ", "One ", "Two ", "Three ", "Four ", "Five ", "Six ", "Seven ", "Eight ", "Nine ", "Ten ", "Eleven ", "Twelve ", "Thirteen ", "Fourteen ", "Fifteen ", "Sixteen ", "Seventeen ", "Eighteen ", "Nineteen " };

class Solution5 {
public:
	string numberToWords(int num) {
		string res;
		for (int i = 0; i < above1000.size(); ++i){
			int base = above1000[i].first;
			string s = above1000[i].second;
			if (num >= base){
				res = res + " " + below1000(num / base) + " " + s; 
			}
			num = num%base; 
		}
		return res; 
	}

	string below1000(int n){
		string r; 
		if (n >= 100)
			return below1000(n / 100) + " hundred " + below1000(n % 100);
		else if (n >= 20)
			return tens[n / 10] + " " + below20[n % 10];
		else
			return below20[n]; 
	}
};




int main() {
	Solution5 a;

	cout << a.numberToWords(100001) << endl; 

}

