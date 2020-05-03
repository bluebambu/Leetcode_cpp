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
		cout << i << " ";
	cout << endl;
}

template <typename T>
void prnt1layer(vector<T> v){
	for (auto i : v)
		cout << i << endl; 
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
	for (auto i : v){
		cout << i << " "<< i.size() << endl;
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
// Given an array of words and a length L, format the text such that each line has exactly L characters and is fully(left and right) justified.
// You should pack your words in a greedy approach; that is, pack as many words as you can in each line.Pad extra spaces ' ' when necessary so that each line has exactly L characters.
// Extra spaces between words should be distributed as evenly as possible.If the number of spaces on a line do not divide evenly between words, the empty slots on the left will be assigned more spaces than the slots on the right.
// For the last line of text, it should be left justified and no extra space is inserted between words.
// For example,
// words: ["This", "is", "an", "example", "of", "text", "justification."]
//    L : 16.
// 	   Return the formatted lines as :
// [
// 	"This    is    an",
// 	"example  of text",
// 	"justification.  "
// ]

// Note : Each word is guaranteed not to exceed L in length.


// pass AC. 
class Solution {
public:
	vector<string> fullJustify(vector<string>& words, int maxWidth) {
		vector<string> res; 

		if (words.empty())
			return res; 
		if (maxWidth == 0)
			return res; 

		for (int i = 0; i < words.size(); ){
			int j = i, curlen = 0, remain_space=0;
			for (; j < words.size() && curlen + words[j].size() <= maxWidth - (j-i); ++j){
				curlen += words[j].size(); 
			}

			if (j == words.size()){ 
				Endcase(words, i, res, maxWidth); 
				return res; 
			}
			else{
				remain_space = maxWidth - curlen; 
				proc(words, i, j, res, maxWidth, remain_space); 
			}

			i = j; 
		}

		return res; 
	}

	void Endcase(vector<string>& words, int i, vector<string>& res, int maxWidth){
		string endline; 
		for (; i < words.size(); ++i){
			if (maxWidth - endline.size() > words[i].size())
				endline += words[i] + " ";
			else
				endline.append(words[i]);
		}

		endline.append(maxWidth - endline.size(), ' '); 

		res.push_back(endline);
	}

	void proc(vector<string>& words, int i, int j, vector<string>& res, int maxWidth, int remain){
		if (i == j)
			return; 
		if (i == j - 1){
			string cur = words[i];
			cur.append(maxWidth - cur.size(), ' ');
			res.push_back(cur); 
			return; 
		}

		int num = j - i, avg = remain / (num - 1), mod = remain % (num - 1);

		string cur; 

		for (; i < j - 1; ++i){
			string tmp = words[i]; 
			if (mod > 0){
				cur.append(tmp.append(avg+1, ' ')); 
				--mod; 
			}
			else{
				cur.append(tmp.append(avg, ' ')); 
			}
		}

		cur.append(words[i]); 

		res.push_back(cur); 

	}
};

// finally passed. 
class Solution2 {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
		int i = 0; 
		vector<string> res; 
		while (i < words.size()){
			int j = i,
				curW = maxWidth; 
			while (j<words.size()){
				curW -= words[j].size() + 1; 
				if (curW <= -1)
					break;
				++j; 
			}
			if (i == j  && curW != -1){
				//
				break;
			}else if (j == words.size()){
				process_last_line(words, i, res, maxWidth); 
				break;
			}
			else if (curW == -1){
				process_perfect_line(words, i, j, res); // [i, j]
				i = j + 1; 
			}
			else{
				process_justified_line(words, i, j, curW + words[j].size() + 1, res); //[i, j)
				i = j; 
			}
		}
		return res; 
    }
	void process_last_line(vector<string>& words, int i, vector<string>& res, int maxWidth){
		string last; 
		while (i < words.size())
			last += words[i++] + " "; 
		while (last.size() < maxWidth)
			last.push_back(' '); 
		res.push_back(last); 
	}

	void process_perfect_line(vector<string>& words, int i, int j, vector<string>& res){
		string last; 
		while (i < j)
			last += words[i++] + " "; 
		last += words[i]; 
		res.push_back(last); 
	}

	void process_justified_line(vector<string>& words, int i, int j, int abudant_spaces,vector<string>& res){
		string last; 
		abudant_spaces += 1; 
		int num_gaps = j - i - 1; 
		if (num_gaps == 0){
			last += words[i] + string(abudant_spaces, ' '); 
			res.push_back(last); 
			return;
		}
		int avg_spaces = abudant_spaces / num_gaps,
			remains = abudant_spaces%num_gaps; 
		while (i < j-1){
			last += words[i] + " "; 
			if (remains){
				last += string(avg_spaces + 1, ' '); 
				--remains; 
			}
			else
				last += string(avg_spaces, ' '); 
			++i; 
		}
		last += words[i]; 
		res.push_back(last);
	}
};


class Solution4 {
public:
	vector<string> fullJustify(vector<string>& words, int maxWidth) {
		vector<string> res;
		int i = 0, j = 0;
		while (i < words.size()){
			int oneline = maxWidth;
			while (j<words.size() && oneline >= words[j].size()){
				if (oneline >= words[j].size() + 1)
					oneline -= words[j].size() + 1;
				else if (oneline == words[j].size())
					oneline -= words[j].size();
				else
					break;
				++j;
			}
			if (j == words.size()){
				add_last_line(words, i, j, res, maxWidth); 
				break;
			}
			else{
				add_line(words, i, j, res, maxWidth); 
				i = j; 
			}

			prnt1layer(res); 
		}
		return res; 
	}
	void add_last_line(vector<string>& words, int i, int j, vector<string>& res, int maxw){
		string last; 
		for (int k = i; k < j; ++k)
			last += words[k] + " "; 
		last.pop_back(); 
		last += string(maxw - last.size(), ' '); 
		res.push_back(last); 
	}

	void add_line(vector<string>& words, int i, int j, vector<string>& res, int maxw){
		int n = j - i; 
		if (n == 1){
			string line = words[i];
			line += string(maxw - line.size(), ' ');
			res.push_back(line);
			return;
		}
		int space_n = maxw; 
		for (int k = i; k < j; ++k)
			space_n -= words[k].size(); 
		int div = space_n / (n - 1), mod = space_n % (n - 1); 

		string line; 
		for (int k = i; k < j-1; ++k){
			line += words[k]; 
			if (mod){
				line += string(div + 1, ' '); 
				--mod; 
			}
			else
				line += string(div, ' '); 
		}
		line += words[j - 1]; 
		res.push_back(line); 
	}
};


int main() {
	Solution4 a;

	vector<string> c = { "this", "is", "an", "cool", "exaple", "justf", "wher", "The", "fuck", "bull", "shit" };
	vector<string> c2 = { "this", "is", "an", "example", "of", "text", "justification" }; 
	vector<string> cc = { "a" };
	vector<string> c3 = { "ask", "not", "what", "your", "country", "can", "do", "for", "you", "ask", "what", "you", "can", "do", "for", "your", "country" }; 
	auto b = a.fullJustify(c3, 16); 

	prnt1layer(b); 

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

