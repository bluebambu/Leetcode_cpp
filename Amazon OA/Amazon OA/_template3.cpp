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

vector<vector<int>> dirs = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };
typedef pair<int, int> PII;
typedef vector<int> VI; 
typedef vector<vector<int>> VVI; 


class Solution {
public:
	vector<vector<int>> topK(vector<vector<int>>& restaurants, vector<int>& coord, int k){
		if (k <= 0)
			return{}; 

		if (restaurants.size() <= k)
			return restaurants; 

		getK(restaurants, coord, 0, restaurants.size() - 1, k); 

		return vector<vector<int>>(restaurants.begin(), restaurants.begin() + k); 
	}

	void getK(vector<vector<int>>& restrnt, vector<int>& coord, int left, int right, int k){
		int r = getRank(restrnt, coord, left, right); 
		if (r == k - 1)
			return;
		else if (r > k - 1)
			getK(restrnt, coord, left, r - 1, k);
		else
			getK(restrnt, coord, r+1, right, k); 
	}

	int getRank(vector<vector<int>>& restrnt, vector<int>& coord, int left, int right){
		vector<int>& pivot = restrnt[0]; 
		int target_d = dist(pivot, coord); 
		int i = left + 1, j = right; 
		while (1){
			while (i <= j && dist(restrnt[i], coord) < target_d) ++i; 
			while (i <= j && dist(restrnt[j], coord) > target_d)--j;
			if (i>j)
				break;
			swap(restrnt[i], restrnt[j]); 
			++i, --j; 
		}
		swap(restrnt[0], restrnt[i - 1]); 
		return i - 1; 
	}

	int dist(vector<int>& from, vector<int>& to){
		int xd = from[0] - to[0], yd = from[1] - to[1]; 
		return xd*xd + yd*yd; 
	}
};


typedef vector<int> VI; 
int dist(const vector<int>& from, const vector<int>& to){
	int xd = from[0] - to[0], yd = from[1] - to[1];
	return xd*xd + yd*yd;
}

struct comp{
	VI cd;
	comp(VI& coord) :cd(coord){}
	bool operator()(const VI& a, const VI& b){
		return dist(a, cd) > dist(b, cd);
	}
};
class Solution2 {
public:
	vector<vector<int>> topK(vector<vector<int>>& restaurants, vector<int>& coord, int k){
		comp c(coord); 
		multiset<vector<int>, comp> pq(c); 

		for (auto& r : restaurants){
			if (pq.size() < k)
				pq.insert(r); 
			else{
				vector<int> top = *(--pq.end());
				if (pq.size() == k && dist(top, coord) >= dist(r, coord)){
					pq.erase(--pq.end());
					pq.insert(r);
				}
			}
		}

		return vector<vector<int>>(pq.begin(), pq.end()); 
	}
	int dist(vector<int>& from, vector<int>& to){
		int xd = from[0] - to[0], yd = from[1] - to[1]; 
		return xd*xd + yd*yd; 
	}
}; 



class Solution3 {
public:
	vector<int> optimalUtilization(vector<int> v1, vector<int> v2, int upbound){
		int maxSum = INT_MIN; 
		vector<int> res = {};
		sort(v2.begin(), v2.end()); 
		for (int i = 0; i < v1.size(); ++i){
			int n1 = v1[i], target = upbound - n1; 
			// n1 + n2 < upbound -> n2 < upbound - n1
			int pos2 = upper_bound(v2.begin(), v2.end(), target) - v2.begin(); 
			if (pos2==0)
				continue;
			if (v1[i] + v2[pos2-1] > maxSum){
				maxSum = v1[i] + v2[pos2-1]; 
				res = { v1[i], v2[pos2-1] }; 
			}
		}
		return res; 
	}
}; 



class Solution4 {
public:
	vector<int> optimalUtilization(vector<int> v1, vector<int> v2, int upbound){
		sort(v1.begin(), v1.begin()); 
		sort(v2.begin(), v2.begin()); 
		int i = 0, j = v2.size() - 1; 
		int maxSum = INT_MIN; 
		vector<int> res; 
		while (i < v1.size() || j >= 0){
			int sum = v1[i] + v2[j]; 
			if (sum > upbound){
				if (j == 0)
					return res; 
				--j; 
			}
			else if (sum < upbound){
				if (sum > maxSum){
					maxSum = sum; 
					res = { i, j }; 
				}
				if (i == v1.size() - 1){
					return res; 
				}
				++i; 
			}
			else if (sum == upbound){

			}
		}
	}
}; 


