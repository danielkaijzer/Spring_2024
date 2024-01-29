#include <iostream>
#include <vector>
#include <queue>

//  Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/*
my guess:
- do a traversal
- maybe store values on stack or queue
- then swap values
*/ 


class Solution {
public:

    void recursiveInvert(TreeNode* root){
        // base case
        if (root == nullptr){
            return;
        }

        // else swap left and right child
        std::swap(root->right,root->left);
        recursiveInvert(root->left);
        recursiveInvert(root->right);
    }

    TreeNode* invertTree(TreeNode* root) {
        recursiveInvert(root);
        return root;
    }



   // Preorder traversal helper function
    void depthFirstSearch(TreeNode* root){
        
        if (root == NULL){
            return;
        }

        // output.push_back(root->val);
        depthFirstSearch(root->left);
        depthFirstSearch(root->right);
    }

    std::vector<std::vector<int>> levelOrder(TreeNode* root) {

        std::vector<std::vector<int>> output;
        if(root==nullptr){
            return output;
        }
        
        std::queue<TreeNode*> level_queue; // queue stores nodes from tree
        level_queue.push(root);

        while(!level_queue.empty()){
            
            int n = level_queue.size();
            std::vector<int> temp(n,0); // initialize a vector

            // iterate through queue at level to store values 
            // at that level in current temp vector
            for (int i = 0; i < n; i++){

                auto curr=level_queue.front();

                if(curr->left){ //if value on left, add to queue
                    level_queue.push(curr->left);
                }
                if(curr->right){ // if value right, add to queue
                    level_queue.push(curr->right);
                }

                temp[i]=curr->val;
                level_queue.pop();
            }

            output.push_back(temp); // at every level we push a new vector to output
        }

        return output;

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

    
    std::vector<std::vector<int>> values1 = s.levelOrder(root);

    // std::cout << values.at(0).at(0) << std::endl;

    for (int i = 0; i < values1.size(); i++){ // iterate through 2D vector
        // iterate through 1D vector
        for (int j = 0; j < values1.at(i).size(); j++){
            std::cout << values1.at(i).at(j) << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    std::vector<std::vector<int>> values2 = s.levelOrder(s.invertTree(root));

    // std::cout << values.at(0).at(0) << std::endl;

    for (int i = 0; i < values2.size(); i++){ // iterate through 2D vector
        // iterate through 1D vector
        for (int j = 0; j < values2.at(i).size(); j++){
            std::cout << values2.at(i).at(j) << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}