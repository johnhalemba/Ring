//
// Created by jhalemba on 19.12.2021.
//
#include "Ring.h"

#ifndef LAB1_EXTERNALFUNCTIONS_H
#define LAB1_EXTERNALFUNCTIONS_H

template <typename Key, typename Info>
void removeAllElements(Ring<Key, Info>& r, const Key& k)
{
    for (auto a = r.begin(); a != r.end(); a++) {
        if (a->key == k)
            r.deleteElement(a);
    }
}

#endif //LAB1_EXTERNALFUNCTIONS_H
