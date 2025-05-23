#include "dynamic_array.h"

#include <iostream>
#include <dsa/structures/arrays/dynamic_array.h>
#include <cassert>

void tests::structures::arrays::dynamicArray() {
    dsa::structures::arrays::DynamicArray<int> arr1;
    dsa::structures::arrays::DynamicArray<int> arr2{ 1, 2, 3, 4 };

    arr1.addLast(10);
    arr1.addLast(20);
    arr1.addFirst(5);

    assert(arr1.get(0) == 5);
    assert(arr1[1] == 10);
    arr1[1] = 15;

    assert(arr1.get(1) == 15);
    assert(arr1.first() == 5);
    assert(arr1.last() == 20);

    arr1.set(2, 25);
    assert(arr1.get(2) == 25);

    arr1.removeFirst();
    assert(arr1.first() == 15);

    arr1.removeLast();
    assert(arr1.getSize() == 1);

    arr1.addLast(100);
    arr1.addLast(200);
    arr1.removeAt(1);
    assert(arr1[1] == 200);

    arr1 = { 9, 8, 7 };
    assert(arr1[0] == 9);
    assert(arr1[2] == 7);

    assert(arr1.getSize() == 3);

    std::cout << "Dynamic array passed successfully!\n";
}
