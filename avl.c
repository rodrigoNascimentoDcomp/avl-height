#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *left, *right;
    int height;
} node;

void print_in_order(node *n) {
    if (n == NULL)
        return;
    print_in_order(n->left);
    printf("%d\n", n->value);
    print_in_order(n->right);
}

void print_pre_order(node *n) {
    if (n == NULL)
        return;
    printf("%d\n", n->value);
    print_pre_order(n->left);
    print_pre_order(n->right);
}

void print_post_order(node *n) {
    if (n == NULL)
        return;
    print_post_order(n->left);
    print_post_order(n->right);
    printf("%d\n", n->value);
}

int max(int a, int b) {
    return a > b ? a : b;
}

int count(node *n) {
    if (n == NULL)
        return 0;
    return count(n->left) + count(n->right) + 1;
}

int get_balance(node *n) {
    if (n == NULL)
        return 0;
    
    int l = n->left ? n->left->height : 0;
    int r = n->right ? n->right->height : 0;
    
    return r - l;
}

int get_height(node *n) {
    if (n == NULL)
        return 0;
    
    int l = n->left ? n->left->height : 0;
    int r = n->right ? n->right->height : 0;
    
    return max(l, r) + 1;
}

int is_ordered(node *n) {
    if (n == NULL)
        return 1;
    
    if (n->left && n->left->value > n->value)
        return 0;
    
    if (n->right && n->right->value <= n->value)
        return 0;
    
    return is_ordered(n->left) && is_ordered(n->right);
}

int is_balanced(node *n) {
    if (n == NULL)
        return 1;
    
    int b = get_balance(n);
    
    if (b > 1 || b < -1)
        return 0;
    
    return is_balanced(n->left) && is_balanced(n->right);
}

int is_avl(node *n) {
    return is_ordered(n) && is_balanced(n);
}

node* create(int v) {
    node *n = (node*) malloc(sizeof(node));
    n->value = v;
    n->left = NULL;
    n->right = NULL;
    n->height = 1;
    return n;
}

node* search(node *n, int v) {
    if (n == NULL)
        return NULL;
    
    if (n->value >= v)
        return search(n->left, v);
    
    if (n->value < v)
        return search(n->right, v);
    
    if (n->value == v)
        return n;
}

node* biggest(node *n) {
    if (n && n->right)
        return biggest(n->right);
    
    return n;
}

node* smallest(node *n) {
    if (n && n->left)
        return smallest(n->left);
    return n;
}

node* rotate_left(node *n) {
    node *axis = n->right;
    n->right = axis->left;
    axis->left = n;
    
    axis->height = get_height(axis);
    axis->left->height = get_height(axis->left);
    
    return axis;
}

node* rotate_right(node *n) {
    node *axis = n->left;
    n->left = axis->right;
    axis->right = n;
    
    axis->height = get_height(axis);
    axis->right->height = get_height(axis);
    
    return axis;
}

node* rotate_left_right(node *n) {
    n->left = rotate_left(n->left);
    n = rotate_right(n);
    return n;
}

node* rotate_right_left(node *n) {
    n->right = rotate_right(n->right);
    n = rotate_left(n);
    return n;
}

node* rotate(node *n) {
    int b = get_balance(n);
    if (b > 1) {
        if (get_balance(n->right) < 0)
            n = rotate_right_left(n);
        else
            n = rotate_left(n);
    } else if (b < -1) {
        if (get_balance(n->left) > 0)
            n = rotate_left_right(n);
        else
            n = rotate_right(n);
    }
    
    return n;
}

node* push(node *r, node *n) {
    if (r == NULL)
        r = n;
    else if (r->value >= n->value)
        r->left = push(r->left, n);
    else if (r->value < n->value)
        r->right =push(r->right, n);
    
    r->height = get_height(r);
    r = rotate(r);
    
    return r;
}

int main()
{
    node *n;
    n = create(10);
    n = push(n, create(5));
    n = push(n, create(50));
    n = push(n, create(60));
    n = push(n, create(55));
    
    print_pre_order(n);

    return 0;
}