#include <initializer_list>
#include <stdexcept>
#include <iostream>

namespace dsa::structures::arrays
{
    /**
     * @brief A simple dynamic array implementation.
     *
     * Provides basic dynamic array functionality such as adding, removing, and accessing elements.
     * Elements are stored in a contiguous memory block and the array resizes as needed.
     *
     * @tparam T Type of elements stored in the array.
     */
    template<typename T>
    class DynamicArray
    {
        private:
            T* pElements;      /// Pointer to the array elements.
            size_t mSize;      /// Number of elements in the array.

        public:
            /**
             * @brief Default constructor. Initializes an empty array.
             */
            DynamicArray()
            {
                this->mSize = 0;
                this->pElements = nullptr;
            }

            /**
             * @brief Constructs the array from an initializer list.
             * @param array Initializer list of elements to populate the array.
             */
            DynamicArray(std::initializer_list<T> array)
            {
                this->mSize = array.size();
                this->pElements = new T[this->mSize]();

                int i = 0;

                for (T it : array)
                {
                    if (i >= this->mSize)
                        break;

                    this->pElements[i++] = it;
                }
            }

            /**
             * @brief Copy constructor. Creates a deep copy of another DynamicArray.
             * @param other The DynamicArray to copy from.
             */
            DynamicArray(const DynamicArray<T>& other)
            {
                this->mSize = other.mSize;
                this->pElements = new T[this->mSize]();

                for (int i = 0; i < this->mSize; i++)
                {
                    this->pElements[i] = other.pElements[i];
                }
            }

            /**
             * @brief Destructor. Releases allocated memory.
             */
            ~DynamicArray()
            {
                if (this->mSize != 0)
                {
                    delete[] this->pElements;
                    this->pElements = nullptr;
                }
            }

            /**
             * @brief Move constructor. Transfers ownership of resources from another DynamicArray.
             *
             * Moves the internal array pointer and size from the source DynamicArray to this instance.
             * The source DynamicArray is left in a valid but empty state.
             *
             * @param other The DynamicArray to move from.
             */
            DynamicArray(DynamicArray<T>&& other) noexcept
            {
                this->mSize = other.mSize;
                this->pElements = other.pElements;

                other.mSize = 0;
                other.pElements = nullptr;
            }

            /**
             * @brief Returns a reference to the element at the specified index.
             * @param index Index of the element to access.
             * @return Reference to the element.
             * @throws std::out_of_range if index is out of bounds.
            */
            T& get(const size_t index)
            {
                if (index >= this->mSize)
                    throw std::out_of_range("Index out of array bounds");

                return this->pElements[index];
            }

            /**
             * @brief Returns a const reference to the element at the specified index.
             * @param index Index of the element to access.
             * @return Const reference to the element.
             * @throws std::out_of_range if index is out of bounds.
             */
            const T& get(const size_t index) const
            {
                if (index >= this->mSize)
                    throw std::out_of_range("Index out of array bounds");

                return this->pElements[index];
            }

            /**
             * @brief Array subscript operator.
             * @param index Index of the element to access.
             * @return Reference to the element.
             */
            T& operator[](const size_t index)
            {
                return this->get(index);
            }

            /**
             * @brief Array subscript operator (const version).
             * @param index Index of the element to access.
             * @return Const reference to the element.
             */
            const T& operator[](const size_t index) const
            {
                return this->get(index);
            }

            /**
             * @brief Returns the number of elements in the array.
             * @return Number of elements.
             */
            constexpr size_t getSize() const
            {
                return this->mSize;
            }

            /**
             * @brief Returns a reference to the first element.
             * @return Reference to the first element.
             * @throws std::out_of_range if the array is empty.
             */
            T& first()
            {
                return this->get(0);
            }

            /**
             * @brief Returns a const reference to the first element.
             * @return Const reference to the first element.
             * @throws std::out_of_range if the array is empty.
             */
            const T& first() const
            {
                return this->get(0);
            }

            /**
             * @brief Returns a reference to the last element.
             * @return Reference to the last element.
             * @throws std::out_of_range if the array is empty.
             */
            T& last()
            {
                return this->get(this->mSize - 1);
            }

            /**
             * @brief Returns a const reference to the last element.
             * @return Const reference to the last element.
             * @throws std::out_of_range if the array is empty.
             */
            const T& last() const
            {
                return this->get(this->mSize - 1);
            }

            /**
             * @brief Sets the value at the specified index.
             * @param index Index of the element to set.
             * @param value Value to assign.
             * @throws std::out_of_range if index is out of bounds.
             */
            void set(size_t index, T value)
            {
                if (index >= this->mSize)
                    throw std::out_of_range("Index out of array bounds");

                this->pElements[index] = value;
            }

            /**
             * @brief Adds an element to the end of the array.
             * @param value Value to add.
             */
            void addLast(T value)
            {
                if (this->mSize == 0)
                {
                    this->pElements = new T[1];
                    this->pElements[0] = value;
                    this->mSize++;

                    return;
                }

                T* temp;
                temp = new T[this->mSize + 1];

                for (size_t i = 0; i < this->mSize; i++)
                {
                    temp[i] = this->pElements[i];
                }

                temp[this->mSize] = value;

                this->mSize++;

                delete[] this->pElements;

                this->pElements = temp;
            }

