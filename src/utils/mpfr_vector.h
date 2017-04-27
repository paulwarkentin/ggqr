//
//  mpfr_vector.h
//  Generalized Gaussian Quadrature
//
//  MIT License
//
//  Copyright (c) 2017 Paul Warkentin
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.
//

#ifndef __MPFR_VECTOR_H__
#define __MPFR_VECTOR_H__

#include <vector>

#include "mpfr_class.h"

class mpfr_vector {

public:

    typedef std::vector<mpfr_class>::size_type size_t;

private:

    std::vector<mpfr_class> m_data;

public:

    mpfr_vector();
    mpfr_vector(const mpfr_vector& other);
    mpfr_vector(size_t size);
    mpfr_vector(size_t size, const mpfr_class& initial_value);
    ~mpfr_vector();

    mpfr_vector& operator=(const mpfr_vector& other);

    mpfr_vector operator+(const mpfr_vector& other) const;
    mpfr_vector& operator+=(const mpfr_vector& other);
    mpfr_vector operator+() const;

    mpfr_vector operator-(const mpfr_vector& other) const;
    mpfr_vector& operator-=(const mpfr_vector& other);
    mpfr_vector operator-() const;

    mpfr_class operator*(const mpfr_vector& other) const;

    mpfr_vector operator*(const mpfr_class& other) const;
    mpfr_vector& operator*=(const mpfr_class& other);

    mpfr_vector operator/(const mpfr_class& other) const;
    mpfr_vector& operator/=(const mpfr_class& other);

    mpfr_class& operator[](const size_t offset);
    const mpfr_class& operator[](const size_t offset) const;

    friend std::ostream& operator<<(std::ostream& left, const mpfr_vector& right);

    mpfr_class euclidean_norm() const;

    void append(const mpfr_class& other);
    void append(const mpfr_vector& other);

    void set_prec(mpfr_prec_t prec);

    bool contains_nan() const;
    bool contains_inf() const;
    bool is_zero() const;

    void set_nan();
    void set_inf(int sign);
    void set_zero(int sign);
    void set_neg();

    size_t size() const;

public:

    static mpfr_vector zero_vector(const size_t size);
    static mpfr_vector eye_vector(const size_t size, const size_t index);

}; // class mpfr_vector

#endif // __MPFR_VECTOR_H__
