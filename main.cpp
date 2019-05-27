#include <iostream>
using namespace std;

struct node {
    int key;
    char color;

    node *parent;
    node *left;
    node *right;
};

class RBTree {
public:
    node *root;

    RBTree() {root = NULL;}

    void add() {
        int data = 0;
        cout << "\n Введите значение: ";
        cin >> data;
        node *r, *q;
        node *tmp = new node;
        tmp->key = data;
        tmp->left = NULL;
        tmp->right = NULL;
        tmp->color = 'r';
        r = root;
        q = NULL;
        if (root == NULL) {
            root = tmp;
            tmp->parent = NULL;
        }
        else {
            while (r != NULL) {
                q = r;
                if (r->key < tmp->key)
                    r = r->right;
                else
                    r = r->left;
            }
            tmp->parent = q;
            if (q->key < tmp->key)
                q->right = tmp;
            else
                q->left = tmp;
        }
        fix(tmp);
    }

    void fix(node *tmp) {
        node *u;
        if (root == tmp) {
            tmp->color = 'b';
            return;
        }
        while (tmp->parent != NULL && tmp->parent->color == 'r') {
            node *g = tmp->parent->parent;
            if (g->left == tmp->parent) {
                if(g->right != NULL) {
                    u = g->right;
                    if (u->color == 'r') {
                        tmp->parent->color = 'b';
                        u->color = 'b';
                        g->color = 'r';
                        tmp = g;
                    }
                }
                else {
                    if (tmp->parent->right == tmp) {
                        tmp = tmp->parent;
                        left(tmp);
                    }
                    tmp->parent->color = 'b';
                    g->color = 'r';
                    right(g);
                }
            }
            else {
                if(g->left != NULL) {
                    u = g->left;
                    if (u->color == 'r') {
                        tmp->parent->color = 'b';
                        u->color = 'b';
                        g->color = 'r';
                        tmp = g;
                    }
                }
                else {
                    if (tmp->parent->left == tmp) {
                        tmp = tmp->parent;
                        right(tmp);
                    }
                    tmp->parent->color = 'b';
                    g->color = 'r';
                    left(g);
                }
            }
            root->color = 'b';
        }
    }

    void left(node *tmp) {
        if (tmp->right == NULL)
            return;
        else {
            node *y = tmp->right;
            if (y->left != NULL) {
                tmp->right = y->left;
                y->left->parent = tmp;
            }
            else
                tmp->right = NULL;
            if (tmp->parent!= NULL)
                y->parent = tmp->parent;
            if (tmp->parent==NULL)
                root=y;
            else {
                if (tmp == tmp->parent->left)
                    tmp->parent->left = y;
                else
                    tmp->parent->right = y;
            }
            y->left = tmp;
            tmp->parent = y;
        }
    }

    void right(node *tmp) {
        if (tmp->left == NULL)
            return;
        else {
            node *y = tmp->left;
            if (y->right!= NULL) {
                tmp->left = y->right;
                y->right->parent = tmp;
            }
            else
                tmp->left = NULL;
            if (tmp->parent != NULL)
                y->parent = tmp->parent;
            if (tmp->parent == NULL)
                root=y;
            else {
                if (tmp == tmp->parent->left)
                    tmp->parent->left = y;
                else
                    tmp->parent->right = y;
            }
            y->right = tmp;
            tmp->parent = y;
        }
    }

    void disp() {
        display(root);
    }

    void display(node *tmp) {
        if (root == NULL) {
            cout << "\n Дерево отсутствует";
            return;
        }
        if (tmp != NULL) {
            cout << "\n\t УЗЕЛ: ";
            cout << "\n Значение: " << tmp->key;
            cout << "\n Цвет: ";
            if (tmp->color == 'b')
                cout << "Чёрный";
            else
                cout << "Красный";
            if (tmp->parent != NULL)
                cout << "\n Родитель: " << tmp->parent->key;
            else
                cout << "\n Родитель остутствует ";
            if (tmp->right != NULL)
                cout << "\n Правый потомок: " << tmp->right->key;
            else
                cout << "\n Правый потомок отсутствует ";
            if (tmp->left != NULL)
                cout << "\n Левый потомок: " << tmp->left->key;
            else
                cout << "\n Левый потомок отсутствует  ";
            cout << endl;
            if (tmp->left) {
                cout << "\n\n Левый:\n";
                display(tmp->left);
            }
            if (tmp->right) {
                cout << "\n\n Правый:\n";
                display(tmp->right);
            }
        }
    }
};

int main() {
    int count1, count2 = 0;
    RBTree tree;

    do {
        cout << "\t КРАСНО-ЧЁРНОЕ ДЕРЕВО " ;
        cout << "\n 1. Вставка элемента ";
        cout << "\n 2. Отобразить дерево";
        cout << "\n 3. Выход " ;
        cout << "\n Выберете действие: ";
        cin >> count1;
        switch(count1) {
            case 1 : tree.add();
                cout << "\n Элемент добавлен \n";
                break;
            case 2 : tree.disp();
                break;
            case 3 : count2 = 1;
                break;
            default : cout << "\n Выберете действие из списка";
        }
        cout << endl;
        }while (count2 != 1);
    return 1;
}