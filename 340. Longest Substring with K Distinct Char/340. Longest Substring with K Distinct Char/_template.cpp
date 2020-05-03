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


// passed. not very fast. 
class Solution
{
public:
	int lengthOfLongestSubstringKDistinct(string s, int k) {
		if (s.size() <= k)
			return s.size();
		if (k == 0)
			return 0;

		unordered_map<char, int>  charmap;

		charmap[s[0]] = 0;
		int i = 0, j = 1, res = 0;
		for (; j < s.size(); ++j){
			if (charmap.find(s[j]) != charmap.end()){
				charmap[s[j]] = j;
			}
			else if (charmap.size() < k){
				charmap[s[j]] = j;
			}
			else{
				while (i < j && charmap.size() == k){
					if (i < charmap[s[i]])
						++i;
					else
						charmap.erase(s[i++]);
				}
				charmap[s[j]] = j;
			}
			res = max(res, j - i + 1);
		}
		return res;
	}
};

// hashmap 能够被 int[256] 取代， 只需要加一个 int num 来记录distinct char 的数目
class Solution2{
public:
	int lengthOfLongestSubstringKDistinct(string s, int k) {
		
	}
};

int main()
{
	Solution a;

	//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
	3       8
	1    4   7    9

	*/

	a.flatten(tree);


}

