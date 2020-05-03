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


class Solution
{
public:
    int sqrt(int x) {
        long long i = 0;
        long long j = x / 2 + 1;
        while (i <= j)
        {
            long long mid = (i + j) / 2;
            long long sq = mid * mid;
            if (sq == x) return mid;
            else if (sq < x) i = mid + 1;
            else j = mid - 1;
        }
        return j;
    }

    // 不用 long 来防止溢出的方法，来自leetcode
    int sqrt2(int x) {
        int left = 1, right = x / 2;
        int last_mid; // 记录最近一次 mid

        if (x < 2) return x;

        while(left <= right) {
            const int mid = left + (right - left) / 2;
            if(x / mid > mid) { // 不要用 x > mid * mid，会溢出
                left = mid + 1;
                last_mid = mid;
            } else if(x / mid < mid) {
                right = mid - 1;
            } else {
                return mid;
            }
        }
        return last_mid;
    }

    //////////////  牛顿迭代法 ///////////
    int mySqrt(int x) {
        long long r = x;
        while (r*r > x)
            r = (r + x/r) / 2;
        return r;
    }
//////////////////////////////////
    int mySqrt(int x) {
        if(x<2) return x;
        long r = x*0.5; // 要想用 r<x/2 的条件，需要把0 和 1 先摘出来。
        while (r*r > x)
              r = (r + x/r) / 2;
        return r;
    }
///////////// leetcode passed , best !!  /////////////////////////////
    int mySqrt(int x) {
        if(x<=0) return 0;
        if(x==1) return 1;

        int start=1, end=x/2+1;
        /// +1 是专门为 x=2 提供的， 因为 x==2时， mid==end， 不符合搜索的condition !!!!

        while(start<end){
            int mid=start+(end-start)/2;
            if(mid<=x/mid && (mid+1)>x/(mid+1)) return mid;
            if(x/mid>mid) start=mid+1;
            else end=mid-1;
        }
        return start;
    }

    /// 也不错的选择
    int mySqrt(int x) {
        if(x<2) return x;

        int i=1, j=x/2; /// x必须从1开始， 否则x=0，  x/mid 就溢出了！ 而x从1开始， 则意味着x=2时， mid == end， 出现上面的情况。 解决方法有两个， 一个是上面的方法， 再一个就是
                        /// i<=j 和 j=mid-1， 将范围变成 [left, right], 最后return得是 j， 而不是j-1

        while(i<=j){
            int mid = i+(j-i)/2;
            if(mid<=x/mid && (mid+1)>x/(mid+1))
                return mid;
            else if(mid<x/mid)
                i=mid+1;
            else
                j=mid-1;
        }
        return j;
    }


///////////// leetcode passed, not quite self-explanatory ////////////////////
    int mySqrt(int x) {
        if(x<2) return x;
        int l=1, r=x/2;

        while(l<=r){
            int mid=l+(r-l)/2;
            if(mid>x/mid) r=mid-1;
            else l=mid+1;
        }
        return r;
    }
};


int main()
{
    Solution a;

    vector<int> intset {1,2,3};

    auto b = a.sqrt3(6);


            cout<<b<<" ";
     cout<<endl;

}
