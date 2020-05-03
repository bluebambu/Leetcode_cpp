#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>
#include <cstring>

using namespace std;

inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}
inline float min(float a, float b) {return a<b?a:b;}

//class X
//{
//public:
//    X(){
//      char *x = 0; //  x=0 说明x是一个nullptr， 对他进行deference 会直接 crash 系统。 这个是个常见的crash system的做法。
//      *x = 1;
//    }
//};
//
//X x;

int main(){
    const char a='p';
     char * const c=&a;
}
