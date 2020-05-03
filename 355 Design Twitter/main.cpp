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

struct TreeNode;
void print();

inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}
inline float min(float a, float b) {return a<b?a:b;}


void print(TreeNode* root){
    queue<TreeNode*> q;
    q.push(root);

    while(q.size()){
        auto tmp = q.front();
        cout<<tmp->val<<" ";
        if(tmp->left) q.push(tmp->left);
        if(tmp->right) q.push(tmp->right);
        q.pop();
    }
}

struct TreeNode
{
	TreeNode(int a):val(a), left(nullptr), right(nullptr) {}
	TreeNode(int a, TreeNode* x, TreeNode* y):val(a), left(x), right(y) {}
	TreeNode():val(0), left(nullptr), right(nullptr) {}

	int val;
	TreeNode *left;
	TreeNode *right;

};


//============================================//

class Twitter {
private:
    struct tweet{
        int userId;
        int tweetId;
        int timestamp;
        tweet(int x, int y, int z):userId(x), tweetId(y), timestamp(z){};
    };

    struct mycompare{
        bool operator()(pair<list<tweet>::iterator, list<tweet>::iterator> p1, pair<list<tweet>::iterator, list<tweet>::iterator> p2){
            return p1.first->timestamp < p2.first->timestamp;
        }
    };
    int timelabel = 0;
    unordered_map<int, unordered_set<int>> follower_dict;
    unordered_map<int, list<tweet>> twitter_dict;
public:
    /** Initialize your data structure here. */
    Twitter() {}

    /** Compose a new tweet. */
    void postTweet(int userId, int tweetId) {
        follower_dict[userId].insert(userId);
        twitter_dict[userId].push_front(tweet(userId, tweetId, timelabel));
        timelabel++;
    }

    /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
    vector<int> getNewsFeed(int userId) {
        vector<int> res;
        if(follower_dict.find(userId) == follower_dict.end()) return res;
        priority_queue< pair<list<tweet>::iterator, list<tweet>::iterator>, vector<pair<list<tweet>::iterator, list<tweet>::iterator>>, mycompare> pq;
        for(auto it = follower_dict[userId].begin(); it != follower_dict[userId].end(); it++){
            if(twitter_dict[*it].begin() != twitter_dict[*it].end()){    /// *it exist in one's followee list
                pq.push(make_pair(twitter_dict[*it].begin(), twitter_dict[*it].end()));
            }
        }
        int index = 0;
        while(!pq.empty() && index < 10){
            auto tmp = pq.top();
            pq.pop();
            res.push_back(tmp.first->tweetId);
            if(++tmp.first != tmp.second){
                pq.push(tmp);
            }
            index++;
        }
        return res;
    }

    /** Follower follows a followee. If the operation is invalid, it should be a no-op. */
    void follow(int followerId, int followeeId) {
        follower_dict[followerId].insert(followerId);
        follower_dict[followerId].insert(followeeId);
    }

    /** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
    void unfollow(int followerId, int followeeId) {
        if(follower_dict.find(followerId) != follower_dict.end() && followerId != followeeId){
            follower_dict[followerId].erase(followeeId);
        }
    }
};


////////////////////////////// 2nd solution from Leetcode /////////////////////////////////////

class Twitter
{
    struct Tweet
    {
        int time;
        int id;
        Tweet(int time, int id) : time(time), id(id) {}
    };

    std::unordered_map<int, std::vector<Tweet>> tweets; // [u] = array of tweets by u
    std::unordered_map<int, std::unordered_set<int>> following; // [u] = array of users followed by u

    int time;

public:
    Twitter() : time(0) {}

    void postTweet(int userId, int tweetId){
        tweets[userId].emplace_back(time++, tweetId);
    }

    std::vector<int> getNewsFeed(int userId){
        std::vector<std::pair<Tweet*, Tweet*>> h; // pair of pointers (begin, current)

        for (auto& u: following[userId]){
            auto& t = tweets[u];
            if (t.size() > 0)
                h.emplace_back(t.data(), t.data() + t.size() - 1); /// t.data() returns the address of internal array.
        }
        auto& t = tweets[userId]; // self
        if (t.size() > 0)
            h.emplace_back(t.data(), t.data() + t.size() - 1);

        auto f = [](const std::pair<Tweet*, Tweet*>& x, const std::pair<Tweet*, Tweet*>& y) { /// lamda expression
            return x.second->time < y.second->time;
        };
        std::make_heap(h.begin(), h.end(), f); /// make a heap in place

        const int n = 10;
        std::vector<int> o;
        o.reserve(n);
        for (int i = 0; (i < n) && !h.empty(); ++i){ /// && is important
            std::pop_heap(h.begin(), h.end(), f); /// pop_heap pop the top() and place it at the tail

            auto& hb = h.back();
            o.push_back(hb.second->id);

            if (hb.first == hb.second--)
                h.pop_back();
            else
                std::push_heap(h.begin(), h.end(), f);
        }
        return o;
    }

    void follow(int followerId, int followeeId){
        if (followerId != followeeId)
            following[followerId].insert(followeeId);
    }

    void unfollow(int followerId, int followeeId){
        following[followerId].erase(followeeId);
    }
};



int main()
{
	Solution a;

//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1),
                                                    new TreeNode(4)),
                                    new TreeNode(8, new TreeNode(7),
                                                    new TreeNode(9)));
    /*      6
        3       8
     1    4   7    9

    */
}
