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
    void recoverTree(TreeNode* root) {
        TreeNode *x = nullptr, *y = nullptr;  // the two nodes that are swapped
        TreeNode *pred = nullptr;             // previous node in inorder traversal
        TreeNode *current = root;

        while (current != nullptr) {
            if (current->left == nullptr) {
                // "Visit" current
                if (pred != nullptr && current->val < pred->val) {
                    if (x == nullptr) x = pred; // first violation: pred is too large
                    y = current;                // current is smaller than pred
                }
                pred = current;
                current = current->right;
            } else {
                // Find the inorder predecessor of current (rightmost in left subtree)
                TreeNode* predecessor = current->left;
                while (predecessor->right != nullptr && predecessor->right != current) {
                    predecessor = predecessor->right;
                }

                if (predecessor->right == nullptr) {
                    // Make current the right child of its inorder predecessor (threading)
                    predecessor->right = current;
                    current = current->left;
                } else {
                    // Thread already exists -> remove it and "visit" current
                    predecessor->right = nullptr;
                    if (pred != nullptr && current->val < pred->val) {
                        if (x == nullptr) x = pred;
                        y = current;
                    }
                    pred = current;
                    current = current->right;
                }
            }
        }

        if (x != nullptr && y != nullptr) {
            std::swap(x->val, y->val);
        }
    }
};
