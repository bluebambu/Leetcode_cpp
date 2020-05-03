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

// wrong code. 
struct comp{
	bool operator()(const vector<int>& a, const vector<int>& b){
		if (a[0] > b[0]){
			if (b[0] % 2 && a[0] == b[0] + 1){
				return a[1] < b[1];
			}
			else
				return true;
		}

		if (a[0] < b[0]){
			if ((a[0] % 2) && (b[0] == a[0] + 1)){
				return a[1] < b[1];
			}
			else
				return false;
		}

		if (a[0] == b[0])
			return a[1] < b[1];
	}
};

class ExamRoom {
public:
	set<vector<int>, comp> q; 
	int n; 
    ExamRoom(int N){
		n = N;
    }
    
    int seat() {
		if (q.empty()){
			q.insert({ 2 * n , 0 });
			return 0; 
		}

		vector<int> longest = *(q.begin()); 
		int len = longest[0], left = longest[1]; 
		q.erase(q.begin());
		int l_len = (len - 2 + 1) / 2;
		q.insert({ l_len + 1 , left });
		int r_pos = left + l_len; 
		if (r_pos < n-1)
			q.insert({ (len - 2 - l_len) + 2, r_pos });

		prt2Layer(q); 

		return r_pos; 
    }
    
    void leave(int p) {
		vector<vector<int>> segs; 
		for (auto it = q.begin(); it != q.end(); ){
			if ((*(it))[1] == p || ((*(it))[0] + (*(it))[1] == p + 1)){
				segs.push_back(*it); 
				q.erase(it++); 
			}
			else{
				++it; 
			}
		}

		if (segs.size() != 2)
			throw exception("too less element"); 

		int left = min(segs[0][1], segs[1][1]),
			len = segs[0][0] + segs[1][0] - 1; 

		q.insert({ len, left }); 
    }
};


class ExamRoom2 {
public:
	int N;
	vector<int> L;
	ExamRoom2(int n) {
		N = n;
	}

	int seat() {
		if (L.size() == 0) {
			L.push_back(0);
			return 0;
		}

		cout << "==========\n"; 
		prt1Layer(L); 

		int d = max(L[0], N - 1 - L[L.size() - 1]);
		for (int i = 0; i < L.size() - 1; ++i) d = max(d, (L[i + 1] - L[i] ) / 2);
		if (L[0] == d) {
			L.insert(L.begin(), 0);
			return 0;
		}
		for (int i = 0; i < L.size() - 1; ++i)
			if ((L[i + 1] - L[i] ) / 2 == d) {
				L.insert(L.begin() + i + 1, (L[i + 1] + L[i]) / 2);
				return L[i + 1];
			}
		L.push_back(N - 1);
		return N - 1;
	}

	void leave(int p) {
		for (int i = 0; i < L.size(); ++i) if (L[i] == p) L.erase(L.begin() + i);
	}
};

class ExamRoom3 {
public:
	int N;
	vector<int> L;
	ExamRoom3(int n) {
		N = n;
	}

	int seat() {
		if (L.empty()){
			L.push_back(0); 
			return 0; 
		}
		int potential_d = max(L[0], N - 1 - L[L.size()-1]); 
		for (int i = 0; i < L.size() - 1; ++i)
			potential_d = max(potential_d, (L[i + 1] - L[i]) / 2); 
		if (L[0] == potential_d){
			L.insert(L.begin(), 0); 
			return 0; 
		}
		for (int i = 0; i < L.size() - 1; ++i){
			if ((L[i + 1] - L[i]) / 2 == potential_d){
				L.insert(L.begin() + i + 1, (L[i + 1] + L[i]) / 2); 
				return L[i + 1]; 
			}
		}
		L.push_back(N - 1); 
		return N - 1; 
	}

	void leave(int p){
		for (int i = 0; i < L.size(); ++i)
			if (L[i] == p)
				L.erase(L.begin() + i); 
	}
};


class ExamRoom2 {
public:
	ExamRoom2(int _n):n(_n) { } 
	multiset<vector<int>> dist_range; 
	int n; 
	int seat() {
		if (dist_range.empty()){
			dist_range.insert({ n, 0, -1 }); 
			return n; 
		}
		else{
			int toprange = *(--dist_range.end())[0]; 
			int start = *(--dist_range.end())[1], end = *(--dist_range.end())[2]; 

			dist_range.erase(--dist_range.end());
			if (start == -1){
				dist_range.insert({ toprange, 0, end }); 
				return toprange; 
			}
			else if (end == -1){
				dist_range.insert({ toprange, start, n-1 }); 
				return toprange; 
			}
			else{
				int mid = start + (end - start) / 2; 
				dist_range.insert({ mid - start, start, mid }); 
				dist_range.insert({ end-mid, mid, start }); 
				return max(mid - start, end - mid); 
			}
		}
	}

	void del(int i){
		vector<int> left, right;
		for (auto iter = dist_range.begin(); iter != dist_range.end();){
			auto p = *iter;
			if (p[1] == i){
				right = p;
				iter = dist_range.erase(iter);
			}
			else if (p[2] == i){
				left = p;
				iter = dist_range.erase(iter);
			}
			else{
				++iter;
			}
		}

		vector<int> new = {}; 
		dist_range.insert(new); 
	}
};


class ExamRoom3 {
public:
	ExamRoom2(int _n) :n(_n) { }
	multiset<vector<int>> dist_range;
	int n;
	int seat() {
		if (dist_range.empty()){
			dist_range.insert({ n, 0, -1 }); 
			return 0; 
		}

		int longestRange = dist_range.rbegin()->at(0),
			left = dist_range.rbegin()->at(1),
			right = dist_range.rbegin()->at(2); 
		dist_range.erase(dist_range.rbegin()); 

		if (left == -1){
			dist_range.insert({ longestRange, 0, right }); 
			return 0; 
		}
		else if (right == -1){
			dist_range.insert({ longestRange, left, n - 1 }); 
			return n - 1; 
		}
		else{
			int midpoint = left + (right - left) / 2; 
			int lftlen = midpoint - left + 1; 
			dist_range.insert({ lftlen, left, midpoint }); 
			dist_range.insert({ right - midpoint + 1, midpoint, right });
			return midpoint; 
		}
		return -1; 
	}
	
	void leave(int i){
		vector<int> lftRec, rtRec; 
		// better to use iterator here; 
		for (auto iter = dist_range.begin(); iter != dist_range.end(); ++iter){
			
		}

	}
}; 

int main(){
	ExamRoom2 a(10); 

	cout << a.seat() << endl; 
	cout << a.seat() << endl; 
	cout << a.seat() << endl; 
	cout << a.seat() << endl; 

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

