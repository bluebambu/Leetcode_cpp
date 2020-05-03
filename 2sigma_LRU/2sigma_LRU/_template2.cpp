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
#include <cassert>

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

// using STL::list to make the linked list

struct node{
	int key; 
	int val; 
	node(){}
	node(int x, int y) :key(x), val(y) {}
};

class LRUCache{
	// there must be a capacity there!!!
	int cap; 
	list<node> chain; 
	unordered_map<int, list<node>::iterator> m; 
public:
	LRUCache(int capacity) {
		cap = capacity; 
	}

	void put(int k, int v){
		if (m.count(k) == 0){
			// remember to check the capacity
			if (chain.size() == cap){
				m.erase(chain.back().key); 
				chain.pop_back(); 
			}
			chain.push_front(node(k, v)); 
			m[k] = chain.begin(); 
		}
		else{
			m[k]->val = v; 
			chain.splice(chain.begin(), chain, m[k]); 
			m[k] = chain.begin(); 
		}
	}

	int get(int k){
		if (m.count(k) == 0)
			return -1; 

		chain.splice(chain.begin(), chain, m[k]); 
		m[k] = chain.begin(); 
		return m[k]->val;
	}
};


// what if not using stl list
// pass AC
struct node2 {
	int key;
	int val;
	node2 *prev, *next; 
	node2():key(-1), val(-1), prev(nullptr),next(nullptr) {}
	node2(int x, int y) :key(x), val(y),prev(nullptr),next(nullptr) {}
}; 

class LRUCache2{
	int cap; 
	node2 *head, *tail; 
	unordered_map<int, node2*> m; 
public:
	LRUCache2(int c) :cap(c), head(new node2),tail(new node2) {
		head->next = tail; 
		tail->prev = head; 
	}

	void put(int k, int v){
		if (k < 0){
			cout << "negative key\n"; 
			return; 
		}
		if (m.count(k) == 0){
			if (m.size() == cap){
				node2* todel = tail->prev; 
				detach(todel); 
				m.erase(todel->key); 
				todel->prev = nullptr; 
				todel->next = nullptr; 
				delete todel; 
			}
			node2* toadd = new node2(k, v); 
			insert(head, toadd); 
			m[k] = toadd; 
		}
		else{
			node2 *tomodify = m[k]; 
			tomodify->val = v; 
			detach(tomodify); 
			insert(head, tomodify); 
		}
	}

	int get(int k){
		if (m.count(k) == 0)
			return -1; 
		node2 *tomove = m[k]; 
		detach(tomove); 
		insert(head, tomove); 
		return tomove->val; 
	}

	void prnt(){
		node2* tmp = head; 
		while (tmp->next != tail){
			tmp = tmp->next; 
			cout << tmp->key << "," << tmp->val << "-> "; 
		}
		cout << endl; 
	}

private:
	void insert(node2* a, node2* b){
		node2* anext = a->next; 
		a->next = b; 
		b->next = anext; 
		anext->prev = b; 
		b->prev = a; 
	}

	void detach(node2* a){
		node2* pre = a->prev; 
		node2* nxt = a->next; 
		pre->next = nxt; 
		nxt->prev = pre; 
	}

	public:
	int size(){ return m.size();  }
};

void TEST_lru_put(){
	LRUCache2 lru(2);
	lru.put(1, 1); 
	lru.put(2, 2); 
	lru.put(3, 3); 
	assert(lru.get(1) == -1); 
	assert(lru.get(2) == 2); 

	lru.put(4, 4); 

	lru.get(1); 

	lru.get(3); 

	lru.get(4); 

	assert(lru.get(4) == 4); 

}


void TEST_lru_zero_cap(){
	LRUCache2 lru(0);
	lru.put(1, 1); 
	lru.put(1, 1); 
	lru.put(1, 1); 
	lru.put(1, 1); 
	lru.put(1, 1); 
	assert(lru.get(2) == -1); 
}

void TEST_lru_put_negative(){
	LRUCache2 lru(100); 
	lru.put(-1, 8); 
}


//
class LRUCache3{
	int cap; 
	list<node> chain; 
	unordered_map<int, list<node>::iterator> m; 
public:
	LRUCache3(int x) :cap(x) { }

	void put(int k, int v){
		if (k < 0)
			return; 

		if (m.count(k) == 0){
			if (m.size() == cap){
				m.erase(chain.back().key); 
				chain.pop_back(); 
			}
			chain.push_front(node(k, v)); 
			m[k] = chain.begin(); 
		}
		else{
			m[k]->val = v; 
			chain.splice(chain.begin(), chain, m[k]); 
			m[k] = chain.begin(); 
		}
	}

