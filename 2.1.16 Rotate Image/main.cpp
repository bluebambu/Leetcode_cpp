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
    vector<vector<int>> Rotate1(int a[][5], int len)
    // with buffer vector, use function: (x,y) -> (n-y, x)
    // here n = len - 1;
    {
        vector<vector<int>> temp;

        for(int i=0;i<5;++i)
        {
            temp.push_back(vector<int>());
            for(int j=0; j<len;++j)
            {
                temp[i].push_back(0);
            }
        }

        for(int i=0;i<len;++i)
        {
            for(int j=0; j<len;++j)
            {
                temp.at(i).at(j) = a[(len-1)-j][i];
            }
        }

        return temp;
    }

    void Rotate2(vector<vector<int>> &matrix)
    {
        for(int i=0;i<matrix.size();++i)
           for(int j=0;j<i;++j)
                swap(matrix[i][j], matrix[j][i]);

        for(int i=0;i<matrix.size();++i)
            for(int j=0; j<=(matrix.size()-1)/2;++j)
                swap(matrix[i][j],matrix[i][(matrix.size()-1)-j]);

    }

    void Rotate3(vector<vector<int>> &matrix)
    {
        for(int i=0; i<matrix.size() ; ++i)
            for(int j=0; j<i; ++j)
                swap(matrix[i][j], matrix[j][i]);

        for(int i=0;  i<matrix.size(); ++i)
            for(int j=0; j<matrix.size()/2; ++j)
                swap(matrix[i][j], matrix[i][matrix.size()-1-j]);
    }
};

int main()
{
    Solution a;

    int b[5][5] = {3,6,4,9,1,3,4,2,9,11,0,5,-2, 14, -6, 7, 2,1,3,4,2,9,11,0,5};
    vector<vector<int>> matrix  {{3,6,4,9,1},{3,4,2,9,11},{0,5,-2, 14, -6}, {7, 2,1,3,4},{2,9,11,0,5}};

    for(int i=0;i<5;i++)
    {
        for(int j=0; j<5;j++)
            cout<<b[i][j]<<"   ";
        cout<<endl<<endl;
    }

    cout<<"this is the rotate:"<<endl;
    a.Rotate3(matrix);

    for(auto i : matrix)
    {for(auto j:i)
            cout<<j<<"   ";
        cout<<endl<<endl;}
}
