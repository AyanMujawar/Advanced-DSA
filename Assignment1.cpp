#include <iostream>
#include <queue>
using namespace std;

class Node
{
public:
    Node *left;
    Node *right;
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
    Node *root;

public:
    tree()
    {
        root = nullptr;
    }

    Node *insert(Node *root, string k, string value)
    {
        if (root == nullptr)
        {
            return new Node(k, value); // Create and return a new node
        }

        if (k < root->key) // Compare with key, not value
        {
            root->left = insert(root->left, k, value);
        }
        else if (k > root->key)
        {
            root->right = insert(root->right, k, value);
        }
        else
        {
            root->value = value; // Update value if duplicate key found
        }

        return root; // Return root of the modified subtree
    }

    Node *getSuccessor(Node *node)
    {
        Node *current = node->right;
        while (current != nullptr && current->left != nullptr)
        {
            current = current->left;
        }
        return current;
    }

    Node *deleteNode(Node *root, string key)
    {
        if (root == nullptr)
        {
            cout << "Node with key " << key << " not found!" << endl;
            return root;
        }

        if (key < root->key)
        {
            root->left = deleteNode(root->left, key);
        }
        else if (key > root->key)
        {
            root->right = deleteNode(root->right, key);
        }
        else
        {
            // Case 1: Node has no children
            if (root->left == nullptr && root->right == nullptr)
            {
                delete root;
                return nullptr;
            }
            // Case 2: Node has one child
            else if (root->left == nullptr)
            {
                Node *temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr)
            {
                Node *temp = root->left;
                delete root;
                return temp;
            }
            // Case 3: Node has two children
            Node *successor = getSuccessor(root);
            root->key = successor->key;
            root->value = successor->value;
            root->right = deleteNode(root->right, successor->key);
        }

        return root;
    }

    Node *search(Node *root, string key)
    {
        while (root != nullptr)
        {
            // If key matches the root node, return it
            if (root->key == key)
            {
                return root;
            }
            // Move left or right based on key comparison
            if (key < root->key)
            {
                root = root->left;
            }
            else
            {
                root = root->right;
            }
        }
        // Return nullptr if the key was not found
        return nullptr;
    }

    void inorder(Node *root)
    {
        if (root != nullptr)
        {
            inorder(root->left);
            cout << root->key << ": " << root->value << endl;
            inorder(root->right);
        }
    }

    void preorder(Node *root)
    {
        if (root != nullptr)
        {
            cout << root->key << ": " << root->value << endl; // Visit the root node first
            preorder(root->left);                             // Traverse the left subtree
            preorder(root->right);                            // Traverse the right subtree
        }
    }

    void postorder(Node *root)
    {
        if (root != nullptr)
        {
            postorder(root->left);  // Traverse the left subtree
            postorder(root->right); // Traverse the right subtree
            cout << root->key << ": " << root->value << endl; // Visit the root node last
        }
    }

    void levelOrderTraversal(Node *root)
    {
        if (!root)
            return;
        queue<Node *> q;
        q.push(root);
        while (!q.empty())
        {
            Node *curr = q.front();
            q.pop();
            cout << curr->key << " : " << curr->value << endl;
            if (curr->left)
                q.push(curr->left);
            if (curr->right)
                q.push(curr->right);
        }
    }

    Node *mirror(Node *root)
    {
        if (root == nullptr)
            return nullptr;
        Node *mirrored = new Node(root->key, root->value);
        mirrored->left = mirror(root->right);
        mirrored->right = mirror(root->left);
        return mirrored;
    }

    void mirrorTree()
    {
        root = mirror(root);
    }

    void copytree(Node *root, tree &copyTree)
    {
        if (root == nullptr)
            return;
        copyTree.insert(root->key, root->value);
        copytree(root->left, copyTree);
        copytree(root->right, copyTree);
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

    void searchnode(string key)
    {
        Node *found = search(root, key);
        if (found)
        {
            cout << "Found node: " << found->key << " : " << found->value << endl;
        }
        else
        {
            cout << "Node with key " << key << " not found!" << endl;
        }
    }

    void displayInorder()
    {
        inorder(root);
    }

    void displayPreorder()
    {
        preorder(root);
    }

    void displayPostorder()
    {
        postorder(root);
    }

    void displayLevelOrder()
    {
        levelOrderTraversal(root);
    }

    void copytree(tree &copyTree)
    {
        copytree(root, copyTree);
    }
};

int main()
{
    tree t;
    tree copyTree;
    int choice;
    string key, value;

    do
    {
        cout << "\n--- Dictionary Menu ---\n";
        cout << "1. Insert Word\n";
        cout << "2. Delete Word\n";
        cout << "3. Search Word\n";
        cout << "4. Display Dictionary (Inorder)\n";
        cout << "5. Display Preorder\n";
        cout << "6. Display Postorder\n";
        cout << "7. Display Level Order\n";
        cout << "8. Create a Copy of Dictionary\n";
        cout << "9. Display Mirror Image\n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter key: ";
            cin >> key;
            cout << "Enter value: ";
            cin >> value;
            t.insert(key, value);
            cout << "Word inserted successfully!\n";
            break;

        case 2:
            cout << "Enter key to delete: ";
            cin >> key;
            t.deleteNode(key);
            cout << "Word deleted successfully!\n";
            break;

        case 3:
            cout << "Enter key to search: ";
            cin >> key;
            t.searchnode(key);
            break;

        case 4:
            cout << "\nDisplaying Dictionary (Inorder Traversal):\n";
            t.displayInorder();
            break;

        case 5:
            cout << "\nDisplaying Preorder Traversal:\n";
            t.displayPreorder();
            break;

        case 6:
            cout << "\nDisplaying Postorder Traversal:\n";
            t.displayPostorder();
            break;

        case 7:
            cout << "\nDisplaying Level Order Traversal:\n";
            t.displayLevelOrder();
            break;

        case 8:
            copyTree = tree(); // Reset copyTree
            t.copytree(copyTree);
            cout << "\nCopied dictionary (Inorder Traversal):\n";
            copyTree.displayInorder();
            break;

        case 9:
            t.mirrorTree();
            cout << "\nMirror Image of Dictionary (Inorder Traversal):\n";
            t.displayInorder();
            break;

        case 10:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 10);

    return 0;
}
