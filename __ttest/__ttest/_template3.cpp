// _template.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <functional>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <set>
#include <unordered_set>

using namespace std;

inline int exchg(int &a, int &b)  { int c = a; a = b; b = c; }
inline int log2(int N){ return log10(N) / log10(2); }
inline float min(float a, float b) { return a < b ? a : b; }


struct TreeNode2 {
	TreeNode2(int a, int b) :start(a), end(b), left(nullptr), right(nullptr) {}
	TreeNode2(int a, int b, TreeNode2* x, TreeNode2* y) :start(a), end(b), left(x), right(y) {}
	TreeNode2() :start(0), end(0), left(nullptr), right(nullptr) {}

	int start;
	int end;
	int max;
	int key;

	int val;
	TreeNode2 *left;
	TreeNode2 *right;
};



struct TreeNode {
	TreeNode(int a) :val(a), left(nullptr), right(nullptr) { parent = nullptr;  }
	TreeNode(int a, TreeNode* x, TreeNode* y) :val(a), left(x), right(y) {
		if (x) left->parent = this; 
		if (y) right->parent = this; 
		parent = nullptr; 
	}
	TreeNode() :val(0), left(nullptr), right(nullptr) { parent = nullptr;  }

	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode *parent; 

};


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
			cout << j << "\t";
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

vector<vector<int>> dirs{ { 0, -1 }, { 0, 1 }, { 1, 0 }, { -1, 0 } };
typedef pair<int, int> PII;
typedef vector<int> VI; 
typedef vector<vector<int>> VVI; 

int preorder(TreeNode *node, TreeNode* left, TreeNode* right, int& largest, TreeNode *&lgstnode); 

int largestBSTSubtree(TreeNode* root){
	int largest = 0; 
	TreeNode *lgstnode = nullptr; 

	preorder(root, nullptr, nullptr, largest, lgstnode); 

	return largest; 
}

int preorder(TreeNode *node, TreeNode* left, TreeNode* right, int& largest, TreeNode *&lgstnode){
	if (!node)
		return 0; 

	int l = preorder(node->left, left, node, largest, lgstnode),
		r = preorder(node->right, node, right, largest, lgstnode); 

	if (l == -1 || r == -1)
		return -1; 
	
	if (left && node->val <= left->val)
		return -1; 
	if (right && node->val >= right->val)
		return -1; 
	
	int cursz = l + r + 1; 
	if (largest < cursz){
		largest = cursz; 
		lgstnode = node; 
	}

	return cursz; 
}


int rk(vector<int>& nums, int left, int right){
	int pivot = nums[left], i = left + 1, j = right; // [ , ) 
	while (i < j){
		while (i < j && nums[i] < pivot) ++i;
		while (i<j && nums[j - 1]>pivot) --j;
		if (i==j)
			break;; 
		
		swap(nums[i], nums[j-1]); 
	}
	swap(nums[i - 1], nums[left]); 

	return i - 1; 
}

int qs(vector<int> nums, int k){
	int left = 0, right = nums.size(); 
	while (left < right){
		int r = rk(nums, left, right); 
		if (r == k - 1)
			return nums[r]; 
		if (r < k - 1)
			left = r + 1;
		else
			right = r; 
	}
	return -1; 
}


vector<int> topo(unordered_map<int, unordered_set<int>> graph){
	unordered_map<int, int> inorder; 
	for (auto i : graph){
		inorder[i.first]; 
		for (auto j : graph[i.first]){
			++inorder[j]; 
		}
	}

	queue<int> q; 
	for (auto i : inorder){
		if (inorder[i.first] == 0)
			q.push(i.first); 
	}

	vector<int> res; 
	while (!q.empty()){
		int f = q.front(); 
		q.pop(); 
		res.push_back(f); 

		for (auto nxt : graph[f]){
			--inorder[nxt]; 
			if (inorder[nxt] == 0)
				q.push(nxt); 
		}
	}

	if (res.size() != inorder.size())
		return{}; 

	return res; 
}

