// _template.cpp : Defines the entry point for the console application.
//
#include <stdafx.h>

#include <iostream>
#include <functional>
#include <bitset>
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



struct Point {
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
};

class Solution {
public:
	int maxPoints(vector<Point>& points) {
		int res = 0; 
		for (int i = 0; i < points.size(); ++i){
			unordered_map<long long, int> slopMap; 
			int maxCnt = 0; 
			for (int j = i + 1; j < points.size(); ++j){
				long double slope; 
				int curx = points[j].x - points[i].x,
					cury = points[j].y - points[i].y; 

				if (points[j].x - points[i].x == 0){
					slope = LONG_MAX*1e3;
				}
				else
					slope = long double(points[j].y - points[i].y) / long double(points[j].x - points[i].x); 
				//slopMap[slope] += 1; 
				//maxCnt = max(maxCnt, slopMap[slope]); 
				cout << endl; 
			}
			res = max(res, maxCnt+1); 
		}
		return res; 
	}
};

// wrong ans. 
// class Solution2 {
// public:
// 	int maxPoints(vector<Point>& points) {
// 		int cnt = -1; 
// 		sort(points.begin(), points.end()); 

// 		for (int i = 0; i < points.size(); ++i){
// 			vector<Point>& start = points[i]; 
// 			int cur_max = 0; 
// 			unordered_map<int, unordered_map<int, int>> slope_cnt; 
// 			for (int j = i + 1; j < points.size(); ++j){
// 				vector<int> slope = getSlopeGcd(start, points[j]); 
// 				slope_cnt[slope[0]][slope[1]] += 1; 
// 				cur_max = max(slope_cnt[slope[0]][slope[1]], cur_max); 
// 			}
// 			cnt = max(cnt, cur_max); 
// 		}
// 		return cnt; 
// 	}

// 	vector<int> getSlopeGcd(vector<Point>& a, vector<Point>& b){
// 		int x = abs(a[0].x - b[0].x), y = abs(a[1].y - b[1].y); 
// 		if (y == 0) return{ 0, 0 }; 
// 		if (x == 0) return{ 0, INT_MAX }; 
// 		int g = gcd(x, y);
// 		vector<int> res = { x / g, y / g };
// 		return res;
// 	}

// 	int gcd(int x, int y){
// 		if (x > y)
// 			return gcd(y, x); 
// 		if (x == 0) return y; 
// 		return gcd(y%x, x);
// 	}
// }; 


class Solution3 {
public:
	int maxPoints(vector<Point>& points) {
		if (points.empty()) return 0; 

		int n = points.size(); 
		int res = 0; 
		for (int i = 0; i < n; ++i){
			unordered_map<int, unordered_map<int, int>> slopes;
			int same_dot = 0; // [0,0],[0,0],[1,1]
			for (int j = i + 1; j < n; ++j)
				if (points[i].x == points[j].x && points[i].y == points[j].y){
					same_dot += 1; 
					res = max(res, same_dot);
				}

			for (int j = i + 1; j < n; ++j){
				if (points[i].x == points[j].x && points[i].y == points[j].y)
					continue;

				vector<int> slope = getSlope(points[i], points[j]); 
				slopes[slope[0]][slope[1]] += 1; 
				if (slopes[slope[0]][slope[1]]+same_dot > res)
					res = slopes[slope[0]][slope[1]]+same_dot; 
			}
		}
		return res + 1; 
	}

	vector<int> getSlope(Point& a, Point& b){
		if (a.x == b.x) return{ 0, INT_MAX }; 
		if (a.y == b.y) return{ INT_MAX, 0 }; 
		if (a.x > b.x) return getSlope(b, a); 
		int delta_x = b.x - a.x, delta_y = b.y - a.y; 
		int g = gcd(abs(delta_x), abs(delta_y)); // gcd only handle positive numbers. 
		return{ delta_x / g, delta_y / g }; 
	}

