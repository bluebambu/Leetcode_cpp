// _template4.cpp : Defines the entry point for the console application.
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

typedef vector<int> VI; 
typedef vector<VI> VVI; 
typedef pair<int, int> PII; 

VVI dirs = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } }; 


class Hashtable {
public:
	struct Node{
		string key; 
		int val;
		Node *prev, *next;
	};
	int cap, size; 
	vector<Node*> chain; 
	Hashtable(int x) :cap(x), size(0), chain(cap) {}

	int calcHash(string key){
		int hash = 0; 
		for (auto c : key)
			hash = 31 * hash + c - 'a'; 
		return hash; 
	}
	int get(string key){
		int h = calcHash(key); 
		int pos = h%cap; 
		for (Node* p = chain[pos]; p; p = p->next){
			if (p->key == key)
				return p->val; 
		}
		return INT_MIN; 
	}

	void put(string key, int val){
		if (size == cap){
			rehash(); 
		}
		int h = calcHash(key), pos = h%cap; 
		
	}

	void rehash(){
		int newcap = cap * 2; 
		vector<Node*> oldChain = chain; 
		chain.clear(); 
		cap *= 2; 
		size = 0; 
		chain.resize(cap); 

		for (Node* n : oldChain){
			for (Node*p = n; p; p = p->next){
				put(p->key, p->next); 
				delete p; 
			}
		}
	}
};

/////////////////////////==================== My old code, but good code =====================================

struct HashNode;


string NumToStr(int num){
	string result;
	stringstream ss;

	ss << num;
	ss >> result;
	return result;
}

string NumToStr2(int num){
	bool sign = num > 0 ? true : false;
	string result = sign ? "" : "-";

	int n = abs(num), pos = 1;

	while (n / 10){
		n /= 10;
		pos *= 10;
	}

	n = abs(num);

	while (pos){
		int curNum = n / pos;
		n %= pos;
		pos /= 10;
		result.push_back('0' + curNum);
	}
	return result;
}


struct HashNode{
	string key;
	int val;
	HashNode* next;

	HashNode(string a, int b) :key(a), val(b), next(nullptr) {}
};

/// don't use STL list
class Hash_chaining
{
private:
	int HashSize;
	int HashSeed;

	vector<HashNode*>    HashContainer;
	int length = 0;
public:
	Hash_chaining() :HashSize(100), HashSeed(3), HashContainer(HashSize, nullptr) {}

	int HashCode(string s){
		int hashcode = 0;
		for (char& i : s)
			hashcode += hashcode*HashSeed + i;
		return hashcode;
	}

	bool insert(string key, int val){
		int hashcode = HashCode(key);
		int containIndex = hashcode%HashSize;

		if (HashContainer[containIndex] == nullptr)
			HashContainer[containIndex] = new HashNode(key, val);
		else{
			HashNode* iter;
			for (iter = HashContainer[containIndex]; iter->next != nullptr; iter = iter->next); // 写错了， 要先找key
			iter->next = new HashNode(key, val);

			if (iter->next == nullptr) return false;
		}

		length++;

		return true;
	}

	int search(string key){
		int containIndex = HashCode(key) % HashSize;
		HashNode* iter;
		for (iter = HashContainer[containIndex]; iter != nullptr; iter = iter->next){
			if (iter && iter->key == key)
				return iter->val;
		}

		cout << "no matches!";
	}

	void del(string key){
		int containIndex = HashCode(key) % HashSize;
		if (HashContainer[containIndex] == nullptr)
			return;
		HashNode *prev = nullptr, *&iter = HashContainer[containIndex];
		while (iter && iter->key != key){
			prev = iter;
			iter = iter->next;
		}
		if (!iter)
			return;
		if (!prev){
			delete iter;
			iter = nullptr;
		}
		else{
			prev->next = iter->next;
			delete iter;
		}
	}

	int size(){
		return length;
	}
};



/// use STL list
class Hash_list{
private:
	int capacity;
	int total;
	vector<list<pair<string, int>>> container; /// 只声明， 不初始化
public:
	Hash_list() :capacity(20), total(0), container(capacity) {} /// 初始化vector。 同时应该给capacity赋一个大的初值， capacity是0的话不好操作也不符合实际情况。

	int HashCode(string s){
		int hash = 0;
		for (char& i : s)
			hash += 31 * hash + i;
		return hash%capacity;
	}