int gcd(int bigger, int smaller){
	return smaller == 0 ? bigger : gcd(smaller, bigger%smaller); 
}


int fit(int rows, int cols, vector<string>& sentence){
	int n = sentence.size(); 
	int left_space = cols; 
	int q = 0; // iter of sentence 
	int qcnt = 0; 
	for (int i = 0; i < rows; ++i){
		int used_cnt = 0; 
		while (true){
			if (used_cnt == 0 && left_space >= sentence[q].size()){
				left_space -= sentence[q].size(); 
				q = (q + 1) % n; 
				++qcnt; 
				used_cnt += 1;
			}
			else if (left_space > sentence[q].size()){
				left_space -= sentence[q].size() + 1; 
				q = (q + 1) % n; 
				++qcnt; 
				used_cnt += 1; 
			}
			else{
				left_space = cols; 
				break;;
			}
		}
	}

	return qcnt / n; 
}

// pass, 27.9%
class Solution {
public:
    int maxDistToClosest(vector<int>& seats) {
		vector<int> pos; 
		for (int i = 0; i < seats.size(); ++i){
			if (seats[i] == 1)
				pos.push_back(i); 
		}

		int maxDist = pos[0]*2; 
		int maxGapStart = -1; 
		int i; 
		for (i = 0; i < pos.size() - 1; ++i){
			int nxt = i + 1; 
			if (pos[nxt] - pos[i] > maxDist){
				maxDist = pos[nxt] - pos[i]; 
				maxGapStart = pos[i]; 
			}
		}
		if (seats.size() - pos.back() - 1 > maxDist / 2){
			maxDist = 2 * (seats.size() - pos.back() - 1); 
		}
		return maxDist / 2; 
    }
};

class Solution2{
public:
	TreeNode* red(TreeNode *root){
		unordered_set<TreeNode*> m; 
		return copy(root, m); 
	}
	TreeNode* copy(TreeNode* node, unordered_set<TreeNode*>& m){
		if (!node)return nullptr; 
		if (m.count(node)) return nullptr; 
		m.insert(node); 
		TreeNode *cur = new TreeNode(node->val); 
		cur->left = copy(node->left, m); 
		cur->right = copy(node->right, m); 
		return cur; 
	}
};


class Solution3{
public:
	int maxpath(TreeNode* root){
		return m(root); 
	}
	int m(TreeNode* n){
		if (!n) return 0; 
		return n->val + max(m(n->left), m(n->right)); 
	}
};

class Solution4{
public:
	unordered_map<int, bool> m; 
	bool canIWin(int maxChoosableInteger, int desiredTotal) {
		if (desiredTotal == 0) return true; 
		if (maxChoosableInteger*(maxChoosableInteger + 1) < 2 * desiredTotal) return false; 
		return win(maxChoosableInteger, desiredTotal, 0); 
	}
	bool win(int maxInt, int target, int v){
		if (target <= 0) return false; 
		if (m.count(v)) return m[v]; 
		bool res = false; 
		for (int i = 1; i <= maxInt; ++i){
			if (!(v&(1 << i - 1))){
				res |= !win(maxInt, target - i, v | (1 << i - 1)); 
			}
		}
		m[v] = res; 
		return res; 
	}
};


class Solution5{
public:
	int cicleMaxSub(vector<int>& nums){
		int localMax = nums[0], localMin = nums[0], gmax = INT_MIN, gmin = INT_MAX;
		int tot = 0; 
		for (int i = 1; i < nums.size(); ++i){
			if (localMax > 0){
				localMax += nums[0]; 
				localMin = nums[0]; 
			}
			else{
				localMax = nums[0]; 
				localMin += nums[0]; 
			}
			gmax = max(gmax, localMax); 
			gmin = min(gmin, localMin); 
			tot += nums[i]; 
		}

		return max(gmax, tot - gmin); 
	}
};


