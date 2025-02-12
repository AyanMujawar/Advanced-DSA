#include <iostream>
#include <queue>
using namespace std;

class Node
{
public:
    Node* left;
    Node* right;
    string key;
    string value;

    Node(string k, string v)
    {
        key = k;
        value = v;
        left = nullptr;
        right = nullptr;
    }
};

class tree
{
    Node* root;

public:
    tree()
    {
        root = nullptr;
    }

    Node* insert(Node* root, string k, string value)
    {
        if (root == nullptr)
        {
            return new Node(k, value); // Create and return a new node
        }

        if (k < root->key) // Compare with key, not value
        {
            root->left = insert(root->left, k, value);
        }
        else
        {
            root->right = insert(root->right, k, value);
        }

        return root; // Return root of the modified subtree
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
    
Node* search(Node* root, string key)
{
    while (root != nullptr) {
        // If key matches the root node, return it
        if (root->key == key) {
            return root;
        }
        // Move left or right based on key comparison
        if (key < root->key) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    // Return nullptr if the key was not found
    return nullptr;
}

 
    void inorder(Node* root)
    {
        if (root != nullptr)
        {
            inorder(root->left);
            cout << root->key << ": " << root->value << endl;
            inorder(root->right);
        }
    }
    void preorder(Node* root)
    {
        if (root != nullptr)
        {
            cout << root->key << ": " << root->value << endl; // Visit the root node first
            preorder(root->left);  // Traverse the left subtree
            preorder(root->right); // Traverse the right subtree
        }
    }

    void postorder(Node* root)
    {
        if (root != nullptr)
        {
            postorder(root->left);  // Traverse the left subtree
            postorder(root->right); // Traverse the right subtree
            cout << root->key << ": " << root->value << endl; // Visit the root node last
        }
    }
    void levelOrderTraversal(Node* root) {
    if (!root) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();
        cout << curr->data << " ";
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
}


    // Utility function to initiate insertion and inorder traversal
    void insert(string key, string value)
    {
        root = insert(root, key, value);
    }

    void deleteNode(string key)
    {
        root = deleteNode(root, key);
    }

    void displayInorder()
    {
        inorder(root);
    }
    
    
   void copytree(Node* root, tree& copyTree)
    {
        if (root == nullptr) return;
        copyTree.insert(root->key, root->value);
        copytree(root->left, copyTree);
        copytree(root->right, copyTree);
    }

    // Utility function to initiate copying
    void copytree(tree& copyTree)
    {
        copytree(root, copyTree);
    }
};

int main()
{
    
}
