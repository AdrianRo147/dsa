#include <gtest/gtest.h>
#include <dsa/structures/arrays/dynamic_array.h>

using dsa::structures::arrays::DynamicArray;


class DynamicArrayTest : public ::testing::Test
{
    protected:
        void SetUp() override {
        }

        void TearDown() override {
        }
};

TEST_F(DynamicArrayTest, DefaultConstructor)
{
    DynamicArray<int> arr;
    EXPECT_EQ(arr.getSize(), 0);
}

TEST_F(DynamicArrayTest, InitializerListConstructor)
{
    DynamicArray<int> arr{1, 2, 3, 4, 5};

    EXPECT_EQ(arr.getSize(), 5);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
    EXPECT_EQ(arr[3], 4);
    EXPECT_EQ(arr[4], 5);
}

TEST_F(DynamicArrayTest, EmptyInitializerList)
{
    DynamicArray<int> arr{};
    EXPECT_EQ(arr.getSize(), 0);
}

TEST_F(DynamicArrayTest, CopyConstructor)
{
    DynamicArray<int> original{10, 20, 30};
    DynamicArray<int> copy(original);

    EXPECT_EQ(copy.getSize(), 3);
    EXPECT_EQ(copy[0], 10);
    EXPECT_EQ(copy[1], 20);
    EXPECT_EQ(copy[2], 30);

    original.set(0, 999);
    EXPECT_EQ(copy[0], 10);
}

TEST_F(DynamicArrayTest, MoveConstructor)
{
    DynamicArray<int> original{100, 200, 300};
    size_t originalSize = original.getSize();

    DynamicArray<int> moved(std::move(original));

    EXPECT_EQ(moved.getSize(), originalSize);
    EXPECT_EQ(moved[0], 100);
    EXPECT_EQ(moved[1], 200);
    EXPECT_EQ(moved[2], 300);
    EXPECT_EQ(original.getSize(), 0);
}


TEST_F(DynamicArrayTest, GetMethod)
{
    DynamicArray<int> arr{5, 10, 15};

    EXPECT_EQ(arr.get(0), 5);
    EXPECT_EQ(arr.get(1), 10);
    EXPECT_EQ(arr.get(2), 15);

    EXPECT_THROW(arr.get(3), std::out_of_range);
    EXPECT_THROW(arr.get(100), std::out_of_range);
}

TEST_F(DynamicArrayTest, ConstGetMethod)
{
    const DynamicArray<int> arr{7, 14, 21};

    EXPECT_EQ(arr.get(0), 7);
    EXPECT_EQ(arr.get(1), 14);
    EXPECT_EQ(arr.get(2), 21);

    EXPECT_THROW(arr.get(3), std::out_of_range);
}

TEST_F(DynamicArrayTest, SubscriptOperator)
{
    DynamicArray<int> arr{1, 2, 3};

    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);

    arr[1] = 99;
    EXPECT_EQ(arr[1], 99);
}

TEST_F(DynamicArrayTest, ConstSubscriptOperator)
{
    const DynamicArray<int> arr{10, 20, 30};

    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
}

TEST_F(DynamicArrayTest, FirstAndLastMethods)
{
    DynamicArray<int> arr{1, 2, 3, 4, 5};

    EXPECT_EQ(arr.first(), 1);
    EXPECT_EQ(arr.last(), 5);

    arr.first() = 100;
    arr.last() = 500;
    EXPECT_EQ(arr[0], 100);
    EXPECT_EQ(arr[4], 500);
}

TEST_F(DynamicArrayTest, FirstAndLastMethodsEmptyArray)
{
    DynamicArray<int> arr;

    EXPECT_THROW(arr.first(), std::out_of_range);
    EXPECT_THROW(arr.last(), std::out_of_range);
}

TEST_F(DynamicArrayTest, ConstFirstAndLastMethods)
{
    const DynamicArray<int> arr{10, 20, 30};

    EXPECT_EQ(arr.first(), 10);
    EXPECT_EQ(arr.last(), 30);
}

TEST_F(DynamicArrayTest, SetMethod)
{
    DynamicArray<int> arr{1, 2, 3};

    arr.set(0, 10);
    arr.set(1, 20);
    arr.set(2, 30);

    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);

    EXPECT_THROW(arr.set(3, 40), std::out_of_range);
}

