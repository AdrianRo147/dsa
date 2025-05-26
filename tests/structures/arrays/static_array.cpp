#include <gtest/gtest.h>
#include <stdexcept>
#include <dsa/structures/arrays/static_array.h>

using namespace dsa::structures::arrays;

class StaticArrayTest : public ::testing::Test
{
    protected:
        void SetUp() override {
        }

        void TearDown() override {
        }
};

TEST_F(StaticArrayTest, DefaultConstructor)
{
    StaticArray<int, 5> arr;
    EXPECT_EQ(arr.getSize(), 5);

    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(arr[i], 0);
    }
}

TEST_F(StaticArrayTest, InitializerListConstructorCorrectSize)
{
    StaticArray<int, 5> arr{1, 2, 3, 4, 5};

    EXPECT_EQ(arr.getSize(), 5);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
    EXPECT_EQ(arr[3], 4);
    EXPECT_EQ(arr[4], 5);
}

TEST_F(StaticArrayTest, InitializerListConstructorIncorrectSize)
{
    EXPECT_THROW((StaticArray<int, 3>{1, 2, 3, 4, 5}), std::runtime_error);
    EXPECT_THROW((StaticArray<int, 5>{1, 2, 3}), std::runtime_error);
}

TEST_F(StaticArrayTest, CopyConstructor)
{
    StaticArray<int, 3> original{10, 20, 30};
    StaticArray<int, 3> copy(original);

    EXPECT_EQ(copy.getSize(), 3);
    EXPECT_EQ(copy[0], 10);
    EXPECT_EQ(copy[1], 20);
    EXPECT_EQ(copy[2], 30);

    original.set(0, 999);
    EXPECT_EQ(copy[0], 10);
}

TEST_F(StaticArrayTest, MoveConstructor)
{
    StaticArray<int, 3> original{100, 200, 300};
    StaticArray<int, 3> moved(std::move(original));

    EXPECT_EQ(moved.getSize(), 3);
    EXPECT_EQ(moved[0], 100);
    EXPECT_EQ(moved[1], 200);
    EXPECT_EQ(moved[2], 300);
}

TEST_F(StaticArrayTest, GetMethod)
{
    StaticArray<int, 3> arr{5, 10, 15};

    EXPECT_EQ(arr.get(0), 5);
    EXPECT_EQ(arr.get(1), 10);
    EXPECT_EQ(arr.get(2), 15);

    EXPECT_THROW(arr.get(3), std::out_of_range);
    EXPECT_THROW(arr.get(100), std::out_of_range);
}

TEST_F(StaticArrayTest, ConstGetMethod)
{
    const StaticArray<int, 3> arr{7, 14, 21};

    EXPECT_EQ(arr.get(0), 7);
    EXPECT_EQ(arr.get(1), 14);
    EXPECT_EQ(arr.get(2), 21);

    EXPECT_THROW(arr.get(3), std::out_of_range);
}

TEST_F(StaticArrayTest, GetSizeMethod)
{
    StaticArray<int, 10> arr1;
    StaticArray<double, 1> arr2;
    StaticArray<std::string, 100> arr3;

    EXPECT_EQ(arr1.getSize(), 10);
    EXPECT_EQ(arr2.getSize(), 1);
    EXPECT_EQ(arr3.getSize(), 100);
}

TEST_F(StaticArrayTest, SubscriptOperator)
{
    StaticArray<int, 3> arr{1, 2, 3};

    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);

    arr[1] = 99;
    EXPECT_EQ(arr[1], 99);
}

TEST_F(StaticArrayTest, ConstSubscriptOperator)
{
    const StaticArray<int, 3> arr{10, 20, 30};

    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
}

TEST_F(StaticArrayTest, FirstAndLastMethods)
{
    StaticArray<int, 5> arr{1, 2, 3, 4, 5};

    EXPECT_EQ(arr.first(), 1);
    EXPECT_EQ(arr.last(), 5);

    arr.first() = 100;
    arr.last() = 500;
    EXPECT_EQ(arr[0], 100);
    EXPECT_EQ(arr[4], 500);
}

TEST_F(StaticArrayTest, FirstAndLastMethodsSizeOne)
{
    StaticArray<int, 1> arr{42};

    EXPECT_EQ(arr.first(), 42);
    EXPECT_EQ(arr.last(), 42);

    arr.first() = 100;
    EXPECT_EQ(arr.last(), 100);
}

