// _template.cpp : Defines the entry point for the console application.
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

using namespace std;

inline int exchg(int &a, int &b)  { int c = a; a = b; b = c; }
inline int log2(int N){ return log10(N) / log10(2); }
inline float min(float a, float b) { return a<b ? a : b; }



class Tweet {
public:
    int id;
    int user_id;
    string text;
    static Tweet create(int user_id, string tweet_text) {
        // This will create a new tweet object,
        // and auto fill id
    }
}

class MiniTwitter {
public:
	unordered_map<int, unordered_set<int>> network; 
	unordered_map<int, vector<Tweet>> twtStore; 

	MiniTwitter() {
		// initialize your data structure here.
	}

	// @param user_id an integer
	// @param tweet a string
	// return a tweet
	Tweet postTweet(int user_id, string tweet_text) {
		//  Write your code here
	}

	// @param user_id an integer
	// return a list of 10 new feeds recently
	// and sort by timeline
	vector<Tweet> getNewsFeed(int user_id) {
		// Write your code here
	}

	// @param user_id an integer
	// return a list of 10 new posts recently
	// and sort by timeline
	vector<Tweet>  getTimeline(int user_id) {
		// Write your code here
	}

	// @param from_user_id an integer
	// @param to_user_id an integer
	// from user_id follows to_user_id
	void follow(int from_user_id, int to_user_id) {
		// Write your code here
	}

	// @param from_user_id an integer
	// @param to_user_id an integer
	// from user_id unfollows to_user_id
	void unfollow(int from_user_id, int to_user_id) {
		// Write your code here
	}
};
