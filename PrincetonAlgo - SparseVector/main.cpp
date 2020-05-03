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

vector<vector<int>> m       {{0,0,1,2,0,0,5,0,0},
                            {0,5,0,0,0,0,0,0,0},
                            {0,0,3,0,0,0,0,0,2},
                            {1,0,0,4,0,0,9,0,0},
                            {3,0,1,0,0,0,0,6,0}
                            };

class SparseV
{
    vector<unordered_map<int, int>> sparse;
    int nRow;
    int nCol;
public:
    explicit SparseV(vector<vector<int>> m) {
        buildFrom(m);
    }

    void buildFrom(vector<vector<int>> matrix){
        nRow = matrix.size();
        nCol = matrix[0].size();
        // cout<<nRow<<" "<<nCol;
        sparse.resize(nRow);

        for(int i=0; i<nRow; ++i){
            for(int j=0; j<matrix[i].size(); ++j){
                if(matrix[i][j]!=0){
                    sparse[i][j]=matrix[i][j];
                }
            }
        }
    }

    vector<int> Multiply1D(vector<int>& X){
        if(X.size() != nCol)
            throw runtime_error("size mismatches");
        vector<int> result(nRow);

        for(int i=0; i<nRow; ++i){
            for(auto iter=sparse[i].begin(); iter!=sparse[i].end(); ++iter){
                result[i] += iter->second * X[iter->first];
            }
        }

        return result;
    }

    void prnt(){
        for(auto i:sparse){
            for(auto j:i){
                cout<<j.first<<"->"<<j.second<<" ";
            }
            cout<<endl;
        }
    }

    vector<unordered_map<int, int>> Multiply2D(vector<unordered_map<int, int>>& X){

    }



};



int main()
{
    SparseV b(m);
    b.prnt();

    vector<int> x{1,1,1,1,1,1,1,1,1};
    vector<int> c = b.Multiply1D(x);

    for(int i:c){
        cout<<i<<" ";
    }
}
