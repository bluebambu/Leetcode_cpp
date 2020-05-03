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
#include <chrono>
#include <bitset>

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


template <typename C>
void prt1Layer(C v){
	for (auto i : v)
		cout << i << " ";
	cout << endl;
}

template <typename C>
void prt2Layer(C v){
	for (auto i : v){
		for (auto j : i)
			cout << j << " ";
		cout << endl; 
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

// ��������һ��Ͷ��ȡ�ɵķ�����ֱ��������built - in�ĺ���bitset��count��������ֱ�ӷ���1�ĸ�������Ŀ��˵�˲��ᳫ�����ַ�����д����ֻ�Ƕ�һ��˼·���ѣ�
// �ⷨ����

class Solution1 {
public:
	vector<int> countBits(int num) {
		vector<int> res;
		for (int i = 0; i <= num; ++i) {
			res.push_back(bitset<32>(i).count());
		}
		return res;
	}
};


// �������ַ�����ȵ�һ�ַ�����Ҫ���ܶ��ˣ���������ҵĸ��ã������ǣ���1��ʼ������ż��ʱ����1�ĸ����͸�ż������2�õ������ֵ�1�ĸ�����ͬ����������ʱ����1�ĸ������ڸ���������2�õ������ֵ�1�ĸ����ټ�1���μ��������£�
// �ⷨ����

class Solution2 {
public:
	vector<int> countBits(int num) {
		vector<int> res{ 0 };
		for (int i = 1; i <= num; ++i) {
			if (i % 2 == 0) res.push_back(res[i / 2]);
			else res.push_back(res[i / 2] + 1);
		}
		return res;
	}
};


// �������ַ����͸��������ˣ������������i&(i - 1)�� ��������������ж�һ�����Ƿ���2��ָ���Ŀ�ݷ���������8��������λ1000, ��ô8&(8 - 1)Ϊ0��ֻҪΪ0����2��ָ��, ��ô������������һ��0��15�����ֺ����Ӧ��i&(i - 1)ֵ��

// i    bin    '1'    i&(i - 1)
// 0    0000    0
// ---------------------- -
// 1    0001    1    0000
// ---------------------- -
// 2    0010    1    0000
// 3    0011    2    0010
// ---------------------- -
// 4    0100    1    0000
// 5    0101    2    0100
// 6    0110    2    0100
// 7    0111    3    0110
// ---------------------- -
// 8    1000    1    0000
// 9    1001    2    1000
// 10   1010    2    1000
// 11   1011    3    1010
// 12   1100    2    1000
// 13   1101    3    1100
// 14   1110    3    1100
// 15   1111    4    1110

// ���ǿ��Է���ÿ��iֵ����i&(i - 1)��Ӧ��ֵ��1���������ǾͿ���д���������£�
// �ⷨ�ģ�

class Solution3 {
public:
	vector<int> countBits(int num) {
		vector<int> res(num + 1, 0);
		for (int i = 1; i <= num; ++i) {
			res[i] = res[i & (i - 1)] + 1;
		}
		return res;
	}
};


class Solution {
public:
	vector<int> countBits(int num) {
		vector<int> res; 
		res.push_back(0); 
		for (int i = 1; i <= num; ++i){
			if (i % 2 == 0){
				res.push_back(res[i / 2]); 
			}
			else{
				res.push_back(res[i / 2] + 1); 
			}
		}
		return res; 
	}
};

int main(){
	Solution a;

	vector<int> b = { 7, 2, 5, 10, INT_MAX };


	//TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
		3       8
	1    4   7    9
	*/



	///////////////////////////
	auto start = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	cout << endl << microseconds << " microseconds elapsed..." << endl;
}

