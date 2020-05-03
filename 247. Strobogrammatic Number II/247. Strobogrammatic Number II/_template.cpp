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
#include <math.h>

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


// 这道题是之前那道Strobogrammatic Number的拓展，那道题让我们判断一个数是否是对称数，
// 而这道题让我们找出长度为n的所有的对称数，我们肯定不能一个数一个数的来判断，那样太不
// 高效了，而且OJ肯定也不会答应。题目中给了提示说可以用递归来做，而且提示了递归调用n - 2，
// 而不是n - 1。我们先来列举一下n为0, 1, 2, 3, 4的情况：
// 
// n = 0:   none
// 
// n = 1 : 0, 1, 8
// 
// n = 2 : 11, 69, 88, 96
// 
// n = 3 : 101, 609, 808, 906, 111, 619, 818, 916, 181, 689, 888, 986
// 
// n = 4 : 1001, 6009, 8008, 9006, 1111, 6119, 8118, 9116, 1691, 6699, 8698, 9696, 1881, 6889, 8888, 9886, 1961, 6969, 8968, 9966
// 
// 我们注意观察n = 0和n = 2，可以发现后者是在前者的基础上，每个数字的左右增加了
// [1 1], [6 9], [8 8], [9 6]，看n = 1和n = 3更加明显，在0的左右增加[1 1]，变成了101, 
// 在0的左右增加[6 9]，变成了609, 在0的左右增加[8 8]，变成了808, 在0的左右增加[9 6]，变
// 成了906, 然后在分别在1和8的左右两边加那四组数，我们实际上是从m = 0层开始，一层一层往上
// 加的，需要注意的是当加到了n层的时候，左右两边不能加[0 0]，因为0不能出现在两位数及多位数的
// 开头，在中间递归的过程中，需要有在数字左右两边各加上0的那种情况，参见代码如下：

class Solution {
public:

	vector<string> findStrobogrammatic(int n) {
		return find(n, n);
	}

	vector<string> find(int x, int total){
		if (x == 0) return vector<string>({ "" });	  // 为0时， 必须有一个空的元素， 而不能是 vector<string>() !! 
		if (x == 1) return vector<string>({ "0", "1", "8" });	// 为1时， 不可能有 6 和 9  

		vector<string> prev = find(x - 2, total), res;
		for (auto str : prev){
			if (x != total)	res.push_back("0" + str + "0");
			res.push_back("1" + str + "1");
			res.push_back("6" + str + "9");
			res.push_back("8" + str + "8");
			res.push_back("9" + str + "6");
		}
		return res;
	}
};


class Solution2 {
public:
	vector<string> findStrobogrammatic(int n) {
		string all = "01689"; 
		string odd = "018"; 

		vector<string> res; 
		res.push_back(""); 
		for (int i = 1; i <= n / 2; ++i){
			vector<string> next; 
			for (int j = 0; j < res.size(); ++j){
				for (int k = 0; k < all.size(); ++k){
					if (i==1 && k==0)
						continue; 
					next.push_back(res[j] + all[k]); 
				}
			}
			res.swap(next); 
		}

		if (n % 2 == 1){
			vector<string> next;
			for (int j = 0; j < res.size(); ++j){
				for (int k = 0; k < odd.size(); ++k){
					next.push_back(res[j] + odd[k]);
				}
			}
			res.swap(next);
		}

		for (int i = 0; i < res.size(); ++i){
			for (int j = n/2-1; j >= 0; --j){
				res[i].push_back(stro(res[i][j])); 
			}
		}
		
		return res; 
	}

	char stro(char c){
		switch (c){
		case '1':return '1'; 
		case '6':return '9'; 
		case '8':return '8'; 
		case '9':return '6'; 
		case '0':return '0'; 
		}
	}
}; 


int main(){
	Solution2 a2; 

	vector<string> b = a2.findStrobogrammatic(1); 
	for (int i = 0; i < b.size(); ++i)
		cout << b[i] <<endl ; 
}

