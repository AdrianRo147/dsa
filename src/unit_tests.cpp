#pragma once

#include "unit_tests.h"

#include <iostream>
#include <dsa/structures/arrays/dynamic_array.h>
#include <cassert>

void tests::dynamicArray() {
    std::cout << "Testing constructors...\n";
    dsa::structures::DynamicArray<int> arr1;
    dsa::structures::DynamicArray<int> arr2{ 1, 2, 3, 4 };

    std::cout << "Testing addLast and addFirst...\n";
    arr1.addLast(10);
    arr1.addLast(20);
    arr1.addFirst(5);

    std::cout << arr1;

    std::cout << "Testing get and operator[]...\n";
    assert(arr1.get(0) == 5);
    assert(arr1[1] == 10);
    arr1[1] = 15;
    assert(arr1.get(1) == 15);

    std::cout << "Testing first and last...\n";
    assert(arr1.first() == 5);
    assert(arr1.last() == 20);

    std::cout << "Testing set...\n";
    arr1.set(2, 25);
    assert(arr1.get(2) == 25);

    std::cout << "Testing removeFirst, removeLast, removeAt...\n";
    arr1.removeFirst();
    assert(arr1.first() == 15);

    arr1.removeLast();
    assert(arr1.getSize() == 1);

    arr1.addLast(100);
    arr1.addLast(200);
    arr1.removeAt(1);
    assert(arr1[1] == 200);

    std::cout << "Testing operator= with initializer_list...\n";
    arr1 = { 9, 8, 7 };
    assert(arr1[0] == 9);
    assert(arr1[2] == 7);

    std::cout << "Testing begin and end (range-based for)...\n";
    std::cout << "Elements: ";

    for (auto& elem : arr1) {
        std::cout << elem << " ";
    }

    std::cout << "\n";

    std::cout << "Testing getSize...\n";
    assert(arr1.getSize() == 3);

    std::cout << "All tests passed successfully!\n";
}