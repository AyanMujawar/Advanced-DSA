#include <iostream>
#include <queue>
#define MAX 3
#define MIN 2
using namespace std;

class BTreeNode {
public:
    int keys[MAX];
    BTreeNode* children[MAX + 1];
    int count;
    bool isLeaf;

    BTreeNode(bool leaf) {
        isLeaf = leaf;
        count = 0;
        for (int i = 0; i <= MAX; i++)
            children[i] = nullptr;
    }
};

class BTree {
    BTreeNode* root;

    void levelOrderTraversal(BTreeNode* root);
    void insertNonFull(BTreeNode* node, int key);
    void splitChild(BTreeNode* node, int i, BTreeNode* child);
    void remove(BTreeNode* node, int key);
    int getPredecessor(BTreeNode* node);
    int getSuccessor(BTreeNode* node);
    void merge(BTreeNode* node, int idx);
    void borrowFromPrev(BTreeNode* node, int idx);
    void borrowFromNext(BTreeNode* node, int idx);
    void fill(BTreeNode* node, int idx);
    int findKey(BTreeNode* node, int key);

public:
    BTree() { root = nullptr; }
    void insert(int key);
    void display() { levelOrderTraversal(root); }
    void deleteKey(int key);
};

// Level Order Traversal using Queue
void BTree::levelOrderTraversal(BTreeNode* root) {
    if (!root) return;
    queue<BTreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int size = q.size();
        while (size--) {
            BTreeNode* node = q.front();
            q.pop();
            cout << "[";
            for (int i = 0; i < node->count; i++) {
                cout << node->keys[i];
                if (i != node->count - 1)
                    cout << ", ";
            }
            cout << "] ";
            if (!node->isLeaf) {
                for (int i = 0; i <= node->count; i++)
                    if (node->children[i]) q.push(node->children[i]);
            }
        }
        cout << endl;
    }
}

void BTree::insert(int key) {
    if (!root) {
        root = new BTreeNode(true);
        root->keys[0] = key;
        root->count = 1;
    } else {
        if (root->count == MAX) {
            BTreeNode* s = new BTreeNode(false);
            s->children[0] = root;
            splitChild(s, 0, root);
            int i = (s->keys[0] < key) ? 1 : 0;
            insertNonFull(s->children[i], key);
            root = s;
        } else {
            insertNonFull(root, key);
        }
    }
}

void BTree::insertNonFull(BTreeNode* node, int key) {
    int i = node->count - 1;
    if (node->isLeaf) {
        while (i >= 0 && node->keys[i] > key) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->count++;
    } else {
        while (i >= 0 && node->keys[i] > key) i--;
        if (node->children[i + 1]->count == MAX) {
            splitChild(node, i + 1, node->children[i + 1]);
            if (node->keys[i + 1] < key) i++;
        }
        insertNonFull(node->children[i + 1], key);
    }
}

void BTree::splitChild(BTreeNode* parent, int i, BTreeNode* child) {
    BTreeNode* newChild = new BTreeNode(child->isLeaf);
    newChild->count = MIN - 1;
    for (int j = 0; j < MIN - 1; j++)
        newChild->keys[j] = child->keys[j + MIN];
    if (!child->isLeaf)
        for (int j = 0; j < MIN; j++)
            newChild->children[j] = child->children[j + MIN];
    child->count = MIN - 1;
    for (int j = parent->count; j > i; j--)
        parent->children[j + 1] = parent->children[j];
    parent->children[i + 1] = newChild;
    for (int j = parent->count - 1; j >= i; j--)
        parent->keys[j + 1] = parent->keys[j];
    parent->keys[i] = child->keys[MIN - 1];
    parent->count++;
}

void BTree::deleteKey(int key) {
    if (!root) return;
    remove(root, key);
    if (root->count == 0) {
        BTreeNode* temp = root;
        root = root->isLeaf ? nullptr : root->children[0];
        delete temp;
    }
}

int BTree::findKey(BTreeNode* node, int key) {
    int idx = 0;
    while (idx < node->count && node->keys[idx] < key)
        ++idx;
    return idx;
}

