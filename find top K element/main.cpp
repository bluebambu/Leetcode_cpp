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

typedef pair<string, int> PSI;

class MinPQComp{
    bool operator() (const PSI& lhs, const, PSI& rhs) const {
        if(lhs.second > rhs.second) return true;
        if(lhs.second < rhs.second) return false;
        if(lhs.second == rhs.second) return (lhs.first < rhs.first);
    }
};

class MaxPQComp{
    bool operator() (const PSI& lhs, const, PSI& rhs) const {
        if(lhs.second > rhs.second) return false;
        if(lhs.second < rhs.second) return true;
        if(lhs.second == rhs.second) return (lhs.first > rhs.first);
    }
};

class Solution
{
public:
    vector<string> findtopKMinH(vector<string> dictionary, int K){
        unordered_map<string, int> hashmap;
        for(int i=0; i<dictionary.size(); ++i){
            hashmap[dictionary[i]]++;
        }

        priority_queue<PSI, vector<PSI>, MinPQComp> MinHeapPQ;

        for(auto& i:hashmap){
            PSI tmp = make_pair(i.first, i.second);
            MinHeapPQ.push(tmp);
            if(MinHeapPQ.size()>K)
                MinHeapPQ.pop();

        }

        vector<string> result;

        while(MinHeapPQ.size()){
            result.push_back(MinHeapPQ.top().first);
            MinHeapPQ.pop();
        }

        return result;
    }


    vector<string> findtopKMaxH(vector<string> dictionary, int K){
        unordered_map<string, int> hashmap;
        for(int i=0; i<dictionary.size(); ++i){
            hashmap[dictionary[i]]++;
        }

        priority_queue<PSI, vector<PSI>, MaxPQComp> MaxHeapPQ;

        for(auto& i:hashmap){
            MaxHeapPQ.push(i);
        }

        vector<string> result;

        for(int i=0; i<K; ++i){
            result.push_back(MaxHeapPQ.top().first);
            MaxHeapPQ.pop();
        }

        return result;
    }


};

int main()
{
    Solution a;

    vector<string> test = { "Do",
                            "Nguyen",
                            "Nguyen",
                            "Doan",
                            "Ngo",
                            "Ngo",
                            "6"
                            };
    auto b=a.findtopKMinH(test, 3);

    for(auto i:b)
            cout<<i<<" ";


}
