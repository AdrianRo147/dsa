// dsa.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <dsa/structures/arrays/static_array.h>
#include <dsa/structures/arrays/dynamic_array.h>

#include "unit_tests/structures/arrays/dynamic_array.h"

int main()
{
    std::cout << "STATIC ARRAY\n";

    dsa::structures::StaticArray<int, 5> arr = { 1,2,3,4,5 };

    arr.set(3, 0);
    arr[0] = 8;
    std::cout << arr;

    std::cout << "\n";

    arr = { 5,4,3,2,1 };
    std::cout << arr;

    for (auto it : arr)
    {
        std::cout << it;
    }

    std::cout << "\n\n\nDYNAMIC ARRAY\n";

    tests::structures::arrays::dynamicArray();
}
