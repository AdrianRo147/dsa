#pragma once

#include <initializer_list>

namespace dsa::structures
{
	template<typename T>
	class DynamicArray
	{
	private:
		T* pElements;
		size_t mSize;

	public:
		DynamicArray()
		{
			this->mSize = 0;
			this->pElements = nullptr;
		}

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

		DynamicArray(const DynamicArray<T>& other)
		{
			this->mSize = other.mSize;
			this->pElements = new T[this->mSize]();

			for (int i = 0; i < this->mSize; i++)
			{
				this->pElements[i] = other.pElements[i];
			}
		}
		~DynamicArray()
		{
			if (this->mSize != 0)
			{
				delete[] this->pElements;
				this->pElements = nullptr;
			}
		}

		DynamicArray(DynamicArray<T>&& other) noexcept
		{
			this->mSize = other.mSize;
			this->pElements = other.pElements;

			other.mSize = 0;
			other.pElements = nullptr;
		}
		T& get(const size_t index)
		{
			if (index >= this->mSize || index < 0)
				throw std::out_of_range("Index out of array bounds");

			return this->pElements[index];
		}

		const T& get(const size_t index) const
		{
			if (index >= this->mSize || index < 0)
				throw std::out_of_range("Index out of array bounds");

			return this->pElements[index];
		}

		T& operator[](const size_t index)
		{
			return this->get(index);
		}

		const T& operator[](const size_t index) const
		{
			return this->get(index);
		}

		constexpr size_t getSize()
		constexpr size_t getSize() const
		{
			return this->mSize;
		}

		T& first()
		{
			return this->get(0);
		}

		const T& first() const
		{
			return this->get(0);
		}

		T& last()
		{
			return this->get(this->mSize - 1);
		}

		const T& last() const
		{
			return this->get(this->mSize - 1);
		}

		void set(size_t index, T value)
		{
			if (index >= this->mSize)
				throw std::out_of_range("Index out of array bounds");

			this->pElements[index] = value;
		}

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

			for (int i = 0; i < this->mSize; i++)
			{
				temp[i] = this->pElements[i];
			}

			temp[this->mSize] = value;

			this->mSize++;

			delete[] this->pElements;

			this->pElements = temp;
		}

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

			for (int i = 0; i < this->mSize; i++)
			{
				temp[i + 1] = this->pElements[i];
			}

			this->mSize++;

			delete[] this->pElements;

			this->pElements = temp;
		}

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

			for (int i = 0; i < this->mSize - 1; i++)
			{
				temp[i] = this->pElements[i];
			}

			delete[] this->pElements;

			this->pElements = temp;

			this->mSize--;
		}

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

			for (int i = 0; i < this->mSize - 1; i++)
			{
				temp[i] = this->pElements[i + 1];
			}

			delete[] this->pElements;

			this->pElements = temp;

			this->mSize--;
		}

		void removeAt(size_t index)
		{
			if (this->mSize == 1)
			{
				delete[] this->pElements;
				this->pElements = nullptr;
				this->mSize--;
				return;
			}

			T* temp;
			temp = new T[this->mSize];

			for (int i = 0; i < this->mSize; i++)
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
		DynamicArray<T>& operator=(const std::initializer_list<T>& list)
		{
			delete this->pElements;
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

		friend std::ostream& operator<<(std::ostream& os, const DynamicArray<T>& array)
		{
			for (int i = 0; i < array.mSize; i++)
			{
				os << "Index: " << i << " | Value: " << array.pElements[i] << std::endl;
			}

			return os;
		}

		T* begin()
		{
			return this->pElements;
		}

		T* end()
		{
			return this->pElements + this->mSize;
		}
	};
}