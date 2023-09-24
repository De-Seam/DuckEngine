#pragma once
#include "CoreLight.h"

#include <cassert>

#define DEFAULT_CAPACITY 12

namespace DE
{
	template<typename T>
	struct Array
	{
	public:
		using value_type = T;
		using size_type = u_size;
		using iterator = T*;
		using const_iterator = const T*;

		Array() : m_size(0), m_capacity(DEFAULT_CAPACITY), m_data(Alloc(m_capacity)) {}

		Array(const T& value, size_type size) : m_size(size), m_capacity(size), m_data(Alloc(m_capacity))
		{
			for (size_type i = 0; i < m_size; ++i) {
				new (&m_data[i]) T(value);
			}
		}

		~Array()
		{
			Clear();
			if (m_data) {
#ifndef _DEBUG //Debugger does it in debug mode
				operator delete[](m_data);
#endif
				m_data = nullptr;
			}
			m_size = 0;
			m_capacity = 0;
		}

		Array(const Array& other) : m_size(other.m_size), m_capacity(other.m_capacity), m_data(Alloc(m_capacity))
		{
			for (size_type i = 0; i < m_size; ++i) {
				if constexpr (std::is_move_constructible_v<T> && !std::is_copy_constructible_v<T>) {
					new (&m_data[i]) T(std::move(other.m_data[i]));  // Note: This will modify other!
				}
				else {
					new (&m_data[i]) T(other.m_data[i]);
				}
			}
		}


		Array(Array&& other) noexcept
			: m_data(other.m_data), m_size(other.m_size), m_capacity(other.m_capacity)
		{
			other.m_data = nullptr;
			other.m_size = 0;
			other.m_capacity = 0;
		}

		Array& operator=(Array&& other) noexcept
		{
			if (this != &other)
			{
				Clear();
				operator delete[](m_data);  // Replace free with delete[] or operator delete[]

				m_data = other.m_data;
				m_size = other.m_size;
				m_capacity = other.m_capacity;

				other.m_data = nullptr;
				other.m_size = 0;
				other.m_capacity = 0;
			}
			return *this;
		}

		Array& operator=(const Array& other)
		{
			if (this == &other) {
				return *this;
			}

			Clear();
			operator delete[](m_data);

			m_size = other.m_size;
			m_capacity = other.m_capacity;
			m_data = Alloc(m_capacity);

			for (size_type i = 0; i < m_size; ++i) {
				if constexpr (std::is_move_constructible_v<T> && !std::is_copy_constructible_v<T>) {
					new (&m_data[i]) T(std::move(other.m_data[i]));  // Note: This will modify other!
				}
				else {
					new (&m_data[i]) T(other.m_data[i]);
				}
			}

			return *this;
		}


		T& operator[](size_type index)
		{
			assert(index < m_size);
			return m_data[index];
		}

		const T& operator[](size_type index) const
		{
			assert(index < m_size);
			return m_data[index];
		}

		iterator begin() { return m_data; }
		const_iterator begin() const { return m_data; }
		const_iterator cbegin() const { return m_data; }

		iterator end() { return m_data + m_size; }
		const_iterator end() const { return m_data + m_size; }
		const_iterator cend() const { return m_data + m_size; }

		// For copy-constructible types
		template<typename U = T, typename std::enable_if<std::is_copy_constructible<U>::value>::type* = nullptr>
		void Add(const T& item)
		{
			if (m_size >= m_capacity)
			{
				Resize(m_capacity * 2);
			}
			new (&m_data[m_size]) T(item);
			++m_size;
		}

		// For move-constructible types
		template<typename U = T, typename std::enable_if<std::is_move_constructible<U>::value>::type* = nullptr>
		void Add(T&& item)
		{
			if (m_size >= m_capacity)
			{
				Resize(m_capacity * 2);
			}
			new (&m_data[m_size]) T(std::move(item));
			++m_size;
		}

		void Remove(size_type index)
		{
			m_data[index].~T();
			std::move(m_data + index + 1, m_data + m_size, m_data + index);
			--m_size;
		}

		void PopBack()
		{
			assert(m_size != 0);
			m_data[--m_size].~T();
		}

		void Clear()
		{
			for (size_type i = 0; i < m_size; ++i) {
				m_data[i].~T();
			}
			m_size = 0;
		}

		void Resize(size_type newSize, const T& item)
		{
			if (newSize > m_size)
			{
				Expand(newSize);
				for (size_type i = m_size; i < newSize; ++i)
				{
					new (&m_data[m_size]) T(item);
					++m_size;
				}
			}
			else if (newSize < m_size)
			{
				Shrink(newSize);
				while (m_size > newSize)
				{
					new (&m_data[m_size]) T(item);
					--m_size;
				}
			}
		}

		void Resize(size_type newSize)
		{
			if (newSize > m_size)
			{
				Expand(newSize);
			}
			else if (newSize < m_size)
			{
				Shrink(newSize);
			}
		}

		void ShrinkToFit()
		{
			Shrink(m_size);
		}

		void Insert(i64 index, const T& item)
		{
			assert(index >= 0 && index <= m_size);
			Add(T()); // Use existing Add method to expand array
			for (i64 i = m_size - 1; i > index; --i)
			{
				m_data[i] = m_data[i - 1];
			}
			m_data[index] = item;
		}

		void FindAndReplace(const T& find_value, const T& replace_value)
		{
			for (i64 i = 0; i < m_size; ++i)
			{
				if (m_data[i] == find_value)
				{
					m_data[i] = replace_value;
				}
			}
		}

		void Reserve(i64 new_capacity)
		{
			if (new_capacity > m_capacity)
			{
				Expand(new_capacity);
			}
		}

		void Swap(Array& other)
		{
			std::swap(m_data, other.m_data);
			std::swap(m_size, other.m_size);
			std::swap(m_capacity, other.m_capacity);
		}

		size_type Size() const { return m_size; }
		size_type Capacity() const { return m_capacity; }
		bool Empty() const { return m_size == 0; }
		T& Front() { return m_data[0]; }
		const T& Front() const { return m_data[0]; }
		T& Back() { return m_data[m_size - 1]; }
		const T& Back() const { return m_data[m_size - 1]; }

	private:
		T* m_data;
		size_type m_size;
		size_type m_capacity;

		T* Alloc(size_type count)
		{
			return static_cast<T*>(operator new[](count * sizeof(T)));
		}

		void Expand(size_type newSize)
		{
			T* newData = Alloc(newSize);
			std::move(m_data, m_data + m_size, newData);
			operator delete[](m_data);
			m_data = newData;
			m_capacity = newSize;
		}

		void Shrink(size_type newSize)
		{
			T* newData = Alloc(newSize);
			std::move(m_data, m_data + newSize, newData);
			operator delete[](m_data);
			m_data = newData;
			m_size = newSize;
			m_capacity = newSize;
		}
	};
}
