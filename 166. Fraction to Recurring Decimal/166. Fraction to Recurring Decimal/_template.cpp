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




// ��ô��������ˣ�����������INT��ȡֵ��Χ�� - 2147483648��2147483647������
// - 2147483648ȡ����ֵ�ͻᳬ����Χ������������Ҫ��תΪlong long����ȡ����ֵ��
// ��ô��ô����ѭ���أ��϶����ٵõ�һ�����ֺ�Ҫ����֮ǰ��û�г����������Ϊ�˽�
// ʡ����ʱ�䣬���ǲ��ù�ϣ��������ÿ��С��λ�ϵ����֡�����һ��С���ɣ���������
// Ҫ���С��ÿһλ����ȡ�ķ�����ÿ�ΰ�������10���ٳ��Գ������õ����̼�ΪС����
// ��һλ���֡�

// �㷨�� ������ÿһ�����������ֵ�һ���ظ���ʱ�򣬾���С����ʼѭ����ʱ��
/// 1/6 = 0.1(6)
/// ���ǵ��������� ������һ�� vector<int> 	����¼ÿ��С�����������Ĵ��� ����һ��������ʲô���ڶ�����ʲô�� 
//  ͬʱ���������ֵ�remain�� ����һ�� rem �ӽ�ȥ���������ܳ�ֿ��ǵ�ǰ�漸��С�������ظ��������

// case 1�� 214748364 û�й��� ��vs�������������� ���˶ԣ� �����ȷ�� �𰸵���˼��Ҫ�� long long ��hold int�� ������ int Խ�硣 Ӧ�ü�ס��Сϸ��
class Solution {
public:
	string fractionToDecimal(int numerator, int denominator) {
		if (denominator == 0)
			return "";
		bool sign = numerator >= 0 ^ denominator >= 0; // sign

		int num = abs(numerator), den = abs(denominator); 
		int integer = num / den, rem = num%den;

		if (rem == 0)
			return to_string(integer); 		  // ����
		
		string res = to_string(integer) + ".", remain;  
		vector<int> remains(den, -1); 
		int remid = 0; remains[rem]=remid++; 

		while (1){
			remain += to_string(rem * 10 / den); 
			rem = rem * 10 % den;
			if (rem == 0)	 // С������
				return sign ? "-" + res + remain : res + remain;

			if (remains[rem] >= 0){	// ����ѭ��
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

