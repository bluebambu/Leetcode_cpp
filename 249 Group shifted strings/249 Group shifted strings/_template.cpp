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
#include <set>


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


class Solution
{
public:
	vector<vector<string>> groupStrings(vector<string> strings){
		vector<vector<string>> res; 
		if (strings.empty())
			return res; 

		unordered_map<string, vector<string>> map;
		unordered_set<string> visited; 

		for (int i = 0; i < strings.size(); ++i){
			if (visited.find(strings[i]) == visited.end()){
				map[strings[i]]; 
				for (int j = i + 1; j < strings.size(); ++j){
					if (visited.find(strings[j]) == visited.end() && match(strings[i], strings[j])){
						map[strings[i]].push_back(strings[j]);
						visited.insert(strings[j]); 
					}
				}
				visited.insert(strings[i]); 
			}
		}

		for (auto& i : map){
			vector<string> cur(1, i.first); 
			cur.insert(cur.end(), i.second.begin(), i.second.end()); 
			res.push_back(cur);
		}

		return res; 
	}

	bool match(string a, string b){
		if (a.size() != b.size())
			return false; 

		if (a.empty() && b.empty())
			return true; 

		for (int i = 1; i < a.size(); ++i){
			if ('a' + (a[1] - 'a' + (b[0] - a[0])) % 26 != b[1] )
				return false; 
		}

		return true; 
	}
};

// simpler solution
class Solution2 {
public:
	vector<vector<string>> groupStrings(vector<string>& strings) {
		vector<vector<string> > res;
		unordered_map<string, multiset<string>> m;
		for (auto a : strings) {
			string t = "";
			for (char c : a) {
				t += to_string((c + 26 - a[0]) % 26) + ",";
			}
			m[t].insert(a);
		}
		for (auto it = m.begin(); it != m.end(); ++it) {
			res.push_back(vector<string>(it->second.begin(), it->second.end()));
		}
		return res;
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

