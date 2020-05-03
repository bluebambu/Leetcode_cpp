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
    void RemoveZero(vector<vector<int>> &matrix)
    {
        // 此处需要考虑第一行和第一列是否有0的情况，需要
        // 单独讨论，否则的话，全矩阵都会变成0，

        bool _1stRow_Zero=false;
        bool _1stCol_Zero=false;

//        for()


        for(int i=0; i<matrix.size() ; ++i)
        {
            for( int j=0 ; j<matrix[0].size() ; ++j )
            {
                if( matrix[i][j] == 0 )
                {
                    matrix[i][0]=0;
                    matrix[0][j]=0;
                }
            }
        }

        for(int i=1 ; i<matrix.size();++i)
        {
            if(matrix[i][0]==0)
            {
                for(int j=1; j< matrix[0].size();++j)
                {
                    matrix[i][j]=0;
                }
            }
        }

        for(int j=1 ; j<matrix[0].size();++j)
        {
            if(matrix[0][j]==0)
            {
                for(int i=1; i< matrix.size();++i)
                {
                    matrix[i][j]=0;
                }
            }
        }


    }

};

int main()
{
    Solution a;
    int b[] = {1,3,5,7,9};
    int c[] = {2,4, 6, 8,10};
    vector<vector<int>> d {{3,0,4,9},{1,2,4,2},{9,11,3,5},{-2, 14, -6, 0}, {2,1,3,4}};

    for(auto i:d)
    {
        for(auto j:i)
            cout<<j<<"      ";
        cout<<endl<<endl;
    }

    a.RemoveZero(d);

    cout<<"result is "<<endl;

    for(auto i:d)
    {
        for(auto j:i)
            cout<<j<<"      ";
        cout<<endl<<endl;
    }


}
