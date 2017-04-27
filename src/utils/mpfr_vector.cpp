//
//  mpfr_vector.cpp
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

#include "mpfr_vector.h"

#include <iostream>

mpfr_vector::mpfr_vector() {
}

mpfr_vector::mpfr_vector(const mpfr_vector& other) {
    this->m_data = other.m_data;
}

mpfr_vector::mpfr_vector(size_t size) {
    mpfr_class initial_value;
    for (size_t i = 0; i < size; ++i) {
        this->m_data.push_back(initial_value);
    }
}

mpfr_vector::mpfr_vector(size_t size, const mpfr_class& initial_value) {
    for (size_t i = 0; i < size; ++i) {
        this->m_data.push_back(initial_value);
    }
}

mpfr_vector::~mpfr_vector() {
}

mpfr_vector& mpfr_vector::operator=(const mpfr_vector& other) {
    if (&other != this) {
        this->m_data = other.m_data;
    }
    return *this;
}

mpfr_vector mpfr_vector::operator+(const mpfr_vector& other) const {
    mpfr_vector tmp = *this;
    if (tmp.m_data.size() == other.m_data.size()) {
        for (size_t i = 0; i < other.m_data.size(); ++i) {
            tmp.m_data[i] += other.m_data[i];
        }
    } else {
        tmp.set_nan();
    }
    return tmp;
}

mpfr_vector& mpfr_vector::operator+=(const mpfr_vector& other) {
    if (this->m_data.size() == other.m_data.size()) {
        for (size_t i = 0; i < other.m_data.size(); ++i) {
            this->m_data[i] += other.m_data[i];
        }
    } else {
        this->set_nan();
    }
    return *this;
}

mpfr_vector mpfr_vector::operator+() const {
    return mpfr_vector(*this);
}

mpfr_vector mpfr_vector::operator-(const mpfr_vector& other) const {
    mpfr_vector tmp = *this;
    if (tmp.m_data.size() == other.m_data.size()) {
        for (size_t i = 0; i < other.m_data.size(); ++i) {
            tmp.m_data[i] -= other.m_data[i];
        }
    } else {
        tmp.set_nan();
    }
    return tmp;
}

mpfr_vector& mpfr_vector::operator-=(const mpfr_vector& other) {
    if (this->m_data.size() == other.m_data.size()) {
        for (size_t i = 0; i < other.m_data.size(); ++i) {
            this->m_data[i] -= other.m_data[i];
        }
    } else {
        this->set_nan();
    }
    return *this;
}

mpfr_vector mpfr_vector::operator-() const {
    mpfr_vector tmp = *this;
    for (size_t i = 0; i < tmp.m_data.size(); ++i) {
        tmp.m_data[i].set_neg();
    }
    return tmp;
}

mpfr_class mpfr_vector::operator*(const mpfr_vector& other) const {
    mpfr_class tmp = 0;
    if (this->m_data.size() == other.m_data.size()) {
        for (size_t i = 0; i < this->m_data.size(); ++i) {
            tmp += this->m_data[i] * other.m_data[i];
        }
    }
    return tmp;
}

mpfr_vector mpfr_vector::operator*(const mpfr_class& other) const {
    mpfr_vector tmp = *this;
    for (size_t i = 0; i < tmp.m_data.size(); ++i) {
        tmp.m_data[i] *= other;
    }
    return tmp;
}

mpfr_vector& mpfr_vector::operator*=(const mpfr_class& other) {
    for (size_t i = 0; i < this->m_data.size(); ++i) {
        this->m_data[i] *= other;
    }
    return *this;
}

mpfr_vector mpfr_vector::operator/(const mpfr_class& other) const {
    mpfr_vector tmp = *this;
    for (size_t i = 0; i < tmp.m_data.size(); ++i) {
        tmp.m_data[i] /= other;
    }
    return tmp;
}

mpfr_vector& mpfr_vector::operator/=(const mpfr_class& other) {
    for (size_t i = 0; i < this->m_data.size(); ++i) {
        this->m_data[i] /= other;
    }
    return *this;
}

mpfr_class& mpfr_vector::operator[](const size_t offset) {
    return this->m_data[offset];
}

const mpfr_class& mpfr_vector::operator[](const size_t offset) const {
    return this->m_data[offset];
}

std::ostream& operator<<(std::ostream& left, const mpfr_vector& right) {
    left << '{';
    for (size_t i = 0; i < right.m_data.size(); ++i) {
        if (i > 0) {
            left << ',';
        }
        left << right.m_data[i];
    }
    left << '}';
    return left;
}

mpfr_class mpfr_vector::euclidean_norm() const {
    mpfr_class norm = 0;
    for (size_t i = 0; i < this->m_data.size(); ++i) {
        norm += this->m_data[i] * this->m_data[i];
    }
    return norm.sqrt_value();
}

void mpfr_vector::append(const mpfr_class& other) {
    this->m_data.push_back(other);
}

void mpfr_vector::append(const mpfr_vector& other) {
    for (size_t i = 0; i < other.m_data.size(); ++i) {
        this->m_data.push_back(other.m_data[i]);
    }
}

void mpfr_vector::set_prec(mpfr_prec_t prec) {
    for (size_t i = 0; i < this->m_data.size(); ++i) {
        this->m_data[i].set_prec(prec);
    }
}

bool mpfr_vector::contains_nan() const {
    for (size_t i = 0; i < this->m_data.size(); ++i) {
        if (this->m_data[i].is_nan()) {
            return true;
        }
    }
    return false;
}

bool mpfr_vector::contains_inf() const {
    for (size_t i = 0; i < this->m_data.size(); ++i) {
        if (this->m_data[i].is_inf()) {
            return true;
        }
    }
    return false;
}

bool mpfr_vector::is_zero() const {
    for (size_t i = 0; i < this->m_data.size(); ++i) {
        if (!this->m_data[i].is_zero()) {
            return false;
        }
    }
    return true;
}

void mpfr_vector::set_nan() {
    for (size_t i = 0; i < this->m_data.size(); ++i) {
        this->m_data[i].set_nan();
    }
}

void mpfr_vector::set_inf(int sign) {
    for (size_t i = 0; i < this->m_data.size(); ++i) {
        this->m_data[i].set_inf(sign);
    }
}

void mpfr_vector::set_zero(int sign) {
    for (size_t i = 0; i < this->m_data.size(); ++i) {
        this->m_data[i].set_zero(sign);
    }
}

void mpfr_vector::set_neg() {
    for (size_t i = 0; i < this->m_data.size(); ++i) {
        this->m_data[i].set_neg();
    }
}

size_t mpfr_vector::size() const {
    return this->m_data.size();
}

mpfr_vector mpfr_vector::zero_vector(const size_t size) {
    return mpfr_vector(size, 0);
}

mpfr_vector mpfr_vector::eye_vector(const size_t size, const size_t index) {
    mpfr_vector tmp(size, 0);
    tmp[index] = 1;
    return tmp;
}
