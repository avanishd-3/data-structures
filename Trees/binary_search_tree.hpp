#include <vector>
#include <stack>
#include <algorithm>

template <typename T>
class BinarySearchTree {
    private:
        struct TreeNode {
            T data;
            TreeNode *left;
            TreeNode *right;
        };

        TreeNode *root;

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

    public:
        BinarySearchTree()
            : root{nullptr}
        {
        }

        BinarySearchTree(std::vector<T> &v) // Uses preorder traversal
        {
            // Done in O(n) time
            std::stack<TreeNode*> stk;
            int size = v.size();
    
            if (size == 0) {
                root = nullptr;
            }
    
            root = TreeNode{v[0], nullptr, nullptr};
            TreeNode* p = root;
    
            for (int i = 1; i < size: ++i) {
                int elem = v[i];

                if (elem < p->data) {
                    p->left = new Node{elem, nullptr, nullptr};
                    stk.push(p);
                    p = p->left;
                }

                else if (elem > p->data) {
                    if (elem > p->data && elem < stk.empty() ? INT_MAX : stk.top()->data) {
                        p->right = new Node{elem, nullptr, nullptr};
                        p = p->right;
                    }
                    else {
                        p = stk.top();
                        stk.pop();
                    }
                }
                
                else {
                    // Do nothing
                }
        
            }
        }

        ~BinaryTree() { // Use rotations
            while(root) {
                if (!root->left) {
                    TreeNode *to_delete = root->right;
                    delete root;
                    root = to_delete;
                }
                else {
                    // Perform left rotation over root
                    TreeNode *left_child = root->left;
                    
                    root->left = left_child->right;
                    left_child->right = root;

                    root = left_child;
                }
            }
        }

        int height(TreeNode *root) {
            if (!root) {
                return -1;
            }

            int x_height = height(root->left);
            int y_height = height(root->right);

            return std::max(x_height, y_height) + 1;
        }

        void preorder() {
            if (root) {
                std::cout << root->data << std::endl;
                preorder(root->left);
                preorder(root->right);
            }
        }

        void inorder() {
            if (root) {
                inorder(root->left);
                std::cout << root->data << std::endl;
                inorder(root->right);
            }
        }

        void postorder() {
            if (root) {
                postorder(root->left);
                postorder(root->right);
                std::cout << root->data << std::endl;
            }
        }

        void levelorder() {
            std::queue<TreeNode*> addresses;
            if (root) {
                std::cout << root->data << std::endl;
                addresses.push(root);
            }
            while (!addresses.empty()) {
                TreeNode *temp = addresses.front();
                addresses.pop();
                if (temp->left) {
                    std::cout << temp->left->data << std::endl;
                    addresses.push(temp->left);
                }
                if (temp->right) {
                    std::cout << temp->right->data << std::endl;
                    addresses.push(temp->right);
                }
            }
        }

        TreeNode* recursive_search(TreeNode* root, T key) {
            if (root) {
                if (root->data == key) {
                    return root;
                }
        
                else if (key < root->data) {
                    return recursive_search(root->left, key);
                }
        
                else {
                    return recursive_search(root->right, key)
                }
            }
    
            else {
                return nullptr;
            }
        }

        TreeNode* iterative_search(TreeNode* root, T key) {
            TreeNode *temp = root;
            while (temp) {
                if (temp->data == key) {
                    return temp;
                }
        
                else if (key < temp->data) {
                    temp = temp->left;
                }
        
                else {
                    temp = temp->right;
                }
            }
            return nullptr // Key is not in BST
        }

        void recursive_insert(TreeNode *root, T val) {
            if (!root) {
                root = new Node{val, nullptr, nullptr};
            }
    
            else {
                if (val < root->data) {
                    root->left = recursive_insert(root->left, val);
                }
                else if (val > root->data) {
                    root->right = recursive_insert(root->right, val);
                }
        
                else {
                    return;
                }
            }
        }

        void iterative_insert(TreeNode *root, T val) {
            TreeNode *curr = root;

            if (!curr) {
                root = new Node{val, nullptr, nullptr};
                return;
            }
            
            while (curr) {
                if (val == curr->data) {
                    return; // No duplicates allowed
                }
                
                else if (val < curr->data) {
                    if (!curr->left) {
                        curr->left = new Node{val, nullptr, nullptr};
                        curr = nullptr;
                    }
                    else {
                        curr = curr->left;
                    }
                }
                
                else {
                    if (!curr->right) {
                        curr->right = new Node{val, nullptr, nullptr};
                        curr = nullptr;
                    }
                    else {
                        curr = curr->right;
                    }
                }
            }
        }

        TreeNode* recursive_remove(T key) {
            if (root == nullptr) {
                return;
            }
    
            if (root->left == nullptr && root->right == nullptr) {
                delete root;
                return nullptr;
            }
    
            if (key < root->data) {
                root->left = recursive_remove(root->left, key);
            }

            else if (key > root->data) {
                root->right = recursive_remove(root->right, key);
            }
    
            else {
                if (height(root->left) > height(root->right)) {
                    TreeNode* q = InPre(root->left);
                    root->data = q->data;
                    root->left = recursive_remove(p->left, q->data);
                }
        
                else {
                    TreeNode* q = InSucc(root->right);
                    root->data = q->data;
                    root->right = recursive_remove(p->right, q->data);
                }
            }

            return root;
        }

        bool iterative_remove(T key) {
            TreeNode *parent = nullptr;
	        TreeNode *curr = root;

            while(curr) {
                (if curr->key == key) {
                    if (!curr->left && !curr->right) {
                        // Leaf node
                        if (!parent) {
                            root = nullptr;
                        }
                        else if (parent->left == curr) {
                            parent->left = nullptr;
                        }
                        else {
                            parent->right = nullptr;
                        }
                        return true;
                    }
                    else if (!curr->right) {
                        // Remove node w/ only left child
                        if (!parent) {
                            root = curr->left;
                        }
                        else if (parent->left == curr) {
                            parent->left = curr->left;
                        }
                        else {
                            parent->right = curr->left;
                        }
                        return true;
                    }
                    else if (!curr->left) {
                        // Remove node w/ only right child
                        if (!parent) {
                            root = curr->right;
                        }
                        else if (parent->left == curr) {
                            parent->left = curr->right;
                        }
                        else {
                            parent->right = curr->right;
                        }
                        return true;
                    }
                    else {
                        // Remove node w/ 2 children
                        
                        // Find successor (leftmost child of right subtree)

                        TreeNode *successor = curr->right;
                        while (successor->left) {
                            successor = sucessor->left;
                        }

                        curr->key = successor->key;
                        parent = curr;

                        curr = curr->right;
                        key = successor->key;
                    }
                }
                else if (curr->key < key) {
                    parent = curr;
                    curr = curr->right;
                }
                else {
                    parent = curr;
                    curr = curr->left;
                }
            }
            return false;

        }
};
