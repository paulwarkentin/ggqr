//
//  mpfr_polynomial.h
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

#ifndef __MPFR_POLYNOMIAL_H__
#define __MPFR_POLYNOMIAL_H__

#include <vector>

#include "mpfr_class.h"

class mpfr_polynomial {

public:

    typedef std::vector<mpfr_class>::size_type size_t;

private:

    std::vector<mpfr_class> m_data;

public:

    mpfr_polynomial();
    mpfr_polynomial(const mpfr_polynomial& other);
    mpfr_polynomial(size_t max_degree);
    mpfr_polynomial(size_t max_degree, const mpfr_class& initial_value);
    ~mpfr_polynomial();

    mpfr_polynomial& operator=(const mpfr_polynomial& other);
    mpfr_polynomial& operator=(const mpfr_class& other);

    mpfr_polynomial operator+(const mpfr_polynomial& other) const;
    mpfr_polynomial operator+(const mpfr_class& other) const;

    mpfr_polynomial& operator+=(const mpfr_polynomial& other);
    mpfr_polynomial& operator+=(const mpfr_class& other);

    mpfr_polynomial operator+() const;

    mpfr_polynomial operator-(const mpfr_polynomial& other) const;
    mpfr_polynomial operator-(const mpfr_class& other) const;

    mpfr_polynomial& operator-=(const mpfr_polynomial& other);
    mpfr_polynomial& operator-=(const mpfr_class& other);

    mpfr_polynomial operator-() const;

    mpfr_polynomial operator*(const mpfr_polynomial& other) const;
    mpfr_polynomial operator*(const mpfr_class& other) const;

    mpfr_polynomial& operator*=(const mpfr_polynomial& other);
    mpfr_polynomial& operator*=(const mpfr_class& other);

    mpfr_polynomial operator/(const mpfr_class& other) const;
    mpfr_polynomial& operator/=(const mpfr_class& other);

    mpfr_class& operator[](const size_t offset);
    const mpfr_class& operator[](const size_t offset) const;

    friend std::ostream& operator<<(std::ostream& left, const mpfr_polynomial& right);

    mpfr_class evaluate_at(const mpfr_class& point) const;
    mpfr_polynomial synthetic_division_without_remainder(const mpfr_class& point, const bool check_remainder = false) const;

    mpfr_polynomial derivative() const;
    mpfr_polynomial antiderivative(const mpfr_class& constant = 0) const;
    mpfr_class integral(const mpfr_class& left, const mpfr_class& right) const;

    void set_zero();
    void set_neg();

    size_t get_degree() const;
    size_t get_max_degree() const;
    void set_max_degree(const size_t degree);

}; // class mpfr_polynomial

#endif // __MPFR_POLYNOMIAL_H__
