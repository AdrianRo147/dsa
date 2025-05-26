#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <iostream>

namespace dsa::structures::arrays
{
    /**
     * @brief Iterator class for StaticArray.
     * @tparam StaticArray Type of static array.
     */
    template<typename StaticArray>
    class StaticArrayIterator
    {
        public:
            using ValueType = typename StaticArray::ValueType;      /// Type of static array elements value.
            using PointerType = ValueType*;                         /// Pointer type to value.
            using ReferenceType = ValueType&;                       /// Reference type to value.

        private:
            PointerType mPtr;                                       /// Pointer to current element.

        public:
            /**
             * @brief Default constructor. Initializes pointer to element.
             * @param ptr Pointer to element.
             */
            StaticArrayIterator(PointerType ptr) : mPtr(ptr) {}

            /**
             * @brief Postfix increment operator. Increments pointer to element.
             * @return Reference to this instance of StaticArrayIterator.
             */
            StaticArrayIterator& operator++()
            {
                this->mPtr++;
                return *this;
            }

            /**
             * @brief Prefix increment operator. Increments pointer to element.
             * @return Instance of iterator.
             */
            StaticArrayIterator operator++(int)
            {
                StaticArrayIterator iterator = *this;
                ++(*this);
                return iterator;
            }

            /**
             * @brief Postfix decrement operator. Decrements pointer to element.
             * @return Reference to this instance of StaticArrayIterator.
             */
            StaticArrayIterator& operator--()
            {
                this->mPtr--;
                return *this;
            }

            /**
             * @brief Prefix decrement operator. Decrements pointer to element.
             * @return Instance of iterator.
             */
            StaticArrayIterator operator--(int)
            {
                StaticArrayIterator iterator = *this;
                --(*this);
                return iterator;
            }

            /**
             * @brief Gets pointer at specific index.
             * @param index Index to get.
             * @return Reference to StaticArray at specific index.
             */
            ReferenceType operator[](int index)
            {
                return this->mPtr[index];
            }

            /**
             * @brief Gets pointer to internal pointer.
             * @return Pointer to StaticArray.
             */
            PointerType operator->()
            {
                return this->mPtr;
            }

            /**
             * @brief Gets reference to dereferenced internal pointer.
             * @return Reference to StaticArray.
             */
            ReferenceType operator*()
            {
                return *this->mPtr;
            }

            /**
             * @brief Equals operator.
             * @param other Other instance of StaticArrayIterator to compare with.
             * @return True if internal pointers equals.
             */
            bool operator==(const StaticArrayIterator& other) const
            {
                return this->mPtr == other.mPtr;
            }

            /**
             * @brief Not equals operator.
             * @param other Other instance of StaticArrayIterator to compare with.
             * @return True if internal pointers do not equals.
             */
            bool operator!=(const StaticArrayIterator& other) const
            {
                return this->mPtr != other.mPtr;
            }
    };

    /**
      * @brief Simple static array implementation
      *
      * Provides basic static array functionality such as setting at index, getting element at index,
      * initializer_list constructor and assignment operator.
      * Elements are stored in heap allocated array
      *
      * @tparam T Type of Elements
      * @tparam size Size of array
      */
    template<typename T, size_t size>
    class StaticArray
    {
        private:
            T* pElements;       /// Pointer to elements array.

        public:
            using ValueType = T;
            using ReferenceType = T&;
            using ConstReferenceType = const T&;
            using PointerType = T*;
            using Iterator = StaticArrayIterator<StaticArray<ValueType, size>>;

        public:
            /**
             * @brief Default constructor. Initializes an empty array.
             */
            StaticArray() : pElements(new ValueType[size]()) {}

            /**
             * @brief Constructs the array from an initializer list.
             * @param list Initializer list of array elements.
             * @throws std::runtime_error if list size does not match array size
             */
            StaticArray(const std::initializer_list<ValueType> list)
            {
                if (size != list.size())
                    throw std::runtime_error("Entered array size does not match template parameter size");

                this->pElements = new ValueType[size];

                size_t i = 0;

                for (ValueType it : list)
                {
                    if (i >= size)
                        return;

                    this->pElements[i++] = it;
                }
            }

            /**
             * @brief Copy constructor. Creates deep copy of another StaticArray.
             * @param other StaticArray to copy from.
             */
            StaticArray(const StaticArray<ValueType, size>& other) : pElements(new ValueType[size])
            {
                for (size_t i = 0; i < size; i++) {
                    this->pElements[i] = other.pElements[i];
                }
            }

