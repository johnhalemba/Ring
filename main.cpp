//
// Created by jhalemba on 19.12.2021.
//
#include "externalFunctions.h"

#include <iostream>

int main()
{
    Ring<int, int> r1;
    r1.push_back(2, 3);
    r1.push_front(5, 5);
    r1.push_front(5, 6);
    r1.push_back(9, 9);
    auto it1 = r1.begin();
    bool found;
    it1++;
    it1++;
    r1.insert_after(it1, 10, 10);
    r1.find(5, 2, found, true);
    removeAllElements(r1, 5);
    return 0;
}

