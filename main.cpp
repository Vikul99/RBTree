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

    RBTree() { root = NULL; }
    void add();
    void add_fix(node *tmp);
    void left(node *tmp);
    void right(node *tmp);
    void del();
    void del_fix(node *tmp);
    node* successor(node *tmp);
    void search();
    void disp();
    void display(node *tmp);
    void destroy(node *tmp);
    ~RBTree();
};

void RBTree:: add() {
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
    add_fix(tmp);
}

void RBTree:: add_fix(node *tmp) {
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

void RBTree:: left(node *tmp) {
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

void RBTree:: right(node *tmp) {
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

void RBTree:: del() {
    if(root==NULL) {
        cout << "\n Дерево отсутствует";
        return;
    }
    int x;
    cout << "\n Введите элемент для удаления: "; cin >> x;
    node *p;
    p = root;
    node *y = NULL;
    node *q = NULL;
    int found=0;
    while (p != NULL && found == 0) {
        if (p->key == x)
            found=1;
        if(found == 0) {
            if (p->key < x)
                p = p->right;
            else
                p=p->left;
        }
    }
    if(found==0) {
        cout<< "\n Элемент не найден ";
        return;
    }
    else {
        cout << "\n Удаленный элемент: " << p->key;
        cout<< "\n Цвет: ";
        if(p->color == 'b')
            cout << "Чёрный";
        else
            cout << "Красный";
        if(p->parent != NULL)
            cout << "\n Родитель: "<< p->parent->key;
        else
            cout << "\n Родитель остутствует";
        if(p->right!= NULL)
            cout << "\n Правый потомок: " << p->right->key;
        else
            cout << "\n Правый потомок отсутствует";
        if(p->left!=NULL)
            cout << "\n Левый потомок: " << p->left->key;
        else
            cout << "\n Левый потомок отсутствует";
        cout << "\n Узел удален";
        if(p->left == NULL || p->right == NULL)
            y = p;
        else
            y = successor(p);
        if(y->left != NULL)
            q = y->left;
        else {
            if(y->right != NULL)
                q = y->right;
            else
                q = NULL;
        }
        if(q != NULL)
            q->parent = y->parent;
        if(y->parent == NULL)
            root = q;
        else {
            if(y == y->parent->left)
                y->parent->left = q;
            else
                y->parent->right = q;
        }
        if(y!=p) {
            p->color = y->color;
            p->key = y->key;
        }
        if(y->color == 'b')
            del_fix(q);
    }
}

void RBTree:: del_fix(node *tmp) {
    node *s;
    while (tmp != root && tmp->color == 'b') {
        if (tmp->parent->left == tmp) {
            s = tmp->parent->right;
            if (s->color == 'r') {
                s->color = 'b';
                tmp->parent->color = 'r';
                left(tmp->parent);
                s = tmp->parent->right;
            }
            if (s->right->color == 'b' && s->left->color == 'b') {
                s->color = 'r';
                tmp = tmp->parent;
            }
            else {
                if (s->right->color == 'b') {
                    s->left->color = 'b';
                    s->color = 'r';
                    right(s);
                    s = tmp->parent->right;
                }
                s->color = tmp->parent->color;
                tmp->parent->color = 'b';
                s->right->color = 'b';
                left(tmp->parent);
                tmp = root;
            }
        }
        else {
            s = tmp->parent->left;
            if (s->color == 'r') {
                s->color = 'b';
                tmp->parent->color = 'r';
                right(tmp->parent);
                s = tmp->parent->left;
            }
            if (s->left->color == 'b' && s->right->color == 'b') {
                s->color = 'r';
                tmp = tmp->parent;
            }
            else {
                if(s->left->color == 'b') {
                    s->right->color = 'b';
                    s->color = 'r';
                    left(s);
                    s = tmp->parent->left;
                }
                s->color = tmp->parent->color;
                tmp->parent->color = 'b';
                s->left->color = 'b';
                right(tmp->parent);
                tmp = root;
            }
        }
        tmp->color = 'b';
        root->color = 'b';
    }
}

node* RBTree:: successor(node *tmp) {
    node *y = NULL;
    if (tmp->left != NULL) {
        y = tmp->left;
        while (y->right != NULL)
            y = y->right;
    }
    else {
        y = tmp->right;
        while (y->left != NULL)
            y = y->left;
    }
    return y;
}

void RBTree:: search() {
    if(root==NULL) {
        cout << "\n Дерево отсутствует";
        return;
    }
    int x;
    cout << "\n Введите значение для поиска: "; cin >> x;
    node *p = root;
    int found = 0;
    while (p != NULL && found==0) {
        if (p->key == x)
            found=1;
        if (found==0) {
            if(p->key < x)
                p = p->right;
            else
                p = p->left;
        }
    }
    if(found == 0)
        cout << "\n Элемент не найден";
    else {
        cout << "\n\t Найденный узел: ";
        cout << "\n Значение: "<< p->key;
        cout << "\n Цвет: ";
        if (p->color == 'b')
            cout << "Чёрный";
        else
            cout << "Красный";
        if(p->parent != NULL)
            cout << "\n Родитель: "<< p->parent->key;
        else
            cout << "\n Родитель остутствует";
        if(p->right != NULL)
            cout << "\n Правый потомок: " << p->right->key;
        else
            cout << "\n Правый потомок отсутствует";
        if(p->left != NULL)
            cout << "\n Левый потомок: " << p->left->key;
        else
            cout << "\n Левый потомок отсутствует";
        cout << endl;
    }
}


void RBTree:: disp() {
    display(root);
}

void RBTree:: display(node *tmp) {
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
            cout << "\n Родитель остутствует";
        if (tmp->right != NULL)
            cout << "\n Правый потомок: " << tmp->right->key;
        else
            cout << "\n Правый потомок отсутствует";
        if (tmp->left != NULL)
            cout << "\n Левый потомок: " << tmp->left->key;
        else
            cout << "\n Левый потомок отсутствует";
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

void RBTree:: destroy(node *tmp) {
    if (tmp != NULL) {
        node *r = tmp->right;
        node *l = tmp->left;
        destroy(r);
        destroy(l);
        delete tmp;
        tmp = NULL;
    }
}

RBTree::~RBTree() {
    if (root != NULL)
        destroy(root);
}

int main() {
    int count1, count2 = 0;
    RBTree tree;

    do {
        cout << "\t КРАСНО-ЧЁРНОЕ ДЕРЕВО " ;
        cout << "\n 1. Вставка элемента ";
        cout << "\n 2. Отобразить дерево";
        cout << "\n 3. Удаление элемента " ;
        cout << "\n 4. Поиск элемента " ;
        cout << "\n 5. Выход " ;
        cout << "\n Выберете действие: ";
        cin >> count1;
        switch(count1) {
            case 1: tree.add();
                cout << "\n Элемент добавлен \n";
                break;
            case 2: tree.disp();
                break;
            case 3: tree.del();
            case 4: tree.search();
            case 5: count2 = 1;
                break;
            default: cout << "\n Выберете действие из списка";
        }
        cout << endl;
        }while (count2 != 1);
    return 1;
}