	int gcd(int x, int y){
		if (x > y) return gcd(y, x); 
		if (x == 0)return y; 
		return gcd(y%x, x); 
	}
};

class Solution4 {
public:
	int maxPoints(vector<Point>& points) {
		int n = points.size();
		int res = 0;
		for (int i = 0; i < n; ++i){
			int same_dot = 1;
			unordered_map<int, unordered_map<int, int>> slopes;
			for (int j = i + 1; j < n; ++j){
				if (points[i].x == points[j].x && points[i].y == points[j].y){
					++same_dot;
					continue;
				}

				int dx = points[j].x - points[i].x,
					dy = points[j].y - points[i].y;
				int g = gcd(dx, dy);
				slopes[dx / g][dy / g] += 1;
			}

			res = max(res, same_dot);
			for (auto& px : slopes){
				for (auto &py : px.second){
					res = max(res, py.second + same_dot);
				}
			}
		}
		return res;
	}

	int gcd(int x, int y){
		return x == 0 ? y : gcd(y%x, x);
	}
};

// wrong ans, only consider vertical identical, not x+y identical. 
class Solution5 {
public:
	int maxPoints(vector<Point>& points) {
		if (points.empty()) return 0; 
		int res = 0; 
		int n = points.size(); 
		for (int i = 0; i < n; ++i){
			int vertNum = 0; 
			unordered_map<int, unordered_map<int, int>> slope_cnt; 
			for (int j = 0; j < n; ++j){
				if (j != i){
					if (points[i].x == points[j].x){
						++vertNum; 
						continue;; 
					}
					vector<int> slope = getSlope(points[i], points[j]); 
					slope_cnt[slope[0]][slope[1]] += 1; 
					if (slope_cnt[slope[0]][slope[1]] > res)
						res = slope_cnt[slope[0]][slope[1]]; 
				}
			}
			res = max(res, vertNum); 
		}
		return res; 
	}

	vector<int> getSlope(Point& a, Point& b){
		int deltax = a.x - b.x, deltay = a.y - b.y; 
		int gcd = getGcd(deltax, deltay); 
		return{ deltax / gcd, deltay / gcd }; 
	}

	int getGcd(int a, int b){
		if (b == 0) return a; 
		return getGcd(b, a%b); 
	}
};


// pass, 10% 
class Solution6 {
public:
	int maxPoints(vector<Point>& points) {
		if (points.empty())return 0; 
		int res = 0, n = points.size(); 
		for (int i = 0; i < n; ++i){
			unordered_map<int, unordered_map<int, int>> slope_cnt; 
			int identical = 1; 
			for (int j = 0; j < n; ++j){
				if (j != i && points[j].x == points[i].x && points[j].y == points[i].y)
					++identical; 
			}

			for (int j = 0; j < n; ++j){
				if (points[j].x != points[i].x || points[j].y != points[i].y){
					vector<int> slope = getSlope(points[i], points[j]);
					slope_cnt[slope[0]][slope[1]] += 1; 
					res = max(res, slope_cnt[slope[0]][slope[1]] + identical); 
				}
			}

			res = max(res, identical); 
		}
		return res; 
	}

	vector<int> getSlope(Point& a, Point& b){
		int deltax = a.x - b.x, deltay = a.y - b.y; 
		int gcd = getGcd(deltax, deltay); 
		return{ deltax / gcd, deltay / gcd }; 
	}

	int getGcd(int a, int b){
		if (b == 0) return a; 
		return getGcd(b, a%b); 
	}
};

int main(){
	Solution3 a; 
	Solution6 a2; 

	vector<Point> b = { Point(0, 0), Point(94911151, 94911150), Point(94911152, 94911151) }; 
	vector<Point> b2 = { Point(1, 1), Point(3, 2), Point(5, 3), Point(4, 1), Point(2, 3), Point(1, 4) }; 
	vector<Point> b3 = { Point(0, 0), Point(0, 0) }; 

	cout << a.maxPoints(b2) << endl; 
	cout << a2.maxPoints(b2) << endl; 

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

