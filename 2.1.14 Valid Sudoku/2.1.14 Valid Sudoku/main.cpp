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


void reset(bool used[])
{
    for(int i=0; i<9; ++i)
    {
        used[i]=false;
    }
}

class Solution
{
public:
    bool isValidSudoku(const vector<string>& board)
    {
        bool used[9];

        for(int i=0; i<9; ++i)
        {
            reset(used);

            for(int j=0; j<9; ++j)
            {
                int square = board[i][j];

                if(square >='0' && square <= '9' )
                {
                    if(used[(square-'1')]==true) return false;

                    used[(square-'1')]=true;
                }
            }
            reset(used);

            for(int j=0; j<9; ++j)
            {
                if(board[j][i] >='0' && board[j][i] <= '9' )
                {
                    if(used[board[j][i]-'1']==true) return false;

                    used[board[j][i]-'1']=true;
                }
            }
            reset(used);

//            for(int j=0; j<3; ++j)
//            {
//                for(int k=0; k<3; ++k)
//                {
//
//                    if(board[i/3*3+j][i%3*3+k] >='0' && board[i/3*3+j][i%3*3+k] <= '9' )
//                    {
//                        if(used[board[i/3*3+j][i%3*3+k]-'1']==true) return false;
//
//                        used[board[i/3*3+j][i%3*3+k]-'1']=true;
//                    }
//                }
//            }
            // 这里不需要2重循环，可以直接

            for(int j=0; j<9; ++j)
            {
                int square = board[i/3*3 + j/3][i%3*3 + j%3];

                if(square >='0' && square <= '9')
                {
                    if(used[square-'1']==true) return false;
                    used[square-'1']=true;
                }
            }
        }
        return true;
    }

    //////////////////////// Leetcode passed ///////////////////////
    bool isValidSudoku(vector<vector<char>>& board) {
        bool check[9]={0};

        for(int i=0; i<9; ++i){
            for(int j=0; j<9; ++j){
                if(board[i][j]!='.'){
                    if(check[board[i][j]-'1']==true) return false;  // 记得要从 1 开始减！！！！
                    check[board[i][j]-'1']=true;
                }
            }

            fill(check, check+9, 0);

            for(int j=0; j<9; ++j){
                if(board[j][i]!='.'){
                    if(check[board[j][i]-'1']==true) return false;
                    check[board[j][i]-'1']=true;
                }
            }

            fill(check, check+9, 0);

            for(int j=0; j<9; ++j){
                char cur = board[i/3*3+j/3][j%3+i%3*3];
                if(cur!='.'){
                    if(check[cur-'1']==true) return false;
                    check[cur-'1']=true;
                }
            }

            fill(check, check+9, 0);

        }
        return true;
    }

};

int main()
{
    Solution a;

    const vector<string> board {
                            "53,,7,,,,", //0
                            "6,,195,,,", //1
                            ",98,,,,6,", //2
                            "8,,,6,,,3", //3
                            "4,,8,3,,1", //4
                            "7,,,2,,,6", //5
                            ",6,,,,28,", //6
                            ",,,419,,5", //7
                            ",,,,8,,79"  //8
                            };
    cout<<a.isValidSudoku(board);




}
