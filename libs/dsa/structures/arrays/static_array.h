#pragma once

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <iostream>

namespace dsa::structures
{
	template<typename T, size_t size>
	class StaticArray
	{
	private:
		T* pElements;

	public:
		StaticArray()
		{
			this->pElements = new T[size]();
		}

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

        // copy constructor
        StaticArray(const StaticArray<T, size>& other)
        {
            this->pElements = new T[size]();

            for (size_t i = 0; i < size; i++) {
                this->pElements[i] = other.pElements[i];
            }
        }

        // move constructor
        StaticArray(StaticArray<T, size>&& other) noexcept
        {
            this->pElements = other.pElements;
            other.pElements = nullptr;
        }

		~StaticArray()
		{
			delete[] this->pElements;
			this->pElements = NULL;
		}

		T& get(const size_t index)
		{
			if (index >= size)
				throw std::out_of_range("Index out of array bounds");

			return this->pElements[index];
		}

		const T& get(const size_t index) const
		{
			if (index >= size)
				throw std::out_of_range("Index out of array bounds");

			return this->pElements[index];
		}

		constexpr int getSize()
		{
			return size;
		}

		T& operator[](const size_t index)
		{
			return this->get(index);
		}

		const T& operator[](const size_t index) const
		{
			return this->get(index);
		}

		T& first()
		{
			return this->get(0);
		}

		T& last()
		{
			return this->get(size - 1);
		}

		void set(const size_t index, T value)
		{
			if (index >= size)
				throw std::out_of_range("Index out of array bounds");

			this->pElements[index] = value;
		}

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

        // copy assignment operator
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

        // move assignment operator
        StaticArray<T, size>& operator=(StaticArray<T, size>&& other) noexcept
        {
            if (this == &other)
                return *this;

            delete[] this->pElements;

            this->pElements = other.pElements;
            other.pElements = nullptr;

            return *this;
        }

		friend std::ostream& operator<<(std::ostream& os, const StaticArray<T, size>& array)
		{
			for (size_t i = 0; i < size; i++)
			{
				os << "Index: " << i << " | " << "Value: " << array.pElements[i] << "\n";
			}

			return os;
		}

		T* begin()
		{
			return this->pElements;
		}

		T* end()
		{
			return this->pElements + size;
		}
	};
}
