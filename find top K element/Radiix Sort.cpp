#include <iostream>
#include <vector>
#include <algorithm>
#include <tr1/unordered_map>
#include <map>

#define BASE 10
#define ALPHABET_SIZE 26

using namespace std;

const char  EMPTY_CHAR = '\0';
inline int INDEX(char c){//lexicographical order: EMPTY_CHAR A-Za-z
    if (c == EMPTY_CHAR) return 0;
    if ('A'<=c && c<='Z') return c-'A' +1;
    if ('a'<=c && c<='z') return ALPHABET_SIZE + c-'a' +1;
    return 255;
};

typedef     pair<string, int>   PSI;
typedef     vector<PSI>         VPSI;
typedef     tr1::unordered_map<string, int> myHash_Type;

//=============================================================================
myHash_Type FrequencyOf;
int         N;
int         K;
int         maxNameLen = 0;
int         maxFrequency = 0;
VPSI        ItemList;
//=============================================================================

void readInput(){
    cin >> N;
    string aName;
    for(int i = 0; i<N; i++){   //  O(N)
        cin >> aName;
        FrequencyOf[aName]++;   // ;
        maxNameLen      = max(maxNameLen, (int)aName.length());
        maxFrequency    = max(maxFrequency, FrequencyOf[aName]);
    };
    cin >> K;
};
//-----------------------------------------------------------------------------

void stableRadixSortInt(VPSI &ItemList, int maxNum){
    VPSI bucket[BASE];
    for(int X=1; X<=maxNum; X*=BASE){
        for(int i=0; i < ItemList.size(); i++){
            int currentDigit = ItemList[i].second/X % BASE;
            bucket[currentDigit].push_back(ItemList[i]);
        };

        int i,k= 0;
        VPSI::iterator it;
        for(i=BASE-1; i>=0; i--){ // sort decreasing order
            for(it=bucket[i].begin(); it!= bucket[i].end(); ++it){
                ItemList[k++]=*it;
            }
            bucket[i].clear();
        }
    };// for X
};
//-----------------------------------------------------------------------------

void radixSortStr(VPSI &ItemList, int maxLen){
    const int bSize = 2*ALPHABET_SIZE+1;
    VPSI bucket[bSize];
    for(int len=maxLen-1; len>=0; len--){
        for(int i=0; i<ItemList.size(); i++){
            char currentChar =  (ItemList[i].first).size() > len ?
                                (ItemList[i].first)[len] : EMPTY_CHAR;
            int id = INDEX(currentChar);
            bucket[id].push_back(ItemList[i]);
        };

        int i,k=0;
        VPSI::iterator it;
        for(int i=0; i<bSize; i++){ // lexicographic order
            for(it = bucket[i].begin(); it!= bucket[i].end(); ++it){
                ItemList[k++] = *it;
            };
            bucket[i].clear();
        }
    };//len
};
//-----------------------------------------------------------------------------

void solveIt(){
    tr1::unordered_map<string, int>::iterator it;
    for(it = FrequencyOf.begin(); it != FrequencyOf.end(); ++it){   // O(M)
        ItemList.push_back(make_pair((*it).first, (*it).second));
    };

    radixSortStr(ItemList, maxNameLen);
    stableRadixSortInt(ItemList, maxFrequency);
};
//-----------------------------------------------------------------------------

void printResult(){
    for(int i=0; i<K; i++){
        if (i>=ItemList.size()) break;
        cout <<ItemList[i].first<<" "<<ItemList[i].second<<endl;
    };
}
//=============================================================================

int main()
{
    readInput();
    solveIt();
    printResult();
    return 0;
}
