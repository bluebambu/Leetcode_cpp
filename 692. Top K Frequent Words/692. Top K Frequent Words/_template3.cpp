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
	typedef pair<string, int> PST; 
    vector<string> topKFrequent(vector<string>& words, int k) {
		unordered_map<string, int> m; 
		for (auto& w : words) m[w] += 1; 
		struct l{ bool operator()(const PST&a, const PST&b){ return a.second < b.second; } }; 
		multiset<PST, l> pq;
		for (auto p : m){
			if (pq.size() < k)
				pq.insert(p); 
			else if (pq.size() == k && pq.begin()->second < p.second){
				pq.erase(pq.begin()); 
				pq.insert(p); 
			}
		}
		vector<string> res; 
		for (auto&p : pq) res.push_back(p.first); 
		return res; 
    }
};


class Solution2 {
public:
	struct node{ 
		bool isWord; 
		string word; 
		vector<node*> childs; 
		node() :isWord(false), childs(26) {}
	};
	struct Trie{
		node *root; 
		int size; 
		Trie() :root(new node), size(0){}
		void add(string s){
			node *p = root; 
			for (auto c : s){
				int idx = c - 'a'; 
				if (p->childs[idx] == nullptr)
					p->childs[idx] = new node(); 
				p = p->childs[idx]; 
			}
			p->isWord = true; 
			p->word = s; 
			++size; 
		}

		vector<string> getAll(){
			vector<string> res; 
			dfs(root, res); 
			return res; 
		}
		void dfs(node*n, vector<string>& res){
			if (!n) return; 
			if (n->isWord) res.push_back(n->word); 
			for (auto& nxt : n->childs)
				dfs(nxt, res); 
		}

	};

	vector<string> topKFrequent(vector<string>& words, int k) {
		unordered_map<string, int> m; 
		for (auto& w : words) m[w] += 1; 
		vector<Trie> buckets(words.size() + 1); 
		for (auto&p : m) buckets[p.second].add(p.first); 
		vector<string> res; 
		for (int i = words.size(); i >= 0; --i){
			if (buckets[i].size){
				auto curb = buckets[i].getAll(); 
				res.insert(res.end(), curb.begin(), curb.end()); 
			}
			if (res.size() >=k)
				break;
		}
		return vector<string>(res.begin(), res.begin() + k); 
	}
}; 

int main(){
	Solution a;

	vector<string> d = { "i", "love", "leetcode", "i", "love", "coding" }; 

	auto b = a.topKFrequent(d, 2); 
	prt1Layer(b); 

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

