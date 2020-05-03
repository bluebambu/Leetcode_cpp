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
	TreeNode(int a, int b):key(a), val(b), color(false), left(nullptr), right(nullptr) {}
	TreeNode(int a, int b, TreeNode* x, TreeNode* y):key(a), val(b), color(false), left(x), right(y) {}
	TreeNode():key(0), val(0), color(false), left(nullptr), right(nullptr) {}

	int key;
	int val;
	bool color;
	TreeNode *left;
	TreeNode *right;

};

void print(TreeNode* root){
    queue<TreeNode*> q;
    TreeNode* it=root;
    q.push(it);

    while(q.size()){
        int n=q.size();
        for(int i=0; i<n; ++i){
            if(q.front()){
                cout<<q.front()->key<<" ";
                q.push(q.front()->left);
                q.push(q.front()->right);
            }
            else
                cout<<"# ";
            q.pop();
        }
        cout<<endl;
    }
}


class RBTree
{
private:
    TreeNode* root;
public:
    RBTree():root(nullptr) {}

    TreeNode* Root(){
        return root;
    }



};

int main()
{



}
