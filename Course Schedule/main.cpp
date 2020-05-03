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



class Solution {
public:
    /// passed, 将 prerequisites 存在 map 中之后， 就不需要再访问prerequisites了。 map用起来更加方便。
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        if(prerequisites.empty()) return true;

        vector<vector<int>> map(numCourses, vector<int>());
        for(int i=0; i<prerequisites.size(); ++i)
            map[prerequisites[i].first].push_back(prerequisites[i].second);

        vector<int> status(numCourses, 0);

        for(int i=0; i<numCourses; ++i){
            if(CanNotPassDFS(i, status, map))
                return false;
        }
        return true;
    }

    // status -1 is temporary status, 1 is permanent status
    bool CanNotPassDFS(int i, vector<int>& status, vector<vector<int>>& map){ /// 没有 prerequisites这里
        if(status[i]==1) return false;
        if(status[i]==-1) return true;

        status[i]=-1;
        for(int j=0; j<map[i].size(); ++j){
            if(CanNotPassDFS(map[i][j], status, map))
                return true;
        }
        status[i]=0;
        return false;
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
