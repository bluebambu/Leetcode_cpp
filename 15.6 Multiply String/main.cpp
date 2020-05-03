#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;

inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}
inline float min(float a, float b) {return a<b?a:b;}


class Solution
{
public:
////////// Leetcode Passed  /////////////////////////
////////////  i 位的num1， j 位的num2， 乘积最大为 i+j 位， 最小为 i+j-1位。 不过要考虑 诸如  234124 × 0 的情况， 前面有很多 0 ；
///////////
    string multiply(string num1, string num2) {
        vector<int> mult(num1.size()+num2.size(), 0);

        for(int i=0; i<num1.size(); ++i)
            for(int j=0; j<num2.size(); ++j)
                mult[mult.size()-1-(i+j)]+= (num1[num1.size()-i-1]-'0')*(num2[num2.size()-j-1]-'0');

        bool carry=true;

        while(carry){
            carry=false;

            for(int i=mult.size()-1; i>0; --i){
                if(!carry && mult[i]>9) carry=true;
                mult[i-1]+=mult[i]/10;
                mult[i]%=10;
            }
        }


        while(mult[0]==0 && mult.size()>1){  // 注意如果结果是 0， 最后得留一个 0 ；
            mult.erase(mult.begin());
        }

        string result;

        for(int i=0; i<mult.size(); ++i){
            result.push_back(mult[i]+'0');
        }

        return result;
    }
};

int main()
{
    Solution a;

//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
    cout<<a.multiply("3475927594352532524532452353245327597", "98237459723453245324543522075987325");

}
