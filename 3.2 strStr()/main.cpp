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
    char *strStr(const char *haystack, const char *needle)
    {
        if(!needle) return nullptr;
        if(!haystack) return nullptr;

        char *i=(char*)haystack, *j=(char*)needle;

        while(*i!='\0')
        {
            j=(char*)needle;
            char* tmp=i;

            while(1)
            {


                if(*j=='\0') return i;

                if(*tmp == '\0') return nullptr;
                // 用 \0 判断终点可行，但是要放在上面
                // 那句的后面

                if(*tmp==*j)
                {
                    ++tmp;
                    ++j;
                }


                else
                    break;
            }

            ++i;
        }


    }

    // 按leetcode 的写一个

    char *strStr2(const char *haystack, const char *needle)
    {
        // 先找到两个数组的end 的地址
        char *hay_end = (char*) haystack;
        for(int i=0; haystack[i]!='\0';++i)
            hay_end++;
        // hay_end 现在是 haystack 的 \0

        char *needle_end = (char*) needle;
        for(int i=0; needle[i]!='\0';++i)
            needle_end++;

        for(char * i = (char*)haystack;1 ;)
        {
            char *hay_tmp = i;
            char *needle_tmp = (char*)needle;

            while(*hay_tmp == *needle_tmp)
            {
                if(needle_tmp==needle_end-1)
                    return i;

                if(hay_tmp==hay_end) return nullptr;

                ++hay_tmp;
                ++needle_tmp;
            }



            ++i;
        }


    }

    char *strStr3(const char *haystack, const char *needle)
    {
        char* p1=const_cast<char*>(haystack);
        char* p2=const_cast<char*>(needle);

        while(*p1)
        {
            p2=const_cast<char*>(needle);

            if(*p1==*p2)
            {
                auto q1=p1;
                while( *p2 && *q1 && *q1==*p2)
                {
                    ++p2;
                    ++q1;
                }

                if(*p2==0) return p1;

            }

            ++p1;
        }

        return nullptr;
    }


};

int main()
{
    Solution a;
    char b[] ="therearenothingslikeyou";
    char c[]="arenothings";

    char* d=a.strStr3(b, c);
//    for(auto i=0;i<a.size();++i)
    if(d) cout<<*d;
    else cout<<"No match!";

}
