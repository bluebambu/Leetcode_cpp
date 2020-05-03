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


/// 1��˼·,
/***
Thanks for chuang's answer. Make a version which is easy to understand.
Example: 7 - ( 6 - 5 - ( 4 - 3 ) - 2 ) - ( 1 )
Result: + 7 '-' 6 + 5 '+' 4 - 3 + 2 '-'1
The '+' '-' are signs just before '('. They are dealt with previous stack sign. Then they are saved in the stack to help decide the signs in the following "(..)" .

https://discuss.leetcode.com/topic/15806/easy-18-lines-c-16-lines-python

�ܶ��˽�����ת��Ϊ��׺���ʽ���沨�����ʽ����⣬��ʵ������ô���ӡ���Ŀ����˵��ֻ�мӼ��������ţ����ڼӼ�������ͬ˳��ģ����Ǵ����ֱ�Ӱ�������˳����㡣
�ѵ����ڶ������ź���δ��������š���������һ�����û���������������������Ϊֻ�мӼ��ţ����ǿ�����һ������sign����¼��һ�εķ����Ǽӻ��Ǽ���������ÿ�ζ�����
���ֳ������sign�Ϳ��Լӵ��ܵĽ�����ˡ��������ź����������ڵĶ�����һ����һ����������Щ�����ڵĶ��������ܵ��������������ڵ�������Ӱ�죨��������ǰ���Ǹ���
�ţ�Ȼ����������������ǰ��Ҳ�Ǹ����ţ��Ǹ����ŵķ��ž������ţ�������ÿ��һ�����ţ���Ҫ��¼��������������������ţ���ÿ��һ�����Ž��������ǻ�Ҫ֪�������Ժ���
�ڵ����������������š�����������ʣ����ǿ���ʹ��һ��ջ������¼��Щ���������������š���������ÿ����һ�����������Ը��ݵ�ǰ���ţ����������ŵķ��ţ���������ʵֵ��
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
        /// ȥ�����пո�
        s = s.replace(" ", "");
        Stack<Integer> stk = new Stack<Integer>();
        /// ��ѹ��һ��1��ջ���������Ϊ�и���������������
        stk.push(1);
        int i = 0, res = 0, sign = 1;
        while(i < s.length()){
            char c = s.charAt(i);
            /// �������ţ�����ǰ�ķ��ű�Ϊ����
            if(c=='+'){
                sign = 1;
                i++;
            /// �������ţ�����ǰ�ķ��ű�Ϊ����
            } else if(c=='-'){
                sign = -1;
                i++;
            /// ���������ţ����㵱ǰ�����ķ��ţ�ѹ��ջ��
            /// ���㷽���ǵ�ǰ���ų��Ե�ǰ�������ŵķ���
            } else if(c=='('){
                stk.push(sign * stk.peek());
                sign = 1;
                i++;
            /// ���������ţ���ǰ���Ž�������ջ
            } else if(c==')'){
                stk.pop();
                i++;
            /// �������֣������������Ų������ܽ����
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
˼· 2 �� ����֮�ڵĶ������������֮����ջ�� ˳����һ�飬 1��stack�� �ٶȺܿ죬����˼·���롣
1+��2+��5-6��-��8+9����   result ��¼�������� ������ ֮������ĺ͡� sign��¼���� cur num ����һ�����ţ� ����˵�� + - ����֮������ֵķ���........
һ������һ�������ţ� ֮ǰ��result�ͱ��浽 nums �����У� ͬʱ�� ���ŵķ���Ҳ���浽 ops �����С� �������ź� �������ɡ�
һ������һ�������ţ� result ���ȳ��Ե�ǰ�����ķ��ţ��� ops.back(), ͬʱ��Ҫ�� ��һ�������ڡ���ǰ����֮ǰ��ֵȫ�������������� ...(1+3+(...result...)+....)
����������У� 1+3 ��Ҫ�� result ȫ���������� 1+3 ���� nums.back().

��� for ѭ��֮�⻹��һ�� result+=num*sign; �� ������Ϊ���һ������ȷʵû����for loop����ɡ� �������˼��û���κ����ŵ������

��������������ȷʵ�ܿ죬����˼·���ӡ�
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


/// ˼· 3 ��׺���ʽ��׼�ⷨ. case: 1-2+3 ��= 1-��2+3���� ��׺���ʽ���ȴ������Ĳ������� Ϊ�˲������ȼ��� ��������ʹ���˴Ӻ���ǰ�����ķ����� ȷʵ�ܾ������
/// �����뷨һ���� �� �����������һ����ջ�� Ȼ�����������ŵ�ʱ�� ���ϳ�ջֱ������ƥ�����š� ���������������뷴������ƽ�����෴�� ��Ϊ�����෴��
/// ���˼·�������� �Ҿ������ʺ�ȥ���ԡ�
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
