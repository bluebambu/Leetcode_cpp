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
// Note: This is a companion problem to the System Design problem: Design TinyURL.
// TinyURL is a URL shortening service where you enter a URL such as https://leetcode.com/problems/design-tinyurl 
// 	  and it returns a short URL such as http://tinyurl.com/4e9iAk.
// Design the encode and decode methods for the TinyURL service. There is no restriction 
// on how your encode/decode algorithm should work. You just need to ensure that a URL can 
// be encoded to a tiny URL and the tiny URL can be decoded to the original URL.




class Solution {
public:
	Solution(){
		dict = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"; 
		long2short.clear(); 
		short2long.clear(); 
		srand(time(NULL)); 
	}

	string dict; 
	unordered_map<string, string> long2short, short2long; 

	// Encodes a URL to a shortened URL.
	string encode(string longUrl) {
		if (long2short.count(longUrl))
			return long2short[longUrl]; 

		string sh = gen(longUrl); 
		while (short2long.count(sh)){
			sh = gen(longUrl); 
		}

		long2short[longUrl] = sh; 
		short2long[sh] = longUrl; 
		return "http://tinyurl.com/"+sh;
	}

	string gen(string& longUrl){
		string res = "";
		for (int i = 0; i < 6; ++i){
			int j = rand() % (dict.size()); 
			res += dict[j];
		}
		return res; 
	}

	// Decodes a shortened URL to its original URL.
	string decode(string shortUrl) {
		string randStr = shortUrl.substr(shortUrl.find_last_of("/") + 1);
		// return short2long[shortUrl]; 
		// remember to check if shortUrl exist or not!!!!!
		return short2long.count(randStr) ? short2long[randStr] : shortUrl;
	}
};

// Your Solution object will be instantiated and called as such:
// Solution solution;
// solution.decode(solution.encode(url));





int main(){
	Solution a;

	vector<int> b = { 7, 2, 5, 10, INT_MAX };

	auto c = a.encode("google.com"); 
	cout << a.decode(c); 


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

