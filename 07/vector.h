#pragma once
#include<limits>
#include <memory>
#include <string.h>

template <class T>
class Allocator
{

    public:
    
        T* allocate (size_t n) 
        {
            if (n > max_size() )
                throw std::bad_alloc();
            
            T* p = static_cast<T*> (operator new (sizeof(T) * n));
            
            return p;
        }

        T* allocate (size_t n, const void*) 
        {
            return allocate (n);
        }


        void deallocate (T* p, size_t n)
        {
            operator delete (p, sizeof(T) * n );
        }


        size_t max_size() const noexcept
        {
            return std::numeric_limits<size_t>::max() / sizeof(T);
        }

        void construct (T* p,  T&& obj)
        {
            
            new (p) T(std::move(obj));
        }


        void destroy (T* p) 
        {
            p->~T(); 
        }

};






template <class T>
class Iterator
    : public std::iterator<std::random_access_iterator_tag, T>
{
    private:

        T* ptr_;
        const bool direct_;


    public:

        explicit Iterator(T* ptr,  bool dir)
            : ptr_(ptr), direct_(dir)
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
                ++ptr_;
            
            else
                --ptr_;

            return *this;
        }

        Iterator& operator++(int)
        {
            if (direct_)
                ++ptr_;

            else    
                --ptr_;
            

            return *this;
        }

        Iterator& operator--()
        {
            if (direct_)
                --ptr_;
            
            else
                ++ptr_;
            

            return *this;
        }
        
        Iterator operator+(size_t n) const 
        { 
            return Iterator(ptr_ + n); 
        }
        
        Iterator& operator+=(size_t n) 
        { 
            ptr_ += n; 
            return *this; 
        }

       
        size_t operator-(const Iterator& other) const 
        { 
            return (static_cast<size_t>(ptr_ - other.ptr_) ); 
        }


        Iterator& operator-=(size_t n) 
        { 
            ptr_ -= n; 
            return *this; 
        }

        
        Iterator operator-(size_t n) const 
        { 
            return Iterator(ptr_ - n); 
        }
};











template <class T, class Alloc = Allocator<T>>
class Vector
{
    private:
        
        Alloc alloc_;
        T* objects_;
        size_t size_;
        size_t capacity_;



    public:
        using iterator = Iterator<T>;

        iterator begin() noexcept
        {
            return iterator(objects_, true);
        }

        iterator end() noexcept
        {
            return iterator(objects_ + size_, true);
        }

        iterator rbegin() noexcept
        {
            return iterator(objects_ + size_ - 1, false);
        }

        iterator rend() noexcept
        {   
            return iterator(objects_ - 1, false);
        }

        Vector(size_t size): objects_(alloc_.allocate(2 * size)), alloc_(), size_(0), capacity_(2 * size)
        {}

        Vector(): objects_(alloc_.allocate(10)), alloc_(), size_(0), capacity_(10)
        {}

        ~Vector()
        {   
            for (size_t i = 0; i < size_; i++)
                alloc_.destroy(objects_ + i);

            alloc_.deallocate(objects_, size_);
        }

        void push_back(const T& obj)
        {
            
            if (capacity_ == size_)
            {    
                auto new_memory = alloc_.allocate(size_ * 2);
                
                for (size_t i = 0; i < size_; i++)
                    alloc_.construct(new_memory + i, std::move(objects_[i]));//1  

                alloc_.deallocate(objects_, size_);
                
                objects_ = new_memory;
                
                capacity_ *= 2;

            }
            
            alloc_.construct(objects_ + size_, static_cast<T>(obj));//2
            
            size_++;
        }

        void push_back(T&& obj)
        {
            if (capacity_ == size_)
            {   
                auto new_memory = alloc_.allocate(size_ * 2);
                
                for (size_t i = 0; i < size_; i++)
                    alloc_.construct(new_memory + i, std::move(objects_[i]));//1

                alloc_.deallocate(objects_, size_);
                
                objects_ = new_memory;
                
                capacity_ *= 2;

            }
            
            alloc_.construct(objects_ + size_, std::move(obj)); //2
            size_++;
        }

        void pop_back()
        {
            alloc_.destroy(objects_ + size_ - 1);
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
                alloc_.destroy(objects_ + i);

            size_ = 0;
        }

        void resize(size_t new_size)
        {
            if (new_size > size_)
            {
                if (new_size >= capacity_)
                {
                    auto new_memory = alloc_.allocate(new_size * 2);
                    
                    for (size_t i = 0; i < size_; i++)
                        alloc_.construct(new_memory + i, std::move(objects_[i]));
                    
                    alloc_.deallocate(objects_, capacity_);
                    
                    objects_ = new_memory;
                    
                    capacity_ = 2 * new_size;
                }
                T t;
                for (size_t i = size_; i < new_size; i++)
                {
                    alloc_.construct (objects_ + i, std::move(t));
                }
                size_ = new_size;
            }
            else
            {
                for (size_t i = new_size; i < size_; i++)
                    alloc_.destroy(objects_ + i);
                    
                size_ = new_size;
            }
                
        }
        
        
        void reserve(size_t add_size)
        {
            auto new_memory = alloc_.allocate(capacity_ + add_size);
            
            for (size_t i = 0; i < size_; i++)
                alloc_.construct(new_memory + i, std::move(objects_[i]));

            alloc_.deallocate(objects_, capacity_);
            
            objects_ = new_memory;
            
            capacity_ += add_size;
        }
        
        size_t capacity()
        {
            return capacity_;
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
