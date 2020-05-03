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



class LRUCache
{
     typedef list<pair<int, int>> LL;
     typedef unordered_map<int, LL::iterator> hash_i_it;

     LL cache;      // 缓存容器
     hash_i_it hash;       // 缓存哈希
     int capacity;   // 缓存容量

public:
     LRUCache(int capacity) : capacity(capacity) {}

     int get(int key)
     {
         auto it = hash.find(key);   // 在Hash中查找
         if(it == hash.end())        // 如果没找到，返回-1
             return -1;

         putFirst(it -> second);     // 把key对应节点放到链表头部
         hash[key] = cache.begin();  // 更新Hash中key对应的值

         return it -> second -> second;
     }

     void set(int key, int value)
     {
         auto it = hash.find(key);               // 在Hash中查找
         if(it != hash.end())                    // 如果找到
         {
             putFirst(it -> second);             // 把key对应节点放到链表头部
             cache.begin() -> second = value;    // 更新对应value的值
         }
         else                                    // 如果没找到
         {
             if(cache.size() == capacity)        // 如果缓存已满
             {
                 hash.erase(cache.back().first); // 在Hash中删除最后节点对应的key
                 cache.pop_back();               // 删除最后节点
             }
             cache.push_front({key, value});     // 在头部插入新节点(key,value)
         }

         hash[key] = cache.begin();              // 更新Hash中key对应的值
     }
private:
     // 把it指向的节点放到链表头部
     void putFirst(LL::iterator it)
     {
         auto c = *it;           // 记录当前节点
         cache.erase(it);        // 删除当前节点
         cache.push_front(c);    // 将已记录的节点插到头部
     }
};



class LRUCache{

private:
    struct CacheNode {
        int key;
        int value;
        CacheNode(int k, int v) :key(k), value(v){}
    };

private:
    list<CacheNode> cacheList;
    // 注意 第二个元素是 iterator
    unordered_map<int, list<CacheNode>::iterator> cacheMap;
    int capacity;

public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }

    int get(int key) {
        if (cacheMap.find(key) == cacheMap.end()) return -1;
        // 把当前访问的节点移到链表头部，并且更新 map 中该节点的地址
        cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
        cacheMap[key] = cacheList.begin();
        return cacheMap[key]->value;
    }

    void set(int key, int value) {
        if (cacheMap.find(key) == cacheMap.end()) {
            if (cacheList.size() == capacity) { //删除链表尾部节点（最少访问的节点）
                cacheMap.erase(cacheList.back().key);
                cacheList.pop_back();
            }
            // 插入新节点到链表头部, 并且在 map 中增加该节点
            cacheList.push_front(CacheNode(key, value));
            cacheMap[key] = cacheList.begin();
        } else {
            //更新节点的值，把当前访问的节点移到链表头部, 并且更新 map 中该节点的地址
            cacheMap[key]->value = value;
            cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
            cacheMap[key] = cacheList.begin();
        }
    }

};



int main()
{
    list<int> ll={1,2,3,4,5};
    unordered_map<int, list<int>::iterator> hashm;
     auto t=ll.begin();
    for(int i=0; i<ll.size(); ++i){
        hashm[i]=t++;
    }
    cout<<*hashm[0];
    ll.splice(ll.begin(), ll, hashm[4]);
    cout<<*ll.begin()<<endl;
    cout<<*hashm[4]<<endl;

    for(auto i:ll)
        cout<<i;

    priority_queue<int> q;

    for(int n : {1,8,5,6,3,4,0,9,7,2})
        q.push(n);

    cout<<q[4];
}
