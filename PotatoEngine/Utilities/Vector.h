#pragma once
#include "CommonHeaders.h"

namespace PotatoEngine::utl {

// a vector class similar to std::vector with basic functionality
// the user can specify in the template argument whether they want
// element's destructor to be called when being removed or while
// clearing/destrucing the vector
template<typename T, bool destruct = true>
class vector
{
public:
	// default constructor. doesn't allocate memory
	vector() = default;

	// constructor resizes the vector and initializes 'count' items
	constexpr explicit vector(u64 count)
	{
		resize(count);
	}

	// constructor resizes the fector and initializes 'count' items using 'value'
	constexpr explicit vector(u64 count, const T& value)
	{
		resize(count, value);
	}

	// copy-constructor. constructs by copying another vector
	// the items in the copied vector must be copyable
	constexpr vector(const vector& o)
	{
		*this = o;
	}

	// move-constructor. constructs by moving another vector
	// the original vector will be empty after move
	constexpr vector(vector&& o)
		: _capacity{ o._capacity }, _size{ o._size }, _data{ o._data }
	{
		o.reset();
	}

	// copy-assignment operator. clears this vector and copies items
	// from another vector. the items must be copyable
	constexpr vector& operator=(const vector& o)
	{
		assert(this != std::addressof(o));
		if (this != std::addressof(o))
		{
			clear();
			reserve(o._size);
			for (auto& item : o)
			{
				emplace_back(item);
			}
			assert(_size == o._size);
		}

		return *this;
	}

	// move-assignment operator. frees all resources in this vector and
	// moves the other vector into this one
	constexpr vector& operator=(vector&& o)
	{
		assert(this != std::addressof(o));
		if (this != std::addressof(o))
		{
			destroy();
			move(o);
		}

		return *this;
	}

	// destructs the vector and its items as specified in template argument
	~vector() { destroy(); }

	// insert an item at the end of the vector by copying 'value'
	constexpr void push_back(const T& value)
	{
		emplace_back(value);
	}

	// insert an item at the end of the vectory by moving 'value'
	constexpr void push_back(T&& value)
	{
		emplace_back(std::move(value));
	}

	// copy- or move-constructs an item at the end of the vector
	template<typename... params>
	constexpr decltype(auto) emplace_back(params&&... p)
	{
		if (_size == _capacity)
		{
			reserve(((_capacity + 1) * 3) >> 1); // reserve 50% more
		}
		assert(_size < _capacity);

		T *const item{ new (std::addressof(_data[_size])) T(std::forward<params>(p)...) };
		++_size;
		return *item;
	}

	// resize the vector and initializes new items with their default value
	constexpr void resize(u64 new_size)
	{
		static_assert(std::is_default_constructible<T>::value,
			"Type must be default-constructible.");

		if (new_size > _size)
		{
			reserve(new_size);
			while (_size < new_size)
			{
				emplace_back();
			}
		}
		else if (new_size < _size)
		{
			if constexpr (destruct)
			{
				destruct_range(new_size, _size);
			}

			_size = new_size;
		}

		// do nothing if new_size == _size
		assert(new_size == _size);
	}

	// resize the vector and initializes new items by copying 'value'
	constexpr void resize(u64 new_size, const T& value)
	{
		static_assert(std::is_copy_constructible<T>::value,
			"Type must be copy-constructible.");

		if (new_size > _size)
		{
			reserve(new_size);
			while (_size < new_size)
			{
				emplace_back(value);
			}
		}
		else if (new_size < _size)
		{
			if constexpr (destruct)
			{
				destruct_range(new_size, _size);
			}

			_size = new_size;
		}

		// do nothing if new_size == _size
		assert(new_size == _size);
	}

	// allocates memory to contain the specified number of items
	constexpr void reserve(u64 new_capacity)
	{
		if (new_capacity > _capacity)
		{
			// NOTE: realloc() will automatically copy the data in the buffer
			//		 if a new region of memory is allocated
			void* new_buffer{ realloc(_data, new_capacity * sizeof(T)) };
			assert(new_buffer);
			if (new_buffer)
			{
				_data = static_cast<T*>(new_buffer);
				_capacity = new_capacity;
			}
		}
	}

	// removes the item at specified index
	constexpr T *const erase(u64 index)
	{
		assert(_data && index < _size);
		return erase(std::addressof(_data[index]));
	}

	// removes the item at specified location
	constexpr T *const erase(T *const item)
	{
		assert(_data && item >= std::addressof(_data[0]) &&
			item < std::addressof(_data[_size]));
		if constexpr (destruct) item->~T();
		--_size;
		if (item < std::addressof(_data[_size]))
		{
			memcpy(item, item + 1, (std::addressof(_data[_size]) - item) * sizeof(T));
		}

		return item;
	}

