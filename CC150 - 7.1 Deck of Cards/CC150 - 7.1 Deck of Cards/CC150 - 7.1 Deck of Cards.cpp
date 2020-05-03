// CC150 - 7.1 Deck of Cards.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

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

inline int exchg(int &a, int &b)  { int c = a; a = b; b = c; }
inline int log2(int N){ return log10(N) / log10(2); }
inline float min(float a, float b) { return a<b ? a : b; }

enum Suit { SPADE, HEART, CLUB, DIAMOND }; // enum 的loop比较麻烦，需要自定义 ++i, iterator, () operator 等....... 

struct Card{
	Suit col;
	int _facevalue;

	bool exist; 

	virtual int value(){ return _facevalue; }

	Card(Suit x, int y) :col(x), _facevalue(y), exist(true) {}
	Card(const Card& other) :col(other.col), _facevalue(other._facevalue), exist(other.exist) {}

};

void swap(Card& a, Card& b){
	Card c = a; 
	a = b;
	b = c;
}

template<typename T> 
class Hand {
protected:
	vector<T> hand; 
public:
	virtual int score() {
		int score = 0; 
		for (auto c : hand)
			score += c.value(); 
		return score; 
	}

	void addCard(T c){
		hand.push_back(c); 
	}
};

class BlackJackCard : public Card {
public:
	BlackJackCard(Card::Color i, int j) :Card(i, j) {}
	int value(){
		
	}

	bool isAce() { return _facevalue == 1;  }
};

class BlackJackCardHand : public Hand<BlackJackCard> {
protected:
	vector<int> possibleScores(){
		vector<int> result; 
		possibleScores(hand, 0, 0, result); 
		return result; 
	}
	void possibleScores(vector<BlackJackCard>& hand, int i, int sum, vector<int>& result){
		if (i == hand.size()){
			result.push_back(sum); 
			return; 
		}
		BlackJackCard curCard = hand[i]; 
		if (curCard.isAce()){
			possibleScores(hand, i + 1, sum += 1, result); 
			possibleScores(hand, i + 1, sum += 10, result); 
		}
		else
			possibleScores(hand, i + 1, sum += curCard.value(), result); 
	}


public:
	int score(){
		vector<int> posScores = possibleScores();
		int maxUnder = INT_MIN, minOver = INT_MAX; 
		for (auto i : posScores){
			if (i <= 21 && i > maxUnder)
				maxUnder = i;
			else if (i > 21 && i < minOver)
				minOver = i; 
		}
		return (maxUnder == INT_MIN) ? minOver : maxUnder;
	}
	
	bool is21() {}
	bool busted(){}
	bool isBlackJace(){}
};


class Deck {
private:
	vector < Card > deck; 
	int dealt; 
	int undealt; 

public:
	Deck() {
		for (int i = 0; i < 4; i = i + 1)
			for (int j = 1; j <= 13; ++j)
				deck.push_back(Card(i, j));
		shuffle(); 
		undealt = 52; 
		dealt = 0; 
	}

	void shuffle(){
		srand(time()); 

		int n = deck.size(); 
		for (int i = 0; i < n; ++i){
			int ranNum = rand() % (n - i); 
			swap(deck[i], deck[ranNum + i]); 
		}
	}

	vector<Card> dealHand(int number){
		vector<Card> result; 
		for (int i = 0; i < number; ++i){
			result.push_back(dealCard()); 
		}
		return result; 
	}

	Card dealCard(){
		deck[dealt++].exist = false; 
		undealt--; 
		return deck[dealt]; 
	}
};



int main()
{
	


}
