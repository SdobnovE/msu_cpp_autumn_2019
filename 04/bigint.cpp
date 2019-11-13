#include<iostream>
#include"bigint.h"
using namespace std;

BigInt::BigInt(): _len(2), _currLen(1), _number(new int8_t[2]), _sign(true)
{
    _number[0] = 0;
}



BigInt::BigInt(int64_t num): _sign(num >= 0)
{
    if (_sign == false)
        num *= -1;

    int64_t temp = num;
    _currLen = 1;
    
    while (num / 10 != 0)
    {
        _currLen++;
        num /= 10;
    }

    _len = 3 * (_currLen + 1) / 2;
    _number = new int8_t[_len];
    
    num = temp;

    for (int i = 0; i < _currLen; i++)
    {
        _number[i] = num % 10;
        num /= 10;
    }
    
}
BigInt::BigInt(const BigInt& T): _len(T._len)
                                , _currLen(T._currLen) 
                                , _sign(T._sign)
{
    _number = new int8_t[_len];

    for (size_t i = 0; i < _currLen; i++)
        _number[i] = T._number[i];

}

BigInt::~BigInt()
{
    //cout << "delete" << *this <<"\n";
    if (_number != nullptr)
        delete[] _number;
    _number = nullptr;
}


ostream& operator<< (std::ostream& out, const BigInt& num)
{
    if (num._sign == false)
        out << "-";
    for (size_t i = 0; i < num._currLen; i++)
        out << unsigned(num._number[num._currLen - 1 - i]);
    
    return out;
    
}


bool BigInt::operator> (const BigInt& num) const
{
    if (this->_sign == true)
    {   
           
        if (num._sign == false)
            return true;

        if (this->_currLen > num._currLen)
            return true;
        
        if (this->_currLen < num._currLen)
            return false;
        
        for (size_t i = 0; i < _currLen; i++)
        {
            if (this->_number[_currLen - 1 - i] > num._number[_currLen - 1 - i])
                return true;

            if (this->_number[_currLen - 1 - i] < num._number[_currLen - 1 - i])
                return false;

        }
        
        return false;
    }
    else
    {
        if (num._sign == true)
            return false;
        
        if (this->_currLen > num._currLen)
            return false;
        
        if (this->_currLen < num._currLen)
            return true;
        
        for (size_t i = 0; i < _currLen; i++)
        {
            if (this->_number[_currLen - 1 - i] < num._number[_currLen - 1 - i])
                return true;

            if (this->_number[_currLen - 1 - i] > num._number[_currLen - 1 - i])
                return false;

        }

        
        
        return false;

    }
}


bool BigInt::operator>= (const BigInt& num) const
{
    if (this->_sign == true)
    {   
           
        if (num._sign == false)
            return true;

        if (this->_currLen > num._currLen)
            return true;
        
        if (this->_currLen < num._currLen)
            return false;
        
        for (size_t i = 0; i < _currLen; i++)
        {
            if (this->_number[_currLen - 1 - i] > num._number[_currLen - 1 - i])
                return true;

            if (this->_number[_currLen - 1 - i] < num._number[_currLen - 1 - i])
                return false;

        }
        
        return true;
    }
    else
    {
        if (num._sign == true)
            return false;
        
        if (this->_currLen > num._currLen)
            return false;
        
        if (this->_currLen < num._currLen)
            return true;
        
        for (size_t i = 0; i < _currLen; i++)
        {
            if (this->_number[_currLen - 1 - i] < num._number[_currLen - 1 - i])
                return true;

            if (this->_number[_currLen - 1 - i] > num._number[_currLen - 1 - i])
                return false;

        }

        
        
        return true;

    }
}


bool BigInt::operator< (const BigInt& num) const
{
    return !(*this >= num);

}


bool BigInt::operator<= (const BigInt& num) const
{
    return !(*this > num);

}


bool BigInt::operator== (const BigInt& num) const
{
    if (this->_currLen != num._currLen
        || this->_sign != num._sign)
        
        return false;
    
    
    for (size_t i = 0; i < _currLen; i++)
    {
        if (this->_number[_currLen - 1 - i] != num._number[_currLen - 1 - i])
            return false;
    }

    return true;
}


bool BigInt::operator!= (const BigInt& num) const
{
    return !(*this == num);
}


void BigInt::clear()
{
    
    if (_number != nullptr)
        delete[] _number;
    _number = nullptr;
    _len = 0;
    _currLen = 0;
    _sign = true;
}


