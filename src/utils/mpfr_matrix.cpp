//
//  mpfr_matrix.cpp
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

#include "mpfr_matrix.h"

#include <iostream>

mpfr_matrix::mpfr_matrix() {
}

mpfr_matrix::mpfr_matrix(const mpfr_matrix& other) :
    m_data(other.m_data) {
}

mpfr_matrix::mpfr_matrix(size_t n_rows, size_t n_cols) {
    mpfr_class initial_value;
    mpfr_vector row(n_cols, initial_value);
    for (size_t i = 0; i < n_rows; ++i) {
        this->m_data.push_back(row);
    }
}

mpfr_matrix::mpfr_matrix(size_t n_rows, size_t n_cols, const mpfr_class& initial_value) {
    mpfr_vector row(n_cols, initial_value);
    for (size_t i = 0; i < n_rows; ++i) {
        this->m_data.push_back(row);
    }
}

mpfr_matrix::~mpfr_matrix() {
}

mpfr_matrix& mpfr_matrix::operator=(const mpfr_matrix& other) {
    this->m_data = other.m_data;
    return *this;
}

mpfr_matrix mpfr_matrix::operator+(const mpfr_matrix& other) const {
    mpfr_matrix tmp = *this;
    if (tmp.n_rows() == other.n_rows() && tmp.n_cols() == other.n_cols()) {
        for (size_t i = 0; i < tmp.m_data.size(); ++i) {
            tmp.m_data[i] += other.m_data[i];
        }
    } else {
        tmp.set_nan();
    }
    return tmp;
}

mpfr_matrix& mpfr_matrix::operator+=(const mpfr_matrix& other) {
    if (this->n_rows() == other.n_rows() && this->n_cols() == other.n_cols()) {
        for (size_t i = 0; i < this->m_data.size(); ++i) {
            this->m_data[i] += other.m_data[i];
        }
    } else {
        this->set_nan();
    }
    return *this;
}

mpfr_matrix mpfr_matrix::operator+() const {
    return mpfr_matrix(*this);
}

mpfr_matrix mpfr_matrix::operator-(const mpfr_matrix& other) const {
    mpfr_matrix tmp = *this;
    if (tmp.n_rows() == other.n_rows() && tmp.n_cols() == other.n_cols()) {
        for (size_t i = 0; i < tmp.m_data.size(); ++i) {
            tmp.m_data[i] -= other.m_data[i];
        }
    } else {
        tmp.set_nan();
    }
    return tmp;
}

mpfr_matrix& mpfr_matrix::operator-=(const mpfr_matrix& other) {
    if (this->n_rows() == other.n_rows() && this->n_cols() == other.n_cols()) {
        for (size_t i = 0; i < this->m_data.size(); ++i) {
            this->m_data[i] -= other.m_data[i];
        }
    } else {
        this->set_nan();
    }
    return *this;
}

mpfr_matrix mpfr_matrix::operator-() const {
    mpfr_matrix tmp = *this;
    for (size_t i = 0; i < tmp.m_data.size(); ++i) {
        tmp.m_data[i].set_neg();
    }
    return tmp;
}

mpfr_matrix mpfr_matrix::operator*(const mpfr_matrix& other) const {
    mpfr_matrix tmp(this->n_rows(), other.n_cols());
    if (this->n_cols() == other.n_rows()) {
        for (size_t i = 0; i < this->n_rows(); ++i) {
            for (size_t j = 0; j < other.n_cols(); ++j) {
                mpfr_class tmp_value = 0;
                for (size_t k = 0; k < this->n_cols(); ++k) {
                    tmp_value += this->m_data[i][k] * other.m_data[k][j];
                }
                tmp.m_data[i][j] = tmp_value;
            }
        }
    }
    return tmp;
}

mpfr_vector mpfr_matrix::operator*(const mpfr_vector& other) const {
    mpfr_vector tmp(this->n_rows(), 1);
    if (this->n_cols() == other.size()) {
        for (size_t i = 0; i < tmp.size(); ++i) {
            mpfr_class tmp_value = 0;
            for (size_t j = 0; j < this->n_cols(); ++j) {
                tmp_value += this->m_data[i][j] * other[j];
            }
            tmp[i] = tmp_value;
        }
    }
    return tmp;
}

