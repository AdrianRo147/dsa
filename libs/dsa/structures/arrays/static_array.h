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
		StaticArray();
		StaticArray(const std::initializer_list<T> list);
		~StaticArray();

		T& get(const size_t index);
		const T& get(const size_t index) const;
		constexpr int getSize();
		T& operator[](const size_t index);
		const T& operator[](const size_t index) const;
		T& first();
		T& last();

		void set(const size_t index, T value);
		StaticArray<T, size>& operator=(const std::initializer_list<T>& list);

		friend std::ostream& operator<<(std::ostream& os, const StaticArray<T, size>& array)
		{
			for (int i = 0; i < size; i++)
			{
				os << "Index: " << i << " | " << "Value: " << array.pElements[i] << "\n";
			}

			return os;
		}

		T* begin();
		T* end();
	};

	template<typename T, size_t size>
	StaticArray<T, size>::StaticArray()
	{
		this->pElements = new T[size]();
	}

	template<typename T, size_t size>
	inline StaticArray<T, size>::StaticArray(const std::initializer_list<T> list)
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

	template<typename T, size_t size>
	inline StaticArray<T, size>::~StaticArray()
	{
		delete this->pElements;
		this->pElements = NULL;
	}

	template<typename T, size_t size>
	T& StaticArray<T, size>::get(const size_t index)
	{
		if (index >= size)
			throw std::out_of_range("Index out of array bounds");

		return this->pElements[index];
	}

	template<typename T, size_t size>
	const T& StaticArray<T, size>::get(const size_t index) const
	{
		if (index >= size)
			throw std::out_of_range("Index out of array bounds");

		return this->pElements[index];
	}

	template<typename T, size_t size>
	constexpr inline int StaticArray<T, size>::getSize()
	{
		return size;
	}

	template<typename T, size_t size>
	T& StaticArray<T, size>::operator[](size_t index)
	{
		return this->get(index);
	}

	template<typename T, size_t size>
	const T& StaticArray<T, size>::operator[](const size_t index) const
	{
		return this->get(index);
	}

	template<typename T, size_t size>
	T& StaticArray<T, size>::first()
	{
		return this->get(0);
	}

	template<typename T, size_t size>
	T& StaticArray<T, size>::last()
	{
		return this->get(size - 1);
	}

	template<typename T, size_t size>
	inline void StaticArray<T, size>::set(const size_t index, T value)
	{
		if (index >= size)
			throw std::out_of_range("Index out of array bounds");

		this->pElements[index] = value;
	}

	template<typename T, size_t size>
	inline StaticArray<T, size>& StaticArray<T, size>::operator=(const std::initializer_list<T>& list)
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

	template<typename T, size_t size>
	T* StaticArray<T, size>::begin()
	{
		return this->pElements;
	}

	template<typename T, size_t size>
	T* StaticArray<T, size>::end()
	{
		return this->pElements + size;
	}
}