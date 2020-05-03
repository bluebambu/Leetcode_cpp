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

// The API : int read4(char *buf) reads 4 characters at a time from a file.
// The return value is the actual number of characters read.For example, it returns 3 if there is only 3 characters left in the file.
// By using the read4 API, implement the function int read(char *buf, int n) that reads n characters from the file.
// Note :
// 	 The read function will only be called once for each test case.
// 
// 
// 
// 这道题给了我们一个Read4函数，每次可以从一个文件中最多读出4个字符，如果文件中的字符不足4
// 个字符时，返回准确的当前剩余的字符数。现在让我们实现一个最多能读取n个字符的函数。这题有迭
// 代和递归的两种解法，我们先来看迭代的方法，思路是我们每4个读一次，然后把读出的结果判断一下，
// 如果为0的话，说明此时的buf已经被读完，跳出循环，直接返回res和n之中的较小值。否则一直读入，
// 直到读完n个字符，循环结束，最后再返回res和n之中的较小值，参见代码如下：

// Forward declaration of the read4 API.
int read4(char *buf);

class Solution {
public:
	/**
	* @param buf Destination buffer
	* @param n   Maximum number of characters to read
	* @return    The number of characters read
	*/
	int read(char *buf, int n) {
		int res = 0; 
		for (int i = 0; i <= n / 4; ++i){
			int cur = read4(buf + res); 
			res += cur; 
		}
		return min(res, n); 
	}
};

				  
//   |		 |       |        |				 read4
//   0 1 2 3 4 5 6 7 8 9 10				 buf
//   |<------ n ------>|					 n

// 关键是要比较三者的长度， 4、buf和n。 以上图为例， 在8-10部分， buf还有3个， read4 返回结果为3， 而n只剩2了。
// 所以这个地方要取一个最小值。 
class Solution2 {
public:
	int read(char *buf, int n){
		if (n < 4)
			return min(read4(buf), n);
		return read4(buf) + read(buf + 4, n - 4);

	}
};



class Solution3{
public:
	int read(char* buf, int n){
		int cnt = 0; 
		while (1){
			int r = read4(buf); 
			cnt += 4; 
			if (r < 4 || n < 4){
				buf += min(r, n); 
				return cnt - 4 + (min(r, n)); 
			}
			buf += 4;
			n -= 4; 
		}
		return -1; 
	}
};


class Solution4 {
public:
	int read(char* buf, int n){
		int cnt = 0;
		while (1){
			int r = read4(buf);
			cnt += r;
			if (r < 4 || (cnt>n && cnt - n < 4)){
				buf += min(r, cnt - n);
				return min(cnt, n);
			}
			buf += r;
		}
		return -1;
	}
};



class Solution5{
public:
	int read(char* buf, int n){
		if (n < 4)
			return min(read4(buf), n); 
		return read4(buf) + read(buf + 4, n - 4); 
	}
};


// wrong ans!! 
class Solution6{
public:
	int read(char* buf, int n){
		if (n < 4)
			return n; 
		return 4 + read(buf, n - 4); 
	}
};


class Solution7{
public:
	int read(char* buf, int n){
		int cur, res = 0; 
		while (n >= 0){
			cur = read4(buf); 
			if (cur<4)
				break;
			if (n < 4){ // cur==4 && n<4
				return res + n; 
			}
			res += 4; 
			buf += 4; 
			n -= 4; 
		}

		return res + min(cur, n); 
	}
};

// pass
class Solution8{
public:
	int read(char* buf, int n){
		int res = 0; 
		while (true){
			int c = read4(buf); 
			if (n < c)
				return res + n; 
			if (c < 4)
				return res + c; 
			res += 4; 
			n -= 4; 
			buf += 4; 
		}
		return res; 
	}
}; 



int main() {
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



}

