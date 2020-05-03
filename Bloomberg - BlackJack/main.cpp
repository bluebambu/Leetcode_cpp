#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>
#include <random>
#include <ctime>

using namespace std;

enum Suit {club, diamond, heart, spade};

class Card {
    bool _available = true;
protected:
    int _faceValue;
    Suit _suit;
public:
    Card(int c, Suit s): _faceValue(c), _suit(s) {}
    virtual int value() = 0;
    Suit suit() {return _suit;}
    bool isAvailable() {return _available;}
    void markUnavailable {_available=false; }
    void markAvailable {_available=true; }
};

class BlackJackcard : public Card {
public:
    BlackJackcard(int c, Suit s):Card(c, s) {}
    int value(){
        if(isAce()) return 1;
        else if (isFaceCard()) return 10;
        else return _faceValue;
    }

    int minValue() {
        if(isAce()) return 1;
        else return value();
    }

    int maxValue(){
        if(isAce()) return 11;
        else return value();
    }

    bool isAce(){
        return _faceValue==1;
    }

    bool isFacecard(){
        return _faceValue>=11 && _faceValue<=13;
    }

};


template<typename cards>
class Deck{
private:
    vector<cards> _cards;
    int _dealIndex=0;
public:
    Deck(){Init(); }

    void Init(){
        for(int i=1; i<13; ++i)
            ///.....
    }

    setDeckOfCards();
    int remainingCards(){
        return _cards.size()-_dealIndex;
    }

    vector<cards> dealHand(int num){
        vector<cards> result;
    }

    cards dealCard(){
        if(_cards.empty())
            return Card(-1, 0);

        cards tmp=_cards[_dealIndex];
        cards[_dealIndex].markUnavailable();
        return tmp;
    }

    void shuffle(){ /// 完美随机洗牌
        srand(std::time(0));
        int full = _cards.size();
        for(int i=0; i<full; ++i){
            int tmp_rand = rand%(full-i);
            swap(_cards[i], _cards[tmp_rand+i]);
        }
    }
};
