#include <iostream>
#include <algorithm>
#include <stdlib.h>

// height-balanced definition:
// the depth of the two subtrees of every node never differ by more than 1

/*strategy:
- Recursively check height of subtrees
- 
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

    int getHeight(TreeNode* root){
        if (root == nullptr){
            return 0;
        }
        return (max(getHeight(root->left),getHeight(root->right)) + 1);
    }

    bool isBalanced(TreeNode* root) {
        if (root == nullptr){
            return true;
        }
        return(abs(getHeight(root->left) - getHeight(root->right)) <=1) && isBalanced(root->left) && isBalanced(root->right);
    }

};

// Driver
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

    cout << s.isBalanced(root) << endl;

    return 0;
}