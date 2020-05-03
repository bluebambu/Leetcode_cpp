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


class SortStack
{
public:
    stack<int> main;
    stack<int> help;

    void sort(){
        int tmp;

        while(main.size()){
            tmp = main.top();
            main.pop();

            if(help.empty()){
                help.push(tmp);
            }else{
                if(tmp < help.top()){
                    int transfer=0;
                    while(help.size() && help.top() > tmp){
                        main.push(help.top());
                        help.pop();
                        transfer++;
                    }
                    help.push(tmp);
                    for(int i=0; i<transfer; ++i){
                        help.push(main.top());
                        main.pop();
                    }
                }else{
                    help.push(tmp);
                }
            }
        }
    }

};

int main()
{
    SortStack a;

    for(auto i: {3,6,4,8,0,1,5,10})
        a.main.push(i);

    a.sort();

    while(a.help.size()){
        cout<<a.help.top()<<" ";
        a.help.pop();
    }


}
