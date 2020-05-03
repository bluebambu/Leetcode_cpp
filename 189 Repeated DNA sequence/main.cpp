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


struct TreeNode
{
    TreeNode(int a):val(a), left(nullptr), right(nullptr) {}
    TreeNode(int a, TreeNode* x, TreeNode* y):val(a), left(x), right(y) {}
    TreeNode():val(0), left(nullptr), right(nullptr) {}

    int val;
    TreeNode *left;
    TreeNode *right;

};
/// �ҳ��ظ����ֵ��ַ�����ֱ�ӿ��Ǿ���Hash������

class Solution
{
public:



    //////////// Leetcode passed //////////////////////
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> result;
        if(s.size()<10) return result;
        const int LEN=10;
        unordered_map<string, int> map;

        for(int i=0; i<=s.size()-10; ++i){  /// ע�� ���ںţ���
            string tmp = s.substr(i, LEN);
            map[tmp]++;
        }

        for(auto iter=map.begin(); iter!=map.end(); ++iter){
            if(iter->second>1)
                result.push_back(iter->first);
        }

        return result;
    }

    ////////////// LEetcode TLE ///////////////////
    /// �Ҿ�����Ҫ2��hash��һ��ȫ�֣�һ��Ϊÿһ�������� ����TLE
    /// �������̫������
    /// ��ÿ������Ϊ10���ַ�������Hash��ͳ�Ƴ��ִ�������������һ���ַ�������
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> result;
        if(s.size()<10) return result;
        const int LEN=10;
        unordered_set<string> set1;

        for(int i=0; i<s.size()-LEN; ++i){
            string std = s.substr(i, LEN);
            if(set1.find(std)!=set1.end()) continue;
            set1.insert(std);
            unordered_set<string> set2;
            set2.insert(std);

            for(int j=i+1; j<=s.size()-LEN; ++j){ /// �˴� j Ҫ ��= size-10 ������
                string tmp = s.substr(j, LEN);
                if(set2.find(tmp)!=set2.end()){
                    result.push_back(tmp);
                    break;
                }
            }
        }

        return result;
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
