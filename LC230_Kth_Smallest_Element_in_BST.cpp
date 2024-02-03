#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>

// height-balanced definition:
// the depth of the two subtrees of every node never differ by more than 1

/*notes
- Do DFS
- Need to backtrack (?)
*/

using namespace std;

//  Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:

    // do inOrder because of BST property. Avoids having to sort vector
    void inOrderTraversal(TreeNode* root, vector<int> &v){
        if (root == nullptr){
            return;
        }

        inOrderTraversal(root->left,v);
        v.push_back(root->val); // add value at current node to vector v
        inOrderTraversal(root->right,v);
    }

    int kthSmallest(TreeNode* root, int k) {
        vector<int> v; // vector that stores ints

        // add all ints to v
        inOrderTraversal(root,v);

        // return kth smallest element
        return(v[k-1]);
        
    }
};

int main(){
    Solution s;
 
    // Task 1: Construct a tree for testing
    TreeNode * root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(7);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(9);

    cout << s.kthSmallest(root,4) << endl;

}