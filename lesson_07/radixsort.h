#pragma once
#include <test_tools.h>
#include <iostream>
#include <list>

namespace otus {

namespace count {

template <typename T>
void count_sort(T& array, typename T::value_type k, typename T::value_type idx)
{
    using element_t = decltype (k);
    T count (k, 0);

    //    std::cout << "\t";
    //    test_tools::debug_print(std::cout, count);

    for (const auto& item : array) {
        count[(item/idx)%k] ++;
    }

    //    std::cout << "\t";
    //    test_tools::debug_print(std::cout, count);

    for (element_t i = 1; i <= k; ++i) {
        count[i] += count[i-1];
    }

    //    std::cout << "\t";
    //    test_tools::debug_print(std::cout, count);

    T sorted(array.size());

    std::for_each(std::rbegin(array), std::rend(array), [&sorted, &count, &k, &idx](const element_t& item) {
        auto i = (item/idx)%k;
        count[i] -= 1;
        sorted[count[i]] = item;
    });

    //    std::cout << "\t";
    //    test_tools::debug_print(std::cout, sorted);

    std::copy(std::begin(sorted), std::end(sorted), std::begin(array));
}

template <typename T>
void radix_sort(T& array, typename T::value_type k)
{
    //    std::cout << "k = " << k << "\n";
    for (int i = 1; i <= k; i *= 10) {
        //        std::cout << "i = " << i << "\n\t";
        //        test_tools::debug_print(std::cout, array);
        count_sort(array, 10, i);
    }
}

}

namespace trie {

template <typename T>
struct RadixNode
{
    RadixNode* parent = nullptr;
    std::list<RadixNode*> children;
    T node_value = T();
    T value = T();
    size_t count = 0;

    RadixNode* contains_node_value(const T& v) {
        for (const auto& c : children) {
            if (c->node_value == v) {
                return c;
            }
        }
        return nullptr;
    }

    RadixNode* add_child(const T& v) {
        RadixNode* n = new RadixNode;
        n->parent = this;
        n->node_value = v;
        children.push_back(n);
        return n;
    }

    void set_node_value(const T& v) {
        value = v;
    }

    void add(const T& v) {
        if (count == 0 || v == value) {
            value = v;
            count += 1;
        }
    }
};

template <typename T>
class RadixTrie
{
    public:
        using node_t = RadixNode<T>;

        RadixTrie() : root_(new node_t), size_(0) {}
        ~RadixTrie() { /*destroy_trie(root_);*/ }

        size_t size() const { return size_; }

        void add(const T& v) {
            std::cout << "v = " << v << "\n";
            auto node = root_;
            for (int i = 1; i <= v; i *= 10) {
                std::cout << "i = " << i << "\n";
                auto radix_v = (v/i)%10;
                std::cout << "radix_v = " << radix_v << "\n";
                node_t* next = node->contains_node_value(radix_v);
                if (next == nullptr) {
                    next = node->add_child(radix_v);
                }
                node = next;
                std::cout << "node->node_value = " << node->node_value << "\n";
//                for (auto& c : root_->children) {
//                    if (!c.contains(radix_v)) {

//                    }
//                }
//                for (const auto& a : array) {
//                    std::cout << "\t" << a << " => " << (a/i)%10 << "\n";
//                }
            }
            node->add(v);
            size_ += 1;
            std::cout << "node->count = " << node->count << "\n";
            std::cout << "node->value = " << node->value << "\n";
        }

    private:
        node_t* root_;
        size_t size_;

        void destroy_trie(node_t* node) {
            if (node == nullptr) {
                return;
            }
            for (auto& n : node->children) {
                destroy_trie(n);
            }
            node->children.clear();
            delete node;
        }
};

template <typename T>
void radix_sort(T& array, typename T::value_type k)
{
    std::cout << "k = " << k << "\n";
    for (int i = 1; i <= k; i *= 10) {
        std::cout << "i = " << i << "\n\t";
        test_tools::debug_print(std::cout, array);
    }
}

}

}
