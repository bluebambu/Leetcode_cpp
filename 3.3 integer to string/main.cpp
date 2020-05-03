#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>

using namespace std;

inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}
inline float min(float a, float b) {return a<b?a:b;}


string itostr(int i)
{
    stringstream ss;
    ss << i;

    string str;
    ss >> str;

    return str;
}
