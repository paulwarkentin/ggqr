//
//  mpfr_matrix.h
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

#ifndef __MPFR_MATRIX_H__
#define __MPFR_MATRIX_H__

#include <vector>

#include "mpfr_class.h"
#include "mpfr_vector.h"

class mpfr_matrix {

public:

    typedef std::vector<mpfr_vector>::size_type size_t;

private:

    std::vector<mpfr_vector> m_data;

public:

    mpfr_matrix();
    mpfr_matrix(const mpfr_matrix& other);
    mpfr_matrix(size_t n_rows, size_t n_cols);
    mpfr_matrix(size_t n_rows, size_t n_cols, const mpfr_class& initial_value);
    ~mpfr_matrix();

    mpfr_matrix& operator=(const mpfr_matrix& other);

    mpfr_matrix operator+(const mpfr_matrix& other) const;
    mpfr_matrix& operator+=(const mpfr_matrix& other);
    mpfr_matrix operator+() const;

    mpfr_matrix operator-(const mpfr_matrix& other) const;
    mpfr_matrix& operator-=(const mpfr_matrix& other);
    mpfr_matrix operator-() const;

    mpfr_matrix operator*(const mpfr_matrix& other) const;
    mpfr_vector operator*(const mpfr_vector& other) const;
    mpfr_matrix operator*(const mpfr_class& other) const;
    mpfr_matrix& operator*=(const mpfr_class& other);

    mpfr_matrix operator/(const mpfr_class& other) const;
    mpfr_matrix& operator/=(const mpfr_class& other);

    mpfr_vector& operator[](const size_t offset);
    const mpfr_vector& operator[](const size_t offset) const;

    friend std::ostream& operator<<(std::ostream& left, const mpfr_matrix& right);

    void set_prec(mpfr_prec_t prec);

    bool contains_nan() const;
    bool contains_inf() const;
    bool is_zero() const;

    void set_nan();
    void set_inf(int sign);
    void set_zero(int sign);
    void set_neg();

    size_t size() const;
    size_t n_rows() const;
    size_t n_cols() const;

public:

    static mpfr_matrix zero_matrix(const size_t n_rows, const size_t n_cols);
    static mpfr_matrix eye_matrix(const size_t size);

}; // class mpfr_matrix

#endif // __MPFR_MATRIX_H__
