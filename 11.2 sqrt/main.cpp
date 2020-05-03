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

    // ���� long ����ֹ����ķ���������leetcode
    int sqrt2(int x) {
        int left = 1, right = x / 2;
        int last_mid; // ��¼���һ�� mid

        if (x < 2) return x;

        while(left <= right) {
            const int mid = left + (right - left) / 2;
            if(x / mid > mid) { // ��Ҫ�� x > mid * mid�������
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

    //////////////  ţ�ٵ����� ///////////
    int mySqrt(int x) {
        long long r = x;
        while (r*r > x)
            r = (r + x/r) / 2;
        return r;
    }
//////////////////////////////////
    int mySqrt(int x) {
        if(x<2) return x;
        long r = x*0.5; // Ҫ���� r<x/2 ����������Ҫ��0 �� 1 ��ժ������
        while (r*r > x)
              r = (r + x/r) / 2;
        return r;
    }
///////////// leetcode passed , best !!  /////////////////////////////
    int mySqrt(int x) {
        if(x<=0) return 0;
        if(x==1) return 1;

        int start=1, end=x/2+1;
        /// +1 ��ר��Ϊ x=2 �ṩ�ģ� ��Ϊ x==2ʱ�� mid==end�� ������������condition !!!!

        while(start<end){
            int mid=start+(end-start)/2;
            if(mid<=x/mid && (mid+1)>x/(mid+1)) return mid;
            if(x/mid>mid) start=mid+1;
            else end=mid-1;
        }
        return start;
    }

    /// Ҳ�����ѡ��
    int mySqrt(int x) {
        if(x<2) return x;

        int i=1, j=x/2; /// x�����1��ʼ�� ����x=0��  x/mid ������ˣ� ��x��1��ʼ�� ����ζ��x=2ʱ�� mid == end�� �������������� ��������������� һ��������ķ����� ��һ������
                        /// i<=j �� j=mid-1�� ����Χ��� [left, right], ���return���� j�� ������j-1

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
