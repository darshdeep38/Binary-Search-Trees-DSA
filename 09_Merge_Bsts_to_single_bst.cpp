class Solution {
public:
    TreeNode* canMerge(vector<TreeNode*>& trees) {
        unordered_map<int, TreeNode*> valToNode; // Maps value to its root node
        unordered_map<int, int> count; // Frequency of each value across all trees
        
        // Build the maps
        for (TreeNode* tree : trees) {
            valToNode[tree->val] = tree;
            count[tree->val]++; // Root value appears once
            
            // Count left and right child values
            if (tree->left) {
                count[tree->left->val]++;
            }
            if (tree->right) {
                count[tree->right->val]++;
            }
        }
        
        // Try each tree as potential final root
        // The final root should have count = 1 (only appears as root, never as leaf)
        for (TreeNode* tree : trees) {
            if (count[tree->val] == 1) {
                // Make a copy of valToNode for this attempt
                unordered_map<int, TreeNode*> tempValToNode = valToNode;
                
                if (isValidBST(tree, nullptr, nullptr, tempValToNode) && 
                    tempValToNode.size() <= 1) {
                    return tree;
                }
                return nullptr; // If one attempt fails, no valid BST possible
            }
        }
        
        return nullptr;
    }
    
private:
    bool isValidBST(TreeNode* node, TreeNode* minNode, TreeNode* maxNode, 
                    unordered_map<int, TreeNode*>& valToNode) {
        if (!node) return true;
        
        // Check BST property
        if (minNode && node->val <= minNode->val) return false;
        if (maxNode && node->val >= maxNode->val) return false;
        
        // If this is a leaf node and we have a tree with this root value, merge it
        if (!node->left && !node->right && valToNode.count(node->val)) {
            int val = node->val;
            TreeNode* subtree = valToNode[val];
            
            // Replace leaf with subtree's children
            node->left = subtree->left;
            node->right = subtree->right;
            
            // Remove from map to mark as used
            valToNode.erase(val);
        }
        
        // Recursively validate left and right subtrees
        return isValidBST(node->left, minNode, node, valToNode) &&
               isValidBST(node->right, node, maxNode, valToNode);
    }
};

/*
Time Complexity: O(N) where N is the total number of nodes
- O(N) to build the frequency maps
- O(N) for each DFS validation attempt
- At most one successful attempt

Space Complexity: O(N) 
- O(N) for the hash maps storing node mappings and frequencies
- O(H) recursion stack where H is the height of the resulting tree

Algorithm Explanation:
1. **Frequency Counting**: Count how many times each value appears across all trees
   - Root values appear once as roots
   - Child values appear once for each time they're referenced

2. **Find Candidate Root**: The final root must have frequency = 1
   - This means it only appears as a root, never as a leaf in any other tree
   - If multiple candidates exist, only one can lead to a valid BST

3. **DFS Validation**: For the candidate root, perform DFS:
   - Validate BST properties (left < root < right)
   - When encountering a leaf, if there's a tree with that root value, merge it
   - Mark merged trees as used by removing from the map

4. **Success Condition**: 
   - BST properties maintained throughout
   - At most 1 tree remains unused (the final root tree itself)

Key Insights:
- Each BST has at most 3 nodes, making the problem tractable
- The final root is the only value that appears exactly once in frequency count
- We merge by replacing leaf nodes with corresponding subtrees
- All trees except the final root must be consumed during merging

This solution correctly handles the constraint that we must perform exactly n-1 
merge operations to combine n trees into a single valid BST.
*/