            /**
             * @brief Adds an element to the beginning of the array.
             * @param value Value to add.
             */
            void addFirst(T value)
            {
                if (this->mSize == 0)
                {
                    this->pElements = new T[1];
                    this->pElements[0] = value;
                    this->mSize++;

                    return;
                }

                T* temp;
                temp = new T[this->mSize + 1];

                temp[0] = value;

                for (size_t i = 0; i < this->mSize; i++)
                {
                    temp[i + 1] = this->pElements[i];
                }

                this->mSize++;

                delete[] this->pElements;

                this->pElements = temp;
            }

            /**
             * @brief Removes the last element from the array.
             * @throws std::runtime_error if the array is empty.
             */
            void removeLast()
            {
                if (this->mSize == 0)
                    throw std::runtime_error("Cannot remove item when no item is present in array");

                if (this->mSize == 1)
                {
                    delete[] this->pElements;
                    this->pElements = nullptr;
                    this->mSize--;

                    return;
                }

                T* temp;
                temp = new T[this->mSize - 1];

                for (size_t i = 0; i < this->mSize - 1; i++)
                {
                    temp[i] = this->pElements[i];
                }

                delete[] this->pElements;

                this->pElements = temp;

                this->mSize--;
            }

            /**
             * @brief Removes the first element from the array.
             * @throws std::runtime_error if the array is empty.
             */
            void removeFirst()
            {
                if (this->mSize == 0)
                    throw std::runtime_error("Cannot remove item when no item is present in array");

                if (this->mSize == 1)
                {
                    delete[] this->pElements;
                    this->pElements = nullptr;
                    this->mSize--;

                    return;
                }

                T* temp;
                temp = new T[this->mSize - 1];

                for (size_t i = 0; i < this->mSize - 1; i++)
                {
                    temp[i] = this->pElements[i + 1];
                }

                delete[] this->pElements;

                this->pElements = temp;

                this->mSize--;
            }

            /**
             * @brief Removes the element at the specified index.
             * @param index Index of the element to remove.
             * @throws std::out_of_range if index is out of bounds.
             */
            void removeAt(size_t index)
            {
                if (index >= this->mSize)
                    throw std::out_of_range("Index out of array bounds");

                if (this->mSize == 1)
                {
                    delete[] this->pElements;
                    this->pElements = nullptr;
                    this->mSize--;

                    return;
                }

                T* temp;
                temp = new T[this->mSize - 1];

                for (size_t i = 0; i < this->mSize; i++)
                {
                    if (i == index)
                        continue;

                    if (i < index)
                        temp[i] = this->pElements[i];

                    if (i > index)
                        temp[i - 1] = this->pElements[i];
                }

                delete[] this->pElements;

                this->pElements = temp;

                this->mSize--;
            }

            /**
             * @brief Copy assignment operator.
             * @param other The DynamicArray to copy from.
             * @return Reference to this DynamicArray.
             */
            DynamicArray<T>& operator=(const DynamicArray<T>& other)
            {
                if (this == &other)
                    return *this;

                delete[] this->pElements;

                this->mSize = other.mSize;
                this->pElements = new T[this->mSize]();

                for (size_t i = 0; i < this->mSize; i++)
                {
                    this->pElements[i] = other.pElements[i];
                }

                return *this;
            }

            /**
             * @brief Move assignment operator.
             * @param other The DynamicArray to move from.
             * @return Reference to this DynamicArray.
             */
            DynamicArray<T>& operator=(DynamicArray<T>&& other) noexcept
            {
                if (this == &other)
                    return *this;

                delete[] this->pElements;

                this->mSize = other.mSize;
                this->pElements = other.pElements;

                other.mSize = 0;
                other.pElements = nullptr;

                return *this;
            }

            /**
             * @brief Assignment operator from an initializer list.
             * @param list Initializer list of elements to assign.
             * @return Reference to this DynamicArray.
             */
            DynamicArray<T>& operator=(const std::initializer_list<T>& list)
            {
                if (list.size() == 0)
                {
                    delete[] this->pElements;
                    this->pElements = nullptr;
                    this->mSize = 0;

                    return *this;
                }

                delete[] this->pElements;

                this->mSize = list.size();

                this->pElements = new T[this->mSize];

                int i = 0;

                for (T it : list)
                {
                    if (i >= this->mSize)
                        break;

                    this->pElements[i++] = it;
                }

                return *this;
            }

            /**
             * @brief Outputs the contents of the array to a stream.
             * @param os Output stream.
             * @param array The DynamicArray to output.
             * @return Reference to the output stream.
             */
            friend std::ostream& operator<<(std::ostream& os, const DynamicArray<T>& array)
            {
                for (size_t i = 0; i < array.mSize; i++)
                {
                    os << "Index: " << i << " | Value: " << array.pElements[i] << std::endl;
                }

                return os;
            }

            /**
             * @brief Returns a pointer to the first element (for range-based for loops).
             * @return Pointer to the first element.
             */
            T* begin()
            {
                return this->pElements;
            }

            /**
             * @brief Returns a pointer past the last element (for range-based for loops).
             * @return Pointer past the last element.
             */
            T* end()
            {
                return this->pElements + this->mSize;
            }
    };
}
