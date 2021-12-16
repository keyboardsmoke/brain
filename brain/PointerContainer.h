#pragma once

#include <cstddef>  // for std::size_t

template<typename T>
class pointer_container
{
public:
    pointer_container() = delete;
    pointer_container(T* ptr, const std::size_t sz)
        : pointer_(ptr), size_(sz)
    {}

    T& operator[](const std::size_t idx)
    {
        return pointer_[idx];
    }

    const T& operator[](const std::size_t idx) const
    {
        return pointer_[idx];
    }

    std::size_t size() const
    {
        return size_;
    }

    template<typename Q>
    class iterator
    {
        friend ::pointer_container<Q>;

        Q* current_;

        iterator(Q* ptr)
            : current_(ptr)
        {}

    public:
        iterator(const iterator& itr)
            : current_(itr.current_)
        {}

        iterator& operator=(const iterator& other)
        {
            (*this)(other);
            return *this;
        }

        Q& operator*()
        {
            return *current_;
        }

        const Q& operator*() const
        {
            return *current_;
        }

        Q* operator->()
        {
            return current_;
        }

        const Q* operator->() const
        {
            return current_;
        }

        iterator<Q>& operator++()
        {
            ++current_;
            return *this;
        }

        iterator<Q> operator++(int)
        {
            iterator tmp(*this);
            operator++();
            return tmp;
        }

        iterator<Q>& operator--()
        {
            --current_;
            return *this;
        }

        iterator<Q> operator--(int)
        {
            iterator tmp(*this);
            operator--();
            return tmp;
        }

        bool operator==(const iterator<Q>& other) const
        {
            return current_ == other.current_;
        }

        bool operator!=(const iterator<Q>& other) const
        {
            return !(*this == other);
        }
    };

    iterator<T> begin()
    {
        return iterator<T>(pointer_);
    }

    const iterator<T> begin() const
    {
        return iterator<T>(pointer_);
    }

    iterator<T> end()
    {
        return iterator<T>(pointer_ + size_);
    }

    const iterator<T> end() const
    {
        return iterator<T>(pointer_ + size_);
    }

private:
    T* pointer_;
    std::size_t size_;
};