mpfr_matrix mpfr_matrix::operator*(const mpfr_class& other) const {
    mpfr_matrix tmp = *this;
    for (size_t i = 0; i < this->m_data.size(); ++i) {
        tmp.m_data[i] *= other;
    }
    return tmp;
}

mpfr_matrix& mpfr_matrix::operator*=(const mpfr_class& other) {
    for (size_t i = 0; i < this->m_data.size(); ++i) {
        this->m_data[i] *= other;
    }
    return *this;
}

mpfr_matrix mpfr_matrix::operator/(const mpfr_class& other) const {
    mpfr_matrix tmp = *this;
    for (size_t i = 0; i < this->m_data.size(); ++i) {
        tmp.m_data[i] /= other;
    }
    return tmp;
}

mpfr_matrix& mpfr_matrix::operator/=(const mpfr_class& other) {
    for (size_t i = 0; i < this->m_data.size(); ++i) {
        this->m_data[i] /= other;
    }
    return *this;
}

mpfr_vector& mpfr_matrix::operator[](const size_t offset) {
    return this->m_data[offset];
}

const mpfr_vector& mpfr_matrix::operator[](const size_t offset) const {
    return this->m_data[offset];
}

std::ostream& operator<<(std::ostream& left, const mpfr_matrix& right) {
    left << '{';
    for (size_t i = 0; i < right.m_data.size(); ++i) {
        if (i > 0) {
            left << ',';
        }
        left << '{';
        for (size_t j = 0; j < right.m_data.size(); ++j) {
            if (j > 0) {
                left << ',';
            }
            left << right.m_data[i][j];
        }
        left << '}';
    }
    left << '}';
    return left;
}

void mpfr_matrix::set_prec(mpfr_prec_t prec) {
    for (size_t i = 0; i < this->m_data.size(); ++i) {
        this->m_data[i].set_prec(prec);
    }
}

bool mpfr_matrix::contains_nan() const {
    for (size_t i = 0; i < this->m_data.size(); ++i) {
        if (this->m_data[i].contains_nan()) {
            return true;
        }
    }
    return false;
}

bool mpfr_matrix::contains_inf() const {
    for (size_t i = 0; i < this->m_data.size(); ++i) {
        if (this->m_data[i].contains_inf()) {
            return true;
        }
    }
    return false;
}

bool mpfr_matrix::is_zero() const {
    for (size_t i = 0; i < this->m_data.size(); ++i) {
        if (this->m_data[i].is_zero()) {
            return true;
        }
    }
    return false;
}

void mpfr_matrix::set_nan() {
    for (size_t i = 0; i < this->m_data.size(); ++i) {
        this->m_data[i].set_nan();
    }
}

void mpfr_matrix::set_inf(int sign) {
    for (size_t i = 0; i < this->m_data.size(); ++i) {
        this->m_data[i].set_inf(sign);
    }
}

void mpfr_matrix::set_zero(int sign) {
    for (size_t i = 0; i < this->m_data.size(); ++i) {
        this->m_data[i].set_zero(sign);
    }
}

void mpfr_matrix::set_neg() {
    for (size_t i = 0; i < this->m_data.size(); ++i) {
        this->m_data[i].set_neg();
    }
}

size_t mpfr_matrix::size() const {
    if (this->m_data.size() == 0) {
        return 0;
    }
    return this->m_data.size() * this->m_data[0].size();
}

size_t mpfr_matrix::n_rows() const {
    return this->m_data.size();
}

size_t mpfr_matrix::n_cols() const {
    if (this->m_data.size() == 0) {
        return 0;
    }
    return this->m_data[0].size();
}

mpfr_matrix mpfr_matrix::zero_matrix(const size_t n_rows, const size_t n_cols) {
    return mpfr_matrix(n_rows, n_cols, 0);
}

mpfr_matrix mpfr_matrix::eye_matrix(const size_t size) {
    mpfr_matrix tmp(size, size, 0);
    for (size_t i = 0; i < size; ++i) {
        tmp[i][i] = 1;
    }
    return tmp;
}
