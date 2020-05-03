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


//
template<typename T>
class SmartPointer2 {
private:
    T* pointer=nullptr;
    int* ref_cnt=nullptr;

public:
    SmartPointer2(T* x): pointer(x), ref_cnt(new int(0)) {*ref_cnt+=1;}
    SmartPointer2(const SmartPointer2<T>& other): pointer(other.returnptr()), ref_cnt(other.returncntp()) {*ref_cnt+=1};

    SmartPointer2<T>& operator = (SmartPointer2<T>& other){
        if(pointer == other.returnptr()) return this;
        if(*ref_cnt>0) revoke(); // 如果 ref count ==0， 则不需要revoke；

        pointer=other.returnptr();
        ref_cnt=other.returncntp();
        *ref_cnt+=1;
        return this; // 要记得return;
    }

    T* returnptr(){ return pointer; }
    int* returncntp() {return ref_cnt;}
    int returncnt(){return *ref_cnt; }

    void revoke(){
        --*ref_cnt;
        if(*ref_cnt==0){
            delete pointer;
            delete ref_cnt;
            // 必须 pointer 和 &count 归零， 否则的话容易leak memory！！！！！！
            pointer = nullptr;
            ref_cnt = nullptr;
        }
    }

    ~SmartPointer2() {revoke();}
};













int main()
{
    Solution a;

//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
    TreeNode* tree = new TreeNode(6,new TreeNode(3, nullptr, nullptr),new TreeNode(8, new TreeNode(7, new TreeNode(3), new TreeNode(4)), new TreeNode(9, new TreeNode(3), new TreeNode(4))));

    /*      6
        3       8
              7    9
            3  4  3  4

    */

    auto b = a.CheckBalance(tree);

        cout<<b<<" ";
}