TEST_F(StaticArrayTest, SetMethod)
{
    StaticArray<int, 3> arr{1, 2, 3};

    arr.set(0, 10);
    arr.set(1, 20);
    arr.set(2, 30);

    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);

    EXPECT_THROW(arr.set(3, 40), std::out_of_range);
}

TEST_F(StaticArrayTest, InitializerListAssignmentCorrectSize)
{
    StaticArray<int, 4> arr{1, 2, 3, 4};

    arr = {10, 20, 30, 40};

    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
    EXPECT_EQ(arr[3], 40);
}

TEST_F(StaticArrayTest, InitializerListAssignmentIncorrectSize)
{
    StaticArray<int, 3> arr{1, 2, 3};

    EXPECT_THROW((arr = {1, 2, 3, 4, 5}), std::runtime_error);

    EXPECT_THROW((arr = {1, 2}), std::runtime_error);
}

TEST_F(StaticArrayTest, CopyAssignmentOperator)
{
    StaticArray<int, 3> arr1{1, 2, 3};
    StaticArray<int, 3> arr2{10, 20, 30};

    arr2 = arr1;

    EXPECT_EQ(arr2[0], 1);
    EXPECT_EQ(arr2[1], 2);
    EXPECT_EQ(arr2[2], 3);

    arr1 = arr1;
    EXPECT_EQ(arr1[0], 1);
    EXPECT_EQ(arr1[1], 2);
    EXPECT_EQ(arr1[2], 3);

    arr1.set(0, 999);
    EXPECT_EQ(arr2[0], 1);
}

TEST_F(StaticArrayTest, MoveAssignmentOperator)
{
    StaticArray<int, 3> arr1{100, 200, 300};
    StaticArray<int, 3> arr2{1, 2, 3};

    arr2 = std::move(arr1);

    EXPECT_EQ(arr2[0], 100);
    EXPECT_EQ(arr2[1], 200);
    EXPECT_EQ(arr2[2], 300);

    StaticArray<int, 3> arr3{1, 2, 3};
    arr3 = std::move(arr3);
    EXPECT_EQ(arr3[0], 1);
    EXPECT_EQ(arr3[1], 2);
    EXPECT_EQ(arr3[2], 3);
}

TEST_F(StaticArrayTest, StreamOutputOperator)
{
    StaticArray<int, 3> arr{1, 2, 3};
    std::ostringstream oss;

    oss << arr;

    std::string expected = "Index: 0 | Value: 1\nIndex: 1 | Value: 2\nIndex: 2 | Value: 3\n";
    EXPECT_EQ(oss.str(), expected);
}

TEST_F(StaticArrayTest, DifferentDataTypes)
{
    StaticArray<std::string, 3> strArr{"hello", "world", "test"};
    EXPECT_EQ(strArr[0], "hello");
    EXPECT_EQ(strArr[1], "world");
    EXPECT_EQ(strArr[2], "test");

    StaticArray<double, 3> doubleArr{1.5, 2.7, 3.14};
    EXPECT_DOUBLE_EQ(doubleArr[0], 1.5);
    EXPECT_DOUBLE_EQ(doubleArr[1], 2.7);
    EXPECT_DOUBLE_EQ(doubleArr[2], 3.14);

    StaticArray<char, 4> charArr{'a', 'b', 'c', 'd'};
    EXPECT_EQ(charArr[0], 'a');
    EXPECT_EQ(charArr[1], 'b');
    EXPECT_EQ(charArr[2], 'c');
    EXPECT_EQ(charArr[3], 'd');
}

TEST_F(StaticArrayTest, ZeroSizedArray)
{
    StaticArray<int, 0> arr;
    EXPECT_EQ(arr.getSize(), 0);

    EXPECT_THROW(arr.get(0), std::out_of_range);
    EXPECT_THROW(arr[0], std::out_of_range);
    EXPECT_THROW(arr.set(0, 1), std::out_of_range);
}

class StaticArrayIteratorTest : public ::testing::Test
{
    protected:
        StaticArray<int, 5> arr;

        void SetUp() override {
            arr = {10, 20, 30, 40, 50};
        }
};

TEST_F(StaticArrayIteratorTest, BeginAndEnd)
{
    auto it_begin = arr.begin();
    auto it_end = arr.end();

    EXPECT_NE(it_begin, it_end);
    EXPECT_EQ(*it_begin, 10);
}

