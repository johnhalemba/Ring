//
// Created by jhalemba on 19.12.2021.
//

#ifndef RING_RING_H
#define RING_RING_H
#include <iostream>
#include <exception>
#include <random>

template <typename Key, typename Info>
class Ring {
private:
    struct Element {
    public:
        Key key;
        Info info;
        Element* left = nullptr;
        Element* right = nullptr;
        Element(const Key& k, const Info& i) : key(k), info(i), left(nullptr), right(nullptr) {}
    };
    Element* root = nullptr;
    int numberOfElements = 0;
public:
    Ring() = default;

    ~Ring();
    friend class iterator;
    class iterator {
    public:
        friend class Ring<Key, Info>;
        iterator() = default;
        iterator(Element* pointer) { ptr = pointer; };
        ~iterator() = default;
        bool operator==(const iterator& rhs) { return ptr == rhs.ptr; };
        bool operator!=(const iterator& rhs) { return ptr != rhs.ptr; };
        iterator& operator++() { ptr = ptr->right; return (*this); };
        iterator& operator++(int) { iterator temp(ptr); ptr = ptr->right; return temp; };
        iterator& operator--() { ptr = ptr->left; return (*this); };
        iterator& operator--(int) { iterator temp(ptr); ptr = ptr->left; return temp; };
        iterator& operator=(const iterator& rhs) { if (this != &rhs) { ptr = rhs.ptr; } return (*this); };
        Element& operator*() { return *ptr; };
        Element* operator->() { return ptr; };

    private:
        Element* ptr = nullptr;
    };
    bool isLastElement();
    iterator begin() { if (root == nullptr) return iterator(root); return iterator(root->right); };
    iterator end() { return iterator(root); };
    void push_front(const Key &k, const Info &i);
    void deleteElement(iterator& itr);
    void push_back(const Key &k, const Info &i);
    Ring::iterator find(const Key& key, int occurance, bool& success, bool forwardDirection);
    void pop_back();
    void pop_front();
    void insert_before(iterator &itr, const Key& k, const Info& i);
    void insert_after(iterator &itr, const Key& k, const Info& i);
};


template<typename Key, typename Info>
Ring<Key, Info>::~Ring() {
    if (root == nullptr)
        return;
    while (!isLastElement())
    {
        pop_back();
    }
    delete root;
}

template<typename Key, typename Info>
bool Ring<Key, Info>::isLastElement() {
    return root == root->right;
}


template<typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::find(const Key &key, int occurance, bool &success, bool forwardDirection) {
    if (occurance <= 0)
        throw std::invalid_argument("Occurance is lower or equal to zero!");
    int tempOcc = 0;
    if (forwardDirection)
    {
        for (auto a = begin(); a != end(); a++)
        {
            if (a->key == key)
            {
                tempOcc++;
                if (tempOcc == occurance)
                {
                    success = true;
                    return a;
                }
            }
        }
    }
    else
    {
        for (auto a = end(); a != begin(); a--)
        {
            if (a->key == key)
            {
                tempOcc++;
                if (tempOcc == occurance)
                {
                    success = true;
                    return a;
                }
            }
        }
    }
    success = false;
    return iterator(nullptr);
}

template<typename Key, typename Info>
void Ring<Key, Info>::push_front(const Key &k, const Info &i) {
    if (root == nullptr)
    {
        auto temp = new Element(k, i);
        root = temp;
        temp -> left = root;
        temp -> right = root;
        numberOfElements++;
        return;
    }
    auto itr = begin();
    insert_before(itr, k, i);
}

template<typename Key, typename Info>
void Ring<Key, Info>::insert_before(iterator &itr, const Key &k, const Info &i) {
    auto temp = new Element(k, i);
    temp->right = itr.ptr;
    temp->left = itr.ptr->left;
    //checking whether there is only one element in the list
    if (itr.ptr == root->left) {
        itr.ptr->left = temp;
    }
    itr.ptr->left = temp;
    temp->left->right = temp;
    numberOfElements++;
}

template<typename Key, typename Info>
void Ring<Key, Info>::push_back(const Key &k, const Info &i) {
    if (root == nullptr)
    {
        auto temp = new Element(k, i);
        root = temp;
        temp -> left = root;
        temp -> right = root;
        numberOfElements++;
        return;
    }
    auto itr = end();
    insert_before(itr, k, i);
}

template<typename Key, typename Info>
void Ring<Key, Info>::deleteElement(Ring::iterator &itr) {
    if (itr.ptr == root)
        return;
    auto temp = itr.ptr;
    itr.ptr = temp->left;
    temp->left->right = temp->right;
    temp->right->left = temp->left;
    delete temp;
    numberOfElements--;
}

template<typename Key, typename Info>
void Ring<Key, Info>::pop_back() {
    iterator i(--end());
    deleteElement(i);
}

template<typename Key, typename Info>
void Ring<Key, Info>::pop_front() {
    iterator i(begin());
    deleteElement(i);
}

template<typename Key, typename Info>
void Ring<Key, Info>::insert_after(Ring::iterator &itr, const Key &k, const Info &i) {
    auto temp = new Element(k, i);
    temp->right = itr.ptr->right;
    temp->left = itr.ptr;
    //checking whether there is only one element in the list
    if (itr.ptr == root->left) {
        itr.ptr->right = temp;
    }
    itr.ptr->right = temp;
    temp->right->left = temp;
    numberOfElements++;
}


#endif //RING_RING_H
