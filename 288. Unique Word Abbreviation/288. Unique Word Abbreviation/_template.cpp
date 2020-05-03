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
#include <map>
#include <utility>
#include <sstream>

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


// An abbreviation of a word follows the form <first letter><number><last letter>.Below are some examples of word abbreviations :
// 
// a) it--> it(no abbreviation)
// 
// 1
// b) d | o | g-- > d1g
// 
// 1    1  1
// 1-- - 5----0----5--8
// c) i | nternationalizatio | n-- > i18n
// 
// 1
// 1-- - 5----0
// d) l | ocalizatio | n-- > l10n
// 
// Assume you have a dictionary and given a word, find whether its abbreviation is unique in the dictionary.A word's abbreviation is unique if no other word from the dictionary has the same abbreviation.
// 
// Example:
// 
// Given dictionary = ["deer", "door", "cake", "card"]
// 
// isUnique("dear") ->
// false
// 
// isUnique("cart") ->
// true
// 
// isUnique("cane") ->
// false
// 
// isUnique("make") ->
// true
// 



// ���������������صĵ�����д��������Ŀ�и������Ӳ��Ǻ����������������������������
// 
// 1. dictionary = { "dear" }, isUnique("door") -> false
// 
// 2. dictionary = { "door", "door" }, isUnique("door") -> true
// 
// 3. dictionary = { "dear", "door" }, isUnique("door") -> false
// 
// 
// 
// �����������������ǿ��Կ���������дһ�µ�ʱ���ֵ��еĵ��ʾ��͸���������ͬʱ����ô����true��
// ������Ҫ�ù�ϣ����������д��ʽ�����Ӧ�ĵ��ʵ�ӳ�䣬��������д��ʽ����ͬ���ʷŵ�һ��set�У�
// Ȼ���������ж��Ƿ�unique��ʱ��ֻ��Ҫ���������ʵ���д��ʽ��set����õ��ʵĸ����Ƿ��set�е�
// Ԫ��������ͬ����ͬ�Ļ���������ĵڶ������������true����Ҫע���������set�в������ظ�ֵ����
// ������ڶ������ֻ����һ��door����set����ǲ���Ӱ���жϽ�����μ��������£�

class ValidWordAbbr {
public:
	ValidWordAbbr(vector<string> &dictionary) {
		for (auto a : dictionary) {
			string k = a[0] + to_string(a.size() - 2) + a.back();
			m[k].insert(a);
		}
	}
	bool isUnique(string word) {
		string k = word[0] + to_string(word.size() - 2) + word.back();
		return m[k].count(word) == m[k].size();
	}
private:
	unordered_map<string, set<string>> m;
};


// Your ValidWordAbbr object will be instantiated and called as such:
// ValidWordAbbr vwa(dictionary);
// vwa.isUnique("hello");
// vwa.isUnique("anotherWord");





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

