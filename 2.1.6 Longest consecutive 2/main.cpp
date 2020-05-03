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
inline int max(int a , int b) {return a>b?a:b;}


class Solution
{
public:
    int LongestConsecutive(const vector<int> &num)
    //use hashmap, complex O(N)

    {
        unordered_map<int, bool> num_hash;

        for(auto i:num) num_hash[i]=true;

        int longest=0, length;

        for(auto i:num)
        {
            if(!num_hash[i]) continue;

            length=1;

            for(auto j=i+1; num_hash.find(j)!=num_hash.end();j++)
            {
                num_hash[j]=false;
                ++length;
            }

            for(auto j=i-1; num_hash.find(j)!=num_hash.end();--j)
            {
                num_hash[j]=false;
                ++length;
            }

            longest = max(length, longest);
        }

        return longest;


    }

};

int main()
{
    Solution a;
    const vector<int> b {1,299,54,2,645,4,6,3};
    int len_final = a.LongestConsecutive(b);
    cout<<"result = "<<len_final<<endl;

    for(int i=0;i<len_final;++i)
        cout<<b.at(i)<<",";
}
