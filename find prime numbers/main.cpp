#include <stdio.h>
#include <iostream>

using namespace std;

int main(){
    bool helper[101]; // to store if number n has been crossed out

    // initialization
    for(int i=0; i<101; ++i){
        helper[i]=true;
    }

    // cross out the products of prime numbers
    for(int i=2; i<100; ++i){
        if(helper[i]==true){
            for(int j=i*i; j<100 ; j+=i){
                    helper[j]=false;
            }
        }else
            continue;
    }

    // print out all the prime numbers
    for(int i=2; i<100; ++i){
        if(helper[i])
            cout<<i<<endl;
    }

    return 1;
}
