//
//  ggqr_lagrange.h
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

#ifndef __GGQR_LAGRANGE_H__
#define __GGQR_LAGRANGE_H__

#include "../utils/mpfr_class.h"
#include "../utils/mpfr_vector.h"
#include "../utils/mpfr_polynomial.h"

class ggqr_lagrange {

private:

    bool m_calculated;

    mpfr_vector m_points;
    mpfr_vector::size_t m_size;

    mpfr_polynomial m_general_polynomial;
    mpfr_vector m_denominators;

public:

    ggqr_lagrange(const mpfr_vector& points);
    ~ggqr_lagrange();

    void calculate();

    mpfr_polynomial get_basis_polynomial(mpfr_vector::size_t index) const;

}; // class ggqr_lagrange

#endif // __GGQR_LAGRANGE_H__