TEST_F(DynamicArrayTest, AddLastMethod)
{
    DynamicArray<int> arr;

    arr.addLast(10);
    EXPECT_EQ(arr.getSize(), 1);
    EXPECT_EQ(arr[0], 10);

    arr.addLast(20);
    arr.addLast(30);
    EXPECT_EQ(arr.getSize(), 3);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
}

TEST_F(DynamicArrayTest, AddFirstMethod)
{
    DynamicArray<int> arr;

    arr.addFirst(10);
    EXPECT_EQ(arr.getSize(), 1);
    EXPECT_EQ(arr[0], 10);

    arr.addFirst(5);
    arr.addFirst(1);
    EXPECT_EQ(arr.getSize(), 3);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 5);
    EXPECT_EQ(arr[2], 10);
}

TEST_F(DynamicArrayTest, RemoveLastMethod)
{
    DynamicArray<int> arr{1, 2, 3, 4, 5};

    arr.removeLast();
    EXPECT_EQ(arr.getSize(), 4);
    EXPECT_EQ(arr.last(), 4);

    arr.removeLast();
    arr.removeLast();
    arr.removeLast();
    EXPECT_EQ(arr.getSize(), 1);
    EXPECT_EQ(arr[0], 1);

    arr.removeLast();
    EXPECT_EQ(arr.getSize(), 0);

    EXPECT_THROW(arr.removeLast(), std::runtime_error);
}

TEST_F(DynamicArrayTest, RemoveFirstMethod)
{
    DynamicArray<int> arr{1, 2, 3, 4, 5};

    arr.removeFirst();
    EXPECT_EQ(arr.getSize(), 4);
    EXPECT_EQ(arr.first(), 2);

    arr.removeFirst();
    arr.removeFirst();
    arr.removeFirst();
    EXPECT_EQ(arr.getSize(), 1);
    EXPECT_EQ(arr[0], 5);

    arr.removeFirst();
    EXPECT_EQ(arr.getSize(), 0);

    EXPECT_THROW(arr.removeFirst(), std::runtime_error);
}

TEST_F(DynamicArrayTest, RemoveAtMethod)
{
    DynamicArray<int> arr{10, 20, 30, 40, 50};

    arr.removeAt(2);
    EXPECT_EQ(arr.getSize(), 4);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 40);
    EXPECT_EQ(arr[3], 50);

    arr.removeAt(0);
    EXPECT_EQ(arr.getSize(), 3);
    EXPECT_EQ(arr[0], 20);

    arr.removeAt(2);
    EXPECT_EQ(arr.getSize(), 2);
    EXPECT_EQ(arr[1], 40);

    EXPECT_THROW(arr.removeAt(5), std::out_of_range);
}

TEST_F(DynamicArrayTest, RemoveAtSingleElement)
{
    DynamicArray<int> arr{42};

    arr.removeAt(0);
    EXPECT_EQ(arr.getSize(), 0);
}

TEST_F(DynamicArrayTest, CopyAssignmentOperator)
{
    DynamicArray<int> arr1{1, 2, 3};
    DynamicArray<int> arr2{10, 20};

    arr2 = arr1;

    EXPECT_EQ(arr2.getSize(), 3);
    EXPECT_EQ(arr2[0], 1);
    EXPECT_EQ(arr2[1], 2);
    EXPECT_EQ(arr2[2], 3);

    arr1 = arr1;
    EXPECT_EQ(arr1.getSize(), 3);
    EXPECT_EQ(arr1[0], 1);
}

TEST_F(DynamicArrayTest, MoveAssignmentOperator)
{
    DynamicArray<int> arr1{100, 200, 300};
    DynamicArray<int> arr2{1, 2};

    arr2 = std::move(arr1);

    EXPECT_EQ(arr2.getSize(), 3);
    EXPECT_EQ(arr2[0], 100);
    EXPECT_EQ(arr2[1], 200);
    EXPECT_EQ(arr2[2], 300);
    EXPECT_EQ(arr1.getSize(), 0);
}

TEST_F(DynamicArrayTest, InitializerListAssignmentOperator)
{
    DynamicArray<int> arr{1, 2, 3};

    arr = {10, 20, 30, 40};

    EXPECT_EQ(arr.getSize(), 4);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
    EXPECT_EQ(arr[3], 40);

    arr = {};
    EXPECT_EQ(arr.getSize(), 0);
}

