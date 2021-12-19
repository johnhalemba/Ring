//
// Created by jhalemba on 19.12.2021.
//

#ifndef RING_RING_H
#define RING_RING_H

template <typename Key, typename Info>
struct val {
    Key key;
    Info info;
};

template <typename Key, typename Info>
class Ring {
public:
    friend class iterator;
    class iterator {

    };
    Ring() = default;
    ~Ring();
private:
    struct Element {
        val<Key, Info> values;
        Element* left = nullptr;
        Element* right = nullptr;
    };
    Element* head = nullptr;
};

template<typename Key, typename Info>
Ring<Key, Info>::~Ring() {

}


#endif //RING_RING_H