	int get(int k){
		if (m.count(k) == 0)
			return -1; 
		chain.splice(chain.begin(), chain, m[k]); 
		m[k] = chain.begin(); 
		return m[k]->val; 
	}
};


class LRUCache4{
public:
	struct node{
		string key; 
		int value; 
		node *prev, *next; 
		node() :value(0) {}
		node(string x, int y) :key(x), value(y), prev(nullptr), next(nullptr) {}
	};

	unordered_map<string, node*> kit; 
	node *head, *tail; 
	int cap; 

	LRUCache4(int x):head(new node), tail(new node), cap(x) {
		head->next = tail; 
		tail->prev = head; 
	}
	
	void put(string k, int v){
		if (kit.count(k)){
			kit[k]->value = v; 
		}
		else{
			if (cap <= 0){ // special case!!!
				return; 
			}
			if (kit.size() == cap){
				node* todel = tail->prev; 
				detach(todel); 
				kit.erase(todel->key); 
				delete todel; 
			}
			node* toadd = new node(k, v); 
			insert(head, toadd); 
			kit[k] = toadd; 
		}
	}

	int get(string k){
		if (kit.count(k) == 0)
			return -1; 
		node* it = kit[k]; 
		detach(it); 
		insert(head, it); 
		return it->value;
	}
	
	void detach(node* cur){
		node *p = cur->prev,
			*n = cur->next; 
		p->next = n; 
		n->prev = p; 
		cur->prev = cur->next = nullptr; 
	}

	void insert(node*pos, node* toPut){
		node* n = pos->next; 
		pos->next = toPut; 
		toPut->next = n; 
		toPut->prev = pos; 
		n->prev = toPut; 
	}

	string getMostRecent(){
		if (kit.size() > 0)
			return head->next->key;
		else
			return "null"; 
	}

	

};

void TEST_LRU_super_set(){
	LRUCache4 lru(1000); 

	for (int i = 0; i < 10000; ++i){
		lru.put(to_string(i), i); 
	}

	assert(lru.get("9999") == 9999); 
	assert(lru.get("1000") == -1); 
	assert(lru.get("9000") == 9000); 
	assert(lru.getMostRecent() == "9000"); 
	assert(lru.get("1000") == -1); 
	assert(lru.getMostRecent() == "9000"); 
	assert(lru.get("9999") == 9999); 
	assert(lru.getMostRecent() == "9999"); 
}

void TEST_LRU_zero_cap(){
	LRUCache4 lru(0); 

	for (int i = 0; i < 10000; ++i){
		lru.put(to_string(i), i); 
	}

	assert(lru.get("9999") == -1); 
	assert(lru.get("1000") == -1); 
	assert(lru.get("9000") == -1); 
	assert(lru.getMostRecent() == "null"); 
}

class LRUCache5{
public:
	struct node{
		string key;
		int value;
		node *prev, *next;
		node() :value(0) {}
		node(string x, int y) :key(x), value(y), prev(nullptr), next(nullptr) {}
	};

	node *head, *tail; 
	int cap;
	unordered_map<string, node*> kit;

	LRUCache5() :head(new node), tail(new node), cap(10) {}

	void put(string k, int v){
		// remember, if k exit, you don't have to del the node. You just update it!!!!!
		if (kit.size() == cap){
			node* todel = tail->prev; 
			detach(todel); 
			kit.erase(todel->key); 
			delete todel; 
		}
		node* newnode = new node(k, v); 
		insert(head, newnode); 
		kit[k] = newnode; 
	}

	void detach(node *n){
		node *p = n->prev, *nxt = n->next; 
		p->next = nxt; nxt->prev = p; 
		n->prev = n->next = nullptr; 
	}

	void insert(node *pos, node *toput){
		node* nxt = pos->next; 
		pos->next = toput; 
		toput->next = nxt; 
		nxt->prev = toput; 
		toput->next = pos; 
	}
}; 



int main(){
	TEST_LRU_super_set(); 
	TEST_LRU_zero_cap(); 

	LRUCache4 lru(2); 
	lru.put("1", 1); 
	lru.put("2", 2); 
	lru.put("3", 4); 
	cout<< lru.get("3")<<endl; 
	cout<< lru.get("1")<<endl; 


	vector<int> b = { 4, 1, -9, 0, INT_MAX }; 


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

