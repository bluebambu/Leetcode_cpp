#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>
#include <bitset>

using namespace std;

inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}
inline float min(float a, float b) {return a<b?a:b;}

int Add(int a, int b)
{
	int t;
	while (b)
		t = a ^ b, b = (a & b) << 1, a = t;
	return a;
}

int Add2(int a, int b){
    char *c = (char*)a;
    return (int)&c[b]; // c+sizeof(char)*b=a + b
}

int mul2(int a, int b){
    char c[a][b];
    return (int)(&c[a-1][b-1] - &c[0][0]);
}

/////////////  无法compile ///////////////////////
int mul3(int a, int b){
    char **c = 0;
    auto d = c[b-1];
    return int(&(d[a-1]));
}


int main()
{
//    cout<<bitset<32>(5)<<endl;
//    cout<<bitset<32>(5<<2)<<endl;
//    cout<<(5<<2)<<endl;
//
//    cout<<Add2(5,-77777);
    cout<<mul3(3,5);
}
