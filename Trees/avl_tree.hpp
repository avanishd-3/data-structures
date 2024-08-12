#include <algorithm>

template<typename T>
class AVLTree {
    private:
        struct TreeNode {
            T data;
            TreeNode *left;
            TreeNode *right;
            int height;

            ~TreeNode() {
                delete left;
                delete right;
            }
        };

        TreeNode *root;

        int balance_factor(TreeNode *p) {
            if (p) {
                return height(p->left) - height(p->right);
            }

            else {
                return 0;
            }
        }

        TreeNode* InPre(TreeNode* p) {
            while (p && p->right) {
                p = p->right;
            }

            return p;
        }

        TreeNode* InSucc(TreeNode* p) {
            while (p && p->left) {
                p = p->left;
            }

            return p;
        }

        TreeNode* LL_rotation(TreeNode *p) {
            if (p) {
                TreeNode* p_left = p->left;
                TreeNode* p_left_right = p_left->right;

                p_left->right = p;
                p->left = p_left_right;

                // Recalculate heights
                p->height = height(p);
                p_left->height = height(p_left);

                if (p == root) {
                    root = p_left;
                }
                return p_left;
            }
            return nullptr;
        }

        void RR_rotation(TreeNode *p) {
            if (p) {
                TreeNode* p_right = p->right;
                TreeNode *p_right_left = p_right->left;

                p_right->left = p;
                p->right = p_right_left;

                // Recalculate heights
                p->height = height(p);
                p_right->height = height(p_right);

                if (p == root) {
                    root = p_right;
                }
                return p_right;
            }
            return nullptr;
        }

        void LR_rotation(TreeNode *p) {
            if (p) {
                TreeNode* p_left = p->left;
                TreeNode* p_left_right = p_left->right;

                p_left->right = p_left_right->left;
                p->left = p_left_right->right;

                p_left_right->left = p_left;
                p_left_right->right = p;

                // Recalculate heights
                p->height = height(p);
                p_left->height = height(p_left);
                p_left_right->height = height(p_left_right);

                if (p == root) {
                    root = p_left_right;
                }
                return p_left_right;
            }
            return nullptr;
        }

        void RL_rotation(TreeNode *p) {
            if (p) {
                TreeNode* p_right = p->right;
                TreeNode* p_right_left = p_right->left;

                p_right->left = p_right_left->right;
                p->right = p_right_left->left;

                p_right_left->right = p_right;
                p_right_left->left = p;

                // Recalculate heights
                p->height = height(p);
                p_right->height = height(p->right);
                p_right_left->height = height(p_right_left);

                if (p == root) {
                    root = p_right_left;
                }
                return p_right_left;
            }
            return nullptr;
        }

    public:
        AVLTree()
            : root{nullptr}
        {
        }

        ~AVLTree() {
            delete root;
        }

        int height(TreeNode *root) {
            if (!root) {
                return -1;
            }

            int x_height = height(root->left);
            int y_height = height(root->right);

            return std::max(x_height, y_height) + 1;
        }

         void insert(TreeNode *root, T val) {
             
            // Insert value into tree
             
            if (!root) {
                root = new Node{val, nullptr, nullptr, 0};
            }
    
            else {
                if (val < root->data) {
                    root->left = insert(root->left, val);
                }
                else if (val > root->data) {
                    root->right = insert(root->right, val);
                }
        
                else {
                    return;
                }
            }
            root->height = height(root);

            // Check balance factors & perform rotations if necessary

            if (balance_factor(root) > 1 && balance_factor(root->left) == 1) { // LL Rotation
                root = LL_rotation(root);
            }

            else if (balance_factor(root) > 1 && balance_factor(root->left) == -1) { // LR Rotation
                root = LR_rotation(root);
            }

            else if (balance_factor(root) < -1 && balance_factor(root->right) == -1) { // RR Rotation
                root = RR_rotation(root);
            }
            else if (balance_factor(root) < -1 && balance_factor(root->right) == 1) { // RL Rotation
                root = RL_Rotation(root);
            }
        }

        TreeNode* remove(TreeNode *root, T key) {
            if (root == nullptr) {
                return;
            }
    
            if (root->left == nullptr && root->right == nullptr) {
                delete root;
                return nullptr;
            }
    
            if (key < root->data) {
                root->left = remove(root->left, key);
            }

            else if (key > root->data) {
                root->right = remove(root->right, key);
            }
    
            else {
                if (height(root->left) > height(root->right)) {
                    TreeNode* q = InPre(root->left);
                    root->data = q->data;
                    root->left = remove(p->left, q->data);
                }
        
                else {
                    TreeNode* q = InSucc(root->right);
                    root->data = q->data;
                    root->right = remove(p->right, q->data);
                }
            }

            root->height = height(root);

            // Check balance factors & perform rotations if necessary

            if (balance_factor(root) > 1 && balance_factor(root->left) == 1) { // L1 Rotation
                root = LL_rotation(root);
            }

            else if (balance_factor(root) > 1 && balance_factor(root->left) == -1) { // L-1 Rotation
                root = LR_rotation(root);
            }

            else if (balance_factor(root) > 1 && balance_factor(root->left) == 0) { // L0 Rotation
                root = LL_rotation(root);
            }

            else if (balance_factor(root) < 1 && balance_factor(root->right) == 1) { // R1 Rotation
                root = RL_rotation(root);
            }

            else if (balance_factor(root) < 1 && balance_factor(root->right) == -1) { // R-1 Rotation
                root = RR_Rotation(root);
            }

            else if (balance_factor(root) < 1 && balance_factor(root->right) == 0) { // R0 Rotation
                root = RR_Rotation(root);
            }

            return root;
        }

};