TEST_F(DynamicArrayTest, StreamOutputOperator)
{
    DynamicArray<int> arr{1, 2, 3};
    std::ostringstream oss;

    oss << arr;

    std::string expected = "Index: 0 | Value: 1\nIndex: 1 | Value: 2\nIndex: 2 | Value: 3\n";
    EXPECT_EQ(oss.str(), expected);
}

class DynamicArrayIteratorTest : public ::testing::Test
{
    protected:
        DynamicArray<int> arr;

        void SetUp() override {
            arr = {10, 20, 30, 40, 50};
        }
};

TEST_F(DynamicArrayIteratorTest, BeginAndEnd)
{
    auto it_begin = arr.begin();
    auto it_end = arr.end();

    EXPECT_NE(it_begin, it_end);
    EXPECT_EQ(*it_begin, 10);
}

TEST_F(DynamicArrayIteratorTest, IncrementOperators)
{
    auto it = arr.begin();

    EXPECT_EQ(*it, 10);

    ++it;
    EXPECT_EQ(*it, 20);

    auto old_it = it++;
    EXPECT_EQ(*old_it, 20);
    EXPECT_EQ(*it, 30);
}

TEST_F(DynamicArrayIteratorTest, DecrementOperators)
{
    auto it = arr.begin();
    ++it;
    ++it;

    EXPECT_EQ(*it, 30);

    --it;
    EXPECT_EQ(*it, 20);

    auto old_it = it--;
    EXPECT_EQ(*old_it, 20);
    EXPECT_EQ(*it, 10);
}

TEST_F(DynamicArrayIteratorTest, SubscriptOperator)
{
    auto it = arr.begin();

    EXPECT_EQ(it[0], 10);
    EXPECT_EQ(it[1], 20);
    EXPECT_EQ(it[2], 30);
    EXPECT_EQ(it[3], 40);
    EXPECT_EQ(it[4], 50);
}

TEST_F(DynamicArrayIteratorTest, ArrowOperator)
{
    DynamicArray<std::pair<int, int>> pairArr{{1, 2}, {3, 4}, {5, 6}};
    auto it = pairArr.begin();

    EXPECT_EQ((*it).first, 1);
    EXPECT_EQ((*it).second, 2);
}

TEST_F(DynamicArrayIteratorTest, EqualityOperators)
{
    auto it1 = arr.begin();
    auto it2 = arr.begin();
    auto it3 = arr.end();

    EXPECT_TRUE(it1 == it2);
    EXPECT_FALSE(it1 != it2);
    EXPECT_FALSE(it1 == it3);
    EXPECT_TRUE(it1 != it3);
}

TEST_F(DynamicArrayIteratorTest, RangeBasedForLoop)
{
    std::vector<int> values;

    for (const auto& value : arr) {
        values.push_back(value);
    }

    EXPECT_EQ(values.size(), 5);
    EXPECT_EQ(values[0], 10);
    EXPECT_EQ(values[1], 20);
    EXPECT_EQ(values[2], 30);
    EXPECT_EQ(values[3], 40);
    EXPECT_EQ(values[4], 50);
}

TEST_F(DynamicArrayTest, DifferentDataTypes)
{
    DynamicArray<std::string> strArr{"hello", "world", "test"};

    EXPECT_EQ(strArr.getSize(), 3);
    EXPECT_EQ(strArr[0], "hello");
    EXPECT_EQ(strArr[1], "world");
    EXPECT_EQ(strArr[2], "test");

    DynamicArray<double> doubleArr{1.5, 2.7, 3.14};

    EXPECT_EQ(doubleArr.getSize(), 3);
    EXPECT_DOUBLE_EQ(doubleArr[0], 1.5);
    EXPECT_DOUBLE_EQ(doubleArr[1], 2.7);
    EXPECT_DOUBLE_EQ(doubleArr[2], 3.14);
}

TEST_F(DynamicArrayTest, StressTest)
{
    DynamicArray<int> arr;

    for (int i = 0; i < 1000; ++i) {
        arr.addLast(i);
    }

    EXPECT_EQ(arr.getSize(), 1000);
    EXPECT_EQ(arr.first(), 0);
    EXPECT_EQ(arr.last(), 999);

    for (int i = 0; i < 500; ++i) {
        arr.removeLast();
    }

    EXPECT_EQ(arr.getSize(), 500);
    EXPECT_EQ(arr.last(), 499);
}
