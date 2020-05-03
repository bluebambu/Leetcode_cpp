#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>
#include <string>

using namespace std;

inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}
inline float min(float a, float b) {return a<b?a:b;}

struct TreeNode
{
    TreeNode(int a):val(a), left(nullptr), right(nullptr) {}
    TreeNode(int a, TreeNode* x, TreeNode* y):val(a), left(x), right(y) {}
    TreeNode():val(0), left(nullptr), right(nullptr) {}

    int val;
    TreeNode *left;
    TreeNode *right;

};

class Raddix_LSD
{
public:
    void LSD(vector<string>& vstr){
        const int Ab = 256;

        int maxSize=0;

        for(auto& i:vstr)
            maxSize = max(maxSize, (int)i.size());

        /// radiix sort 要从最后一位开始向第一位排序， 因为人类读string的时候， 默认是所有string的第一位对齐，且从第一位开始排序。 试比较  z  与  az
        /// 若从第一位开始排， z > az.  若从尾部开始排， az>z.
        /// radiix sort work 的关键因素之一是 它是 stable sort， 所以一旦某一位上排好序， 排另一位的时候， 之前的位的顺序不变。
        for(int d=maxSize-1; d>=0; --d){
        // for(int d=0; d<maxSize; ++d){
            vector<int> count(256+2, 0);

            for(int i=0; i<vstr.size(); ++i)
                count[charAt(vstr[i],d)+2]+=1;

            for(int i=1; i<count.size(); ++i)
                count[i]+=count[i-1];

            vector<string> aux(vstr.size());

            for(int i=0; i<vstr.size(); ++i)
                aux[count[charAt(vstr[i],d)+1]++]=vstr[i];

            vstr = aux;
        }
    }

    int charAt(string& str, int d){
        int ch=0;
        if(d>=str.size())
            ch=-1;
        else
            ch=str[d];
        return ch;
    }

};

int main()
{
    Raddix_LSD a;

    vector<string> ss{"slkjf","a","db","34","abcc","zzzzz","z","yui"};
    a.LSD(ss);

    for(auto i:ss)
        cout<<i<<endl;
}
