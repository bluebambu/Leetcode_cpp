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

int dp[20];

int factorial(int a)
{
    if(a==0) return 1;
    if(a==1) return 1;

    dp[a]=a*factorial(a-1);
    return dp[a];

}

class Solution
{
public:
    vector<int> PermutationSequence(vector<int> &num, int k)
    {
        vector<int> temp (num);

        sort(temp.begin(), temp.end());


        unordered_map<int, pair<int,bool>> idx;

        for(int i=0;i<temp.size();++i)
        {
            idx[i+1]=pair<int,bool>(temp.at(i),true);
        }

        vector<int> temp2;

        for(int i=1; i<=num.size();++i)
        {
            int j = (k-1)/factorial(num.size()-i)+1;
            // 321， 第6号permutation，除2得3，再加1 到4了，显然是不对的。所以要这么处理。

            int m=0;
            int n=1;

            while(n<=idx.size() )
            {
                if(idx[n].second==true) ++m;
                if(m==j) break;
                ++n;
            }

            temp2.push_back(idx[n].first);

            idx[n].second=false;

            k = (k-1)%factorial(num.size()-i)+1;
            // 想象一下 321， 除去3之后，余数应该是2，但实际上是0，所以需要这么写！！！ 细节！！！
        }

        return temp2;
    }

};

int main()
{
    Solution a;
    int b[] = {1,3,5,7,9};
    int c[] = {2,4, 6, 8,10};
    vector<int> d {1,3,2,4, 5,6,7,8,9};
    int fff=123268;

//    for(;fff<555;++fff)
//    {

    cout<< "the k value is: " << fff<<endl;

    vector<int> len_final (a.PermutationSequence(d,fff));

    for(auto i : len_final)
        cout<<i<<",";
    cout<<endl;
//
//    }
}
