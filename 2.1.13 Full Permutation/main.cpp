#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>

using namespace std;

inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}
inline float min(float a, float b) {return a<b?a:b;}

class Solution
{
public:
    void SequencePermutation(string str, int i, int j, int k)
    // 模仿 {} 的permutation，这里我用 i， j， k 记录 1，2，3 的剩余个数
    {
        if(i==0 && j==0 && k==0)
        {
            cout<<str<<endl;
        }

        if(i!=0)
            SequencePermutation(str+"1", i-1, j, k);
        if(j!=0)
            SequencePermutation(str+"2", i, j-1, k);
//        if(k!=0)
//            SequencePermutation(str+"3", i, j, k-1);
    }

};

int main()
{
    Solution a;
    int b[] = {1,3,5,7,9};
    int c[] = {2,4, 6, 8,10};
    vector<int> d {1,299,54,2,645,4,6,3};

    string bff;
    a.SequencePermutation(bff,2,1,0);

//    float len_final = a.FindMedianSortedArray2(b, sizeof(b)/sizeof(float),c, sizeof(c)/sizeof(float), 8);
//    cout<<"result = "<<len_final<<endl;
//
//    for(float i : b)
//        cout<<i<<",";
//    cout<<endl;
//    for(float i : c)
//        cout<<i<<",";
}
