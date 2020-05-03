// _template.cpp : Defines the entry point for the console application.
//
#include <stdafx.h>

#include <iostream>
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

// ////////////////////////////////////////////////////////////////
// Design a search autocomplete system for a search engine. Users may input a sentence (at least one word and end with a special character '#'). For each character they type except '#', you need to return the top 3 historical hot sentences that have prefix the same as the part of sentence already typed. Here are the specific rules:
// The hot degree for a sentence is defined as the number of times a user typed the exactly same sentence before. 
// The returned top 3 hot sentences should be sorted by hot degree (The first is the hottest one). If several sentences have the same degree of hot, you need to use ASCII-code order (smaller one appears first). 
// If less than 3 hot sentences exist, then just return as many as you can.
// When the input is a special character, it means the sentence ends, and in this case, you need to return an empty list.
// Your job is to implement the following functions:
// The constructor function:
// AutocompleteSystem(String[] sentences, int[] times): This is the constructor. The input is historical data. Sentences is a string array consists of previously typed sentences. Times is the corresponding times a sentence has been typed. Your system should record these historical data.
// Now, the user wants to input a new sentence. The following function will provide the next character the user types: 
// List<String> input(char c): The input c is the next character typed by the user. The character will only be lower-case letters ('a' to 'z'), blank space (' ') or a special character ('#'). Also, the previously typed sentence should be recorded in your system. The output will be the top 3 historical hot sentences that have prefix the same as the part of sentence already typed.

// Example:
// Operation: AutocompleteSystem(["i love you", "island","ironman", "i love leetcode"], [5,3,2,2]) 
// The system have already tracked down the following sentences and their corresponding times: 
// "i love you" : 5 times 
// "island" : 3 times 
// "ironman" : 2 times 
// "i love leetcode" : 2 times 
// Now, the user begins another search: 

// Operation: input('i') 
// Output: ["i love you", "island","i love leetcode"] 
// Explanation: 
// There are four sentences that have prefix "i". Among them, "ironman" and "i love leetcode" have same hot degree. Since ' ' has ASCII code 32 and 'r' has ASCII code 114, "i love leetcode" should be in front of "ironman". Also we only need to output top 3 hot sentences, so "ironman" will be ignored. 

// Operation: input(' ') 
// Output: ["i love you","i love leetcode"] 
// Explanation: 
// There are only two sentences that have prefix "i ". 

// Operation: input('a') 
// Output: [] 
// Explanation: 
// There are no sentences that have prefix "i a". 

// Operation: input('#') 
// Output: [] 
// Explanation: 
// The user finished the input, the sentence "i a" should be saved as a historical sentence in system. And the following input will be counted as a new search. 

// Note:
// The input sentence will always start with a letter and end with '#', and only one blank space will exist between two words. 
// The number of complete sentences that to be searched won't exceed 100. The length of each sentence including those in the historical data won't exceed 100. 
// Please use double-quote instead of single-quote when you write test cases even for a character input.
// Please remember to RESET your class variables declared in class AutocompleteSystem, as static/class variables are persisted across multiple test cases. Please see here for more details.



// both hashtable and trie should be fine
// pass AC
class AutocompleteSystem {
public:
	string data; 
	unordered_map<string, int> dict; 
	typedef pair<string, int> PSI; 

	AutocompleteSystem(vector<string> sentences, vector<int> times) {
		for (int i = 0; i < sentences.size(); ++i){
			dict[sentences[i]] += times[i]; 
		}
	}

	vector<string> input(char c) {
		if (c == '#'){
			dict[data] += 1; 
			data.clear();
			return {};
		}

		data.push_back(c); 

		// pq, 比较的operator 方向是相反的。 
		auto cmp = [](const PSI& a, const PSI& b){
			return a.second > b.second || (a.second == b.second && a.first < b.first); 
		};

		priority_queue<PSI, vector<PSI>, decltype(cmp)> pq(cmp); 

		for (auto a : dict){
			bool match = true; 
			for (int i = 0; i < data.size(); ++i){
				if (i >= a.first.size() || data[i] != a.first[i]){
					match = false; 
					break;
				}
			}
			if (match){
				pq.push(a); 
				if (pq.size() > 3){
					pq.pop(); 
				}
			}
		}

		vector<string> res(pq.size()); 
		for (int i = pq.size() - 1; i >= 0; i--) {
			res[i] = pq.top().first;
			pq.pop();
		}
		return res; 
	}
};





