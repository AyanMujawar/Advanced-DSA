#include<iostream>
using namespace std;

class node
{
    node*left;
    node*right;
    string key;
    string  value;
    node(string  k , string v )
    {
        key= k ;
        value = v;
        left= nullptr;
        right = nullptr;
        
    }
    
}

class tree 
{
    node * root;
    public:

    tree()
    {
        root = nullptr;
    }
    node insert(node * root , string key, string value)
    {
        if (root == nullptr) {
            return new Node(key);
        }

        
        if (key < root->value) {
            root->left = insert(root->left, key ,value );  
        } else {
            root->right = insert(root->right, key , value );  

       
        return root;
    }


    }

  Node* deleteNode(Node* root, string key) {
        Node* parent = nullptr;
        Node* current = root;

        // Find the node to delete and keep track of its parent
        while (current != nullptr && current->key != key) {
            parent = current;
            if (key < current->key) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        if (current == nullptr) {
            cout << "Node with key " << key << " not found!" << endl;
            return root;  // Node not found, return the root unchanged
        }

        // Case 1: Node has no children (leaf node)
        if (current->left == nullptr && current->right == nullptr) {
            if (parent == nullptr) {
                // If root is the node to be deleted
                delete current;
                return nullptr;
            } else if (parent->left == current) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
            delete current;
        }
        // Case 2: Node has one child
        else if (current->left == nullptr || current->right == nullptr) {
           // If the node has one child, replace it with its only child
            if (current->left == nullptr) {
                // If there's no left child, the right child replaces it
                if (parent == nullptr) {
                    // If the node to be deleted is the root
                    root = current->right;
                } else if (parent->left == current) {
                    parent->left = current->right;
                } else {
                    parent->right = current->right;
                }
            } else if (current->right == nullptr) {
                // If there's no right child, the left child replaces it
                if (parent == nullptr) {
                    // If the node to be deleted is the root
                    root = current->left;
                } else if (parent->left == current) {
                    parent->left = current->left;
                } else {
                    parent->right = current->left;
                }
            }

    }

    void inorder(Node* root) {
        if (root != nullptr) {
            inorder(root->left);
            cout << root->key << ": " << root->value << endl;
            inorder(root->right);
        }
    }
}
