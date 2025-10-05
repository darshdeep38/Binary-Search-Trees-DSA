/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
        int sum = 0 ;

    TreeNode* convertBST(TreeNode* root) {
        reverseInorder(root);
        return root ;
    }

    void reverseInorder(TreeNode* node){
        if(!node) return ;
        reverseInorder(node->right);
        sum += node->val; // add current node's value to the sum 
        node->val = sum; //update current node's value 

        reverseInorder(node->left);
    }
};
