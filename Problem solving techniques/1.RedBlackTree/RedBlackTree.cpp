#include <iostream>
#include <fstream>
using namespace std;

ifstream inp("rbt.inp");
ofstream out("rbt.out");

struct Node
{
    int key;
    Node *parent;
    Node *left;
    Node *right;
    // 1 -> Red, 0 -> Black
    int color;
};

class RBTree
{
    Node *root;
    Node *leaf;

public:
    RBTree()
    {
        leaf = new Node;
        leaf->color = 0;
        leaf->left = nullptr;
        leaf->right = nullptr;
        root = leaf;
    }
    void rbInsert(int key)
    {
        Node *insertNode = new Node;
        insertNode->parent = nullptr;
        insertNode->key = key;
        insertNode->left = leaf;
        insertNode->right = leaf;
        insertNode->color = 1;

        Node *p = nullptr;
        Node *find_position = this->root;

        while (find_position != leaf)
        {
            p = find_position;
            if (insertNode->key < find_position->key)
            {
                find_position = find_position->left;
            }
            else
            {
                find_position = find_position->right;
            }
        }

        insertNode->parent = p;
        if (p == nullptr)
        {
            root = insertNode;
        }
        else if (insertNode->key < p->key)
        {
            p->left = insertNode;
        }
        else
        {
            p->right = insertNode;
        }

        if (insertNode->parent == nullptr)
        {
            insertNode->color = 0;
            return;
        }

        if (insertNode->parent->parent == nullptr)
        {
            return;
        }

        rbInsertFixup(insertNode);
    }

    void rbDelete(int key)
    {
        Node *z = findNode(key);
        Node *x, *y;

        y = z;
        int yColor = y->color;
        if (z->left == leaf)
        {
            x = z->right;
            rbTransplant(z, z->right);
        }
        else if (z->right == leaf)
        {
            x = z->left;
            rbTransplant(z, z->left);
        }
        else
        {
            y = TreeSuccessor(z->right);
            yColor = y->color;
            x = y->right;
            if (y->parent == z)
            {
                x->parent = y;
            }
            else
            {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (yColor == 0)
        {
            rbDeleteFixup(x);
        }
    }

    void rbColor(int key)
    {
        Node *x = findNode(key);
        if (x->color == 1)
        {
            out << "color(" << key << ")"
                << " : "
                << "RED" << endl;
        }
        else
        {
            out << "color(" << key << ")"
                << " : "
                << "BLACK" << endl;
        }
    }

private:
    Node *findNode(int key)
    {
        Node *x = this->root;

        while (x->key != key)
        {
            if (x->key > key)
            {
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }

        return x;
    }

    Node *TreeSuccessor(Node *x)
    {
        while (x->left != leaf)
        {
            x = x->left;
        }
        return x;
    }

    void leftRotate(Node *x)
    {
        Node *y = x->right;
        x->right = y->left;
        if (y->left != leaf)
        {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr)
        {
            this->root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node *x)
    {
        Node *y = x->left;
        x->left = y->right;
        if (y->right != leaf)
        {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr)
        {
            this->root = y;
        }
        else if (x == x->parent->right)
        {
            x->parent->right = y;
        }
        else
        {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    void rbTransplant(Node *u, Node *v)
    {
        if (u->parent == nullptr)
        {
            root = v;
        }
        else if (u == u->parent->left)
        {
            u->parent->left = v;
        }
        else
        {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    void rbInsertFixup(Node *x)
    {
        while (x != this->root && x->parent->color == 1)
        {
            Node *grandparent = x->parent->parent;
            if (x->parent == grandparent->right)
            {
                Node *uncle = grandparent->left;
                // case1
                if (uncle->color == 1)
                {
                    uncle->color = 0;
                    x->parent->color = 0;
                    grandparent->color = 1;
                    x = grandparent;
                }
                else
                {
                    // case2
                    if (x == x->parent->left)
                    {
                        x = x->parent;
                        rightRotate(x);
                    }
                    // case3
                    x->parent->color = 0;
                    grandparent->color = 1;
                    leftRotate(grandparent);
                }
            }
            else
            {
                Node *uncle = grandparent->right;
                // case1
                if (uncle->color == 1)
                {
                    uncle->color = 0;
                    x->parent->color = 0;
                    grandparent->color = 1;
                    x = grandparent;
                }
                else
                {
                    // case2
                    if (x == x->parent->right)
                    {
                        x = x->parent;
                        leftRotate(x);
                    }
                    // case3
                    x->parent->color = 0;
                    grandparent->color = 1;
                    rightRotate(grandparent);
                }
            }
        }
        root->color = 0;
    }

    void rbDeleteFixup(Node *x)
    {
        while (x != root && x->color == 0)
        {
            if (x == x->parent->left)
            {
                Node *w = x->parent->right;

                // case1
                if (w->color == 1)
                {
                    w->color = 0;
                    x->parent->color = 1;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }

                // case2
                if (w->left->color == 0 && w->right->color == 0)
                {
                    w->color = 1;
                    x = x->parent;
                }
                else
                {
                    // case3
                    if (w->right->color == 0)
                    {
                        w->left->color = 0;
                        w->color = 1;
                        rightRotate(w);
                        w = x->parent->right;
                    }

                    // case4
                    w->color = x->parent->color;
                    x->parent->color = 0;
                    w->right->color = 0;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else
            {
                Node *w = x->parent->left;

                // case1
                if (w->color == 1)
                {
                    w->color = 0;
                    x->parent->color = 1;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }

                // case2
                if (w->right->color == 0 && w->right->color == 0)
                {
                    w->color = 1;
                    x = x->parent;
                }
                else
                {
                    // case3
                    if (w->left->color == 0)
                    {
                        w->right->color = 0;
                        w->color = 1;
                        leftRotate(w);
                        w = x->parent->left;
                    }

                    // case4
                    w->color = x->parent->color;
                    x->parent->color = 0;
                    w->left->color = 0;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = 0;
    }
};

int main(void)
{
    char mode;
    int key;
    RBTree rt;

    while (1)
    {
        inp >> mode >> key;
        if (key == -1)
            break;

        switch (mode)
        {
        case 'i': // insert
            rt.rbInsert(key);
            break;
        case 'd': // delete
            rt.rbDelete(key);
            break;

        case 'c': // color
            rt.rbColor(key);
            break;
        }
    }