#include <iostream>
using namespace std;

struct Player {
    int player_id, score, height;
    Player *left, *right;
    Player(int id, int s) {
        player_id = id;
        score = s;
        height = 0;
        left = right = NULL;
    }
};

int getHeight(Player *node) {
    return node ? node->height : 0;
}

int getBalanceFactor(Player *node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

Player* rotateRight(Player *y) {
    Player *x = y->left;
    y->left = x->right;
    x->right = y;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

Player* rotateLeft(Player *x) {
    Player *y = x->right;
    x->right = y->left;
    y->left = x;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

Player* insert(Player *node, int id, int score) {
    if (!node) return new Player(id, score);
    if (id < node->player_id) node->left = insert(node->left, id, score);
    else if (id > node->player_id) node->right = insert(node->right, id, score);
    else return node;

    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    int balance = getBalanceFactor(node);

    if (balance > 1 && id < node->left->player_id) return rotateRight(node);
    if (balance < -1 && id > node->right->player_id) return rotateLeft(node);
    if (balance > 1 && id > node->left->player_id) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && id < node->right->player_id) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

Player* minValueNode(Player *node) {
    Player *current = node;
    while (current->left) current = current->left;
    return current;
}

Player* remove(Player *node, int id) {
    if (!node) return node;
    if (id < node->player_id) node->left = remove(node->left, id);
    else if (id > node->player_id) node->right = remove(node->right, id);
    else {
        if (!node->left || !node->right) {
            Player *temp = node->left ? node->left : node->right;
            delete node;
            return temp;
        }
        Player *temp = minValueNode(node->right);
        node->player_id = temp->player_id;
        node->score = temp->score;
        node->right = remove(node->right, temp->player_id);
    }

    if (!node) return node;
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    int balance = getBalanceFactor(node);

    if (balance > 1 && getBalanceFactor(node->left) >= 0) return rotateRight(node);
    if (balance > 1 && getBalanceFactor(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && getBalanceFactor(node->right) <= 0) return rotateLeft(node);
    if (balance < -1 && getBalanceFactor(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

void displayLeaderboard(Player *node) {
    if (!node) return;
    displayLeaderboard(node->right);
    cout << "Player ID: " << node->player_id << ", Score: " << node->score << endl;
    displayLeaderboard(node->left);
}

int main() {
    Player *root = NULL;
    int choice, id, score;

    while (true) {
        cout << "\n1. Register Player\n2. Display Leaderboard\n3. Remove Player\n4. Exit\nEnter choice: ";
        cin >> choice;
        if (choice == 1) {
            cout << "Enter Player ID and Score: ";
            cin >> id >> score;
            root = insert(root, id, score);
        } else if (choice == 2) {
            cout << "Leaderboard:\n";
            displayLeaderboard(root);
        } else if (choice == 3) {
            cout << "Enter Player ID to remove: ";
            cin >> id;
            root = remove(root, id);
        } else break;
    }
    return 0;
}
