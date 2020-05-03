//////////// words IO////////
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    map<string, int> dict;

    while(!cin.eof()){
        string s;
        char c;
        while(!cin.eof()){
            cin.get(c);
            if(c!= ' ' && c<'a' || c>'z'){ /// c!=' ' 很重要 ！！
                while(c!=' ' && !cin.eof()) cin.get(c);;
                s.clear();
            }
            if(c==' ')
                break;
            s.push_back(c);
        }
        if(s.empty()) continue;
        dict[s]+=1;
    }

    cout<<dict.size()<<endl;
    cout<<"words"<<endl;

    for(auto iter=dict.begin(); iter!=dict.end(); ++iter){
        cout<<iter->first<<" "<<iter->second<<endl;
    }

    cout<<"letters"<<endl;

    for(auto iter=dict.begin(); iter!=dict.end(); ++iter){
        string cur = iter->first;
        for(char i='a'; i<='z'; ++i){
            int times = count(cur.begin(), cur.end(), i);
            cout<<i<<" "<<times<<endl;
        }
    }

    return 0;
}


///////////// market equilibrium ///////////
float precise(float f){
    int tmp = f*1000000000;
    float f2 = tmp/1000000000.0;
    return f2;
}

bool same(vector < float > & a, vector < float > & b){
    int n=a.size();
    for(int i=0; i<n; ++i)
        if(precise(a[i]) != precise(b[i]))
            return false;
    return true;
}

vector < float > market_equilibrium(vector < float > initial_market_share, vector < vector < float > > switch_probability) {
    int n = initial_market_share.size();

    vector<vector<float>> update(n, vector<float>(n, 0.0));
    vector<float> last(n, 0.0);

    do{
        for(int i=0; i<n; ++i)
            last[i] = initial_market_share[i];

        for(int i=0; i<n; ++i){
            for(int j=0; j<n; ++j){
                update[i][j] = switch_probability[i][j]*initial_market_share[i];
            }
            initial_market_share[i]=0.0;
        }

        for(int j=0; j<n; ++j){
            for(int i=0; i<n; i++){
                initial_market_share[j]+= update[i][j];
            }
        }

    }while( ! same(last, initial_market_share));

    return initial_market_share;
}


////////////