TEST_F(StaticArrayIteratorTest, IncrementOperators)
{
    auto it = arr.begin();

    EXPECT_EQ(*it, 10);

    ++it;
    EXPECT_EQ(*it, 20);

    auto old_it = it++;
    EXPECT_EQ(*old_it, 20);
    EXPECT_EQ(*it, 30);
}

TEST_F(StaticArrayIteratorTest, DecrementOperators)
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

TEST_F(StaticArrayIteratorTest, SubscriptOperator)
{
    auto it = arr.begin();

    EXPECT_EQ(it[0], 10);
    EXPECT_EQ(it[1], 20);
    EXPECT_EQ(it[2], 30);
    EXPECT_EQ(it[3], 40);
    EXPECT_EQ(it[4], 50);
}

TEST_F(StaticArrayIteratorTest, ArrowOperator)
{
    StaticArray<std::pair<int, int>, 3> pairArr{{1, 2}, {3, 4}, {5, 6}};
    auto it = pairArr.begin();

    EXPECT_EQ((*it).first, 1);
    EXPECT_EQ((*it).second, 2);

    ++it;
    EXPECT_EQ((*it).first, 3);
    EXPECT_EQ((*it).second, 4);
}

TEST_F(StaticArrayIteratorTest, DereferenceOperator)
{
    auto it = arr.begin();

    EXPECT_EQ(*it, 10);

    *it = 999;
    EXPECT_EQ(arr[0], 999);
    EXPECT_EQ(*it, 999);
}

TEST_F(StaticArrayIteratorTest, EqualityOperators)
{
    auto it1 = arr.begin();
    auto it2 = arr.begin();
    auto it3 = arr.end();

    EXPECT_TRUE(it1 == it2);
    EXPECT_FALSE(it1 != it2);
    EXPECT_FALSE(it1 == it3);
    EXPECT_TRUE(it1 != it3);

    ++it1;
    EXPECT_FALSE(it1 == it2);
    EXPECT_TRUE(it1 != it2);
}

TEST_F(StaticArrayIteratorTest, RangeBasedForLoop)
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

TEST_F(StaticArrayIteratorTest, RangeBasedForLoopModification)
{
    for (auto& value : arr) {
        value *= 2;
    }

    EXPECT_EQ(arr[0], 20);
    EXPECT_EQ(arr[1], 40);
    EXPECT_EQ(arr[2], 60);
    EXPECT_EQ(arr[3], 80);
    EXPECT_EQ(arr[4], 100);
}

TEST_F(StaticArrayIteratorTest, EmptyArrayIterator)
{
    StaticArray<int, 0> emptyArr;

    auto begin_it = emptyArr.begin();
    auto end_it = emptyArr.end();

    EXPECT_EQ(begin_it, end_it);

    int count = 0;

    for (const auto& value : emptyArr) {
        ++count;
    }
    EXPECT_EQ(count, 0);
}

TEST_F(StaticArrayIteratorTest, SingleElementArrayIterator)
{
    StaticArray<int, 1> singleArr{42};

    auto begin_it = singleArr.begin();
    auto end_it = singleArr.end();

    EXPECT_NE(begin_it, end_it);
    EXPECT_EQ(*begin_it, 42);

    ++begin_it;
    EXPECT_EQ(begin_it, end_it);

    std::vector<int> values;

    for (const auto& value : singleArr) {
        values.push_back(value);
    }

    EXPECT_EQ(values.size(), 1);
    EXPECT_EQ(values[0], 42);
}

TEST_F(StaticArrayTest, LargeArrayPerformance)
{
    constexpr size_t LARGE_SIZE = 10000;
    StaticArray<int, LARGE_SIZE> largeArr;

    EXPECT_EQ(largeArr.getSize(), LARGE_SIZE);

    for (size_t i = 0; i < LARGE_SIZE; ++i) {
        largeArr.set(i, static_cast<int>(i));
    }

    for (size_t i = 0; i < LARGE_SIZE; ++i) {
        EXPECT_EQ(largeArr[i], static_cast<int>(i));
    }

    size_t count = 0;

    for (const auto& value : largeArr) {
        EXPECT_EQ(value, static_cast<int>(count));
        ++count;
    }

    EXPECT_EQ(count, LARGE_SIZE);
}

TEST_F(StaticArrayTest, MemoryManagement)
{
    {
        StaticArray<int, 1000> arr;
    }

    {
        StaticArray<int, 5> arr1{1, 2, 3, 4, 5};
        StaticArray<int, 5> arr2 = std::move(arr1);
    }
}
