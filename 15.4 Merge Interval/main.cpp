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

struct TreeNode
{
	TreeNode(int a):val(a), left(nullptr), right(nullptr) {}
	TreeNode(int a, TreeNode* x, TreeNode* y):val(a), left(x), right(y) {}
	TreeNode():val(0), left(nullptr), right(nullptr) {}

	int val;
	TreeNode *left;
	TreeNode *right;

};

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


  struct Interval {
      int start;
      int end;
      Interval() : start(0), end(0) {}
      Interval(int s, int e) : start(s), end(e) {}
  };


class Solution
{
public:
    ///// passed, fast  Sort first, then merge //////
    struct comp{
        bool operator() (Interval& a, Interval& b){
            if(a.start < b.start || (a.start == b.start && a.end < b.end)) // (a.start == b.start && a.end < b.end) is not necessary, in fact better not having it.
                return true;
            else
                return false;
        }
    };

    vector<Interval> merge(vector<Interval>& intervals) {
        sort(intervals.begin(), intervals.end(), comp());

        vector<Interval> result;
        if(intervals.empty()) return result;
        result.push_back(intervals[0]);

        for(int i=1; i<intervals.size(); ++i){
            Interval tmp = result.back();

            if(tmp.end >= intervals[i].end)
                continue;
            else if(tmp.end >= intervals[i].start && tmp.end < intervals[i].end)
                result.back().end = intervals[i].end;
            else
                result.push_back(intervals[i]);
        }

        return result;
    }

};

class Solution2 {
public:
    void add(vector<Interval>& result, Interval& a){
        Interval tmp = result.back();
        if(tmp.end >= a.end)
            return;
        else if(tmp.end >= a.start && tmp.end < a.end)
            result.back().end = a.end;
        else
            result.push_back(a);
    }

    vector<Interval> merge(vector<Interval>& intervals) {
        vector<Interval> result;
        if(intervals.empty()) return result;
        sort(intervals.begin(), intervals.end(), [](Interval& a, Interval& b){return (a.start < b.start) || (a.start==b.start && a.end<=b.end);});

        result.push_back(intervals[0]);

        for(int i=1; i<intervals.size(); ++i){
            add(result, intervals[i]);
        }

        return result;


    }
};


int main()
{
	Solution2 a;

//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1),
//                                                    new TreeNode(4)),
//                                    new TreeNode(8, new TreeNode(7),
//                                                    new TreeNode(9)));
//    /*      6
//        3       8
//     1    4   7    9
//
//    */

    vector<Interval> c{Interval(1,3), Interval(2,3), Interval(8,10)};

    auto d =(a.merge(c));

    cout<<d.size();



}
