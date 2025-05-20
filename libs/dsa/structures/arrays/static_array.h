#pragma once

#include <initializer_list>
#include <ostream>

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

			int i = 0;

			for (T it : list)
			{
				if (i >= size)
					return;

				this->pElements[i++] = it;
			}
		}

		~StaticArray()
		{
			delete this->pElements;
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

			int i = 0;

			for (T value : list)
			{
				if (i >= size)
					break;

				this->pElements[i++] = value;
			}

			return *this;
		}

		friend std::ostream& operator<<(std::ostream& os, const StaticArray<T, size>& array)
		{
			for (int i = 0; i < size; i++)
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