void BTree::remove(BTreeNode* node, int key) {
    int idx = findKey(node, key);
    if (idx < node->count && node->keys[idx] == key) {
        if (node->isLeaf) {
            for (int i = idx + 1; i < node->count; ++i)
                node->keys[i - 1] = node->keys[i];
            node->count--;
        } else {
            if (node->children[idx]->count >= MIN) {
                int pred = getPredecessor(node->children[idx]);
                node->keys[idx] = pred;
                remove(node->children[idx], pred);
            } else if (node->children[idx + 1]->count >= MIN) {
                int succ = getSuccessor(node->children[idx + 1]);
                node->keys[idx] = succ;
                remove(node->children[idx + 1], succ);
            } else {
                merge(node, idx);
                remove(node->children[idx], key);
            }
        }
    } else {
        if (node->isLeaf) return;
        bool flag = (idx == node->count);
        if (node->children[idx]->count < MIN)
            fill(node, idx);
        if (flag && idx > node->count)
            remove(node->children[idx - 1], key);
        else
            remove(node->children[idx], key);
    }
}

int BTree::getPredecessor(BTreeNode* node) {
    while (!node->isLeaf)
        node = node->children[node->count];
    return node->keys[node->count - 1];
}

int BTree::getSuccessor(BTreeNode* node) {
    while (!node->isLeaf)
        node = node->children[0];
    return node->keys[0];
}

void BTree::merge(BTreeNode* node, int idx) {
    BTreeNode* child = node->children[idx];
    BTreeNode* sibling = node->children[idx + 1];
    child->keys[MIN - 1] = node->keys[idx];
    for (int i = 0; i < sibling->count; ++i)
        child->keys[i + MIN] = sibling->keys[i];
    if (!child->isLeaf) {
        for (int i = 0; i <= sibling->count; ++i)
            child->children[i + MIN] = sibling->children[i];
    }
    for (int i = idx + 1; i < node->count; ++i)
        node->keys[i - 1] = node->keys[i];
    for (int i = idx + 2; i <= node->count; ++i)
        node->children[i - 1] = node->children[i];
    child->count += sibling->count + 1;
    node->count--;
    delete sibling;
}

void BTree::borrowFromPrev(BTreeNode* node, int idx) {
    BTreeNode* child = node->children[idx];
    BTreeNode* sibling = node->children[idx - 1];
    for (int i = child->count - 1; i >= 0; --i)
        child->keys[i + 1] = child->keys[i];
    if (!child->isLeaf)
        for (int i = child->count; i >= 0; --i)
            child->children[i + 1] = child->children[i];
    child->keys[0] = node->keys[idx - 1];
    if (!child->isLeaf)
        child->children[0] = sibling->children[sibling->count];
    node->keys[idx - 1] = sibling->keys[sibling->count - 1];
    child->count += 1;
    sibling->count -= 1;
}

void BTree::borrowFromNext(BTreeNode* node, int idx) {
    BTreeNode* child = node->children[idx];
    BTreeNode* sibling = node->children[idx + 1];
    child->keys[child->count] = node->keys[idx];
    if (!child->isLeaf)
        child->children[child->count + 1] = sibling->children[0];
    node->keys[idx] = sibling->keys[0];
    for (int i = 1; i < sibling->count; ++i)
        sibling->keys[i - 1] = sibling->keys[i];
    if (!sibling->isLeaf) {
        for (int i = 1; i <= sibling->count; ++i)
            sibling->children[i - 1] = sibling->children[i];
    }
    child->count += 1;
    sibling->count -= 1;
}

void BTree::fill(BTreeNode* node, int idx) {
    if (idx != 0 && node->children[idx - 1]->count >= MIN)
        borrowFromPrev(node, idx);
    else if (idx != node->count && node->children[idx + 1]->count >= MIN)
        borrowFromNext(node, idx);
    else {
        if (idx != node->count)
            merge(node, idx);
        else
            merge(node, idx - 1);
    }
}

int main() {
    BTree bt;
    int choice, key;

    do {
        cout << "\n1. Insert\n2. Display\n3. Delete\n4. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter key to insert: ";
                cin >> key;
                bt.insert(key);
                break;
            case 2:
                cout << "Level order traversal:\n";
                bt.display();
                break;
            case 3:
                cout << "Enter key to delete: ";
                cin >> key;
                bt.deleteKey(key);
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}
