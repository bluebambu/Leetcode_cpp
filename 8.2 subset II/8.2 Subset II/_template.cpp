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


// DFS�ķ����� �� if(cur==size()) ��û�� for loop�� ��for loop��û��if(cur==size()) !!!!!
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
		//if (cur == vec.size()){  // ������if statement�� �����ǿ��Բ����ڵ� cur λ�Ͻ��� cur ֮�������Ԫ�صģ� ������subset��Ҫ��
			res.push_back(path);
		//	return;
		//}
		/*
		
		��������for loop û��if statement�� ��1��2 Ϊ��

		1��
		1��2
		2��

		ÿһλ�϶��ڲ����ڵ� cur λ�Ͻ��� cur ֮�������Ԫ�أ� ����ÿһ��������¼������ ����ȷ��subset��ȡֵ��ʽ. 

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



// �������� ���ظ����ֵ������ ��Ϊ res ��size ������ÿ�ζ�double�ġ� 
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
��������ظ�Ԫ�ص����� ��  

1��1��1��2��2��

[]
[1]
[1,1]
[1,1,1]
[2]
[1,2]
[1,1,2]
[1,1,1,2]

s[i] != s[i - 1] || j >= preSz		�ĺ����ǣ� 
	�ӵڶ���2��ʱ�� ��Ϊ��һ��2 �Ǽӵ�ǰ�ĸ�vector����ģ� ���Եڶ���2��Ȼ����Ҫ�ӵ�ǰ4��vector�� ���Ҫ�� j>=preSz ��ʼ�ӵڶ���2. 

	ͬ������ӵ�����2�Ļ��� index 5��8 ��Щ����1��2�ľͲ����ټ��ˣ�ֻ��Ҫ�� j>=preSz �ĵط���ʼ��2�� 

*/
class Solution4{
public:
	vector<vector<int>> subsetII4(vector<int>& s){
		vector<vector<int>> res(1);
		int preSz = 0;

		for (int i = 0; i < s.size(); ++i){
			size_t cursz = res.size(); 
			for (int j = 0; j < cursz; ++j){
				if (i == 0 || s[i] != s[i - 1] || j >= preSz){ // ������
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