class Solution5{
public:
	int min(vector<vector<int>>& mtx){
		int n = mtx.size(), m = mtx[0].size(); 
		queue<vector<int>> q; 
		q.push({ 0, 0 }); 
		set<vector<int>> visited; 
		visited.insert({ 0, 0 }); 

		int dist = 0; 
		while (!q.empty()){
			int sz = q.size(); 
			++dist; 
			for (int k = 0; k < sz; ++k){
				vector<int> f = q.front();
				q.pop();
				int i = f[0], j = f[1];

				for (auto& d : dirs){
					int x = i + d[0], y = j + d[1];
					if (x >= 0 && x < n&&y >= 0 && y < m&& !visited.count({x, y}) && mtx[x][y] != 1){
						if (mtx[x][y] == 9)
							return dist; 
						visited.insert({ x, y }); 
						q.push({ x, y }); 
					}
				}
			}
		}

		return -1; 
	}
};


class Solution6{
public:
	// INCLUDE HEADER FILES NEEDED BY YOUR PROGRAM
	// SOME LIBRARY FUNCTIONALITY MAY BE RESTRICTED
	// DEFINE ANY FUNCTION NEEDED
	// FUNCTION SIGNATURE BEGINS, THIS FUNCTION IS REQUIRED

	int dist(pair<int, int>& loc){
		return loc.first*loc.first + loc.second*loc.second;
	}

	int getRank(vector<pair<int, int>>& locations, int left, int right){
		pair<int, int> pivot = locations[left];
		int pivot_dist = dist(pivot);
		int i = left + 1, j = right;
		while (1){
			while (i <= j && dist(locations[i]) < pivot_dist)++i;
			while (i <= j && dist(locations[j]) > pivot_dist)--j;
			if (i > j)
				break;
			swap(locations[i], locations[j]);
			++i, --j;
		}
		swap(locations[left], locations[i - 1]);
		return i - 1;
	}

	void quickSelect(vector<pair<int, int>>& locations, int left, int right, int k){
		int r = getRank(locations, left, right);
		if (r == k - 1)
			return;
		else if (r > k - 1)
			quickSelect(locations, left, r - 1, k);
		else
			quickSelect(locations, r + 1, right, k);
	}

	vector<pair<int, int> > ClosestXdestinations(int numDestinations,
		vector<pair<int, int>> locations,
		int numDeliveries)
	{
		// WRITE YOUR CODE HERE
		if (numDeliveries <= 0) return{};
		if (locations.size() <= numDeliveries) return locations;

		quickSelect(locations, 0, locations.size() - 1, numDeliveries);

		return vector<pair<int, int>>(locations.begin(), locations.begin() + numDeliveries);
	}
	// FUNCTION SIGNATURE ENDS
};


class Solution7{
public:
	typedef pair<int, int> PII;

	vector<pair<int, int> > optimalUtilization(int maxTravelDist,
		vector<pair<int, int> > forwardRouteList,
		vector<pair<int, int> > returnRouteList)
	{
		// WRITE YOUR CODE HERE
		sort(forwardRouteList.begin(), forwardRouteList.end(), [](const PII&a, const PII& b){
			return a.second < b.second;
		});

		struct Comp{
			bool operator()(const PII& a, const PII& b){
				return a.second < b.second;
			}
		};

		vector<PII> res;
		int maxSum = INT_MIN;
		for (int i = 0; i < returnRouteList.size(); ++i){
			PII& curReturn = returnRouteList[i];
			int returnIdx = curReturn.first, returnCost = curReturn.second;
			int fwdTarget = maxTravelDist - returnCost;
			auto iter = upper_bound(forwardRouteList.begin(), forwardRouteList.end(), pair<int, int>(0, fwdTarget), Comp());
			if (iter == forwardRouteList.begin())
				continue;
			int fwdIdx = iter - forwardRouteList.begin();
			int curSum = returnCost + iter->second;
			if (curSum > maxSum){
				maxSum = curSum;
				res.clear();
				res.push_back({ returnIdx, iter->first });
			}
			else if (curSum == maxSum){
				res.push_back({ returnIdx, iter->first });
			}
		}
		return res;
	}
}; 


