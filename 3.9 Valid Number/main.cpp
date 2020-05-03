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
    bool isNumber(const char *s, int len)
    {
        if(s==nullptr) return false;

        bool dotFlag(false);

        for(int i=0 ; i<len ; ++i)
        {
            switch(s[i])
            {
            case '+':
            case '-':
                if(

                   (i!=0 && !((s[i-1]=='e' || s[i-1]=='E') && (s[i+1]>='0' && s[i+1]<='9')) ) // �е㸴�ӣ�Ҫ�� ��1E+��֮�����������
                   || (s[i+1]=='e' || s[i+1]=='E') || i==len-1

                   ) // �����ſ����ж�������翪ͷ��E����ͬʱ��
                    return false;
                break;

            case '.':
                if(i==0 || s[i-1]=='+' || s[i-1]=='-' || s[i-1]=='e' || s[i-1]=='E'
                   || s[i+1]=='+' || s[i+1]=='-' || s[i+1]=='e' || s[i+1]=='E'
                   || i==len-1 )
                   // С����Ҳ�����ж��������e֮ǰ��e֮��ͬʱ����С����
                   return false;
                break;

            case 'e':
            case 'E':
                if(i==0 || i==len-1 || s[i-1]=='e' || s[i-1]=='E')
                    return false;
                break;
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '0':
                break;
            default:
                return false;
                break;
            }

        }
            return true;


    }

};

int main()
{
    Solution a;
    char b[] = "-2.3e+87E-9.3";

    auto c=a.isNumber(b,sizeof(b)/sizeof(char)-1); // delete \0 at the end
//    for(auto i=0;i<a.size();++i)
        cout<<c;

}
