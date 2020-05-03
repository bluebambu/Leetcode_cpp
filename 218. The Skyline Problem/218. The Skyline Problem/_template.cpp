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
#include <set>

using namespace std;

inline int exchg(int &a, int &b)  { int c = a; a = b; b = c; }
inline int log2(int N){ return log10(N) / log10(2); }
inline float min(float a, float b) { return a<b ? a : b; }


struct TreeNode {
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

// 
// 
// [LeetCode] The Skyline Problem
// 
// A city's skyline is the outer contour of the silhouette formed by all the buildings in that city when viewed from a distance. Now suppose you are given the locations and height of all the buildings as shown on a cityscape photo (Figure A), write a program to output the skyline formed by these buildings collectively (Figure B).
// 
// 
// 
// The geometric information of each building is represented by a triplet of integers[Li, Ri, Hi], where Li and Ri are the x coordinates of the left and right edge of the ith building, respectively, and Hi is its height.It is guaranteed that 0 ≤ Li, Ri ≤ INT_MAX, 0 < Hi ≤ INT_MAX, and Ri - Li > 0. You may assume all buildings are perfect rectangles grounded on an absolutely flat surface at height 0.
// 
// For instance, the dimensions of all buildings in Figure A are recorded as : [[2 9 10], [3 7 15], [5 12 12], [15 20 10], [19 24 8]] .
// 
// The output is a list of "key points" (red dots in Figure B) in the format of[[x1, y1], [x2, y2], [x3, y3], ...] that uniquely defines a skyline.A key point is the left endpoint of a horizontal line segment.Note that the last key point, where the rightmost building ends, is merely used to mark the termination of the skyline, and always has zero height.Also, the ground in between any two adjacent buildings should be considered part of the skyline contour.
// 
// For instance, the skyline in Figure B should be represented as : [[2 10], [3 15], [7 12], [12 0], [15 10], [20 8], [24, 0]].
// 
// Notes :
// 
// 	  The number of buildings in any input list is guaranteed to be in the range[0, 10000].
// 	  The input list is already sorted in ascending order by the left x position Li.
// 	  The output list must be sorted by the x position.
// 	  There must be no consecutive horizontal lines of equal height in the output skyline.For instance, [...[2 3], [4 5], [7 5], [11 5], [12 7]...] is not acceptable; the three lines of height 5 should be merged into one in the final output as such : [...[2 3], [4 5], [12 7], ...]
// 
// 
// 
//   Credits :
// 		  Special thanks to @stellari for adding this problem, creating these two awesome images and all test cases.
// 
// 	  https://leetcode.com/problems/the-skyline-problem/
// 
// 
// 
// 分别将每个线段的左边节点与右边节点存到新的vector height中，根据x坐标值排序，然后遍历求拐点。求拐点的时候用一个最大化heap来保存当前的楼顶高度，遇到左边节点，
// 就在heap中插入高度信息，遇到右边节点就从heap中删除高度。分别用pre与cur来表示之前的高度与当前的高度，当cur != pre的时候说明出现了拐点。在从heap中删除元素时要注
// 意，我使用priority_queue来实现，priority_queue并不提供删除的操作，所以又用了别外一个unordered_map来标记要删除的元素。在从heap中pop的时候先看有没有被标记过，
// 如果标记过，就一直pop直到空或都找到没被标记过的值。别外在排序的时候要注意，如果两个节点的x坐标相同，我们就要考虑节点的其它属性来排序以避免出现冗余的答案。且体的
// 规则就是如果都是左节点，就按y坐标从大到小排，如果都是右节点，按y坐标从小到大排，一个左节点一个右节点，就让左节点在前。下面是AC的代码。



class Solution {
public:
	struct node{
		int x; 
		int y; 
		bool lnr; // l-true, r-false
		node(int a, int b, bool c) :x(a), y(b), lnr(c) {}
	};

