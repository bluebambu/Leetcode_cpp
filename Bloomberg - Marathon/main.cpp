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


class SensorSignal{
public:
    SensorSignal(int x, int y): Athlete_Num(x), dist(y) {}
    int Sensor_Num;
    int Athlete_Num;
    int dist;
};

class Marathon{
private:
    unordered_map<int, int> cur_scores;
    typedef unordered_map<int, int>::iterator UI;

public:
    void update(SensorSignal sig){
        int ath = sig.Athlete_Num;
        int dist = sig.dist;
        cur_scores[ath] = dist;
    }

    struct comp{
        bool operator() (UI& a, UI& b){
            return a->second > b->second;
        }
    };

    vector<int> GetTopK(int k){
        vector<int> result;

        priority_queue<UI, vector<UI>, comp> pq;
        for(auto iter = cur_scores.begin(); iter!=cur_scores.end(); ++iter){
            if(pq.empty())
                pq.push(iter);
            else{
                pq.push(iter);
                if(pq.size()>k)
                    pq.pop();
            }
        }

        while(pq.size()){
            result.push_back(pq.top()->first);
            pq.pop();
        }
        return result;
    }

};

class SensorSignal2{
public:
    SensorSignal2(int x, int y, int z): Athlete_Num(x), dist(y), timestamp(z) {}
    int Sensor_Num;
    int Athlete_Num;
    int dist;
    int timestamp;
};

class Marathon2{
private:
    unordered_map<int, pair<int, int>> cur_scores;
    typedef unordered_map<int, pair<int,int>>::iterator UI;

public:
    void update(SensorSignal2 sig){
        int ath = sig.Athlete_Num;
        int dist = sig.dist;
        int timestamp = sig.timestamp;
        cur_scores[ath] = make_pair(dist, timestamp);
    }

    struct comp{
        bool operator() (UI& a, UI& b){ /// 判断条件很重要， 先判断距离dist， 再判断时间， 不能直接写  dist a < b && time a > b
            return (a->second.first > b->second.first ) || (a->second.first == b->second.first && a->second.second < b->second.second);
        }
    };

    vector<int> GetTopK(int k){
        vector<int> result;

        priority_queue<UI, vector<UI>, comp> pq;
        for(auto iter = cur_scores.begin(); iter!=cur_scores.end(); ++iter){
            if(pq.empty())
                pq.push(iter);
            else{
                pq.push(iter);
                if(pq.size()>k)
                    pq.pop();
            }
        }

        while(pq.size()){
            result.push_back(pq.top()->first);
            pq.pop();
        }
        return result;
    }

};


class Marathon3{ /// only consider distance
private:
    unordered_map<int, int> global;
    map<int, int, [](int a, int b){return a>b;}> topKmap;
    /// 我觉得用 list 和 map 都不好， list不能用二分插入， 要一个一个找。 map 要用dist 做key， athlet num 做value， 这样的话两个athlet的dist会可能相等， 那就要map< dist, vector<athlet>> ， 或者multimap
    /// 感觉不如 priority queue 方便

public:
    void update(SensorSignal sg1){
        int ath = sg1.Athlete_Num;
        int dist = sg1.dist;
        global[ath]=dist;


    }

};


int main(){
    Marathon2 x;
    for(int i=0; i<10; i++){
        x.update(SensorSignal2(i+1, 100-(i-8)*(i-8), i*60+1));
        cout<<i+1<<" "<<100-(i-8)*(i-8)<<" "<<i*60+1<<endl;
    }

    auto b = x.GetTopK(3);

    for(auto i:b)
        cout<<i<<" ";
}
