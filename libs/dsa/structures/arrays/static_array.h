#pragma once

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <iostream>

namespace dsa::structures::arrays
{
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
            /**
             * @brief Default constructor. Initializes an empty array.
             */
            StaticArray()
            {
                this->pElements = new T[size]();
            }

            /**
             * @brief Constructs the array from an initializer list.
             * @param list Initializer list of array elements.
             * @throws std::runtime_error if list size does not match array size
             */
            StaticArray(const std::initializer_list<T> list)
            {
                if (size != list.size())
                    throw std::runtime_error("Entered array size does not match template parameter size");

                this->pElements = new T[size]();

                size_t i = 0;

                for (T it : list)
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
            StaticArray(const StaticArray<T, size>& other)
            {
                this->pElements = new T[size]();

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
            StaticArray(StaticArray<T, size>&& other) noexcept
            {
                this->pElements = other.pElements;
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
            T& get(const size_t index)
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
            const T& get(const size_t index) const
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
            T& operator[](const size_t index)
            {
                return this->get(index);
            }

            /**
             * @brief Gets const element at specific index using operator[].
             * @param index Index of element.
             * @return Const reference to element of template type T.
             */
            const T& operator[](const size_t index) const
            {
                return this->get(index);
            }

            /**
             * @brief Gets first element.
             * @return Reference to first element of template type T.
             */
            T& first()
            {
                return this->get(0);
            }

            /**
             * @brief Gets last element.
             * @return Reference to last element of template type T.
             */
            T& last()
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
            void set(const size_t index, T value)
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
            StaticArray<T, size>& operator=(const std::initializer_list<T>& list)
            {
                if (size != list.size())
                    throw std::runtime_error("Entered array size does not match template parameter size");

                size_t i = 0;

                for (T value : list)
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
            StaticArray<T, size>& operator=(const StaticArray<T, size>& other)
            {
                if (this == other)
                    return *this;

                delete[] this->pElements;

                this->pElements = new T[size]();

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
            StaticArray<T, size>& operator=(StaticArray<T, size>&& other) noexcept
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
            friend std::ostream& operator<<(std::ostream& os, const StaticArray<T, size>& array)
            {
                for (size_t i = 0; i < size; i++)
                {
                    os << "Index: " << i << " | " << "Value: " << array.pElements[i] << "\n";
                }

                return os;
            }

            /**
             * @brief Gets pointer to first element (for range-based for loops).
             * @return Pointer to first element.
             */
            T* begin()
            {
                return this->pElements;
            }

            /**
             * @brief Gets pointer to last element (for range-based for loops).
             * @return Pointer to last element.
             */
            T* end()
            {
                return this->pElements + size;
            }
    };
}
