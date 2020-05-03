#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each

using namespace std;

inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}
inline float min(float a, float b) {return a<b?a:b;}

class Solution
{
public:
    float FindMedianSortedArray2(int a[], int m, int b[], int n, int k){
            //always assume that m is equal or smaller than n, 可以不用处理两种情况！！！
            //if (m > n) return find_kth(B, n, A, m, k);
            if(k==0) return 0;
            if(k==1) return min(a[0], b[0]);

            if(m==0) return b[k-1];
            if(n==0) return a[k-1];

            int temp = k/2;

            if(m < temp)
            {
                if(a[m-1] > b[k-m-1]) return a[m-1];
                else return b[k-m-1];
            }

            if(n < temp)
            {
                if(b[n-1] > a[k-n-1]) return b[n-1];
                else return a[k-n-1];
            }

            if( a[temp-1] > b[temp-1]) return FindMedianSortedArray2(a, m, b+temp, n-temp, k-temp);
            if( a[temp-1] < b[temp-1]) return FindMedianSortedArray2(a+temp, m-temp, b, n, k-temp);

        }

    float FindMedianSortedArray3(int a[], int m, int b[], int n, int k){
            if(m<n) return FindMedianSortedArray3(b, n, a, m, k);

            if(k==1) return min(a[0], b[0]);

            int mid = k/2;

            if(n<mid)
            {
                if(b[n-1]<a[n-1]) return a[(k-n)-1];
                else return FindMedianSortedArray3(a+n, m-n, b, n, k-n);
            }

            else
            {
                if(a[mid-1] > b[mid-1]) return FindMedianSortedArray3(a, m, b+mid, n-mid, k-mid);
                else return FindMedianSortedArray3(a+mid, m-mid, b, n, k-mid);
            }

    }

    ////////////////////////   Leetcode passed , too ugly  ////////////////////////
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if(nums1.size() > nums2.size()) return findMedianSortedArrays(nums2, nums1);
        if(nums1.empty() && nums2.empty()) return 0;


         int len = nums1.size() + nums2.size();
         int mid = (len+1)/2;
         double median=0;

         int i1=-1, i2=-1;
         int rest=mid;

         while(1){
            /// 有一条array走完的情况
            if(i1==nums1.size()-1 || i2==nums2.size()-1) {
                 median = (i1==nums1.size()-1) ? nums2[i2+=rest] : nums1[i1+=rest];
                 break;
            }
            /// 仅剩1个元素
            if(rest==1){
                median = nums1[i1+1] < nums2[i2+1] ? nums1[++i1] : nums2[++i2];
                break;
            }

            int seperate = rest/2;
            int forw1=0, forw2=0;

            /// array1 扩展遇到结尾
            if(i1+seperate >= nums1.size())
                forw1=nums1.size()-1;
            else
                forw1=i1+seperate;

            int gap1 = forw1 - i1;
            int gap2 = rest - gap1;

            forw2 = i2 + gap2;
            /// 正常比较
            if(nums1[forw1] < nums2[forw2]){
                i1=forw1;
                rest-=gap1;
            }else{
                i2=forw2;
                rest-=gap2;
            }
         }
        /// 考虑偶数个总数， median 是两个数的平均
         if(len%2==0) {
             double median_even;
                /// arr1 走到结尾
             if( i1+1 > int(nums1.size()-1)){
                 median_even = nums2[++i2];
             }else{
                /// arr2 走到结尾
                 if(i2+1 > int(nums2.size()-1)){
                     median_even = nums1[++i1];
                 }else
                    median_even = (nums1[i1+1] < nums2[i2+1]) ? nums1[++i1] : nums2[++i2];
             }
             median = (median+median_even)/2;
         }
         return median;
    }
};

int main()
{
    Solution a;
    int b[] = {1,3,5,7,9};
    int c[] = {2,4,6,8,10};
    float len_final = a.FindMedianSortedArray3(b, sizeof(b)/sizeof(float),c, sizeof(c)/sizeof(float), 4);
    cout<<"result = "<<len_final<<endl;

    for(float i : b)
        cout<<i<<",";
    cout<<endl;
    for(float i : c)
        cout<<i<<",";
}
