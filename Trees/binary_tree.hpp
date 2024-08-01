#include <vector>
#include <queue>
#include <algorithm>


template <typename T>
class BinaryTree {

    private:
        struct TreeNode {
            T data;
            TreeNode *left;
            TreeNode *right;

            ~TreeNode() {
                delete left;
                delete right;
            }
        };

        TreeNode *root;

    public:
        BinaryTree()
            : root{nullptr}
        {
        }

        BinaryTree(std::vector<T> &i) 
        {
            int size = i.size();

            if (size == 0) {
                root = nullptr;
            }

            else {
                root = new TreeNode{i[0], nullptr, nullptr};

                if (size != 1) {
                    std::queue<TreeNode*> addresses;
                    addresses.push(root);
    
                    int counter = 1;
                    while (!addresses.empty() && counter < size) {
                        TreeNode *temp = addresses.front();
                        addresses.pop();
                        if (i[counter] != -1) {
                            temp->left = new TreeNode{i[counter], nullptr, nullptr};
                            addresses.push(temp->left);
                        }
                        ++counter;

                        if (i[counter] != -1) {
                            temp->right = new TreeNode{i[counter], nullptr, nullptr};
                            addresses.push(temp->right);
                        }
                        ++counter;
                    }
                }
            }
        }

        ~BinaryTree() {
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
};