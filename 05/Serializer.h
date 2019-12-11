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
    std::ostream * _stream;
    

public:

    Serializer(std::ostream& stream) : _stream(&stream){}


    template <typename T>
    Error save(const T &data) { return data.serialize(*this); }


    template <typename T>
    Error operator() (const T& one) const
    {  
        if (std::is_same<T, std::uint64_t>::value)
        {
            (*_stream) << one;
            return Error::NoError;
        }
        else 
        {
            if (std::is_same<T, bool>::value)
            {
                if (one)
                    (*_stream) << "true";
                else
                    (*_stream) << "false";

                return Error::NoError;     
            }
            else
                return Error::CorruptedArchive;   
        }
    }


    template <typename T, typename... Args>
    Error operator() (const T& one, const Args&... args) const
    {  
        if (std::is_same<T, std::uint64_t>::value)
        {
            (*_stream) << one << "_";
            
            if ((*this)(args...) == Error::NoError)
                return Error::NoError;
            else
                return Error::CorruptedArchive;
        }
        else
        {
            if (std::is_same<T, bool>::value)
            {
                if (one)
                    (*_stream) << "true" << "_";
                else
                    (*_stream) << "false" << "_";

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
    std::istream* _stream;
    template<typename T>
    Error take_one(T& one)
    {
        std::string value = "";
        char t;
        if (std::is_same<T, std::uint64_t>::value)
        {
            
            
            (*_stream) >> t; 
            if (!isdigit (t))
                return Error::CorruptedArchive;

            while ((*_stream).rdbuf()->in_avail() != 0 && t != '_')
            {
                value += t;
                (*_stream) >> t;
            }
            value += t;

            one = std::stoul (value);
            
            
        }
        else
        {
            if (std::is_same<T, bool>::value)
            {
                if ((*_stream).rdbuf()->in_avail() < 4)
                    return Error::CorruptedArchive;

                for (size_t i = 0; i < 4; i++)
                {
                    (*_stream) >> t;
                    value += t;
                }

                if (value == "true")
                {
                    if ((*_stream).rdbuf()->in_avail() == 0)
                    {
                        one = true;
                    }
                    else
                    {
                        (*_stream) >> t;
                        if (t == '_')
                        {
                            one = true;
                        }
                        else
                            return Error::CorruptedArchive;
                    }
                }
                else if (value == "fals")
                {
                    if ((*_stream).rdbuf()->in_avail() == 0)
                    {
                        return Error::CorruptedArchive;
                    }

                    if ((*_stream).rdbuf()->in_avail() == 1)
                    {
                        (*_stream) >> t;
                        if (t == 'e')
                        {
                            one = false;
                        }
                        else
                            return Error::CorruptedArchive;
                    }
                    else
                    {
                        (*_stream) >> t;
                        if (t == 'e')
                        {
                            (*_stream) >> t;
                            if (t == '_')
                                one = false;
                            else
                                return Error::CorruptedArchive;
                        }
                        else
                            return Error::CorruptedArchive;
                    }

                }
                else
                    return Error::CorruptedArchive;  
                
            }
            else
                return Error::CorruptedArchive;
        }
        return Error::NoError;
    }
public:
    Deserializer(std::istream& stream): _stream(&stream)
    {}
    
    template<typename T>
    Error load(T &data) { return data.deserialize(*this); }

    
    
    template<typename T>
    Error operator()(T &one)
    {
        
        if ((*_stream).rdbuf()->in_avail() == 0)
            return Error::CorruptedArchive;

        if (take_one(one) != Error::NoError)
            return Error::CorruptedArchive;
        
        return Error::NoError;
    }  

 
 
 
    template<typename T, typename... Args>
    Error operator() (T &one, Args&... args)
    {
        
        if ((*_stream).rdbuf()->in_avail() == 0)
            return Error::CorruptedArchive;
        
        if (take_one (one) == Error::NoError)
        {
            if ((*this)(args...) == Error::NoError)
                return Error::NoError;
            else
                return Error::CorruptedArchive;
        }
        else
            return Error::CorruptedArchive;
        
     
    }  
};