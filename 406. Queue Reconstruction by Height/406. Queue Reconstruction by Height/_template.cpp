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
#include <string>

using namespace std;



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


// Suppose you have a random list of people standing in a queue.Each person 
// is described by a pair of integers(h, k), where h is the height of the person 
// and k is the number of people in front of this person who have a height greater 
// than or equal to h.Write an algorithm to reconstruct the queue.

// Note:
// The number of people is less than 1, 100.
// Example
// Input :
// 	[[7, 0}, [4, 4], [7, 1], [5, 0], [6, 1], [5, 2]]

// Output :
// 	[[5, 0], [7, 0], [5, 2], [6, 1], [4, 4], [7, 1]]



// 想象一下解题需要的东西， 有一些排序的提示。 这个解法是先按 *value左大右小* 排序， 然后再根据 h 值进行调整。 
// 这里 insert 函数非常契合题目的意思， 很有意思。 
class Solution {
public:
	struct comparator{
		bool operator () (pair<int, int>& a, pair<int, int>& b){
			return (a.first < b.first || (a.first == b.first && a.second > b.second));
		}
	};

	vector<pair<int, int>> reconstructQueue(vector<pair<int, int>>& people) {
		sort(people.begin(), people.end(), comparator()); 

		auto res = people; 
		res.clear(); 

		for (int i = 0; i < people.size(); ++i){
			res.insert(res.begin() + people[i].second, people[i]); 
		}

		return res; 
	}
};


// 不需要额外空间的解法
class Solution2 {
public:
	vector<pair<int, int>> reconstructQueue(vector<pair<int, int>>& people) {
		sort(people.begin(), people.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
			return a.first > b.first || (a.first == b.first && a.second < b.second);
		});

		for (int i = 1; i < people.size(); ++i) {
			int cnt = 0;
			for (int j = 0; j < i; ++j) {
				// 感觉这种方法更接近解法的实质。 先左大右小排序， 然后从右向左统计比当前数值大的元素的数量（左边所有元素都大于当前
				// 元素）， 这样就将问题转化成单一方向的问题， 从而的到解决。 
				if (cnt == people[i].second) {
					pair<int, int> t = people[i];
					for (int k = i - 1; k >= j; --k) {
						people[k + 1] = people[k];
					}
					people[j] = t;
					break;
				}
				if (people[j].first >= people[i].first)
					++cnt;
			}
		}
		return people;
	}
};

// practice
// 	[[5, 0], [7, 0], [5, 2], [6, 1], [4, 4], [7, 1]]
class Solution3{
public:
	struct comp{
		bool operator()(pair<int, int>& a, pair<int, int>& b){
			return a.first > b.first || (a.first == b.first && a.second < b.second);
		}
	};

	vector<pair<int, int>> sssss(vector<pair<int, int>>& people){
		sort(people.begin(), people.end(), comp()); 						

		for (int i = 1; i < people.size(); ++i){
			int cnt = 0; 
			// 0 -> i-1
			for (int j = 0; j < i; ++j){
				// 一定要先判断 cnt == h， 因为 h 等于零时， people[i]要排在第一个。 
				if (cnt == people[i].second){
					// has gone through h bigger number, replace with people[j]
					pair<int, int> tmp = people[i]; 
					for (int k = i; k > j; --k){
						people[k] = people[k - 1]; 
					}
					people[j] = tmp; 
					break; 
				}
				if (people[j].first > people[i].first)
					++cnt; 
			}
		}

		return people; 
	}
};

typedef pair<int, int> PII; 
class Solution4 {
public:
	vector<pair<int, int>> reconstructQueue(vector<pair<int, int>>& people) {
		sort(people.begin(), people.end(), [](PII& a, PII& b){
			return a.first > b.first || (a.first == b.first && a.second < b.second); 
		}); 

		vector<PII> res; 
		for (auto p : people){
			res.insert(res.begin() + p.second, p); 
		}
		return res; 
	}
};


int main()
{
	Solution4 a;
	vector<pair<int, int>> b = { { 7, 0 }, { 4, 4 }, { 7, 1 }, { 5, 0 }, { 6, 1 }, { 5, 2 } }; 

	auto c = a.reconstructQueue(b);

	for (auto i : c){
		cout << i.first << " " << i.second << "--";
	}
}