	struct comp{
		bool operator() (const node& a, const node& b){		// 注意 comp 的写法和逻辑！ comp 最好不要写  if(x>a) return true;  因为这样做并没有condition能 return false！！ 
			if (a.x != b.x)
				return a.x < b.x;
			else if (a.lnr == true && b.lnr == true)
				return a.y > b.y;
			else if (a.lnr == false && b.lnr == false)
				return a.y < b.y;
			else
				return a.lnr == true; 
		}
	};

	vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
		vector<node> newSkyl; 
		for (auto &b : buildings){
			newSkyl.push_back(node(b[0], b[2], true)); 
			newSkyl.push_back(node(b[1], b[2], false));
		}
		sort(newSkyl.begin(), newSkyl.end(), comp()); 

		priority_queue<int> heap; 	  // pq 没有 erase 函数， 所以需要用 hashtable 来record
		vector<pair<int, int>> res; 
		unordered_map<int, int> mp; 
		heap.push(0); 
		int pre = 0, cur = 0; 

		for (node &b : newSkyl){
			if (b.lnr)
				heap.push(b.y); 
			else{
				++mp[b.y]; 
				while (!heap.empty() && mp[heap.top()] > 0){
					--mp[heap.top()]; 
					heap.pop(); 
				}
			}
			cur = heap.top(); 
			if (pre != cur){
				res.push_back(make_pair(b.x, heap.top())); 
				pre = cur; 
			}
		}
		return res; 
	}
};


// 也可以 left point 增加mp计数， right point减少计数。 原理一样， 更加易懂一些。 
// passed leetcode
class Solution2 {
public:
	struct node{
		int x;
		int y;
		bool lnr; // l-true, r-false
		node(int a, int b, bool c) :x(a), y(b), lnr(c) {}
	};

	struct comp{
		bool operator() (const node& a, const node& b){		// 注意 comp 的写法和逻辑！ comp 最好不要写  if(x>a) return true;  因为这样做并没有condition能 return false！！ 
			if (a.x != b.x)
				return a.x < b.x;
			else if (a.lnr == true && b.lnr == true)
				return a.y > b.y;
			else if (a.lnr == false && b.lnr == false)
				return a.y < b.y;
			else
				return a.lnr == true;
		}
	};

	vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
		vector<node> sorted; 
		for (auto& b : buildings){
			sorted.push_back(node(b[0], b[2], true));
			sorted.push_back(node(b[1], b[2], false));
		}
		sort(sorted.begin(), sorted.end(), comp()); 

		vector<pair<int, int>> res; 
		priority_queue<int> heap; 
		heap.push(0); 
		unordered_map<int, int> mp;
		mp[0] = -1;  // 这句话非常重要， 因为在上一个solution，这个条件被 while 循环巧妙规避了
		int cur = 0, pre = 0;

		for (auto& n : sorted){
			if (n.lnr){
				heap.push(n.y); 
				++mp[n.y]; 
			}
			else{
				--mp[n.y]; 
				while (!heap.empty() && mp[heap.top()] == 0)
					heap.pop(); 
			}
			cur = heap.top(); 
			if (pre != cur){
				res.push_back(make_pair(n.x, cur)); 
				pre = cur; 
			}
		}
		return res; 
	}
};

// 下面的思路有点太巧妙了， 面试想出来基本不可能。 不过还是可以借鉴 multiset这个容器，能简化一些操作

// 使用一些技巧可以大大减少编码的复杂度，priority_queue并没有提供erase操作，但是multiset
// 提供了，而且multiset内的数据是按BST排好序的。在区分左右节点时，我之前自己建了一个结构体，
// 用一个属性type来标记。这里可以用一个小技巧，那就是把左边节点的高度值设成负数，右边节点的
// 高度值是正数，这样我们就不用额外的属性，直接用pair<int, int>就可以保存了。而且对其排序，
// 发现pair默认的排序规则就已经满足要求了。

