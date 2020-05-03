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
// 
// Given N axis - aligned rectangles where N > 0, determine if they all together form an exact cover of a rectangular region.
// Each rectangle is represented as a bottom - left point and a top - right point.For example, a unit square is represented as[1, 1, 2, 2]. (coordinate of bottom - left point is(1, 1) and top - right point is(2, 2)).

// Example 1:
// rectangles = [
// 	[1, 1, 3, 3],
// 		[3, 1, 4, 2],
// 		[3, 2, 4, 4],
// 		[1, 3, 2, 4],
// 		[2, 3, 3, 4]
// ]

// Return true.All 5 rectangles together form an exact cover of a rectangular region.

// Example 2:
// rectangles = [
// 	[1, 1, 2, 3],
// 		[1, 3, 2, 4],
// 		[3, 1, 4, 2],
// 		[3, 2, 4, 4]
// ]

// Return false.Because there is a gap between the two rectangular regions.

// Example 3:
// rectangles = [
// 	[1, 1, 3, 3],
// 		[3, 1, 4, 2],
// 		[1, 3, 2, 4],
// 		[3, 2, 4, 4]
// ]

// Return false.Because there is a gap in the top center.

// Example 4:
// rectangles = [
// 	[1, 1, 3, 3],
// 		[3, 1, 4, 2],
// 		[1, 3, 2, 4],
// 		[2, 2, 4, 4]
// ]

// Return false.Because two of the rectangles overlap with each other.



// 太巧妙了， 直接看的答案
// 下面这种方法也相当的巧妙， 提出这种算法的大神细心的发现了每种点的规律，每个绿点其实都是两个顶点的重合，
// 每个红点都是四个顶点的重合，而每个蓝点只有一个顶点，有了这条神奇的性质就不用再去判断“每个点最多只能是
// 一个矩形的左下，左上，右上，或右下顶点”这条性质了，我们直接用一个set，对于遍历到的任意一个顶点，如果set中已经存在了，
// 则删去这个点，如果没有就加上，这样最后会把绿点和红点都滤去，剩下的都是蓝点，我们只要看蓝点的个数是否为四个，
// 再加上检测每个矩形面积累加和要等于最后的大矩形的面积即可，参见代码如下：
class Solution {
public:
	bool isRectangleCover(vector<vector<int>>& rectangles) {
		unordered_set<string> st;
		int min_x = INT_MAX, min_y = INT_MAX, max_x = INT_MIN, max_y = INT_MIN, area = 0;
		for (auto rect : rectangles) {
			min_x = min(min_x, rect[0]);
			min_y = min(min_y, rect[1]);
			max_x = max(max_x, rect[2]);
			max_y = max(max_y, rect[3]);
			area += (rect[2] - rect[0]) * (rect[3] - rect[1]);
			string s1 = to_string(rect[0]) + "_" + to_string(rect[1]); // bottom-left
			string s2 = to_string(rect[0]) + "_" + to_string(rect[3]); // top-left
			string s3 = to_string(rect[2]) + "_" + to_string(rect[3]); // top-right
			string s4 = to_string(rect[2]) + "_" + to_string(rect[1]); // bottom-right
			if (st.count(s1)) st.erase(s1);
			else st.insert(s1);
			if (st.count(s2)) st.erase(s2);
			else st.insert(s2);
			if (st.count(s3)) st.erase(s3);
			else st.insert(s3);
			if (st.count(s4)) st.erase(s4);
			else st.insert(s4);
		}
		string t1 = to_string(min_x) + "_" + to_string(min_y);
		string t2 = to_string(min_x) + "_" + to_string(max_y);
		string t3 = to_string(max_x) + "_" + to_string(max_y);
		string t4 = to_string(max_x) + "_" + to_string(min_y);
		if (!st.count(t1) || !st.count(t2) || !st.count(t3) || !st.count(t4) || st.size() != 4) return false;
		return area == (max_x - min_x) * (max_y - min_y);
	}
};



// 自己的代码 ETL， 不知道为啥......... weird。  
struct pair_hash {
	template <class T1, class T2>
	std::size_t operator () (const std::pair<T1, T2> &p) const {
		auto h1 = std::hash < T1 > {}(p.first);
		auto h2 = std::hash < T2 > {}(p.second);

		// Mainly for demonstration purposes, i.e. works but is overly simple
		// In the real world, use sth. like boost.hash_combine
		return h1 ^ h2;
	}
};

