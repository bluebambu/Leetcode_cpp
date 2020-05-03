




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

