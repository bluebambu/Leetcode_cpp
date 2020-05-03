#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>
#include <string>
#include <sstream>

using namespace std;

inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}
inline float min(float a, float b) {return a<b?a:b;}

struct HashNode;


string NumToStr(int num){
    string result;
    stringstream ss;

    ss<<num;
    ss>>result;
    return result;
}

string NumToStr2(int num){
    bool sign = num>0 ? true : false;
    string result = sign ? "" : "-";

    int n=abs(num), pos=1;

    while(n/10){
        n/=10;
        pos*=10;
    }

    n=abs(num);

    while(pos){
        int curNum = n/pos;
        n%=pos;
        pos/=10;
        result.push_back('0'+curNum);
    }
    return result;
}


struct HashNode{
    string key;
    int val;
    HashNode* next;

    HashNode(string a, int b):key(a),val(b),next(nullptr) {}
};

class Solution
{
public:

};



int main()
{
    Hash_list a;

    for(int i=0; i<10; ++i){
        a.insert(NumToStr2(i),i);
        cout<<a.HashCode(NumToStr(i))<<" ";
    }

    cout<<endl;

    cout<<"size: "<<a.size()<<endl;
    cout<<"capacity: "<<a.cap()<<endl;

    for(int i=0; i<10; ++i){
       if(a.find(NumToStr(i)))
            cout<<((a.find(NumToStr(i)))->second);
    }

    a.del("3");
        cout<<endl;

    cout<<"size: "<<a.size()<<endl;
    cout<<"capacity: "<<a.cap()<<endl;
    for(int i=0; i<10; ++i){
       if(a.find(NumToStr(i)))
            cout<<((a.find(NumToStr(i)))->second);
    }

    cout<<endl<<endl;

    for(int i=0; i<9; ++i){
       a.del(NumToStr(i));
       cout<<a.HashCode(NumToStr(i))<<" ";
    }





}