class AutocompleteSystem2 {
public:
	unordered_map<string, int> coutmap; 
	unordered_map<string, unordered_set<string>> strmap; 
	string data; 
	
	AutocompleteSystem2(vector<string> sentences, vector<int> times) {
		coutmap.clear(); 
		strmap.clear(); 

		for (int i = 0; i < sentences.size(); ++i){
			coutmap[sentences[i]] += times[i]; 
			addStr(sentences[i]); 
		}
	}

	vector<string> input(char c) {
		if (c == '#'){
			addStr(data); 
			coutmap[data] += 1; 
			data.clear();
			return{}; 
		}

		data.push_back(c); 

		if (strmap.count(data) == 0)
			return{}; 

		unordered_set<string>& results = strmap[data]; 

		typedef pair<string, int> PSI; 
		
		auto cmp = [](const PSI& a, const PSI& b){
			return a.second > b.second || (a.second == b.second && a.first < b.first); 
		}; 

		priority_queue<PSI, vector<PSI>, decltype(cmp)> pq(cmp); 

		for (string s : results){
			pq.push(make_pair(s, coutmap[s])); 
			if (pq.size() > 3)
				pq.pop(); 
		}

		vector<string> res(pq.size()); 
		for (int i = pq.size() - 1; i >= 0; --i){
			res[i] = pq.top().first; 
			pq.pop(); 
		}
		return res; 

	}

	void addStr(string s){
		string tmp; 
		for (int i = 0; i < s.size(); ++i){
			tmp.append(1, s[i]); 
			strmap[tmp].insert(s); 
		}
	}
};



// trie
// should pass AC, but memory limit reached!!
class AutocompleteSystem3 {
public:
	typedef pair<string, int> PSI; 

	struct cmp{
		bool operator()(PSI& a, PSI& b){
			return a.second > b.second || (a.second == b.second && a.first < b.first);
		}
	};

	typedef priority_queue<PSI, vector<PSI>, cmp> PQPSI; 

	struct node{
		bool flag; 
		int count; 
		string fullstr; 
		vector<node*> childs; 

		node() :flag(false), count(0), childs(256, nullptr) {}
	};

	struct trie{
		node *root; 
		trie() :root(new node()) {}

		void addStr(string s, int cnt){
			node* p = root; 
			for (int i = 0; i < s.size(); ++i){
				if (p->childs[s[i]] == nullptr){
					p->childs[s[i]] = new node();
				}
				p = p->childs[s[i]] ; 
			}
			if (p->flag == false){
				p->flag = true;
				p->fullstr = s; 
			}
			p->count += cnt; 
		}

		vector<string> search(string pre){
			node *p = root; 
			for (int i = 0; i < pre.size(); ++i){
				if (p->childs[pre[i]] == nullptr)
					return {};
				p = p->childs[pre[i]]; 
			}

			PQPSI pq; 
			
			findall(p, pq); 

			vector<string> res(pq.size()); 

			for (int i = res.size() - 1; i >= 0; --i){
				res[i] = pq.top().first; 
				pq.pop(); 
			}
			return res; 
		}

		void findall(node* p, PQPSI& pq){
			if (p->flag){
				pq.push(make_pair(p->fullstr, p->count)); 
				if (pq.size() > 3)
					pq.pop(); 
			}
			for (int i = 0; i < 256; ++i){
				if (p->childs[i] != nullptr){
					findall(p->childs[i], pq); 
				}
			}
		}
	};


	string data;
	trie tree; 

	AutocompleteSystem3(vector<string> sentences, vector<int> times):tree() {
		for (int i = 0; i < sentences.size(); ++i){
			tree.addStr(sentences[i], times[i]); 
		}
	}

	vector<string> input(char c){
		if (c == '#'){
			tree.addStr(data, 1); 
			data.clear(); 
			return {}; 
		}

		data.push_back(c);

		return tree.search(data); 
	}
};



int main(){

	vector<int> b = { 7, 2, 5, 10, INT_MAX };

	vector<string> vstr = { "i love", "i live", "island", "abcd" }; 
	vector<int>		vc = { 5, 3, 2, 1 }; 

	AutocompleteSystem3 a(vstr, vc);

	prt1Layer(a.input('i')); 
	prt1Layer(a.input(' ')); 
	prt1Layer(a.input('#')); 
	
	



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

	return 0; 
}

