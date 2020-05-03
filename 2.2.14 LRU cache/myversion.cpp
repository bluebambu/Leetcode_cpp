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

inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}
inline float min(float a, float b) {return a<b?a:b;}

///////////// Leetcode passed /////////////////////////////
class LRUCache{
public:
    class node{
    public:
        int key;
        int val;
        node* prev;
        node* next;
        node(int x, int y):key(x), val(y) {}
    };

    list<node> nlist;
    unordered_map<int, list<node>::iterator> hashmap;
    int cap;

    LRUCache(int capacity):cap(capacity) {
    }

    int get(int key) {
        if(hashmap.find(key)==hashmap.end()) return -1;
        auto iter = hashmap[key];
        nlist.splice(nlist.begin(), nlist, iter);
        hashmap[key]=nlist.begin();
        return hashmap[key]->val;
    }

    void set(int key, int value) {
        if(hashmap.find(key)==hashmap.end()){
            if(nlist.size()==cap){  /// 用hashtable的size（） 会快一些
                hashmap.erase(nlist.back().key);  // remember to delete the key in hashmap!
                nlist.pop_back();
            }
            nlist.insert(nlist.begin(), node(key, value));
            hashmap[key]=nlist.begin();
        }else{
            hashmap[key]->val = value;
            nlist.splice(nlist.begin(), nlist, hashmap[key]);
            hashmap[key]=nlist.begin();
        }
    }
};

///////passed/////////
class LRUCache{
private:
    int size=0;
    list<pair<int, int>> cl;
    unordered_map<int, list<pair<int, int>>::iterator> map;

public:
    LRUCache(int capacity) {
        size=capacity;
    }

    int get(int key) {
        if(map.find(key)==map.end()) return -1;
        auto iter = map[key];
        cl.splice(cl.begin(), cl, iter);
        map[key] = cl.begin();
        return cl.begin()->second;
    }

    void set(int key, int value) {
        if(map.find(key) == map.end()){
            if(map.size() == size){
                int tmpkey = cl.back().first;
                cl.pop_back();
                map.erase(tmpkey);
            }
            cl.push_front(make_pair(key, value));
            map[key]=cl.begin();
        }else{
            cl.splice(cl.begin(), cl, map[key]);
            map[key] = cl.begin();
            cl.begin()->second = value;
        }
    }
};

