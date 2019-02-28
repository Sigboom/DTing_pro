#include <stdio.h>
#include <stdlib.h>

typedef struct RBTNode {
    int key, color;
    struct RBTNode *lchild, *rchild;
} RBTNode;

enum color_t {
    RED, BLACK, DOUBLE_BLACK
} color_t;

RBTNode *NIL;

__attribute__((constructor)) void init_NIL() {
    NIL = (RBTNode *)malloc(sizeof(RBTNode));
    NIL->key = 0;
    NIL->color = BLACK;
    NIL->lchild = NIL->rchild = NIL;
    return ;
}

RBTNode *init(int key) {
    RBTNode *node = (RBTNode *)malloc(sizeof(RBTNode));
    node->key = key;
    node->color = RED;
    node->lchild = node->rchild = NIL;
    return node;
}

int has_red_child(RBTNode *node) {
    return node->lchild->color == RED || node->rchild->color == RED;
}

RBTNode *left_rotate(RBTNode *node) {
    RBTNode *temp = node->rchild;
    node->rchild = temp->lchild;
    temp->lchild = node;
    return temp;
}

RBTNode *right_rotate(RBTNode *node) {
    RBTNode *temp = node->lchild;
    node->lchild = temp->rchild;
    temp->rchild = node;
    return temp;
}

RBTNode *insert_maintain(RBTNode *root) {
    if (!has_red_child(root)) return root;
    if (root->lchild->color == RED && root->rchild->color == RED) {
        if (has_red_child(root->lchild) || has_red_child(root->rchild)) {
            root->color = RED;
            root->lchild->color = root->rchild->color = BLACK;
        }
        return root;
    }
    if (root->lchild->color == RED) {
        if (!has_red_child(root->lchild)) return root;
        if (root->lchild->rchild->color == RED) {
            root->lchild = left_rotate(root->lchild);
        }
        root = right_rotate(root);
    } else {
        if (!has_red_child(root->rchild)) return root;
        if (root->rchild->lchild->color == RED) {
            root->rchild = right_rotate(root->rchild);
        }
        root = left_rotate(root);
    }
    root->color = RED;
    root->lchild->color = root->rchild->color = BLACK;
    return root;
}

RBTNode *__insert(RBTNode *root, int val) {
    if (root == NULL || root == NIL) return init(val);
    if (root->key == val) return root;
    if (root->key > val) root->lchild = __insert(root->lchild, val);
    else root->rchild = __insert(root->rchild, val);
    return insert_maintain(root);
}

RBTNode *insert(RBTNode *root, int val) {
    root = __insert(root, val);
    root->color = BLACK;
    return root;
}

RBTNode *predecessor(RBTNode *root) {
    RBTNode *temp = root->lchild;
    while (temp->rchild != NIL) temp = temp->rchild;
    return temp;
}

RBTNode *erase_maintain(RBTNode *root) {
    if (root->lchild->color != DOUBLE_BLACK && root->rchild->color != DOUBLE_BLACK) return root;
    #define UNBALANCE(a, b) (root->a->color == DOUBLE_BLACK && root->b->color == BLACK && !has_red_child(root->b))
    if (UNBALANCE(lchild, rchild) || UNBALANCE(rchild, lchild)) {
        root->color += 1;
        root->lchild->color -= 1;
        root->rchild->color -= 1;
        return root;
    }
    #undef UNBALANCE
    if (root->lchild->color == DOUBLE_BLACK) {
        if (root->rchild->color == RED) {
            root = left_rotate(root);
            root->color = BLACK;
            root->lchild->color = RED;
            root->lchild = erase_maintain(root->lchild);
            return root;
        }
        root->lchild->color = BLACK;
        if (root->rchild->rchild->color != RED) {
            root->rchild = right_rotate(root->rchild);
            root->rchild->color = BLACK;
            root->rchild->rchild->color = RED;
        }
        root = left_rotate(root);
        root->color = root->lchild->color;
    } else {
        if (root->lchild->color == RED) {
            root = right_rotate(root);
            root->color = BLACK;
            root->rchild->color = RED;
            root->rchild = erase_maintain(root->rchild);
            return root;
        }
        root->rchild->color = BLACK;
        if (root->lchild->lchild->color != RED) {
            root->lchild = left_rotate(root->lchild);
            root->lchild->color = BLACK;
            root->lchild->lchild->color = RED;
        }
        root = right_rotate(root);
        root->color = root->rchild->color;
    }
    root->lchild->color = root->rchild->color = BLACK;
    return root;
}

RBTNode *__erase(RBTNode *root, int val) {
    if (root == NIL || root == NULL) return NIL;
    if (root->key > val) root->lchild = __erase(root->lchild, val);
    else if (root->key < val) root->rchild = __erase(root->rchild, val);
    else {
        if (root->lchild == NIL || root->rchild == NIL) {
            RBTNode *temp = (root->lchild == NIL) ? root->rchild : root->lchild;
            temp->color += root->color;
            free(root);
            return temp;
        } else {
            RBTNode *temp = predecessor(root);
            root->key = temp->key;
            root->lchild = __erase(root->lchild, temp->key);
        }
    }
    return erase_maintain(root);
}

RBTNode *erase(RBTNode *root, int val) {
    root = __erase(root, val);
    root->color = BLACK;
    return root;
}

void clear(RBTNode *root) {
    if (root == NULL || root == NIL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}
