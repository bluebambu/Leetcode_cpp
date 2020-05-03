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



class Solution
{
public:

    //////////////////// 答案正确，不通过大数据集合 ////////////////////////////////
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        if(intervals.empty()){
            intervals.push_back(newInterval);
            return intervals;
        }

        // 过两遍，第一遍找到位置并且插入new interval，但对数据不做处理
        // 第二遍将 i+1 被 i 元素 覆盖的删除掉。

        for(int i=0; i<intervals.size(); ++i){
            int start=newInterval.start;

            if(i==0 && start<intervals[i].start)
                intervals.insert(intervals.begin(), newInterval);
            else if(start>=intervals[i].start && start<=intervals[i].end)
                intervals[i].end = intervals[i].end >newInterval.end ? intervals[i].end : newInterval.end;
            else if(i!=intervals.size()-1 && start>intervals[i].end && start<intervals[i+1].start)
                intervals.insert(intervals.begin()+i+1, newInterval);
            else if(i==intervals.size()-1 && start>intervals[i].end)
                intervals.insert(intervals.begin()+i+1, newInterval);
        }

        for(int i=0; i<intervals.size()-1;){
            if(intervals[i].end >= intervals[i+1].end)
                intervals.erase(intervals.begin()+i+1);
            else
                ++i;
        }

        return intervals;
    }

    //////////////////  更直观的方法是将 intervals 成员插入一个vector，这个vector 包含 newInterval 并以之为参照标准 ///////////////
    /////////////////  不过都是 O（n)， 没有用 binary search. 但是用binary search 又有一点过于复杂了。。。。。。。
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        vector<Interval> res;
        int i = 0;
        // add all the intervals ending before newInterval starts
        int n = intervals.size();
        while (i < n&&newInterval.start > intervals[i].end)  res.push_back(intervals[i++]);
        newInterval.start = ((i == n) ? newInterval.start : min(newInterval.start, intervals[i].start));
        // merge all overlapping intervals to one considering newInterval
        while (i < n&&newInterval.end >= intervals[i].start) i++;
        newInterval.end = ((i == 0) ? newInterval.end : max(intervals[i - 1].end, newInterval.end));
        res.push_back(newInterval);
        // add the union of intervals we got
        // add all the rest
        while (i < n&&newInterval.end < intervals[i].start) res.push_back(intervals[i++]);
        return res;
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

    a.flatten(tree);


}
