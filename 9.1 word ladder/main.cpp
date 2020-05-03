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
    /// lc passed, similar to WordLadder II
    int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList) {
        if(wordList.empty()) return 0;
        unordered_set<string> head, tail;
        head.insert(beginWord); tail.insert(endWord);
        wordList.erase(beginWord); wordList.erase(endWord);
        int step = 2;
        bool headfirst=true;

        while(!head.empty()){
            if(head.size() > tail.size()){
                swap(head, tail);
                headfirst = !headfirst;
            }

            unordered_set<string> newset;
            for(auto iter=head.begin(); iter!=head.end(); iter++){
                string cur = *iter;

                for(int i=0; i<cur.size(); ++i){
                    string tmp = cur;
                    for(char j='a'; j<='z'; ++j){
                        tmp[i]=j;

                        if(tail.find(tmp)!=tail.end())
                            return step;
                        if(wordList.find(tmp)!=wordList.end()){
                            newset.insert(tmp);
                            wordList.erase(tmp);
                        }
                    }
                }
            }
            head=newset;
            ++step;
        }
        return 0;
    }


    /// mkyforever answer  /////////////
     int ladderLength(string start, string end, unordered_set<string> &dict){
         // 标记字典中的单词是否被访问过
         unordered_set<string> visited;

         queue<string> q;
         q.push(start);
         visited.insert(start);

         int height = 1;
         while(!q.empty())
         {
             // 接下来处理下一层
             ++ height;
             for(int i = 0, n = q.size(); i < n; ++ i)
             {
                 string s = q.front();
                 q.pop();
                 // 对单词中的每个字符都进行替换处理
                 for(int j = 0; j < s.size(); ++ j)
                 {
                     string temp = s;
                     // 依次用26个字母进行替换
                     for(char c = 'a'; c <= 'z'; ++ c)
                     {
                         temp[j] = c;
                         // 如果替换后等于end，直接返回遍历的层高height即可
                         if(temp == end)
                             return height;
                         // 如果在字典中且没被访问过，入队列并标记为已访问
                         if(dict.find(temp) != dict.end() && visited.find(temp) == visited.end())
                         {
                             q.push(temp);
                             visited.insert(temp);
                         }
                     }
                 }
             }
         }

         return 0;
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
