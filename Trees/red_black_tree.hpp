#include <iostream>

template<typename T>
class RedBlackTree {
    private:
        struct TreeNode {
            T data;
            TreeNode *parent;
            TreeNode *left;
            TreeNode *right;
            int color; // 0 = black, 1 = red
        };

        TreeNode *root;

        void left_rotate(TreeNode *x) {
            TreeNode *y = x->right;
            x->right = y->left; // y left subtree = x right subtree

            if (y->left != nullptr) {
                y->left->parent = x; // x is parent of left subtree
            }

            y->parent = x->parent;

            if (x == root) {
                root = y;
            }

            else if (x == x->parent->left) {
                x->parent->left = y;
            }
            else {
                x->parent->right = y;
            }

            y->left = x;
            x->parent = y;
        }

        void right_rotate(TreeNode *x) {
            TreeNode *y = x->left;
            x->left = y->right; // y left subtree = x right subtree

            if (y->right != nullptr) {
                y->right->parent = x; // x is parent of left subtree
            }

            y->parent = x->parent;

            if (x == root) {
                root = y;
            }

            else if (x == x->parent->right) {
                x->parent->right = y;
            }
            else {
                x->parent->left = y;
            }

            y->right = x;
            x->parent = y;
        }

        void fixInsert(TreeNode *node) { // Runs in O(log(n)) time with max 2 rotations
            TreeNode *y;

            while (node->parent->color == 1) {
                if (node->parent == node->parent->parent->left) {  
                    y = node->parent->parent->right; // y is node's uncle

                    if (y->color == 1) { // Check if parent & uncle are both red
                        node->parent->color = 0;
                        y->color = 0;
                        node->parent->parent->color = 1;
                        node = node->parent->parent;
                    }
                    else {
                        if (node == node->parent->right) {
                            node = node->parent;
                            left_rotate(node);
                        }
                        node->parent->color = 0;
                        node->parent->parent->color = 1;
                        right_rotate(node->parent->parent);
                    }
                }
                else {
                    y = node->parent->parent->left; // y is node's uncle

                    if (y->color == 1) { // Check if parent & uncle are both red
                        node->parent->color = 0;
                        y->color = 0;
                        node->parent->parent->color = 1;
                        node = node->parent->parent;
                    }
                    else {
                        if (node == node->parent->left) { // Left child
                            node = node->parent;
                            right_rotate(node);
                        }
                        node->parent->color = 0;
                        node->parent->parent->color = 1;
                        left_rotate(node->parent->parent);
                    }
                }
            }
            root->color = 0;
        }

        void transplant(TreeNode *u, TreeNode *v) {
            if (u->parent == nullptr) {
                root = v;
            }
            else if (u == u->parent->left) { // Left child
                u->parent->left = v;
            }
            else {
                u->parent->right = v;
            }
            v->parent = u->parent;
        }

        void fixDelete(TreeNode *node) { // Runs in O(log(n)) time & max 3 rotations
            while (node != root && node->color == 0) {
                if (node == node->parent->left) { // Node is left child
                    TreeNode *w = node->parent->right;
                    if (w->color == 1) { // Sibling is red
                        w->color = 0;
                        node->parent->color = 1;
                        left_rotate(node->parent);
                        w = node->parent->right;
                    }

                    if (w->left->color == 0 && w->right->color == 0) { // Sibling is black & nephews are black
                        w->color = 1;
                        node = node->parent;
                    }
                    else {
                        if (w->right->color == 0) { // Sibling is black & left nephew is red
                            w->left->color == 0;
                            w->color == 1;
                            right_rotate(w);
                            w = node->parent->right;
                        }
                        w->color = node->parent->color; // Sibling is black & right nephew is red
                        node->parent->color = 0;
                        w->right->color = 0;
                        left_rotate(x->parent);
                        x = root;
                    }
                }
                else { // Node is right child
                    TreeNode *w = node->parent->left;
                    if (w->color == 1) { // Sibling is red
                        w->color = 0;
                        node->parent->color = 1;
                        right_rotate(node->parent);
                        w = node->parent->left;
                    }

                    if (w->right->color == 0 && w->left->color == 0) { // Sibling is black & nephews are black
                        w->color = 1;
                        node = node->parent;
                    }
                    else {
                        if (w->left->color == 0) { // Sibling is black & right nephew is red
                            w->right->color == 0;
                            w->color == 1;
                            left_rotate(w);
                            w = node->parent->left;
                        }
                        w->color = node->parent->color; // Sibling is black & left nephew is red
                        node->parent->color = 0;
                        w->left->color = 0;
                        right_rotate(x->parent);
                        x = root;
                    }
                }
            }
            x->color = 0;
        }
    public:
        TreeNode* minimum(TreeNode *node) { // Find minimum node of a subtree
            while (node != nullptr) {
                node = node->left;
            }
            return node;
        }

        T min_value(TreeNode *u) {
            TreeNode* min_node = minimum(u);
            return min_node->data;
        }

        TreeNode* maximum(TreeNode *node) { // Find minimum node of a subtree
            while (node != nullptr) {
                node = node->right;
            }
            return node;
        }

        T max_value(TreeNode *u) {
            TreeNode* max_node = maximum(u);
            return max_node->data;
        }

        void insert(T val) { // Runs in O(log(n)) time
            TreeNode *z = new TreeNode{val, nullptr, nullptr, 1}; // All new nodes are red

            TreeNode *x = root;
            TreeNode *y = nullptr;

            while (x != nullptr) { // Find proper location to insert data
                y = x;
                if (z->data < x->data) {
                    x = x->left;
                }

                else {
                    x = x->right;
                }
            }

            z->parent = y;
            
            if (y == nullptr) { // If tree is empty
                root = z; 
            }

            else if (z->data < y->data) {
                y->left = z;
            }

            else {
                y->right = z;
            }

            // No need to fix if new node is root
            if (z == root) {
                z->color = 0; // Make sure root node is black
                return;
            }

            // No need to fix if there is no grandparent
            if (node->parent->parent == nullptr) {
                return;
            }

            // Corect red-red violations
            fixInsert(z);
        }

        void delete(T val) { // Runs in O(log(n)) time
            TreeNode *x = nullptr;
            TreeNode *y = nullptr;
            TreeNode *z = root;

            while (z != nullptr) { // Find node to delete

                if (val < z->data) {
                    z = z->left;
                }

                else if (val == z->data) {
                    break;
                }
                else {
                    z = z->right;
                }
            }

            if (!z) {
                std::cout << "Value is not in tree" << std::endl;
                return;
            }

            y = z;
            int y_original_color = y->color;

            if (z->left == nullptr) {
                x = z->right;
                transplant(z, z->right); // Replace z w/ it's right child
            }
            else if (z->right == nullptr) {
                x = z->left;
                transplant(z, z->left);
            }
            else {
                y = minimum(z->right);
                y_original_color = y->color;
                x = y->right;
                if (y != z->right) {
                    transplant(y, y->right);
                    y->right = z->right;
                    r->right->parent = y;
                }
                else {
                    x->parent = y;
                }
                transplant(z, y);
                y->left = z->left;
                y->left->parent = y;
                y->color = z->color;
            }
            delete z;
            if (y_original_color == 0) {
                fixDelete(x);
            }
        }
};