BigInt& BigInt::operator= (const BigInt& num)
{
    if(this == &num)
        return *this;

    this->clear();
    
    _len = num._len;
    _currLen = num._currLen;
    _sign = num._sign;
    _number = new int8_t[_len];

    for (size_t i = 0; i < _currLen; i++)
        _number[i] = num._number[i];
    
    return *this;

}


BigInt& BigInt::operator= (int64_t num)
{
    BigInt temp = num;
    *this = temp;
    return *this;
}

void BigInt::realloc()
{
    int8_t* new_number = new int8_t[3 * _len / 2];
    
    for (size_t i = 0; i < _currLen; i++)
        new_number[i] = _number[i];
    
    _len = 3 * _len / 2;

    delete[] _number;
    _number = new_number;
}

BigInt BigInt::operator+ (const BigInt& num) const
{
    if (_sign == num._sign)
    {
        
        BigInt res;

        const BigInt* another = nullptr;
        if (this->abs() > num.abs())
        {
            res = BigInt(*this);
            another = &num;
            
        }
        else
        {
            res = BigInt(num);
            another = this;
        }
        
        if (res._len - res._currLen == 0)
            res.realloc();

        size_t len = min(res._currLen, another->_currLen);
        int8_t add = 0;

        for (size_t i = 0; i < len; i++)
        {
            res._number[i] += another->_number[i] + add;
            if (res._number[i] >= 10)
            {
                add = 1;
                res._number[i] -= 10;
            }
            else
                add = 0;
        }
        
        if (add == 1)
        {
            
            size_t j = len;
            while (add == 1 && j < res._currLen)
            {
                res._number[j] += 1;
                if (res._number[j] >= 10)
                {
                    add = 1;
                    res._number[j] -= 10;
                }
                else
                    add = 0;
                j++;
            }

            if (add == 1)
            {
                res._number[res._currLen] = 1;
                res._currLen++;
            }
        }
        return res;
    }
    else
    {
        
        if (_sign == true)//10 + -3
            
        {
            if (this->abs() > num.abs())
                return (*this - -num).check_zero();
            else
                return (*this - -num).check_zero();
            
        }
        else//-10 + 3
        {
            if (this->abs() > num.abs())
                return (num - -*this).check_zero();
            else
                return (num - -*this).check_zero();
        }
            
    }
    
    
}

BigInt BigInt::operator-() const
{
    BigInt res(*this);
    if (res._sign == true)
        res._sign = false;
    else
        res._sign = true;

    return res.check_zero();

}

BigInt BigInt::operator- (const BigInt& num) const
{
    if (_sign == num._sign)
    {
        //cout << "HERE\n";
        BigInt res;

        const BigInt* another = nullptr;
        if (this->abs() > num.abs())
        {
            res = BigInt(*this);
            another = &num;
            
        }
        else
        {
            res = -BigInt(num);
            another = this;
        }
        
        if (res._len - res._currLen == 0)
            res.realloc();

        size_t len = min(res._currLen, another->_currLen);
        int8_t add = 0;

        for (size_t i = 0; i < len; i++)
        {
            res._number[i] -= another->_number[i] + add;
            if (res._number[i] < 0)
            {
                add = 1;
                res._number[i] += 10;
            }
            else
                add = 0;
        }
        // cout << res << " " << *another << endl;
        
        if (add == 1)//10_000 - 99
        {
            
            size_t j = len;
            while (add == 1 && j < res._currLen)
            {
                res._number[j] -= 1;
                if (res._number[j] < 0)
                {
                    add = 1;
                    res._number[j] += 10;
                }
                else
                    add = 0;
                j++;
            }
            //cout << res << " " << *another << endl;
            //res._currLen -= iter;
            
        }
        while (res._number[res._currLen - 1] == 0 && res._currLen > 1)
            res._currLen--;
        return res.check_zero();
    }
    else
    {
        //cout << "haha\n";
        if (_sign == true)//100 - -20
            return (*this + -num).check_zero();
        else//-20 - 100
        {
            return (-num + *this).check_zero();
        }
    }
}


BigInt BigInt::abs() const
{
    BigInt res = *this;
    
    if (res._sign == false)
        res._sign = true;
    
    return res;
}


BigInt& BigInt::check_zero()
{
    if (_currLen == 1 && _number[0] == 0 && _sign == false)
        _sign = true;

    return *this;

}