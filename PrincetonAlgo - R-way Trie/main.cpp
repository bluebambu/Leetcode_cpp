#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>
#include <cstring>

using namespace std;

inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}
inline float min(float a, float b) {return a<b?a:b;}


struct TrieNode
{
    bool is_word;
    TrieNode *next[26];

    TrieNode(bool b = false) {
        memset(next, 0, sizeof(next));
        is_word = b;
    }
};


class Trie
{
    TrieNode* root;
public:
    Trie():root(new TrieNode()) {}

    void insert(string s){
        TrieNode* p=root;

        for(int i=0; i<s.size(); ++i){
            if(p->next[s[i]-'a'] == nullptr)
                p->next[s[i]-'a'] = new TrieNode();
            p=p->next[s[i]-'a'];
        }

        p->is_word = true;
    }

    bool search(string s){
        TrieNode* p = find(s);
        return p && p->is_word;
    }

    bool startsWith(string prefix){
        TrieNode* p = find(prefix);
        return p;
    }

    bool del(string s){
        if(search(s)){
            TrieNode* p=root;
            for(int i=0; i<s.size() && p!=nullptr; ++i){
                TrieNode* q=p;
                p=p->next[s[i]-'a'];
                if(SingleNext(q) || (i==s.size()-1))
                    delete q;
            }
            return true;
        }
        else
            return false;
    }

    bool SingleNext(TrieNode* q){
        int next=0;
        for(int i=0; i<26; ++i)
            if(q->next[i])
                ++next;
        return next==1;
    }

private:
    TrieNode* find(string s){
        TrieNode* p=root;
        for(int i=0; i<s.size() && p!=nullptr; ++i){
            p = p->next[s[i]-'a'];
        }
        return p;
    }

};


/** From Geeksforgeeks
bool deleteHelper(trie_node_t *pNode, char key[], int level, int len)
{
    if( pNode )
    {
        // Base case
        if( level == len )
        {
            if( pNode->value )
            {
                // Unmark leaf node
                pNode->value = 0;

                // If empty, node to be deleted
                if( isItFreeNode(pNode) )
                {
                    return true;
                }

                return false;
            }
        }
        else // Recursive case
        {
            int index = INDEX(key[level]);

            if( deleteHelper(pNode->children[index], key, level+1, len) )
            {
                // last node marked, delete it
                FREE(pNode->children[index]);

                // recursively climb up, and delete eligible nodes
                return ( !leafNode(pNode) && isItFreeNode(pNode) );
            }
        }
    }

    return false;
}

void deleteKey(trie_t *pTrie, char key[])
{
    int len = strlen(key);

    if( len > 0 )
    {
        deleteHelper(pTrie->root, key, 0, len);
    }
}
*/

int main()
{
    Solution a;

//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
    TrieNode* tree = new TrieNode(6,new TrieNode(3, new TrieNode(1),
                                                    new TrieNode(4)),
                                    new TrieNode(8, new TrieNode(7),
                                                    new TrieNode(9)));
    /*      6
        3       8
     1    4   7    9

    */

    a.flatten(tree);


}