class Solution3 {
public:
	vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
		vector<pair<int, int>> height;
		for (auto &b : buildings) {
			height.push_back({ b[0], -b[2] });
			height.push_back({ b[1], b[2] });
		}
		sort(height.begin(), height.end());
		multiset<int> heap;
		heap.insert(0);
		vector<pair<int, int>> res;
		int pre = 0, cur = 0;
		for (auto &h : height) {
			if (h.second < 0) {
				heap.insert(-h.second);
			}
			else {
				heap.erase(heap.find(h.second));
			}
			cur = *heap.rbegin();
			if (cur != pre) {
				res.push_back({ h.first, cur });
				pre = cur;
			}
		}
		return res;
	}
};


class Solution4 {
public:
	vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
		typedef pair<int, int> PII; 
		vector<PII> pts; 

		for (auto i : buildings){
			pts.push_back({ i[0], i[2] }); 
			pts.push_back({ i[1], -i[2] }); 
		}

		sort(pts.begin(), pts.end(), [](PII& a, PII& b){
			return a.first<b.first || (a.first == b.first && a.second>b.second); 
		});

		vector<PII> res; 
		multiset<int> heightRec; 
		heightRec.insert(0); 
		int prevH = 0; 

		for (int i = 0; i < pts.size(); ++i){
			int pos = pts[i].first, hght = pts[i].second; 

			if (hght >= 0){
				if (hght > *(--heightRec.end())){
					res.push_back({ pos, hght }); 
				}
				heightRec.insert(hght); 
				prevH = *(--heightRec.end()); 
			}
			else{
				// multiset.erase(val) will delete mutltiple values!!!!
				// so here it's best to use find(val) to get the iterator. 
				heightRec.erase(heightRec.find(abs(hght))); 
				if (*(--heightRec.end()) != prevH){
					res.push_back({ pos, *(--heightRec.end() ) }); 
					prevH = *(--heightRec.end()); 
				}
			}
		}

		return res; 
	}
};


class Solution5 {
public:
	vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
		if (buildings.empty())
			return{}; 

		vector<vector<int>> verticals; 
		for (auto& b : buildings){
			verticals.push_back({ b[0], b[2], 1 }); 
			verticals.push_back({ b[1], b[2], -1 }); 
		}
		sort(verticals.begin(), verticals.end()); 

		set<int> pq; 
		pq.insert(0); 

		int height_tracker = 0; 
		vector<pair<int, int>> res; 
		for (int i = 0; i < verticals.size(); ++i){
			auto& cur = verticals[i]; 
			if (cur[2] == 1){
				int old_front = *(--pq.end()); 
				pq.insert(cur[1]); 
				if (*(--pq.end()) != old_front)
					res.push_back({ cur[0], *(--pq.end()) }); 
			}
			else if (cur[2] == -1){
				int old_front = *(--pq.end()); 
				pq.erase(cur[1]); 
				if (*(--pq.end()) != old_front)
					res.push_back({ cur[0], *(--pq.end()) });
			}
		}

		return res; 
	}
};



int main() {
	Solution4 a;
	Solution5 a2;

	vector<vector<int>> b = { { 2 ,9, 10 }, { 3, 7, 15 }, { 5, 12, 12 }, { 15, 20 ,10 }, { 19, 24 ,8 } }; 

	auto c = a.getSkyline(b);

	for (auto i : c){
		cout << i.first << " " << i.second << endl; 
	}

	cout << endl; 


	c = a.getSkyline(b);

	for (auto i : c){
		cout << i.first << " " << i.second << endl; 
	}

	cout << endl; 


	vector<vector<int>> d = { { 0, 2, 3 }, { 2, 5, 3 } }; 

	auto e = a.getSkyline(d); 

	for (auto i : e){
		cout << i.first << " " << i.second << endl; 
	}

	e = a.getSkyline(d); 

	for (auto i : e){
		cout << i.first << " " << i.second << endl; 
	}
}

