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
		DynamicArray();
		DynamicArray(std::initializer_list<T> array);
		~DynamicArray();

		T& get(const size_t index);
		const T& get(const size_t index) const;
		T& operator[](const size_t index);
		const T& operator[](const size_t index) const;
		constexpr size_t getSize();
		T& first();
		const T& first() const;
		T& last();
		const T& last() const;

		void set(size_t index, T value);
		void addLast(T value);
		void addFirst(T value);

		void removeLast();
		void removeFirst();
		void removeAt(size_t index);

		DynamicArray<T>& operator=(const std::initializer_list<T>& list);

		friend std::ostream& operator<<(std::ostream& os, const DynamicArray<T>& array)
		{
			for (int i = 0; i < array.mSize; i++)
			{
				os << "Index: " << i << " | Value: " << array.pElements[i] << std::endl;
			}

			return os;
		}

		T* begin();
		T* end();
	};

	template<typename T>
	inline DynamicArray<T>::DynamicArray()
	{
		this->mSize = 0;
	}

	template<typename T>
	inline DynamicArray<T>::DynamicArray(std::initializer_list<T> array)
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

	template<typename T>
	inline DynamicArray<T>::~DynamicArray()
	{
		if (this->mSize != 0)
		{
			delete this->pElements;
			this->pElements = NULL;
		}
	}

	template<typename T>
	inline T& DynamicArray<T>::get(const size_t index)
	{
		if (index >= this->mSize || index < 0)
			throw std::out_of_range("Index out of array bounds");

		return this->pElements[index];
	}

	template<typename T>
	inline const T& DynamicArray<T>::get(const size_t index) const
	{
		if (index >= this->mSize || index < 0)
			throw std::out_of_range("Index out of array bounds");

		return this->pElements[index];
	}

	template<typename T>
	inline T& DynamicArray<T>::operator[](const size_t index)
	{
		return this->get(index);
	}

	template<typename T>
	const inline T& DynamicArray<T>::operator[](const size_t index) const
	{
		return this->get(index);
	}

	template<typename T>
	inline constexpr size_t DynamicArray<T>::getSize()
	{
		return this->mSize;
	}

	template<typename T>
	inline T& DynamicArray<T>::first()
	{
		return this->pElements[0];
	}

	template<typename T>
	inline const T& DynamicArray<T>::first() const
	{
		return this->pElements[0];
	}

	template<typename T>
	inline T& DynamicArray<T>::last()
	{
		return this->pElements[this->mSize - 1];
	}

	template<typename T>
	inline const T& DynamicArray<T>::last() const
	{
		return this->pElements[this->mSize - 1];
	}

	template<typename T>
	inline void DynamicArray<T>::set(size_t index, T value)
	{
		if (index >= this->mSize)
			throw std::out_of_range("Index out of array bounds");

		this->pElements[index] = value;
	}

	template<typename T>
	inline void DynamicArray<T>::addLast(T value)
	{
		if (this->mSize == 0)
		{
			this->pElements = new T[1];
			this->pElements[0] = value;
			this->mSize++;

			return;
		}

		T * temp;
		temp = new T[this->mSize + 1];

		for (int i = 0; i < this->mSize; i++)
		{
			temp[i] = this->pElements[i];
		}

		temp[this->mSize] = value;

		this->mSize++;

		delete this->pElements;

		this->pElements = temp;
	}

	template<typename T>
	inline void DynamicArray<T>::addFirst(T value)
	{
		if (this->mSize == 0)
		{
			this->pElements = new T[1];
			this->pElements[0] = value;
			this->mSize++;

			return;
		}

		T * temp;
		temp = new T[this->mSize + 1];

		temp[0] = value;

		for (int i = 0; i < this->mSize; i++)
		{
			temp[i + 1] = this->pElements[i];
		}

		this->mSize++;

		delete this->pElements;

		this->pElements = temp;
	}

	template<typename T>
	inline void DynamicArray<T>::removeLast()
	{
		if (this->mSize == 0)
			throw std::runtime_error("Cannot remove item when no item is present in array");

		T * temp;
		temp = new T[this->mSize - 1];

		for (int i = 0; i < this->mSize - 1; i++)
		{
			temp[i] = this->pElements[i];
		}

		delete this->pElements;

		this->pElements = temp;

		this->mSize--;
	}

	template<typename T>
	inline void DynamicArray<T>::removeFirst()
	{
		if (this->mSize == 0)
			throw std::runtime_error("Cannot remove item when no item is present in array");

		T* temp;
		temp = new T[this->mSize - 1];

		for (int i = 0; i < this->mSize - 1; i++)
		{
			temp[i] = this->pElements[i + 1];
		}

		delete this->pElements;

		this->pElements = temp;

		this->mSize--;
	}

	template<typename T>
	inline void DynamicArray<T>::removeAt(size_t index)
	{
		T * temp;
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

		delete this->pElements;

		this->pElements = temp;

		this->mSize--;
	}

	template<typename T>
	inline DynamicArray<T>& DynamicArray<T>::operator=(const std::initializer_list<T>& list)
	{
		delete this->pElements;

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

	template<typename T>
	inline T* DynamicArray<T>::begin()
	{
		return this->pElements;
	}

	template<typename T>
	inline T* DynamicArray<T>::end()
	{
		return this->pElements + this->mSize;
	}
}