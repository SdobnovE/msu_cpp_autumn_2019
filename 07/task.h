#include<iostream>
#include<cstring>
#pragma once

template <class T>
class Allocator
{
    private:
        size_t _max_size;
        size_t _size_T;
        T* _memory;
    public:
        Allocator(size_t size): _max_size(size), _size_T(sizeof(T))
        {
            _memory = static_cast<T*>(operator new(_max_size * _size_T));
            if (_memory == nullptr)
                throw std::bad_alloc();
        }

        Allocator(): _max_size(1024), _size_T(sizeof(T))
        {
            _memory = static_cast<T*>(operator new(_max_size * _size_T));
            if (_memory == nullptr)
                throw std::bad_alloc();
        }

        ~Allocator()
        {
            if (_memory != nullptr)
                operator delete (_memory);
        }

        void resize(size_t new_size)
        {
            T* new_memory = static_cast<T*>(operator new(new_size * _size_T));

            if (new_memory == nullptr)
                throw std::bad_alloc(); 
            
            memcpy(new_memory, _memory, _max_size * _size_T);
            
            operator delete (_memory);
            _memory = new_memory;

            _max_size = new_size;
            
        }

        T* get_mem()
        {
            return _memory;
        }

        size_t get_size()
        {
            return _max_size;
        }
};

template <class T>
class Iterator
    : public std::iterator<std::bidirectional_iterator_tag, T>
{
    private:
        T* ptr_;
        T* begin_;
        const bool direct_;
    public:
        explicit Iterator(T* ptr, T* begin,  bool dir)
            : ptr_(ptr), begin_(begin), direct_(dir)
        {
        }

        bool operator==(const Iterator<T>& other) const
        {
            return ptr_ == other.ptr_;
        }

        bool operator!=(const Iterator<T>& other) const
        {
            return !(*this == other);
        }

        T& operator*() const
        {
            return *ptr_;
        }

        Iterator& operator++()
        {
            
            if (direct_)
            {   
                if (ptr_ == nullptr)
                {
                    ptr_ = begin_;
                    return *this; 
                }

                ++ptr_;
            }
            else
            {
                if (ptr_ == begin_)
                {
                    ptr_ = nullptr;
                    return *this;
                }
                    
                --ptr_;
            }

            return *this;
        }

        Iterator& operator++(int)
        {
            if (direct_)
            {   
                if (ptr_ == nullptr)
                {
                    ptr_ = begin_;
                    return *this; 
                }
                 
                ++ptr_;
            }
            else
            {
                if (ptr_ == begin_)
                {
                    ptr_ = nullptr;
                    return *this;
                }
                    
                --ptr_;
            }
            
            return *this;
        }

        Iterator& operator--()
        {
            if (direct_)
            {
                if (ptr_ == begin_)
                {
                    ptr_ = nullptr;
                    return *this;
                }

                --ptr_;
            }
            else
            {   
                if(ptr_ == nullptr)
                {
                    ptr_ = begin_;
                    return *this; 
                }
                
                ++ptr_;
            }
            return *this;
        }
};

template <class T, class Alloc = Allocator<T>>
class Vector
{
    private:
        Alloc alloc_;
        T* objects_;
        size_t size_;

    public:
        using iterator = Iterator<T>;

        iterator begin() noexcept
        {
            return iterator(objects_, objects_ , true);
        }

        iterator end() noexcept
        {
            return iterator(objects_ + size_, objects_, true);
        }

        iterator rbegin() noexcept
        {
            return iterator(objects_ + size_ - 1, objects_, false);
        }

        iterator rend() noexcept
        {
            return iterator(nullptr, objects_, false);
        }

        Vector(size_t size): objects_(alloc_.get_mem()), alloc_(size), size_(0)
        {}

        Vector(): objects_(alloc_.get_mem()), alloc_(1024), size_(0)
        {}

        ~Vector()
        {   
            for (size_t i = 0; i < size_; i++)
                objects_[i].~T();
        }

        void push_back(const T& obj)
        {
            if (alloc_.get_size() == size_)
            {    
                alloc_.resize(size_ * 2);
                objects_ = alloc_.get_mem();
            }

            new (objects_ + size_) T(obj);
            size_++;
        }

        void push_back(T&& obj)
        {
            if (alloc_.get_size() < size_ + 1)
            {    
                alloc_.resize(size_ * 2);
                objects_ = alloc_.get_mem();
            }
            
            objects_[size_] = std::move(obj);
            size_++;
        }

        void pop_back()
        {
            objects_[size_ - 1].~T();
            size_--;   
        }

        bool empty() const
        {
            if (size_ == 0)
                return true;
            else
                return false;
        }

        size_t size() const
        {
            return size_;
        }

        void clear()
        {
            for (size_t i = 0; i < size_; i++)
                objects_[i].~T();

            size_ = 0;
        }

        void resize(size_t new_size)
        {
            if (new_size > size_)
            {
                if (new_size > alloc_.get_size())
                {
                    alloc_.resize(new_size * 2);
                    objects_ = alloc_.get_mem();
                }
                
                for (size_t i = size_; i < new_size; i++)
                {
                    new (objects_ + i) T();
                }
                size_ = new_size;
            }
            else
            {
                for (size_t i = new_size; i < size_; i++)
                    objects_[i].~T();
                size_ = new_size;
            }
            
            
        }
        
        void reserve(size_t add_size)
        {
            
            alloc_.resize(size_ + add_size);
            objects_ = alloc_.get_mem();
        }
        
        size_t capacity()
        {
            return alloc_.get_size();
        }

        T& operator[](size_t i)
        {
            return objects_[i];
        }

        const T& operator[](size_t i) const
        {
            return objects_[i];
        }

};