bool backspace(string s, string t){
	int sbs = 0, tbs = 0; 
	int i = s.size() - 1, j = t.size() - 1; 
	while (1){
		while (i >= 0 && (sbs > 0 || s[i] == '#')){
			if (s[i] == '#')
				sbs += 1;
			else
				sbs -= 1; 
			--i; 
		}
		while (j >= 0 && (tbs > 0 || t[i] == '#')){
			if (t[i] == '#')
				tbs += 1;
			else
				tbs -= 1; 
			--j; 
		}
		if (i == -1 && j == -1) return true; 
		if (i == -1 || j == -1) return false; 
		if (s[i] != s[j]) return false; 
		--i, --j; 
	}

	return false; 
}

int maxdist(vector<int>& nums){
	int i = -1, j = 0; 
	int maxLen = nums.size(), start = 0; 
	for (; j < nums.size(); ++j){
		if (nums[j] == 1){
			int curLen; 
			if (i == -1)
				curLen = j;
			else
				curLen = (j - i - 1) / 2;
			if (maxLen < curLen){
				maxLen = curLen; 
				start = i; 
			}
			i = j; 
		}
	}
	if (maxLen < nums.size() - i - 1){
		maxLen = nums.size() - i - 1; 
		start = i; 
	}
	return maxLen; 
}

class SegmentTree{
public:
	struct node{
		int max; 
		int lb, rb; 
		node *left, *right; 
		node(int a, int b, int c) :max(a), lb(b), rb(c), left(nullptr), right(nullptr) {}
	};

	node *root; 
	SegmentTree(vector<int>& nums){
		root = build(nums, 0, nums.size() - 1); 
	}

	node* build(vector<int>& nums, int left, int right){
		if (left > right) return nullptr; 
		node * cur = new node(nums[left], left, right); 
		if (left == right) return cur; 

		int mid = left + (right - left) / 2; 
		node *head = build(nums, left, mid),
			*tail = build(nums, mid + 1, right); 
		cur->left = head, cur->right = tail; 
		cur->max = max(head->max, tail->max); 

		return cur; 
	}

	int search(node* n, int left, int right){
		if (!n) return INT_MIN; 
		if (n->lb == left && n->rb == right)
			return n->max; 

		int mid = n->lb + (n->rb - n->lb) / 2; 
		if (left > mid)
			return search(n->right, mid + 1, right);
		else if (right <= mid)
			return search(n->left, left, mid); 
		else{
			int lres = search(n->left, left, mid),
				rres = search(n->right, mid + 1, right); 
			return max(lres, rres); 
		}
	}

	void modify(node* n,  int idx, int newval){
		if (!n) return; 
		if (n->rb < idx || n->lb>idx) return; 
		if (n->lb == idx && n->rb == idx){
			n->max = newval; 
			return; 
		}

		int mid = n->lb + (n->rb - n->lb) / 2;

		if (idx <= mid)
			modify(n->left, idx, newval);
		else
			modify(n->right, idx, newval); 

		n->max = max(n->left->max, n->right->max); 
	}
};


struct Trie22{
	struct node{
		bool isWord; 
		string word; 
		vector<node*> childs; 
		node() :childs(256), isWord(false) {}
	};

	node *root; 
	Trie22() :root(new node) {}

	void insert(node* root, string s){
		node *p = root; 
		for (char c : s){
			int i = c; 
			if (p->childs[i] == nullptr)
				p->childs[i] = new node(); 
			p = p->childs[i]; 
		}
		p->isWord = true; 
		p->word = s; 
	}
	
	vector<int> search2(string& s, int i){
		node* p = root; 
		vector<int> res; 

		for (; i < s.size(); ++i){
			int idx = s[i]; 
			if (p->childs[idx] == nullptr)
				break; 
			p = p->childs[idx]; 
			if (p->isWord)
				res.push_back(i); 
		}
		return res; 
	}
};