class Solution8{
public:
	// INCLUDE HEADER FILES NEEDED BY YOUR PROGRAM
	// SOME LIBRARY FUNCTIONALITY MAY BE RESTRICTED
	// DEFINE ANY FUNCTION NEEDED
	// FUNCTION SIGNATURE BEGINS, THIS FUNCTION IS REQUIRED
	typedef pair<int, int> PII;

	// brutal force
	vector<pair<int, int> > optimalUtilization2(int maxTravelDist,
		vector<pair<int, int> > forwardRouteList,
		vector<pair<int, int> > returnRouteList)
	{
		if (forwardRouteList.empty() || returnRouteList.empty()) return{};
		if (maxTravelDist <= 0) return{};

		vector<pair<int, int>> res;
		int maxSum = -1;
		int n = forwardRouteList.size(), m = returnRouteList.size();
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				int curSum = forwardRouteList[i].second + returnRouteList[j].second;
				if (curSum <= maxTravelDist){
					if (curSum > maxSum){
						maxSum = curSum;
						res.clear();
						res.push_back({ forwardRouteList[i].first, returnRouteList[j].first });
					}
					else if (curSum == maxSum){
						res.push_back({ forwardRouteList[i].first, returnRouteList[j].first });
					}
				}
			}
		}
		return res;
	}


	// binary search 
	vector<pair<int, int> > optimalUtilization(int maxTravelDist,
		vector<pair<int, int> > forwardRouteList,
		vector<pair<int, int> > returnRouteList)
	{
		if (forwardRouteList.empty() || returnRouteList.empty()) return{};
		if (maxTravelDist <= 0) return{};

		// WRITE YOUR CODE HERE
		sort(forwardRouteList.begin(), forwardRouteList.end(), [](const PII&a, const PII& b){
			return a.second < b.second;
		});

		struct Comp{
			bool operator()(const PII& a, const PII& b){
				return a.second < b.second;
			}
		};

		vector<PII> res;
		int maxSum = -1;
		for (int i = 0; i < returnRouteList.size(); ++i){
			PII& curReturn = returnRouteList[i];
			int returnIdx = curReturn.first, returnCost = curReturn.second;
			int fwdTarget = maxTravelDist - returnCost;

			auto iter = upper_bound(forwardRouteList.begin(), forwardRouteList.end(), PII(0, fwdTarget), Comp());
			if (iter == forwardRouteList.begin())
				continue;
			--iter; // set iter to the last lower_bound

			while (1){
				int fwdIdx = iter - forwardRouteList.begin();
				int curSum = returnCost + iter->second;
				if (curSum > maxSum){
					maxSum = curSum;
					res.clear();
					res.push_back({ iter->first, returnIdx });
				}
				else if (curSum == maxSum){
					res.push_back({ iter->first, returnIdx });
				}

				if (iter == forwardRouteList.begin() || (iter->second != prev(iter)->second)) break;
				--iter;
			}
		}

		return res;
	}
	// FUNCTION SIGNATURE ENDS
};



int main(){
	Solution2 a;

	vector<vector<int>> rest = {
		{ 1, 1 },
		{ 1, 2 },
		{ 2, 2 },
		{ 3, 3 },
		{ 4, 3 },
		{ 3, 6 },
	}; 
	vector<vector<int>> rest2 = {
		{ 1, 1 },
		{ 1, 1 },
		{ 1, 1 },
		{ 1, 1 },
		{ 1, 2 },
		{ 2, 2 },
		{ 3, 3 },
		{ 4, 3 },
		{ 3, 6 },
	}; 
	vector<int> coord = { 0, 0 }; 

	auto c = a.topK(rest2, coord, 3);

	prt2Layer(c); 

	Solution3 bb; 
	vector<int> v1 = { 2000, 5000 }, v2 = { 5000, 2000, 8000 }; 
	auto r = bb.optimalUtilization(v1, v2, 1000); 
	prt1Layer(r);

	Solution5 s5; 
	vector<vector<int>> mtx = {
		{0,1,9,0,0,0},
		{0,0,0,1,0,0},
		{1,1,0,0,0,1},
		{0,1,1,0,0,0},
		{0,0,0,1,0,0},
		{0,0,0,0,9,0}
	};
	cout << s5.min(mtx) << endl; 

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

