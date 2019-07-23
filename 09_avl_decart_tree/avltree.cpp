#include "avltree.h"
#include <algorithm>

hw::AvlTree::~AvlTree() { destroyTree(root_); }

void hw::AvlTree::insert(int value)
{
    auto n = new hw::AvlNode(value);
    root_  = insertNodeAt(root_, n);
}

bool hw::AvlTree::empty() const { return (root_ == nullptr || root_->height == -1); }

int hw::AvlTree::height() const { return (root_ == nullptr) ? -1 : root_->height; }

int hw::AvlTree::balance() const { return (root_ == nullptr) ? 0 : root_->balance; }

void hw::AvlTree::rebalance(hw::AvlNode* n)
{
    if (n->balance >= -1 || n->balance <= 1) {
        return;
    }
}

void hw::AvlTree::destroyTree(hw::AvlNode* n) { delete n; }

hw::AvlNode* hw::AvlTree::insertNodeAt(hw::AvlNode* p, hw::AvlNode* n)
{
    if (p == nullptr || n == nullptr) {
        return n;
    }

    if (n->value < p->value) {
        p->left = insertNodeAt(p->left, n);
    } else {
        p->right = insertNodeAt(p->right, n);
    }

    auto l    = (p->left != nullptr) ? p->left->height : 0;
    auto r    = (p->right != nullptr) ? p->right->height : 0;
    p->height = std::max(l, r) + 1;

    p->balance = r - l;
    rebalance(p);
    return p;
}
