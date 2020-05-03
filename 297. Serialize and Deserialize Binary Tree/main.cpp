#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>
#include <sstream>
#include <string>

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

int stoi(string s){
    bool signal=true;
    if(s[0]=='-') signal=false;

    int result=0;

    int i=0;
    while(s[i]<'0' || s[i]>'9') ++i;

    for(;i<s.size(); ++i){
        result = 10*result + s[i]-'0';
    }
    return signal ? result : -result;
}


class Solution
{
public:
    /// 正确写法
    string serialize(TreeNode* root) {
        ostringstream out;
        queue<TreeNode*> q;
        if (root) q.push(root);
        while (!q.empty()) {
            TreeNode *t = q.front(); q.pop();
            if (t) {
                out << t->val << ' ';
                q.push(t->left);
                q.push(t->right);
            } else {
                out << "# ";
            }
        }
        return out.str();
    }

    /// 错误写法！！！ '0'+tmp->val   如果val是负数怎么办？？ 必须用 stoi ！！
     string serialize2(TreeNode* root) {
        if(!root) return string();
        queue<TreeNode*> q;
        q.push(root);
        string result;

        while(q.size()){
            TreeNode* tmp=q.front();
            q.pop();

            if(!tmp){
                result+="# ";
            }else{
                result.push_back('0'+tmp->val);
                result+=" ";

                q.push(tmp->left);
                q.push(tmp->right);
            }
        }
        return result;

    }

    TreeNode* deserialize(string data) {
        if(data.empty()) return nullptr;

        istringstream in(data);
        string tmp;
        in>>tmp;
        TreeNode* root=new TreeNode(stoi(tmp)), *cur=root;
        queue<TreeNode*> q;
        q.push(root);

        while(true){ /// 每次pop一个数， push进去两个数， push进去的是pop出来的左右子树
            cur = q.front();
            q.pop();
            if(!(in>>tmp)) break;
            if(tmp!="#"){
                TreeNode* left = new TreeNode(stoi(tmp));
                cur->left=left;
                q.push(left);
            }
            if(!(in>>tmp)) break;
            if(tmp!="#"){
                TreeNode* right = new TreeNode(stoi(tmp));
                cur->right=right;
                q.push(right);
            }
        }
        return root;
    }
};



class Codec2 {
public:

    // Encodes a tree to a single string.
    /// preorder 的方法！！ 更加简洁。 注意 stringstream的使用
    string serialize(TreeNode* root) {
        ostringstream out;
        input(root, out);
        return out.str();
    }

    void input(TreeNode* root, ostringstream& out){ /// preorder
        if(!root){
            out<<"# ";
            return;
        }
        out<<root->val<<" ";
        input(root->left, out);
        input(root->right, out);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream in(data);
        return output(in);
    }

    /// preorder， 处理节点方便， 因为只需要自顶向下生成节点。
    TreeNode* output(istringstream& in){  /// 只有一个参数......
        string val;
        in>>val; /// << and >> are totally different, pay attention to the direction.
        if(val=="#") return nullptr;
        TreeNode* root = new TreeNode(stoi(val));
        root->left = output(in);
        root->right = output(in);
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));

int main()
{
	Solution a;

//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
    TreeNode* tree = new TreeNode(-1,new TreeNode(0, nullptr, nullptr),
                                    new TreeNode(1, nullptr, nullptr));
    /*      6
        3       8
     1    4   7    9

    */

    istringstream isss(a.serialize(tree));

    cout<<isss.str();

    auto bbb = a.deserialize(isss.str());

    print(bbb);
}
