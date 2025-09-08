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



    private:
    bool validate(TreeNode* node , long minVal , long maxVal){
        if(!node ) return true;

        //check current node value
        if( node->val <= minVal || node->val >= maxVal) return false;


        // Recursively validate left and right subtrees
        return  validate(node->left , minVal , node->val) && validate(node->right ,  node->val , maxVal);


    }
public:
    bool isValidBST(TreeNode* root) {
        return validate(root , LONG_MIN , LONG_MAX);
    }
};
