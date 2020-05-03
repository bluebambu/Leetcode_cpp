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
// Given a rows x cols screen and a sentence represented by a list of non-empty words, find how many times the given sentence can be fitted on the screen.

// Note:
//     A word cannot be split into two lines.
//     The order of words in the sentence must remain unchanged.
//     Two consecutive words in a line must be separated by a single space.
//     Total words in the sentence won't exceed 100.
//     Length of each word is greater than 0 and won't exceed 10.
//     1 ¡Ü rows, cols ¡Ü 20,000.

// Example 1:

// Input:
// rows = 2, cols = 8, sentence = ["hello", "world"]

// Output: 
// 1

// Explanation:
// hello---
// world---

// The character '-' signifies an empty space on the screen.

// Example 2:

// Input:
// rows = 3, cols = 6, sentence = ["a", "bcd", "e"]

// Output: 
// 2

// Explanation:
// a-bcd- 
// e-a---
// bcd-e-

// The character '-' signifies an empty space on the screen.

// Example 3:

// Input:
// rows = 4, cols = 5, sentence = ["I", "had", "apple", "pie"]

// Output: 
// 1

// Explanation:
// I-had
// apple
// pie-I
// had--

// The character '-' signifies an empty space on the screen.



// pass AC
class Solution {
public:
	int wordsTyping(vector<string>& sentence, int rows, int cols) {
		string perfect = ""; 
		for (string str : sentence){
			perfect += (str + " "); 
		}

		int adjustLen = 0; 
		int len = perfect.size(); 
		for (int i = 0; i < rows; ++i){
			adjustLen += cols; 
			if (perfect[adjustLen%len] == ' ')
				++adjustLen; 
			else{
				while (adjustLen > 0 && perfect[(adjustLen - 1) % len] != ' ')
					--adjustLen; 
			}
		}

		return adjustLen / len; 
	}
};

// correct solution, but slow, TLE
class Solution2 {
public:
	int wordsTyping(vector<string>& sentence, int rows, int cols) {
		int i = 0, cnt = 0; 
		for (int r = 0; r < rows; ++r){
			int curcol = cols; 
			while (curcol >= sentence[i].size()){
				(curcol == sentence[i].size()) ? curcol = 0 : curcol -= (sentence[i].size() + 1); 
				if (i == sentence.size() - 1)
					cnt += 1; 
				i = (i + 1) % (sentence.size()); 
			}
		}
		return cnt;
	}
};


class Solution3 {
public:
	int wordsTyping(vector<string>& sentence, int rows, int cols) {
		string perfStr; 
		for (auto s : sentence)
			perfStr += s + " "; 

		int augLen = 0; 
		for (int r = 0; r < rows; ++r){
			augLen += cols; 
			int perfIdx = (augLen - 1) % perfStr.size(); 
			if (perfStr[perfIdx + 1] == ' ')
				augLen += 1; 
			else{
				while (augLen > 1 && perfStr[perfIdx] != ' '){
					augLen -= 1; 
					perfIdx = (augLen - 1) % perfStr.size();
				}
			}
		}
		return augLen / perfStr.size(); 
	}
};

class Solution4 {
public:
	int wordsTyping(vector<string>& sentence, int rows, int cols) {
						

	}
};

int main(){
	
	Solution a; 
	Solution2 a2; 
	Solution3 a3;

	vector<string> b = {
		"I",
		"have",
		"a",
		"dream"
	}; 

	vector<string> b2 = { "a" }; 

	cout << a.wordsTyping(b2, 2000, 2000) << endl; 
	cout << a3.wordsTyping(b2, 2000, 2000) << endl;
	cout << a2.wordsTyping(b2, 2000, 2000) << endl;

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

