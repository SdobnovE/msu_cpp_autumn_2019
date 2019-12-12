#include <iostream>
#include <string>
#include <ctype.h>

#pragma once

enum class Error 
{ 
    NoError, 
    CorruptedArchive
};

class Serializer
{
    std::ostream& _stream;
    

public:

    Serializer(std::ostream& stream) : _stream(stream){}


    template <typename T>
    Error save(const T &data) { return data.serialize(*this); }


    template <typename T>
    Error operator() (const T& one) const
    {  
        if constexpr (std::is_same<T, std::uint64_t>::value)
        {
            _stream << one;
            return Error::NoError;
        }
        else 
        {
            if constexpr (std::is_same<T, bool>::value)
            {
                if (one)
                    _stream << "true";
                else
                    _stream << "false";

                return Error::NoError;     
            }
            else
                return Error::CorruptedArchive;   
        }
    }


    template <typename T, typename... Args>
    Error operator() (const T& one, const Args&... args) const
    {  
        if constexpr (std::is_same<T, std::uint64_t>::value)
        {
            _stream << one << " ";
            
            if ((*this)(args...) == Error::NoError)
                return Error::NoError;
            else
                return Error::CorruptedArchive;
        }
        else
        {
            if constexpr (std::is_same<T, bool>::value)
            {
                if (one)
                    _stream << "true" << " ";
                else
                    _stream << "false" << " ";

                if ((*this)(args...) == Error::NoError)
                    return Error::NoError;
                else
                    return Error::CorruptedArchive;
            }
            else
                return Error::CorruptedArchive;
        }
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Deserializer
{
    std::istream& _stream;
    
    template<typename T>
    Error take_one(T& one)
    {
        std::string value = "";
        _stream >> value;
        // std::cout << value << std::endl;

        if constexpr (std::is_same<T, std::uint64_t>::value)
        {
            if (!isdigit(value[0]))
                return Error::CorruptedArchive; 
            one = std::stoul (value);
            
        }
        else
        {
            if constexpr (std::is_same<T, bool>::value)
            {
                 
                 if (value == "true")
                    one = true;
                else if (value == "false")
                    one = false;
                else
                    return Error::CorruptedArchive; 
                
            }
            else
                return Error::CorruptedArchive;
        }
        return Error::NoError;
    }
public:
    Deserializer(std::istream& stream): _stream(stream)
    {}
    
    template<typename T>
    Error load(T &data) { return data.deserialize(*this); }

    
    
    template<typename T>
    Error operator()(T &one)
    {
        
        if (_stream.rdbuf()->in_avail() == 0)
            return Error::CorruptedArchive;

        if (take_one(one) != Error::NoError)
            return Error::CorruptedArchive;
        
        return Error::NoError;
    }  

 
 
 
    template<typename T, typename... Args>
    Error operator() (T &one, Args&... args)
    {
        
        if (_stream.rdbuf()->in_avail() == 0)
            return Error::CorruptedArchive;
        
        if (take_one (one) == Error::NoError)
        {
            // std::cout << " HA " << one << std::endl;
            if ((*this)(args...) == Error::NoError)
                return Error::NoError;
            else
                return Error::CorruptedArchive;
        }
        else
            return Error::CorruptedArchive;
        
     
    }  
};