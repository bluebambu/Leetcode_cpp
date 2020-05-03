#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <string>

using namespace std;

inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}
inline float min(float a, float b) {return a<b?a:b;}


class Solution
{
public:
    string addBinary(string num1, string num2)
    // 我自己用iterator实现，效果不好，因为到边界后
    // 情况不是很好处理。 可以仿效答案，用 [i] 处理
    {
        if(num1.size()>num2.size()) return addBinary(num2, num1);

        string result;
        int carry=0;

        for(auto i=num1.end()-1,
                 j=num2.end()-1; 1 ;)
        {
            int num_i = *i-'0';
            int num_j = *j-'0';

            int digit = (num_i + num_j + carry)%2;

            result.insert(result.begin(), digit);

            carry = (num_i + num_j + carry)/2;



            if(i==num1.begin() && j>num2.begin())
            {
                while(j!=num2.begin())
                {
                    --j;

                    digit = (*j -'0' + carry)%2;

                    result.insert(result.begin(), digit);

                    carry = (*j -'0' + carry)/2;

                    if(j==num2.begin() && carry!=0)
                        result.insert(result.begin(), carry);

                }

                break;
            }

            else if(i==num1.begin() && j==num2.begin())
            // 等长 和 不等长 是不同的case，需要分开讨论
            {
                if(carry >0)
                    result.insert(result.begin(),carry);
                break;
            }

            --i;
            --j;
        }

        for( auto& i:result) // 要用 引用！！
            i=i+'0';

        return result;
    }

    string addBinary2(string num1, string num2)
    {
        int len = num1.size()>num2.size() ? num1.size():num2.size();

        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());

        string result;
        int idx_1, idx_2, digit, carry=0;

        for(int i=0; i<len ; ++i)
        {
            idx_1 = i<num1.size()?num1[i]-'0' : 0;
            idx_2 = i<num2.size()?num2[i]-'0' : 0;
            digit = (idx_1 + idx_2 + carry)%2;
            carry = (idx_1 + idx_2 + carry)/2;

            result.insert(result.begin(), digit);
        }

        if(carry == 1)
            result.insert(result.begin(),carry);

        for( auto& i:result)
            i+='0';

        return result;


    }

    string addBinary3(string a, string b) {
        string result;

        string::iterator pa=a.end()-1, pb=b.end()-1;

        for(;pa>=a.begin() && pb>=b.begin(); --pa, --pb){
            const char tmp = *pa + *pb-'0';
            result.insert(result.begin(),tmp);
        }

        if(pa<a.begin() && pb<b.begin()){

        }
        else if(pa<a.begin())
            result.insert(0, b, 0, pb-b.begin()+1); // 这里要+1， 谨记！！
        else if(pb<b.begin()){
            result.insert(0, a, 0, pa-a.begin()+1);
        }

//        for(auto i : a)
//            cout<<i;
//            cout<<endl;
//
//        for(auto i : b)
//            cout<<i;
//            cout<<endl;
//
//        for(auto i : result)
//            cout<<i;
//            cout<<endl;

        auto pc=result.end()-1;

        for(;pc>=result.begin();--pc){
            if(*pc>'1' && pc!=result.begin()){
                int carry = (*pc-'0')/2;
                *pc= (*pc-'0')%2+'0';
                *(pc-1)+=carry;
            }
        }


    for(auto i : result)
        cout<<i;
        cout<<endl;

        if(result[0]>'1'){
            int carry=(result[0]-'0')/2;
            result[0]=(result[0]-'0')%2+'0';
            result.insert(result.begin(),carry+'0');
        }

        return result;
    }



};

int main()
{
    Solution a;
    string b("101001");
    string c("1111");

    auto d=a.addBinary3(b, c);
    for(auto i : d)
        cout<<i;

}
