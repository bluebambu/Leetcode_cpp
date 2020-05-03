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


struct Node {
	string key; 
	int value; 
	Node(string x, int y) :key(x), value(y) {}
};

class LRUCache
{
	list<Node> cache; 
	unordered_map<string, list<Node>::iterator> map; 
	int capacity;
	int size; 
public:
	LRUCache():capacity(10) {}

	bool insert(string key, int val){
		if (map.find(key) == map.end()){
			if (size == capacity){
				Node tmp = cache.back(); 
				map.erase(tmp.key); 
				size--; 
				cache.pop_back(); 
			}
			cache.push_front(Node(key, val));
			size++;
			map[key] = cache.begin(); 
			return true; 
		}
		else{
			auto iter = map[key];
			map.erase(key); 
			Node tmp = *iter;
			tmp.value = val; 
			cache.erase(iter); 
			cache.push_front(tmp); 
			map[key] = cache.begin(); 
			return false; 
		}
	}

	bool del(string key){
		if (map.find(key) == map.end()){
			return false; 
		}
		else{
			auto iter = map[key]; 
			map.erase(key); 
			cache.erase(iter); 
			size--; 
			return true; 
		}
	}

	int sz(){ return size;  }

};




int main()
{
	LRUCache a; 

	for (int i = 0; i < 12; ++i){
		string tmp = "kkk";
		tmp.push_back('0' + i); 
		a.insert(tmp, i); 
	}

	cout << a.sz();

	for (int i = 0; i < 12; ++i){
		string tmp = "kkk";
		tmp.push_back('0' + i);
		cout<<endl<<a.insert(tmp, i);
	}


}

