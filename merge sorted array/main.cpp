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


class Solution {
public:
    void merges(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        for(int i=m+n-1; i>=0; --i){
            if(m==0 && n!=0){
                nums1[i]=nums2[n-1];
                --n;
            }else if(n==0)
                break;
            else if(nums1[m-1]>nums2[n-1]){
                nums1[i]=nums1[m-1];
                --m;
            }else{
                nums1[i]=nums2[n-1];
                --n;
            }
        }
    }
};


int main()
{
    Solution a;

    vector<int> intset1 {1,3,4,5,6,0,0,0,0};
    vector<int> intset2 {2, 7,8,9};

    a.merges(intset1, 5, intset2, 4);

    for(auto i:intset1)
    {
            cout<<i<<" ";

    }
}
