//
//  ggqr_lu.cpp
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

#include "ggqr_lu.h"

#include <iostream>

ggqr_lu::ggqr_lu(const mpfr_matrix& original_matrix) {
    if (original_matrix.n_rows() != original_matrix.n_cols()) {
        printf("ggqr_lu[%s:%d]: Matrix has to be a square matrix.\n", __FILE__, __LINE__);
        abort();
    }
    this->m_decomposed = false;
    this->m_original = original_matrix;
    this->m_size = this->m_original.n_rows();
    this->m_lower = mpfr_matrix(this->m_size, this->m_size);
    this->m_upper = mpfr_matrix(this->m_size, this->m_size);
    this->m_pivot = mpfr_matrix(this->m_size, this->m_size);
}

ggqr_lu::~ggqr_lu() {
}

void ggqr_lu::decompose() {
    if (this->m_decomposed) {
        return;
    }
    this->pivot();
    this->m_lower = mpfr_matrix::eye_matrix(this->m_size);
    this->m_upper = mpfr_matrix::zero_matrix(this->m_size, this->m_size);
    mpfr_matrix pivot_original = this->m_pivot * this->m_original;
    mpfr_class tmp_sum;
    for (mpfr_matrix::size_t i = 0; i < this->m_size; ++i) {
        for (mpfr_matrix::size_t j = 0; j < this->m_size; ++j) {
            if (j <= i) {
                tmp_sum = 0;
                for (mpfr_matrix::size_t k = 0; k < j; ++k) {
                    tmp_sum += this->m_lower[j][k] * this->m_upper[k][i];
                }
                this->m_upper[j][i] = pivot_original[j][i] - tmp_sum;
            }
            if (j >= i) {
                tmp_sum = 0;
                for (mpfr_matrix::size_t k = 0; k < i; ++k) {
                    tmp_sum += this->m_lower[j][k] * this->m_upper[k][i];
                }
                this->m_lower[j][i] = (pivot_original[j][i] - tmp_sum) / this->m_upper[i][i];
            }
        }
    }
    this->m_decomposed = true;
}

mpfr_matrix ggqr_lu::inverse() const {
    if (!this->m_decomposed) {
        printf("ggqr_lu[%s:%d]: Original matrix was not decomposed.\n", __FILE__, __LINE__);
        abort();
    }
    mpfr_matrix inverse(this->m_size, this->m_size);
    for (mpfr_matrix::size_t i = 0; i < this->m_size; ++i) {
        mpfr_vector right = mpfr_vector::eye_vector(this->m_size, i);
        mpfr_vector solution = this->solve(right);
        for (mpfr_vector::size_t j = 0; j < this->m_size; ++j) {
            inverse[j][i] = solution[j];
        }
    }
    return inverse;
}

mpfr_vector ggqr_lu::solve(const mpfr_vector& right) const {
    if (!this->m_decomposed) {
        printf("ggqr_lu[%s:%d]: Original matrix was not decomposed.\n", __FILE__, __LINE__);
        abort();
    }
    if (right.size() != this->m_size) {
        printf("ggqr_lu[%s:%d]: Cannot operate on objects of different sizes.\n", __FILE__, __LINE__);
        abort();
    }
    mpfr_vector tmp_right = this->m_pivot * right;
    mpfr_vector buffer(this->m_size);
    mpfr_vector solution(this->m_size);
    for (mpfr_vector::size_t i = 0; i < this->m_size; ++i) {
        mpfr_class sum = 0;
        for (mpfr_vector::size_t j = 0; j < i; ++j) {
            sum += this->m_lower[i][j] * buffer[j];
        }
        buffer[i] = (tmp_right[i] - sum) / this->m_lower[i][i];
    }
    for (mpfr_vector::size_t i = this->m_size; i > 0; --i) {
        mpfr_class sum = 0;
        for (mpfr_vector::size_t j = this->m_size; j > i; --j) {
            sum += this->m_upper[i - 1][j - 1] * solution[j - 1];
        }
        solution[i - 1] = (buffer[i - 1] - sum) / this->m_upper[i - 1][i - 1];
    }
    return solution;
}

void ggqr_lu::pivot() {
    mpfr_matrix original_copy = this->m_original;
    this->m_pivot = mpfr_matrix::eye_matrix(this->m_size);
    for (mpfr_matrix::size_t i = 0; i < this->m_size; ++i) {
        mpfr_matrix::size_t max_j = i;
        for (mpfr_matrix::size_t j = i; j < this->m_size; ++j) {
            if (original_copy[j][i].abs_value() > original_copy[max_j][i].abs_value()) {
                max_j = j;
            }
        }
        if (max_j != i) {
            for (mpfr_matrix::size_t k = 0; k < this->m_size; ++k) {
                mpfr_class tmp = this->m_pivot[i][k];
                this->m_pivot[i][k] = this->m_pivot[max_j][k];
                this->m_pivot[max_j][k] = tmp;
                tmp = original_copy[i][k];
                original_copy[i][k] = this->m_pivot[max_j][k];
                original_copy[max_j][k] = tmp;
            }
        }
    }
}
