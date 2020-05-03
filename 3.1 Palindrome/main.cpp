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
    bool isPalindrome(string &str)
    // Ҫע��strΪ�ջ���ֻ��һ��Ԫ�ص������
    {
        if(str.begin()==str.end()-1) return true;
        // ��һ�ж��� null ��string��˵��false�ģ���Ϊbegin������end������������......
        // �������code�ö� null str �Ľ��Ϊ true
        // ��ü�һ�� if����str��

        transform(str.begin(), str.end(), str.begin(), ::tolower);

        for(auto i=str.begin(),
                 j=str.end()-1; i<j ; )
        {
            if(*i>'z' || *i<'a') { ++i; continue; }
            if(*j>'z' || *j<'a') { --j; continue; }

            if(*i==*j) {++i;--j;continue;}
            if(*i!=*j) return false;


        }

        return true;


    }

    bool  isPalindrome2(string &str)
    {
        if(str.size()<=1) return 1;

        transform(str.begin(), str.end(), str.begin(), ::tolower);

        auto lp = str.begin();
        auto rp = str.end()-1;

        while(lp<=rp)
        {
            if(*lp < 'a' || *lp > 'z')
                {++lp; continue; }
            if(*rp < 'a' || *rp > 'z')
                {--rp; continue;}
            if(*lp == *rp)
            {
                ++lp ; --rp;
            }
            else
            {
                return false;
            }
        }

        return true;

    }

    bool isPalindrome(string s) { // ����ȷ�𰸡� ����Ķ�û�п��� ���������� ���
        if(s.size()<2) return true;

        transform(s.begin(), s.end(), s.begin(), ::tolower);
        int i=0, j=s.size()-1;

        while(i<j){
            if(!isalnum(s[i])) ++i;
            else if(!isalnum(s[j])) --j;
            else if(s[i]!=s[j]) return false;
            else {++i; --j;}
        }

        return true;
    }
};

int main()
{
    Solution a;
    string b("!!!");

    auto c=a.isPalindrome3(b);
//    for(auto i=0;i<a.size();++i)
        cout<<c;

}