            /**
             * @brief Move constructor. Transfers ownership of resources form another StaticArray.
             *
             * Moves the pElements array from one instance to another.
             *
             * @param other StaticArray to move from.
             */
            StaticArray(StaticArray<ValueType, size>&& other) noexcept : pElements(other.pElements)
            {
                other.pElements = nullptr;
            }

            /**
             * @brief Destructor. Releases allocated memory.
             */
            ~StaticArray()
            {
                delete[] this->pElements;
                this->pElements = NULL;
            }

            /**
             * @brief Gets value at specific index.
             * @param index Index of element to get.
             * @throws std::out_of_range if index is out of array bounds.
             * @return Reference to element of template type T.
             */
            ReferenceType get(const size_t index)
            {
                if (index >= size)
                    throw std::out_of_range("Index out of array bounds");

                return this->pElements[index];
            }

            /**
             * @brief Gets const value at specific index.
             * @param index Index of element to get.
             * @throws std::out_of_range if index is out of array bounds.
             * @return Const reference to element of template type T.
             */
            ConstReferenceType get(const size_t index) const
            {
                if (index >= size)
                    throw std::out_of_range("Index out of array bounds");

                return this->pElements[index];
            }

            /**
             * @brief Gets size of array.
             * @return Number of elements.
             */
            constexpr int getSize()
            {
                return size;
            }

            /**
             * @brief Gets element at specific index using operator[].
             * @param index Index of element.
             * @return Reference to element of template type T.
             */
            ReferenceType operator[](const size_t index)
            {
                return this->get(index);
            }

            /**
             * @brief Gets const element at specific index using operator[].
             * @param index Index of element.
             * @return Const reference to element of template type T.
             */
            ConstReferenceType operator[](const size_t index) const
            {
                return this->get(index);
            }

            /**
             * @brief Gets first element.
             * @return Reference to first element of template type T.
             */
            ReferenceType first()
            {
                return this->get(0);
            }

            /**
             * @brief Gets last element.
             * @return Reference to last element of template type T.
             */
            ReferenceType last()
            {
                return this->get(size - 1);
            }

            /**
             * @brief Sets element value at specific index.
             *
             * @param index Index of element to set.
             * @param value Value to set at specific index.
             * @throws std::out_of_range if index is out of array bounds.
             */
            void set(const size_t index, ValueType value)
            {
                if (index >= size)
                    throw std::out_of_range("Index out of array bounds");

                this->pElements[index] = value;
            }

            /**
             * @brief Replace array values by values from std::initializer_list using operator=.
             * @param list Initializer list of elements to set.
             * @throws std::runtime_error if list size does not match array size from template parameter.
             * @return Reference to this StaticArray.
             */
            StaticArray<ValueType, size>& operator=(const std::initializer_list<ValueType>& list)
            {
                if (size != list.size())
                    throw std::runtime_error("Entered array size does not match template parameter size");

                size_t i = 0;

                for (ValueType value : list)
                {
                    if (i >= size)
                        break;

                    this->pElements[i++] = value;
                }

                return *this;
            }

            /**
             * @brief Copy assignment operator.
             * @param other StaticArray to copy from.
             * @return Reference to this StaticArray.
             */
            StaticArray<ValueType, size>& operator=(const StaticArray<ValueType, size>& other)
            {
                if (this == &other)
                    return *this;

                delete[] this->pElements;

                this->pElements = new ValueType[size]();

                for (size_t i = 0; i < size; i++)
                {
                    this->pElements[i] = other.pElements[i];
                }

                return *this;
            }

            /**
             * @brief Move assignment operator.
             * @param other StaticArray to copy from.
             * @return Reference to this StaticArray.
             */
            StaticArray<ValueType, size>& operator=(StaticArray<ValueType, size>&& other) noexcept
            {
                if (this == &other)
                    return *this;

                delete[] this->pElements;

                this->pElements = other.pElements;
                other.pElements = nullptr;

                return *this;
            }

            /**
             * @brief Outputs content of array to stream.
             * @param os Output stream.
             * @param array Array to output.
             * @return Reference to output stream.
             */
            friend std::ostream& operator<<(std::ostream& os, const StaticArray<ValueType, size>& array)
            {
                for (size_t i = 0; i < size; i++)
                {
                    os << "Index: " << i << " | " << "Value: " << array.pElements[i] << "\n";
                }

                return os;
            }

            /**
             * @brief Returns a new instance of StaticArrayIterator which points to first element.
             * @return Instance of StaticArrayIterator.
             */
            Iterator begin()
            {
                return Iterator(this->pElements);
            }

            /**
             * @brief Returns a new instace of StaticArrayIterator which points to last element.
             * @return Instance of StaticArrayIterator.
             */
            Iterator end()
            {
                return Iterator(this->pElements + size);
            }
    };
}
