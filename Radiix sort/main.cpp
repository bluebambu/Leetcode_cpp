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

int maxdigit(vector<int>& arr){
    int maxnum=INT_MIN;

    for(auto i:arr)
        maxnum=max(i, maxnum);
    return maxnum;
}

void countsort(vector<int>& arr, int exp){
    // cur digit = arr[i]/exp%10
    int counting[10]={0};
    int output[arr.size()] = {0};

    for(int i=0; i<arr.size(); ++i)
        counting[(arr[i]/exp)%10]++;

    for(int i=1; i<10; ++i)
        counting[i]+=counting[i-1];

    for(int i=arr.size()-1; i>=0; --i){
    //  这个地方必须 从 N 到 0， 详细解释见笔记本
    // 大致是为了不破坏上一层排列好的上一位的顺序。
    // 原因是上一个循环， 累加的方向是从 0 到 N， 故这个循环是N->0,
    // 类似于 stack
        output[counting[(arr[i]/exp)%10]-1]=arr[i];
        counting[(arr[i]/exp)%10]--;
    }

    for(int i=0; i<arr.size(); ++i)
        arr[i]=output[i];
}

void radiixsort(vector<int>& arr, int maxnum){
    for(int exp=1; maxnum/exp>0; exp*=10)
        countsort(arr, exp);
//    for(auto i:arr)
//        cout<<i<<" ";
}






int main(){
    vector<int> arr =  {170, 45, 75, 90, 802, 24, 2, 66};
    int m = maxdigit(arr);
    radiixsort(arr, m);
    for(auto i:arr)
        cout<<i<<" ";
}
