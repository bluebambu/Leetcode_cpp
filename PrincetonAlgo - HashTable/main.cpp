#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>
#include <string>
#include <sstream>

using namespace std;

inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}
inline float min(float a, float b) {return a<b?a:b;}

struct HashNode;


string NumToStr(int num){
    string result;
    stringstream ss;

    ss<<num;
    ss>>result;
    return result;
}

string NumToStr2(int num){
    bool sign = num>0 ? true : false;
    string result = sign ? "" : "-";

    int n=abs(num), pos=1;

    while(n/10){
        n/=10;
        pos*=10;
    }

    n=abs(num);

    while(pos){
        int curNum = n/pos;
        n%=pos;
        pos/=10;
        result.push_back('0'+curNum);
    }
    return result;
}


struct HashNode{
    string key;
    int val;
    HashNode* next;

    HashNode(string a, int b):key(a),val(b),next(nullptr) {}
};

/// don't use STL list
class Hash_chaining
{
private:
    int HashSize;
    int HashSeed;

    vector<HashNode*>    HashContainer;
    int length=0;
public:
    Hash_chaining():HashSize(100),HashSeed(3),HashContainer(HashSize, nullptr) {}

    int HashCode(string s){
        int hashcode=0;
        for(char& i:s)
            hashcode += hashcode*HashSeed + i;
        return hashcode;
    }

    bool insert(string key, int val){
        int hashcode = HashCode(key);
        int containIndex = hashcode%HashSize;

        if(HashContainer[containIndex]==nullptr)
            HashContainer[containIndex] = new HashNode(key, val);
        else{
            HashNode* iter;
            for(iter = HashContainer[containIndex]; iter->next!=nullptr; iter=iter->next); // 写错了， 要先找key
            iter->next = new HashNode(key, val);

            if(iter->next==nullptr) return false;
        }

        length++;

        return true;
    }

    int search(string key){
        int containIndex = HashCode(key)%HashSize;
        HashNode* iter;
        for(iter = HashContainer[containIndex]; iter!=nullptr; iter=iter->next){
            if(iter && iter->key == key)
                return iter->val;
        }

        cout<< "no matches!";
    }

    void del(string key){
        int containIndex = HashCode(key)%HashSize;
        if(HashContainer[containIndex]==nullptr)
            return;
        HashNode *prev=nullptr, *&iter=HashContainer[containIndex];
        while(iter && iter->key != key){
            prev=iter;
            iter=iter->next;
        }
        if(!iter)
            return;
        if(!prev){
            delete iter;
            iter=nullptr;
        }else{
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
    Hash_list():capacity(20), total(0), container(capacity) {} /// 初始化vector。 同时应该给capacity赋一个大的初值， capacity是0的话不好操作也不符合实际情况。

    int HashCode(string s){
        int hash=0;
        for(char& i : s)
            hash += 31*hash + i;
        return hash%capacity;
    }

    void rehash(){
        if(total > capacity ){  /// expand space
            vector<list<pair<string, int>>> oldcont = container;
            container.clear();
            container.resize(2*capacity);
            capacity*=2;
            total = 0; /// caution!!

            for(auto i:oldcont)
                for(auto j:i)
                    insert(j.first, j.second);
        }
        else if(total < capacity/4){  /// shrink space . 其实最好和 expand space 分开， 因为 insert不可能call shrink， 而  del 也不可能调用 expand。
            vector<list<pair<string, int>>> oldcont = container;
            container.clear();
            container.resize(capacity/2);
            capacity/=2;
            total=0;

            for(auto& i:oldcont)
                for(auto& j:i)
                    insert(j.first, j.second);
        }
    }

    bool insert(string key, int val){
        if(total > capacity)
            rehash();

        int hash = HashCode(key);
        list<pair<string, int>>& curList = container[hash];

        for(auto iter=curList.begin(); iter!=curList.end(); ++iter){
            if(iter->first == key){
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

        for(auto iter=curList.begin(); iter!=curList.end(); ++iter){
            if(iter->first == key){
                return &(*iter);
            }
        }

        return nullptr;
    }

    bool del(string key){
        rehash();
        int hash = HashCode(key);
        list<pair<string, int>>& curList = container[hash];

        for(auto iter=curList.begin(); iter!=curList.end(); ++iter){
            if(iter->first == key){
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



int main()
{
    Hash_list a;

    for(int i=0; i<10; ++i){
        a.insert(NumToStr2(i),i);
        cout<<a.HashCode(NumToStr(i))<<" ";
    }

    cout<<endl;

    cout<<"size: "<<a.size()<<endl;
    cout<<"capacity: "<<a.cap()<<endl;

    for(int i=0; i<10; ++i){
       if(a.find(NumToStr(i)))
            cout<<((a.find(NumToStr(i)))->second);
    }

    a.del("3");
        cout<<endl;

    cout<<"size: "<<a.size()<<endl;
    cout<<"capacity: "<<a.cap()<<endl;
    for(int i=0; i<10; ++i){
       if(a.find(NumToStr(i)))
            cout<<((a.find(NumToStr(i)))->second);
    }

    cout<<endl<<endl;

    for(int i=0; i<9; ++i){
       a.del(NumToStr(i));
       cout<<a.HashCode(NumToStr(i))<<" ";
    }




}
