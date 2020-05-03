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


// DFS的方法， 有 if(cur==size()) 则没有 for loop， 有for loop则没有if(cur==size()) !!!!!
class Solution
{
public:
	vector<vector<int>> subset(vector<int>& vec){
		sort(vec.begin(), vec.end()); 
		vector<int> path;
		vector<vector<int>> res;
		dfs(vec, 0, path, res);
		return res;
	}

	void dfs(vector<int>& vec, int cur, vector<int>& path, vector<vector<int>>& res){
		//if (cur == vec.size()){  // 不能有if statement。 这样是可以不断在第 cur 位上交换 cur 之后的所有元素的， 正好是subset的要求
			res.push_back(path);
		//	return;
		//}
		/*
		
		如果下面的for loop 没有if statement， 以1，2 为例

		1，
		1，2
		2，

		每一位上都在不断在第 cur 位上交换 cur 之后的所有元素， 并且每一步都被记录下来。 是正确的subset的取值方式. 

		*/

		for (int i = cur; i < vec.size(); ++i){
			if (i>cur && vec[i] == vec[i - 1]) 
				continue;
			path.push_back(vec[i]);
			dfs(vec, i + 1, path, res);
			path.pop_back();
		}
	}

};

class Solution2 {
public:
	vector<vector<int>> subsetII(vector<int>& vec){
		vector<vector<int>> res; 
		vector<int> path; 
		dfs(vec, 0, path, res);
		return res;
	}
	void dfs(vector<int>& vec, int cur, vector<int>& path, vector<vector<int>>& res){
		if (cur == vec.size()){
			res.push_back(path);
			return;
		}
		path.push_back(vec[cur]); 
		dfs(vec, cur + 1, path, res); 
		path.pop_back(); 
		dfs(vec, cur + 1, path, res); 
	}
};



// 不适用于 有重复数字的情况， 因为 res 的size 并不是每次都double的。 
class Solution3{
public:
	vector<vector<int>> subsetII3(vector<int>& vec){ 
		vector<vector<int>> res; 
		res.push_back(vector<int>()); 

		int cur = 0; 
		while (cur < vec.size()){
			res.reserve(2 * res.size()); 
			int newsz = res.capacity(), oldsz = res.size(); 
			res.insert(res.begin() + oldsz, res.begin(), res.begin() + oldsz); 

			for (int i = oldsz; i < newsz; ++i){
				res[i].push_back(vec[cur]); 
			}
			++cur; 
		}

		return res; 
	}
};


/*
完美解决重复元素的问题 ！  

1，1，1，2，2，

[]
[1]
[1,1]
[1,1,1]
[2]
[1,2]
[1,1,2]
[1,1,1,2]

s[i] != s[i - 1] || j >= preSz		的含义是： 
	加第二个2的时候， 因为第一个2 是加到前四个vector上面的， 所以第二个2当然不需要加到前4个vector。 因此要从 j>=preSz 开始加第二个2. 

	同理，如果加第三个2的话， index 5～8 这些加了1个2的就不用再加了，只需要在 j>=preSz 的地方开始加2， 

*/
class Solution4{
public:
	vector<vector<int>> subsetII4(vector<int>& s){
		vector<vector<int>> res(1);
		int preSz = 0;

		for (int i = 0; i < s.size(); ++i){
			size_t cursz = res.size(); 
			for (int j = 0; j < cursz; ++j){
				if (i == 0 || s[i] != s[i - 1] || j >= preSz){ // ！！！
					res.push_back(res[j]); 
					res.back().push_back(s[i]);
				}
			}
			preSz = cursz; 
		}
		return res; 
	}
};

int main()
{
	Solution4 a;
	vector<int> b{ 1, 2, 2, 2};

	auto c = a.subsetII4(b);

	for (auto i : c){
		for (auto j : i)
			cout << j << " ";
		cout << endl;
	}
}

