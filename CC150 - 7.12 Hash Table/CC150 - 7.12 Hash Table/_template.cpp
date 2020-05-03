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

using namespace std;

inline int exchg(int &a, int &b)  { int c = a; a = b; b = c; }
inline int log2(int N){ return log10(N) / log10(2); }
inline float min(float a, float b) { return a<b ? a : b; }

template<typename T, typename K>
struct Node {
	K key; 
	T value;
	Node(K x, T y) :key(x), value(y) {}
};

template<typename T, typename K>
class HashTable {
protected:
	vector<list<Node<T,K>>> table; 
	int size;
	int capacity;  // 按道理， size == capacity时就应该 rehash， 保证 O(1) 
public:


	HashTable();

	int HashCode(K k); 

	bool insert(K k, T t); 

	bool del(K k);

	void resize(int newSize);

	int sz();
	int cp(); 
};

template<typename T, typename K>
HashTable< T,  K>::HashTable() :size(0), capacity(10), table(capacity) {}

template<typename T, typename K>
int HashTable< T,  K>::HashCode(K k){
	return 5%capacity;
}

template<typename K> // 错误的， 不能只partial specify一个member function，必须partial 整个class！！！！
int HashTable<string, K>::HashCode(string s){
	int result = 0; 
	for (auto i : s)
		result = 31 * result + i; 
	return result%capacity; 
}

template<typename T, typename K>
bool HashTable< T,  K>::insert(K k, T t){
	int hcode = HashCode(k); 
	list<Node>& curList = table[hcode];  
	for (auto iter = curList.begin(); iter != curList.end(); ++iter){
		if (iter->key == k){
			iter->value = t;
			return false;
		}
	}
	curList.push_back(Node(k, t));
	size++; 
	return true; 
}

template<typename T, typename K>
bool HashTable<T, K>::del(K k){
	int hcode = HashCode(k);
	list<Node>& curList = table[hcode];
	for (auto iter = curList.begin(); iter != curList.end(); ++iter){
		if (iter->key == k){
			curList.erase(iter); 
			size--;
			return true; 
		}
	}
	return false; 
}

template<typename T, typename K>
void HashTable<T, K>::resize(){
	if (capacity < 2 * size)
		return; 
	vector<list<Node>> oldtable = table; 
	table = vector<list<Node>>(2 * capacity);
	capacity *= 2; 
	size = 0; 
	for (int i = 0; i < oldtable.size(); ++i){
		list<Node>& curList = oldtable[i]; 
		for (Node& node : curList){
			insert(node.key, node.value); 
		}
	}
	
}

int main(){


}