	// same as erase() but faster because it just copies the last item
	constexpr T* const erase_unordered(u64 index)
	{
		assert(_data && index < _size);
		return erase_unordered(std::addressof(_data[index]));
	}

	// same as erase() but faster because it just copies the last item
	constexpr T* const erase_unordered(T* const item)
	{
		assert(_data && item >= std::addressof(_data[0]) &&
			item < std::addressof(_data[_size]));
		if constexpr (destruct) item->~T();
		--_size;
		if (item < std::addressof(_data[_size]))
		{
			memcpy(item, std::addressof(_data[_size]), sizeof(T));
		}

		return item;
	}

	// clears the vector and destructs items as specified in template argument
	constexpr void clear()
	{
		if constexpr (destruct)
		{
			destruct_range(0, _size);
		}
		_size = 0;
	}

	// swaps two vectors
	constexpr void swap(vector& o)
	{
		if (this != std::addressof(o))
		{
			auto temp(std::move(o));
			o.move(*this);
			move(temp);
		}
	}

	// pointer to the start of data. might be null
	[[nodiscard]] constexpr T* data()
	{
		return _data;
	}

	// pointer to the start data. might be null
	[[nodiscard]] constexpr T* const data() const
	{
		return _data;
	}

	// returns true if vector is empty
	[[nodiscard]] constexpr bool empty() const
	{
		return _size == 0;
	}

	// return the number of items in the vector
	[[nodiscard]] constexpr u64 size() const
	{
		return _size;
	}

	// returns the current capacity of the vector
	[[nodiscard]] constexpr u64 capacity() const
	{
		return _capacity;
	}

	// indexing operator. returns a reference to the item at specified index
	[[nodiscard]] constexpr T& operator[](u64 index)
	{
		assert(_data && index < _size);
		return _data[index];
	}

	// indexing operator. returns a constant reference to the item at specified index
	[[nodiscard]] constexpr const T& operator[](u64 index) const
	{
		assert(_data && index < _size);
		return _data[index];
	}

	// returns a reference to the first item. will fault the application if called
	// when the vector is empty
	[[nodiscard]] constexpr T& front()
	{
		assert(_data && _size);
		return _data[0];
	}

	// returns a constant reference to the first item. will fault the application 
	// if called when the vector is empty
	[[nodiscard]] constexpr const T& front() const
	{
		assert(_data && _size);
		return _data[0];
	}

	// returns a reference to the last item. will fault the application if called
	// when the vector is empty
	[[nodiscard]] constexpr T& back()
	{
		assert(_data && _size);
		return _data[_size - 1];
	}

	// returns a constant reference to the last item. will fault the application 
	// if called when the vector is empty
	[[nodiscard]] constexpr const T& back() const
	{
		assert(_data && _size);
		return _data[_size - 1];
	}

	// returns a pointer to the first item. returns null when vector is empty
	[[nodiscard]] constexpr T* begin()
	{
		//assert(_data);
		return std::addressof(_data[0]);
	}

	// returns a constant pointer to the first item. returns null when vector is empty
	[[nodiscard]] constexpr const T* begin() const
	{
		//assert(_data);
		return std::addressof(_data[0]);
	}

	// returns a pointer to the last item. returns null when vector is empty
	[[nodiscard]] constexpr T* end()
	{
		//assert(_data);
		assert(!(_data == nullptr && _size > 0));
		return std::addressof(_data[_size]);
	}

	// returns a constant pointer to the last item. returns null when vector is empty
	[[nodiscard]] constexpr const T* end() const
	{
		//assert(_data);
		assert(!(_data == nullptr && _size > 0));
		return std::addressof(_data[_size]);
	}

private:
	constexpr void move(vector& o)
	{
		_capacity = o._capacity;
		_size = o._size;
		_data = o._data;
		o.reset();
	}

	constexpr void reset()
	{
		_capacity = 0;
		_size = 0;
		_data = nullptr;
	}

	constexpr void destruct_range(u64 first, u64 last)
	{
		assert(destruct);
		assert(first <= _size && last <= _size && first <= last);
		if (_data)
		{
			for (; first != last; ++first)
			{
				_data[first].~T();
			}
		}
	}

	constexpr void destroy()
	{
		assert([&] { return _capacity ? _data != nullptr : _data == nullptr; }());
		clear();
		_capacity = 0;
		if (_data) free(_data);
		_data = nullptr;
	}

	u64 _capacity{ 0 };
	u64 _size{ 0 };
	T* _data{ nullptr };
};
}