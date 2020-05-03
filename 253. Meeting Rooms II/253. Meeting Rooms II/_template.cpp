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

/**
Definition for an interval.**/ 
struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

class Solution {
public:
	int minMeetingRooms(vector<Interval>& intervals) {
		map<int, int> m; 

		for (Interval& in : intervals){
			++m[in.start]; 
			--m[in.end]; 
		}

		int res = 0, curRoom=0; 
		for (auto& it : m){
			res = max(res, curRoom += it.second); 
		}
		return res; 
	}
};

class Solution2 {
public:
	int minMeetingRooms(vector<Interval>& intervals) {
		sort(intervals.begin(), intervals.end(),
			[&](Interval& a, Interval& b){return a.start < b.start; }); 

		auto comp = [](int a, int b){return a > b; }; 
		priority_queue<int, vector<int>, decltype(comp)> pq(comp); 

		for (Interval& it : intervals){
			if (!pq.empty() && it.start >= pq.top()){ // Here it is IF, not WHILE!!!
				// think about [1,5], [3,6], and third one is [7,8]. [7,8] can only pop out one precedent. 
				// otherwise, both [1,5], [3,6] will be popped and the answer is not right. 
				pq.pop(); 
			}
			pq.push(it.end); 
		}
		return pq.size(); 
	}
};


class Solution3 {
public:
	int minMeetingRooms(vector<Interval>& intervals){
		typedef pair<int, int> PII; 
		struct comp{
			bool operator()(PII& a, PII& b){
				return a.first > b.first || (a.first == b.first && a.second > b.second); 
			}
		};
		priority_queue<PII, vector<PII>, comp> pq; 

		for (Interval& in : intervals){
			pq.push({ in.start, 1 }); 
			pq.push({ in.end, -1 }); 
		}

		int res = 0, cur=0; 
		while (!pq.empty()){
			PII front = pq.top(); 
			pq.pop(); 

			if (front.second == 1){
				cur += 1; 
				res = max(res, cur); 
			}
			else
				cur -= 1; 
		}
		return res; 
	}
};


// passed
class Solution4 {
public:
	int minMeetingRooms(vector<Interval>& intervals){
		struct pt{
			int time; 
			bool isStart; 
			pt(int x, bool y) :time(x), isStart(y) {}
		};

		vector<pt> points; 

		for (auto& i : intervals){
			points.emplace_back(i.start, true); 
			points.emplace_back(i.end, false); 
		}

		sort(points.begin(), points.end(), [](pt& a, pt& b){
			return a.time < b.time || (a.time == b.time && a.isStart < b.isStart); 
		}); 

		int res = INT_MIN, cur = 0;

		for (int i = 0; i < points.size(); ++i){  
			cur += points[i].isStart ? 1 : -1; 
			res = max(res, cur); 
		}

		return res==INT_MIN ? 0 : res; 
	}
};


struct pt{
	int time;
	bool isStart;
	pt(int x, bool y) :time(x), isStart(y) {}
};


// FB follow-up: how to get the interval that has most overlapps. 
class mostOverlapped{
public:
	pair<int, int> mostOverlap(vector<pt>& points){
		int res = 0; 
		int fstart = 0, fend = 0; 

		int cur = 0; 
		bool atHighest = false; 
		for (int i = 0; i < points.size(); ++i){
			cur += points[i].isStart ? 1 : -1; 
			if (cur > res){
				res = cur; 
				fstart = points[i].time; 
				atHighest = true; 
			}
			else if (atHighest && points[i].isStart == false){
				atHighest = false; 
				fend = points[i].time; 
			}
		}

		return{ fstart, fend }; 
	}
};

int main() {
	Solution a;
	Solution4 a2;

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

