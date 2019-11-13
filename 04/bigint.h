
#include <iostream>
#ifndef BIGINT_H
#define BIGINT_H
class BigInt
{
    private:
        int8_t* _number;
        uint64_t _len;
        uint64_t _currLen;
        bool _sign;
        void clear();
        BigInt& check_zero();
        void realloc();
    public:
        BigInt (int64_t num);
        BigInt ();
        BigInt(const BigInt& T);
        ~BigInt ();
        friend std::ostream& operator<< (std::ostream& out, const BigInt& dt);
        bool operator> (const BigInt& num) const;
        bool operator>= (const BigInt& num) const;
        bool operator< (const BigInt& num) const;
        bool operator<= (const BigInt& num) const;
        bool operator== (const BigInt& num) const;
        bool operator!= (const BigInt& num) const;
        BigInt operator+(const BigInt& num) const;
        BigInt operator-() const;
        BigInt operator-(const BigInt& num) const;
        BigInt abs() const;
        BigInt& operator= (const BigInt& num);
        BigInt& operator= (int64_t num);
};

#endif