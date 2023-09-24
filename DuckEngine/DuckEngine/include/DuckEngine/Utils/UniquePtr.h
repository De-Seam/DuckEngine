#pragma once
#include "CoreLight.h"

namespace DE
{
    template<typename T, typename Deleter = std::default_delete<T>>
    struct UniquePtr
    {
        // Constructors
        constexpr UniquePtr() noexcept : m_pointer(nullptr) {}
        explicit UniquePtr(T* ptr) noexcept : m_pointer(ptr) {}

        // Destructor
        ~UniquePtr() { Deleter()(m_pointer); }

        // Move constructor
        UniquePtr(UniquePtr&& other) noexcept : m_pointer(other.m_pointer)
        {
            other.m_pointer = nullptr;
        }

        // Move assignment operator
        UniquePtr& operator=(UniquePtr&& other) noexcept
        {
            if (this != &other)
            {
                Deleter()(m_pointer);
                m_pointer = other.m_pointer;
                other.m_pointer = nullptr;
            }
            return *this;
        }

        // Deleted copy semantics
        UniquePtr(const UniquePtr&) = delete;
        UniquePtr& operator=(const UniquePtr&) = delete;

        // Accessors
        T* Get() const noexcept { return m_pointer; }
        T* operator->() const noexcept { return m_pointer; }

        // Utility functions
        T* Release() noexcept
        {
            T* oldPointer = m_pointer;
            m_pointer = nullptr;
            return oldPointer;
        }

        void Reset(T* newPtr = nullptr) noexcept
        {
            Deleter()(m_pointer);
            m_pointer = newPtr;
        }

    private:
        T* m_pointer;
    };
}