struct TurnBold{
	string bold(string sentence, vector<string> dict){
		Trie22 t; 
		for (string& s : dict)
			t.insert(t.root, s); 

		vector<vector<int>> ranges; 
		for (int i = 0; i < sentence.size(); ++i){
			vector<int> ends = t.search2(sentence, i); 
			for (int x : ends)
				ranges.push_back({ i, x }); 
		}

		prt2Layer(ranges); 

		auto newrange = merge_range(ranges);
		prt2Layer(newrange); 
		return ""; 
	}

	vector<vector<int>> merge_range(vector<vector<int>>& ranges){
		map<int, int> terminals; 
		for (auto& v : ranges){
			terminals[v[0]] += 1; 
			terminals[v[1]] -= 1; 
		}

		vector<vector<int>> res; 
		int tracker = 0, start;
		for (auto& p : terminals){
			if (tracker == 0)
				start = p.first; 
			tracker += p.second; 
			if (tracker == 0){
				res.push_back({ start, p.first }); 
			}
		}

		return res; 
	}
};


int getNth(vector<int>& nums, int k){
	return qs(nums, 0, nums.size() - 1, k);
}
int qs(vector<int>& nums, int left, int right, int k){

}
class Solution {
public:
	bool isNumber(string s) {
		
	}
};





int main() {
	TurnBold tb; 
	vector<string> vs = { "eb", "bc", "a" }; 
	string sent = "ebcda"; 
	tb.bold(sent, vs); 


	Solution4 a; 
	cout << a.canIWin(10, 11) << endl; 
	cout << a.canIWin(5, 50) << endl; 


	vector<int> v1 = { 1, 0, 0, 0, 1, 0, 1 },
		v2 = { 1, 0, 0, 0 },
		v3 = { 0, 0, 0, 0, 1, 0, 0 },
		v4 = { 0, 0, 1, 0, 0, 1, 0, 0, 0, 0 },
		v5 = { 0, 1, 1, 1, 0, 0, 1, 0, 0 }; 





	vector<vector<int>> b = {
		{ 0, 0, 1, 0, 0 },
		{ 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 1, 0 },
		{ 1, 1, 0, 1, 1 },
		{ 0, 0, 0, 0, 0 }
	};

	vector<vector<int>> bb = {
		{ 3, 0, 1, 4, 2 },
		{ 5, 6, 3, 2, 1 },
		{ 1, 2, 0, 1, 5 },
		{ 4, 1, 0, 1, 7 },
		{ 1, 0, 3, 0, 5 }
	};


	vector<pair<string, string>> f = {
		{ "MUC", "LHR" }, { "JFK", "MUC" }, { "SFO", "SJC" }, { "LHR", "SFO" }
	};


	vector<pair<int, int>> cc = { { 0, 3 }, { 1, 3 }, { 2, 3 }, { 4, 3 }, { 5, 4 } };

	vector<vector<int>> dd = {
		{ INT_MAX, -1, 0, INT_MAX },
		{ INT_MAX, INT_MAX, INT_MAX, -1 },
		{ INT_MAX, -1, INT_MAX, -1 },
		{ 0, -1, INT_MAX, INT_MAX },
	};


	vector<int> nums = { 2, 6, 7, 8, 12, 4, 9 };



	//TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
														new TreeNode(4)),
									new TreeNode(8, new TreeNode(7),
														new TreeNode(9)));
	/*      6
		3       8
	1    4   7    9
	*/

	TreeNode* tree2 = new TreeNode(1, new TreeNode(3, nullptr, nullptr), nullptr); 

	TreeNode* tree3 = new TreeNode(6, nullptr,
									new TreeNode(8, nullptr,
														new TreeNode(9)));
	/*      6
		       8
					9
	*/

	TreeNode *redu = new TreeNode(10); 
	TreeNode* tree4 = new TreeNode(6, new TreeNode(3, new TreeNode(1),
														new TreeNode(4, nullptr, redu)),
									new TreeNode(8, new TreeNode(7),
														redu));
	/*      6
		3       8
	1    4   7     9
	*/

}

