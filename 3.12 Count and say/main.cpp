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
    string countSay(int num)
    {
        string numstr;

        for(int i=1;num!=0;++i)
        {
            int resid = num % 10;
            num /= 10;
            numstr.insert(numstr.begin(), resid+'0');
        }

        int count=1;

        string temp;

        for(auto iter = numstr.begin();iter<numstr.end();++iter)
        {
            if(*(iter+1)==*iter && iter!=numstr.end()-1)
            {
                ++count;
                continue;
            }

            else
            {
                temp.append(Say(count)+" ");
                temp.push_back(*iter);
                if(count>1)
                    temp.append("s");
                temp.append(" ");
                count = 1;
            }
        }

        return temp;


    }

    string Say(int n)
    {
        switch(n)
        {
        case 1:
            return "one";
            break;
        case 2:
            return "two";
            break;
        case 3:
            return "three";
            break;
        case 4:
            return "four";
            break;
        case 5:
            return "five";
            break;
        }
    }

};

int main()
{
    Solution a;
    string b("");

    auto c=a.countSay(1112111);
    for(auto i : c)
        cout<<i;

}
