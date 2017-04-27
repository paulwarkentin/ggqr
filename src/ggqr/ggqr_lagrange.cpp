//
//  ggqr_lagrange.cpp
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

#include "ggqr_lagrange.h"

#include <iostream>

ggqr_lagrange::ggqr_lagrange(const mpfr_vector& points) {
    if (points.size() < 2) {
        printf("ggqr_lagrange[%s:%d]: The set must contain at least two points.\n", __FILE__, __LINE__);
        abort();
    }
    this->m_calculated = false;
    this->m_points = points;
    this->m_size = this->m_points.size();
    this->m_general_polynomial = mpfr_polynomial();
    this->m_denominators = mpfr_vector(this->m_size, 1);
}

ggqr_lagrange::~ggqr_lagrange() {
}

void ggqr_lagrange::calculate() {
    if (this->m_calculated) {
        return;
    }
    for (mpfr_vector::size_t i = 0; i < this->m_size; ++i) {
        mpfr_polynomial linear_polynomial = mpfr_polynomial(1, 1);
        linear_polynomial[0] = -this->m_points[i];
        if (i == 0) {
            this->m_general_polynomial = linear_polynomial;
        } else {
            this->m_general_polynomial *= linear_polynomial;
        }
    }
    for (mpfr_vector::size_t i = 0; i < this->m_size; ++i) {
        for (mpfr_vector::size_t j = 0; j < this->m_size; ++j) {
            if (i != j) {
                this->m_denominators[i] *= this->m_points[i] - this->m_points[j];
            }
        }
    }
    this->m_calculated = true;
}

mpfr_polynomial ggqr_lagrange::get_basis_polynomial(mpfr_vector::size_t index) const {
    if (!this->m_calculated) {
        printf("ggqr_lagrange[%s:%d]: Polynomials were not calculated.\n", __FILE__, __LINE__);
        abort();
    }
    mpfr_class point = this->m_points[index];
    mpfr_polynomial basis = this->m_general_polynomial.synthetic_division_without_remainder(point, false);
    if (basis.get_degree() + 1 != this->m_size) {
        printf("ggqr_lagrange[%s:%d]: Basis polynomial calculation went wrong.\n", __FILE__, __LINE__);
        abort();
    }
    basis /= this->m_denominators[index];
    return basis;
}
