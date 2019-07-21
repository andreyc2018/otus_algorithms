#include "avltree.h"

hw::AvlTree::~AvlTree() { destroyTree(root_); }

void hw::AvlTree::insert(int value)
{
    if (root_ == nullptr) {
        root_ = new hw::AvlNode(value);
    }
}

bool hw::AvlTree::empty() const { return (root_ == nullptr || root_->height == -1); }

int hw::AvlTree::height() const { return (root_ == nullptr) ? -1 : root_->height; }

int hw::AvlTree::balance() const { return (root_ == nullptr) ? 0 : root_->balance; }

void hw::AvlTree::destroyTree(hw::AvlNode* n) { delete n; }
