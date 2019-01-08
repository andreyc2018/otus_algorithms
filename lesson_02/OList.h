#pragma once
/*********************************************************
OList<int>* a = new OList<int>();
for (int i = 0; i < 10; i++)
        a->add(i*i);

while (!a.empty())
{
        cout << a->head() << "\n";
        a->pop_head();;
}
*********************************************************/

template<class T>
class ListItem
{
  private:
    T data_;
    ListItem<T>* next_;
    ListItem<T>* prev_;

  public:
    using node_ptr = ListItem<T>*;

    ListItem(T item)
        : data_(item), next_(nullptr), prev_(nullptr) {}

    T get() { return data_; }

    void setNext(ListItem<T>* node) { next_ = node; }
    ListItem<T>* getNext() { return next_; }

    void setPrev(ListItem<T>* node) { prev_ = node; }
    ListItem<T>* getPrev() { return prev_; }
};

template<class T>
class OList
{
  public:
    using node_ptr = ListItem<T>*;

    OList() : head_(nullptr), tail_(nullptr), size_(0) {}
    ~OList() { destroy(); }

    T head()
    {
        if (head_ == nullptr) {
            return T();
        }
        return head_->get();
    }

    T tail()
    {
        if (tail_ == nullptr) {
            return T();
        }
        return tail_->get();
    }

    void add(T item)
    {
        ListItem<T>* li = new ListItem<T>(item);
        if (!first_node(li)) {
            append_node(li);
        }
        size_++;
    }

    void insert(T item)
    {
        ListItem<T>* li = new ListItem<T>(item);
        if (!first_node(li)) {
            insert_node(li);
        }
        size_++;
    }

    int size() const { return size_; }
    bool empty() const { return head_ == nullptr; }

    node_ptr get_head() { return head_; }
    node_ptr get_tail() { return tail_; }

    void pop_head()
    {
        if (head_ != nullptr) {
            node_ptr tmp = head_->getNext();
            if (tmp != nullptr) {
                tmp->setPrev(nullptr);
            }
            delete head_;
            head_ = tmp;
            if (head_ == nullptr) {
                tail_ = nullptr;
            }
            size_--;
        }
    }

    void pop_tail()
    {
        if (tail_ != nullptr) {
            node_ptr tmp = tail_->getPrev();
            if (tmp != nullptr) {
                tmp->setNext(nullptr);
            }
            delete tail_;
            tail_ = tmp;
            if (tail_ == nullptr) {
                head_ = nullptr;
            }
            size_--;
        }
    }

  protected:
    void destroy()
    {
        while (head_ != nullptr) {
            node_ptr tmp = head_->getNext();
            delete head_;
            head_ = tmp;
        }
    }

  private:
    node_ptr head_;
    node_ptr tail_;
    int size_;

    bool first_node(node_ptr node)
    {
        if (head_ == nullptr) {
            head_ = node;
            tail_ = node;
            return true;
        }
        return false;
    }

    void append_node(node_ptr node)
    {
        if (node != nullptr) {
            node->setPrev(tail_);
            tail_->setNext(node);
            tail_ = node;
        }
    }

    void insert_node(node_ptr node)
    {
        if (node != nullptr) {
            head_->setPrev(node);
            node->setNext(head_);
            head_ = node;
        }
    }
};
