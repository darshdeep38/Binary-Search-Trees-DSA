class Solution {
public:
    Node* connect(Node* root) {
        if (root == NULL || root->left == NULL) {
            return root;
        }

        queue<Node*> q;
        q.push(root);
        q.push(NULL);  // Marker for level end

        Node* prev = NULL;

        while (!q.empty()) {
            Node* curr = q.front();
            q.pop();

            if (curr == NULL) {
                // End of current level
                if (!q.empty()) {
                    q.push(NULL); // Add marker for the next level
                }
                prev = NULL; // Reset prev for the new level
            } else {
                if (prev != NULL) {
                    prev->next = curr;
                }
                prev = curr;

                if (curr->left != NULL) {
                    q.push(curr->left);
                }
                if (curr->right != NULL) {
                    q.push(curr->right);
                }
            }
        }

        return root;
    }
};