class Solution2 {
public:
	bool isRectangleCover(vector<vector<int>>& rectangles) {
		// Only for pairs of std::hash-able types for simplicity.
		// You can of course template this struct to allow other hash functions

		typedef pair<int, int> cord; 
		unordered_set<cord, pair_hash> points; 
		cord righttop = { INT_MIN, INT_MIN }, leftbot = { INT_MAX, INT_MAX }; 
		int totArea = 0; 

		for (auto point : rectangles){
			righttop.first = max(righttop.first, point[2]);
			righttop.second = max(righttop.second, point[3]); 
			leftbot.first = min(leftbot.first, point[0]);
			leftbot.second = min(leftbot.second, point[1]);

			totArea += (point[3] - point[1])*(point[2] - point[0]); 

			cord lb = make_pair(point[0], point[1]), rt = make_pair(point[2], point[3]); 
			cord lt = make_pair(point[0], point[3]), rb = make_pair(point[2], point[1]); 

			if (points.count(lb))
				points.erase(lb);
			else
				points.insert(lb); 

			if (points.count(rt))
				points.erase(rt);
			else
				points.insert(rt);

			if (points.count(lt))
				points.erase(lt);
			else
				points.insert(lt); 

			if (points.count(rb))
				points.erase(rb);
			else
				points.insert(rb); 
		}
		if (points.size() != 4 | points.count(righttop) == 0 | points.count(leftbot) == 0 | totArea!=(righttop.second-leftbot.second)*(righttop.first-leftbot.first))
			return false; 
		return true; 

	}
};

// wrong ans. Not considering vacancies wihtin the  rectangles. 
class Solution3 {
public:
	bool isRectangleCover(vector<vector<int>>& rectangles) {
		vector<int> rd = { -1, -1 }, lu = rd, ld = rd, ru = rd;
		set<vector<int>> v; 
		int n = rectangles.size();
		int tarea = 0;
		for (int i = 0; i < n; ++i){
			vector<int> crd = { rectangles[i][2], rectangles[i][1] },
				clu = { rectangles[i][0], rectangles[i][3] },
				cld = { rectangles[i][0], rectangles[i][1] },
				cru = { rectangles[i][2], rectangles[i][3] };
			if (v.count(crd))
				v.erase(crd);
			else
				v.insert(crd); 

			if (v.count(cru))
				v.erase(cru);
			else
				v.insert(cru); 

			if (v.count(cld))
				v.erase(cld);
			else
				v.insert(cld); 

			if (v.count(clu))
				v.erase(clu);
			else
				v.insert(clu); 

			if (cru > ru || ru[0] == -1)
				ru = cru;
			if (cld < ld || ld[0] == -1)
				ld = cld;
			if ((clu[0] <= lu[0] && clu[1] >= lu[1]) || lu[0] == -1)
				lu = clu;
			if ((crd[0] >= rd[0] && crd[1] <= rd[1]) || rd[0] == -1)
				rd = crd;

			tarea += (cru[1] - crd[1] )*(crd[0] - cld[0] );
		}

		int cand = (ru[1] - rd[1] )*(rd[0] - ld[0] ); 
		return cand == tarea && v.size() == 4 && v.count(ld) && v.count(rd) && v.count(lu) && v.count(ru); 
	}
};



int main()
{
	Solution3 a;

	vector<vector<int>> b = { { 1, 1, 3, 3 }, { 3, 1, 4, 2 }, { 3, 2, 4, 4 }, { 1, 3, 2, 4 }, { 2, 3, 3, 4 } };

	vector<vector<int>> c = { { 1, 1, 2, 3 }, { 1, 3, 2, 4 }, { 3, 1, 4, 2 }, { 3, 2, 4, 4 } };

	vector<vector<int>> d = {{0, 0, 2, 2}, { 1, 1, 3, 3 }, { 2, 0, 3, 1 }, { 0, 3, 3, 4 }
}; 

	for (auto i : c){
		for (auto j : i){
			cout << j << '\t'; 
		}
		cout << endl; 
	}

	cout << a.isRectangleCover(d) << endl; 


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

