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


// �������֮ǰ�ǵ�Strobogrammatic Number����չ���ǵ����������ж�һ�����Ƿ��ǶԳ�����
// ��������������ҳ�����Ϊn�����еĶԳ��������ǿ϶�����һ����һ���������жϣ�����̫��
// ��Ч�ˣ�����OJ�϶�Ҳ�����Ӧ����Ŀ�и�����ʾ˵�����õݹ�������������ʾ�˵ݹ����n - 2��
// ������n - 1�����������о�һ��nΪ0, 1, 2, 3, 4�������
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
// ����ע��۲�n = 0��n = 2�����Է��ֺ�������ǰ�ߵĻ����ϣ�ÿ�����ֵ�����������
// [1 1], [6 9], [8 8], [9 6]����n = 1��n = 3�������ԣ���0����������[1 1]�������101, 
// ��0����������[6 9]�������609, ��0����������[8 8]�������808, ��0����������[9 6]����
// ����906, Ȼ���ڷֱ���1��8���������߼���������������ʵ�����Ǵ�m = 0�㿪ʼ��һ��һ������
// �ӵģ���Ҫע����ǵ��ӵ���n���ʱ���������߲��ܼ�[0 0]����Ϊ0���ܳ�������λ������λ����
// ��ͷ�����м�ݹ�Ĺ����У���Ҫ���������������߸�����0������������μ��������£�

class Solution {
public:

	vector<string> findStrobogrammatic(int n) {
		return find(n, n);
	}

	vector<string> find(int x, int total){
		if (x == 0) return vector<string>({ "" });	  // Ϊ0ʱ�� ������һ���յ�Ԫ�أ� �������� vector<string>() !! 
		if (x == 1) return vector<string>({ "0", "1", "8" });	// Ϊ1ʱ�� �������� 6 �� 9  

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

