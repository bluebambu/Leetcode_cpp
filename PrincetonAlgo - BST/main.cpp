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
	TreeNode(int a, int b):key(a), val(b), left(nullptr), right(nullptr) {}
	TreeNode(int a, int b, TreeNode* x, TreeNode* y):key(a), val(b), left(x), right(y) {}
	TreeNode():key(0), val(0), left(nullptr), right(nullptr) {}

	int key;
	int val;
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



class BST
{
private:
    TreeNode* root;
public:
    BST():root(nullptr) {}

    TreeNode* Root(){
        return root;
    }

    void buildPreorder(vector<pair<int, int>> vec){
        root = buildPreorder(root, vec, 0, vec.size()-1);
    }
    TreeNode* buildPreorder(TreeNode* root, vector<pair<int, int>>& vec,int low, int high){
        if(low>high) return root;

        root = new TreeNode(vec.at(low).first, vec.at(low).second);

        int i;
        for(i=low+1; i<=high; ++i){
            if(vec[i].first>root->key)
                break;
        }

        root->left = buildPreorder(root->left, vec, low+1, i-1);
        root->right = buildPreorder(root->right, vec, i, high);
        return root;
    }


    int get(int key){
        return get(root, key);
    }
    int get(TreeNode* root, int key){
        if(!root)
            throw runtime_error("No elem");
        if(root->key == key)
            return root->val;
        if(root->key > key)
            return get(root->left, key);
        else
            return get(root->right, key);
    }


    void put(int key, int val){
        put(root, key, val);
    }
    TreeNode* put(TreeNode* root, int key, int value){
        if(!root)
            return root=new TreeNode(key, value);
        if(root->key == key)
            root->val = value;
        else if(root->key > key)
            root->left = put(root->left, key, value);
        else
            root->right = put(root->right, key, value);
        return root;
    }


    int size(){
        return size(root);
    }
    int size(TreeNode* root){
        if(!root) return 0;
        return size(root->left)+size(root->right)+1;
    }

    int floor(int key){
        if(!root)
            throw runtime_error("empty tree");
        return floor(root, key)->val;
    }
    TreeNode* floor(TreeNode* root, int key){
        if(!root) return nullptr;
        if(root->key == key)
            return root;
        if(root->key > key)
            return floor(root->left, key);
        else{
            TreeNode* right = floor(root->right, key);
            if(!right)
                return root;
            else
                return right;
        }
    }


    void insert(int key, int val){
        TreeNode* p=root;

        while(1){
            if(!p){
                p = new TreeNode(key, val);
                break;
            }
            else if(p->key == key){
                p->val = val;
                break;
            }else if(p->key > key){
                if(p->left){
                    p=p->left;
                    continue;
                }else{
                    p->left = new TreeNode(key, val);
                    break;
                }
            }else if(p->key < key){
                if(p->right){
                    p=p->right;
                    continue;
                }else{
                    p->right = new TreeNode(key, val);
                    break;
                }
            }
        }
    }



    void del(int key){
        del(root, key);
    }
    void del(TreeNode*& node, int key){
        if(!node)
            return;
        if(node->key > key)
            del(node->left, key);
        else if(node->key < key)
            del(node->right, key);
        else{
            if(node->left && node->right){
                TreeNode* tmp = findMin(node->right);
                node->key = tmp->key;
                node->val = tmp->val;
                del(node->right, node->key);
            }else if(node->left || node->right){
                TreeNode* tmp = node;
                node = node->left ? node->left : node->right;
                delete tmp;
            }else
                delete node;
        }
    }

    TreeNode* findMin(TreeNode* node){
        TreeNode* result=node;
        while(result->left)
            result=result->left;
        return result;
    }


};



int main()
{
	BST a;
	a.buildPreorder(vector<pair<int, int>>({{3,2},{1,2},{2,2},{4,2},{6,2},{5,2}}));
	print(a.Root());
	a.del(4);
	a.insert(4,2);
	print(a.Root());
	cout<<a.size();


}
