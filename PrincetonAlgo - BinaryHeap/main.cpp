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

struct TreeNode;
void print();

inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}
inline float min(float a, float b) {return a<b?a:b;}

class BinaryHeap{
private:
    int arr[100]={0};
    int size=0;
    int capacity=100;
public:
    void swim(int k){
        while(k>0 && arr[k]>arr[(k-1)/2]){
            exchg(arr[k], arr[(k-1)/2]);
            k=(k-1)/2;
        }
    }
    /**
    void sink(int k){
        while(2*k+2<size && !(arr[k] > arr[2*k+1] && arr[k] > arr[2*k+2])){
            int j = arr[2*k+1] > arr[2*k+2] ? (2*k+1) : (2*k+2) ;
            exchg(arr[j], arr[k]);
            k=j;
        }
    }
    */ /// 这么写是错的， 因为不能保证 k 节点一定同时有 左子树 和 右子树

    /// 这才是正确的写法！ 先判断左树存在， 再判断右树存在！
    void sink(int k){
        while(2*k+1<size){
            int j=2*k+1;
            if(j+1<size && arr[j]<arr[j+1])
                j+=1;
            if(arr[k]>arr[j])
                break;
            exchg(arr[k], arr[j]);
            k=j;
        }
    }

    void insert(int k){
        if(size==capacity)
            throw runtime_error("Overflow");
        arr[size]=k;
        swim(size);
        size++;
    }

    void DelTop(){
        if(!size)
            throw runtime_error("Empty heap");
        exchg(arr[0], arr[size-1]);
        size--;
        sink(0);
    }

    int top(){
        if(!size)
            throw runtime_error("Empty heap");
        return arr[0];
    }

    int s(){
        return size;
    }

    void heapify(){  /// heapify 只需要 sink 操作，不需要 swim
        for(int i=size/2-1; i>=0; --i)
            sink(i);
    }

    void prt(){
        for(int i=0; i<size; ++i)
            cout<<arr[i]<<" ";
        cout<<endl;
    }
};

void build(vector<int>& v){
    int n=v.size();

    /// heapify first
    for(int i=n/2-1; i>=0; --i){
        while(2*i+1 < n){
            int j=2*i+1;
            if(j+1<n && v[j+1]>v[j]) j=j+1;
            if(v[i]>v[j]) break;
            exchg(v[i], v[j]);
            i=j;
        }
    }

    /// continue to pop next
    int nn=n;
    for(int i=0; i<nn; ++i){
        exchg(v[0], v[n-1]);
        n-=1;

        int k=0;
        while(2*k+1 < n){
            int kk=2*k+1;
            if(kk+1<n && v[kk+1]>v[kk])
                kk+=1;
            if(v[k] > v[kk])
                break;
            exchg(v[k], v[kk]);
            k=kk;
        }
    }
}


int main(){
    vector<int> vec({6,5,7,4,32,1,2,0,56,113,17,8});
    build(vec);

    for(auto i:vec)
        cout<<i<<" ";

    cout<<endl<<endl<<endl;

    BinaryHeap a;

    for(int i=0; i<10; ++i){
        a.insert((i-5)*(i-5));
        //a.prt();
    }

    // a.heapify();

    for(int i=0; i<10; ++i){
        //a.prt();
        a.DelTop();
    }
}
