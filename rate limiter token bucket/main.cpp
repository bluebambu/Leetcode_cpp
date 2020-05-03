#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>
#include <ctime>

using namespace std;

inline void exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}
inline float min(float a, float b) {return a<b?a:b;}

//  m rate/ n second

//class RateLimiterToken {
//public:
//    int m=5; // rate
//    double n=10.0 ; //second
//    double ratio = m/n;
//    double capacity = m;
//    int time;
//    int last_time=0;
//
//    while( askrequest() ){
//        time = request_time();
//        int diff = time - last_time;
//        last_time = time;
//
//        capacity += diff * ratio;
//
//        if(capacity > m)
//            capacity = m;
//
//        if(capacity < 1.0)
//            reject();
//        else{
//            capacity--;
//            process_request();
//        }
//    }
//};


class Signal{
public:
    string info;
};

class RateLimiter2{
private:
    int maxNum = 10;
    double TimeInverval = 7.0;
    double ratio = (double)maxNum/TimeInverval;
    double capacity = maxNum;
    int cur_time;
    int last_time=time(0);

public:
    RateLimiter2(){}
    bool AnySpace(){
        cur_time = time(0);
        double difference = cur_time - last_time;
        last_time = cur_time;
        capacity += difference*ratio;

        if(capacity>maxNum)
            capacity=maxNum;
        if(capacity>=1.0)
            return true;
        else
            return false;
    }

    void push(Signal s){
        if(AnySpace()){
            process(s);
            capacity-=1.0;
        }
        else
            reject(s);
    }

    void process(Signal s) {}

    void reject(Signal s) {}

    double getCap(){return capacity;}
};



int main()
{
    RateLimiter2 a;

    for(int i=0; i<30; ++i){
        Signal tmp;
        a.push(tmp);
        cout<<time(0)<<" "<<a.getCap()<<endl;

        if(i>3)
            std::cin.ignore();
    }


}
