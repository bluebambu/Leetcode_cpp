#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each

using namespace std;

inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}

class Solution
{
public:
    /////////////////////////////////////////////////////////
    int removeDuplicates(int a[], int n)
        {
            if(n==0) return 0;
            int idx = 0;
            for(int i=1; i<n;++i)
            {
                if(a[i] != a[i-1])  // 这里可以是 i-1， 也可以是idx-1。 但如果gap >1 则只能用 idx-gap。
                    a[++idx]=a[i];
            }

            return idx+1;
        }

/////////////////////////////////////////////
    int removeDuplicates3(int a[], int n)
    {
        int new_inx = 0;
        int ptr=1;

        for(;ptr<n;++ptr)
        {
            if(a[ptr]!=a[new_idx])
            {
                a[++new_inx]=a[ptr];
            }
        }

        return new_inx+1;
    }
};

int main()
{
    Solution a;
    int b[] = {1,1,1,1,3,3,4,5,6,6,6,6,7,7,8,9,11,14,14};
    cout<<"size = "<<a.removeDuplicates3(b, sizeof(b)/sizeof(int))<<endl;

    for(auto i:b)
        cout<<i<<",";
}