	void rehash(){
		if (total > capacity){  /// expand space
			vector<list<pair<string, int>>> oldcont = container;
			container.clear();
			container.resize(2 * capacity);
			capacity *= 2;
			total = 0; /// caution!!

			for (auto i : oldcont)
				for (auto j : i)
					insert(j.first, j.second);
		}
		else if (total < capacity / 4){  /// shrink space . 其实最好和 expand space 分开， 因为 insert不可能call shrink， 而  del 也不可能调用 expand。
			vector<list<pair<string, int>>> oldcont = container;
			container.clear();
			container.resize(capacity / 2);
			capacity /= 2;
			total = 0;

			for (auto& i : oldcont)
				for (auto& j : i)
					insert(j.first, j.second);
		}
	}

	bool insert(string key, int val){
		if (total > capacity)
			rehash();

		int hash = HashCode(key);
		list<pair<string, int>>& curList = container[hash];

		for (auto iter = curList.begin(); iter != curList.end(); ++iter){
			if (iter->first == key){
				iter->second = val;
				return true;
			}
		}

		curList.push_back(make_pair(key, val));
		total++;
		return true;
	}

	pair<string, int>* find(string key){
		int hash = HashCode(key);
		list<pair<string, int>>& curList = container[hash];

		for (auto iter = curList.begin(); iter != curList.end(); ++iter){
			if (iter->first == key){
				return &(*iter);
			}
		}

		return nullptr;
	}

	bool del(string key){
		rehash();
		int hash = HashCode(key);
		list<pair<string, int>>& curList = container[hash];

		for (auto iter = curList.begin(); iter != curList.end(); ++iter){
			if (iter->first == key){
				curList.erase(iter);
				--total;
				return true;
			}
		}
		return false;
	}

	int size(){
		return total;
	}

	int cap(){
		return capacity;
	}
};


class Hashtable2{
	struct Node{
		string key; 
		int val; 
		Node(string a, int b) :key(a), val(b) {}
	};

	int cap, size; 
	vector<list<Node>> chain; 
public:
	Hashtable2(int x) :cap(x), size(0), chain(10) {}
	void put(string key, int val){
		int h = getHash(key); 
		if (size == cap)
			rehash(); 

		list<Node> &bucket = chain[h]; 
		for (auto iter = bucket.begin(); iter != bucket.end(); ++iter){
			if (iter->key == key){
				iter->val = val;
				return; 
			}
		}

		bucket.emplace_back(key, val); 
	}

	int get(string& key, int val){
		int h = getHash(key); 
		list<Node> &bucket = chain[h]; 
		for (auto iter = bucket.begin(); iter != bucket.end(); ++iter){
			if (iter->key == key){
				return iter->val = val;
			}
		}

		return -1; 
	}

	int getHash(string key){
		int hash = 1; 
		for (auto c : key)
			hash = hash * 31 + c - 'a'; 
		return hash%cap; 
	}

	void rehash(){
		cap *= 2; 
		vector<list<Node>> new_chain; 
		for (int i = 0; i < chain.size(); ++i){
			list<Node> &list = chain[i]; 
			for (auto iter = list.begin(); iter != list.end(); ){
				string k = iter->key; 
				int new_h = getHash(k); 
				auto old_iter = iter; 
				++iter; 

				new_chain[new_h].splice(new_chain[new_h].end(), list, old_iter); 
			}
		}
		chain = new_chain; 
	}
};


int main() {
	Hash_list a;

	for (int i = 0; i < 10; ++i){
		a.insert(NumToStr2(i), i);
		cout << a.HashCode(NumToStr(i)) << " ";
	}

	cout << endl;

	cout << "size: " << a.size() << endl;
	cout << "capacity: " << a.cap() << endl;

	for (int i = 0; i < 10; ++i){
		if (a.find(NumToStr(i)))
			cout << ((a.find(NumToStr(i)))->second);
	}

	a.del("3");
	cout << endl;

	cout << "size: " << a.size() << endl;
	cout << "capacity: " << a.cap() << endl;
	for (int i = 0; i < 10; ++i){
		if (a.find(NumToStr(i)))
			cout << ((a.find(NumToStr(i)))->second);
	}

	cout << endl << endl;

	for (int i = 0; i < 9; ++i){
		a.del(NumToStr(i));
		cout << a.HashCode(NumToStr(i)) << " ";
	}

}

