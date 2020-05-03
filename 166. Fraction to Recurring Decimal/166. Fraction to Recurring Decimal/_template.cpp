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




// 那么问题就来了：由于整型数INT的取值范围是 - 2147483648～2147483647，而对
// - 2147483648取绝对值就会超出范围，所以我们需要先转为long long型再取绝对值。
// 那么怎么样找循环呢，肯定是再得到一个数字后要看看之前有没有出现这个数。为了节
// 省搜索时间，我们采用哈希表来存数每个小数位上的数字。还有一个小技巧，由于我们
// 要算出小数每一位，采取的方法是每次把余数乘10，再除以除数，得到的商即为小数的
// 下一位数字。

// 算法： 当除法每一步的余数出现第一个重复的时候，就是小数开始循环的时候
/// 1/6 = 0.1(6)
/// 考虑到这个情况， 必须用一个 vector<int> 	来记录每个小数除法余数的次序， 即第一个余数是什么，第二个是什么。 
//  同时把整数部分的remain， 即第一个 rem 加进去，这样才能充分考虑到前面几个小数不能重复的情况。

// case 1， 214748364 没有过， 但vs里面可以算出来， 经核对， 结果正确。 答案的意思是要用 long long 来hold int， 否则怕 int 越界。 应该记住的小细节
class Solution {
public:
	string fractionToDecimal(int numerator, int denominator) {
		if (denominator == 0)
			return "";
		bool sign = numerator >= 0 ^ denominator >= 0; // sign

		int num = abs(numerator), den = abs(denominator); 
		int integer = num / den, rem = num%den;

		if (rem == 0)
			return to_string(integer); 		  // 整除
		
		string res = to_string(integer) + ".", remain;  
		vector<int> remains(den, -1); 
		int remid = 0; remains[rem]=remid++; 

		while (1){
			remain += to_string(rem * 10 / den); 
			rem = rem * 10 % den;
			if (rem == 0)	 // 小数整除
				return sign ? "-" + res + remain : res + remain;

			if (remains[rem] >= 0){	// 无限循环
				remain.insert(remains[rem], "("); 
				break;
			}

			remains[rem] = remid++; 
		}
		return sign ? "-" + res + remain + ")" : res + remain + ")";
	}
};

int main()
{
	Solution a;

	cout << a.fractionToDecimal(1, -214748364);


}

