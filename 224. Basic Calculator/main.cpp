#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>
#include <ctype.h>

using namespace std;

inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}
inline float min(float a, float b) {return a<b?a:b;}


/// 1种思路,
/***
Thanks for chuang's answer. Make a version which is easy to understand.
Example: 7 - ( 6 - 5 - ( 4 - 3 ) - 2 ) - ( 1 )
Result: + 7 '-' 6 + 5 '+' 4 - 3 + 2 '-'1
The '+' '-' are signs just before '('. They are dealt with previous stack sign. Then they are saved in the stack to help decide the signs in the following "(..)" .

https://discuss.leetcode.com/topic/15806/easy-18-lines-c-16-lines-python

很多人将该题转换为后缀表达式后（逆波兰表达式）求解，其实不用那么复杂。题目条件说明只有加减法和括号，由于加减法是相同顺序的，我们大可以直接把所有数顺序计算。
难点在于多了括号后如何处理正负号。我们想象一下如果没有括号这题该怎们做：因为只有加减号，我们可以用一个变量sign来记录上一次的符号是加还是减，这样把每次读到的
数字乘以这个sign就可以加到总的结果中了。有了括号后，整个括号内的东西可一看成一个东西，这些括号内的东西都会受到括号所在区域内的正负号影响（比如括号前面是个负
号，然后括号所属的括号前面也是个负号，那该括号的符号就是正号）。但是每多一个括号，都要记录下这个括号所属的正负号，而每当一个括号结束，我们还要知道出来以后所
在的括号所属的正负号。根据这个性质，我们可以使用一个栈，来记录这些括号所属的正负号。这样我们每遇到一个数，都可以根据当前符号，和所属括号的符号，计算其真实值。
*/
class Solution {
public:
    int calculate(string s) {
        stack<int> t;  //previous sign just before the '('
        t.push(1);  //for all the signs those are not in the parentheses
        int sum=0, temp=0, lastSign=1;
        for(auto c: s)
        {
            if(c=='(') t.push(lastSign); //save the sign just before the '('
            else if(c==')') t.pop();

            if(c>='0' && c<='9'){
                temp=temp*10+c-'0';
            }

            if(c=='-'||c=='+'){
                sum+=lastSign*temp; //calculate the number before current sign
                temp=0;
                lastSign=(c=='-'?-1:1)*t.top();  //deal with the stack influencing sign
            }
        }
        sum+=lastSign*temp; //calculate the last number
        return sum;
    }
};


/// JAVA implementation !!!!
public class Solution {
    public int calculate(String s) {
        /// 去掉所有空格
        s = s.replace(" ", "");
        Stack<Integer> stk = new Stack<Integer>();
        /// 先压入一个1进栈，可以理解为有个大括号在最外面
        stk.push(1);
        int i = 0, res = 0, sign = 1;
        while(i < s.length()){
            char c = s.charAt(i);
            /// 遇到正号，将当前的符号变为正号
            if(c=='+'){
                sign = 1;
                i++;
            /// 遇到负号，将当前的符号变为负号
            } else if(c=='-'){
                sign = -1;
                i++;
            /// 遇到左括号，计算当前所属的符号，压入栈中
            /// 计算方法是当前符号乘以当前所属括号的符号
            } else if(c=='('){
                stk.push(sign * stk.peek());
                sign = 1;
                i++;
            /// 遇到右括号，当前括号结束，出栈
            } else if(c==')'){
                stk.pop();
                i++;
            /// 遇到数字，计算其正负号并加入总结果中
            } else {
                int num = 0;
                while(i < s.length() && Character.isDigit(s.charAt(i))){
                    num = num * 10 + s.charAt(i) - '0';
                    i++;
                }
                res += num * sign * stk.peek();
            }
        }
        return res;
    }
}

/**
思路 2 ， （）之内的东西可以算出来之后入栈。 顺序走一遍， 1个stack， 速度很快，但是思路难想。
1+（2+（5-6）-（8+9））   result 记录的是两个 左括号 之间的数的和。 sign记录的是 cur num 的下一个括号， 或者说， + - 符号之后的数字的符号........
一旦遇到一个左括号， 之前的result就被存到 nums 数组中， 同时， 括号的符号也被存到 ops 数组中。 进入括号后， 计算依旧。
一旦遇到一个右括号， result 首先乘以当前（）的符号，即 ops.back(), 同时还要将 上一层括号内、当前括号之前的值全部都加起来，即 ...(1+3+(...result...)+....)
在这个例子中， 1+3 需要和 result 全部加起来。 1+3 即是 nums.back().

最后 for 循环之外还有一个 result+=num*sign; ， 那是因为最后一次运算确实没有在for loop中完成。 具体可以思考没有任何括号的情况。

总体而言这个方法确实很快，但是思路复杂。
*/
class Solution {
public:
    int calculate(string s) {
        int result=0;
        int num=0, sign=1;
        stack<int> nums, ops;

        for(int i=0; i<s.size(); ++i){
            char c=s[i];
            if(c>='0' && c<='9'){
                num=10*num + c-'0'; /// For case: "23"
            }else if(c=='+'){
                result+=num*sign; /// everytime meets an operator, sum up previous number
                num=0;
                sign=1;    /// sign is the sign of next number
            }else if(c=='-'){
                result+=num*sign; /// everytime meets an operator, sum up previous number
                num=0;
                sign=-1;
            }else if(c=='('){
                nums.push(result); /// ...(1+3+(..xx..)+...)... before go into cur (..xx..), record the forefront result (in this case it is 1+3 ) into nums array
                ops.push(sign);  /// record cur (..xx..) sign
                result=0;  /// result is to record the total value in the cur (..xx..)
                sign=1;
            }else if(c==')' && ops.size()){
                result+=num*sign; /// For case: 1-(5)
                num=0;

                result = result*ops.top() + nums.top();  /// ...(1+3+(..xx..)+...)... sum up cur (..xx..)  and the forefront result (in this case it is 1+3 )
                nums.pop();
                ops.pop();
            }
        }
        result+=num*sign; /// For the last one operation. consider the case:  1+2+3
        return result;
    }
};


/// 思路 3 后缀表达式标准解法. case: 1-2+3 ！= 1-（2+3）， 后缀表达式是先处理后面的操作符。 为了不用优先级， 他在这里使用了从后往前遍历的方法， 确实很精妙！！！
/// 与我想法一样， 将 括号与运算符一起入栈， 然后遇到反括号的时候， 不断出栈直到遇到匹配括号。 不过他这里括号与反括号与平常的相反， 因为方向相反。
/// 这个思路最清晰， 我觉得最适合去面试。
int calculate(string s) {
    stack<int> operands;
    stack<char> operations;
    string operand;

    for (int i = (int)s.length() - 1; i >= 0; i--) {
        if (s[i] == ')' || s[i] == '+' || s[i] == '-')
            operations.push(s[i]);
        else if (isdigit(s[i])) {
            operand = s[i] + operand;
            if (!i || !isdigit(s[i - 1])) {
                operands.push(stoi(operand));
                operand.clear();
            }
        }
        else if (s[i] == '(') {
            while (operations.top() != ')')
                compute(operands, operations);
            operations.pop();
        }
    }
    while (!operations.empty())
        compute(operands, operations);
    return operands.top();
}

void compute(stack<int>& operands, stack<char>& operations) {
    int left = operands.top();
    operands.pop();
    int right = operands.top();
    operands.pop();
    int op = operations.top();
    operations.pop();
    if (op == '+') operands.push(left + right);
    if (op == '-') operands.push(left - right);
}

int main()
{
    Solution a;



}
