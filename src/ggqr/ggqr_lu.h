//
//  ggqr_lu.h
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

#ifndef __GGQR_LU_H__
#define __GGQR_LU_H__

#include "../utils/mpfr_class.h"
#include "../utils/mpfr_vector.h"
#include "../utils/mpfr_matrix.h"

class ggqr_lu {

private:

    bool m_decomposed;

    mpfr_matrix m_original;
    mpfr_matrix::size_t m_size;

    mpfr_matrix m_lower;
    mpfr_matrix m_upper;
    mpfr_matrix m_pivot;

public:

    ggqr_lu(const mpfr_matrix& original_matrix);
    ~ggqr_lu();

    void decompose();

    mpfr_matrix inverse() const;
    mpfr_vector solve(const mpfr_vector& right) const;

private:

    void pivot();

}; // class ggqr_lu

#endif // __GGQR_LU_H__
