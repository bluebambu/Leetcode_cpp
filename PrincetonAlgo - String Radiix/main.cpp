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

        /// radiix sort Ҫ�����һλ��ʼ���һλ���� ��Ϊ�����string��ʱ�� Ĭ��������string�ĵ�һλ���룬�Ҵӵ�һλ��ʼ���� �ԱȽ�  z  ��  az
        /// ���ӵ�һλ��ʼ�ţ� z > az.  ����β����ʼ�ţ� az>z.
        /// radiix sort work �Ĺؼ�����֮һ�� ���� stable sort�� ����һ��ĳһλ���ź��� ����һλ��ʱ�� ֮ǰ��λ��˳�򲻱䡣
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
