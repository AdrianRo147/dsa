// dsa.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <gtest/gtest.h>

int main(int argc, char** argv)
{
    /*
    std::cout << "STATIC ARRAY\n";

    dsa::structures::arrays::StaticArray<int, 5> arr = { 1,2,3,4,5 };

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


    dsa::structures::linked_list::Node<int> node = 1;
    */

    if (argc > 1 && std::string(argv[1]) == "--test") {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
}
