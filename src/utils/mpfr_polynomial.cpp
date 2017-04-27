//
//  mpfr_polynomial.cpp
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

#include "mpfr_polynomial.h"

#include <iostream>

mpfr_polynomial::mpfr_polynomial() {
    mpfr_class initial_value;
    this->m_data.push_back(initial_value);
}

mpfr_polynomial::mpfr_polynomial(const mpfr_polynomial& other) :
    m_data(other.m_data) {
}

mpfr_polynomial::mpfr_polynomial(size_t max_degree) {
    mpfr_class initial_value;
    for (size_t i = 0; i < max_degree + 1; ++i) {
        this->m_data.push_back(initial_value);
    }
}

mpfr_polynomial::mpfr_polynomial(size_t max_degree, const mpfr_class& initial_value) {
    for (size_t i = 0; i < max_degree + 1; ++i) {
        this->m_data.push_back(initial_value);
    }
}

mpfr_polynomial::~mpfr_polynomial() {
}

mpfr_polynomial& mpfr_polynomial::operator=(const mpfr_polynomial& other) {
    this->m_data = other.m_data;
    return *this;
}

mpfr_polynomial& mpfr_polynomial::operator=(const mpfr_class& other) {
    this->set_max_degree(0);
    this->m_data[0] = other;
    return *this;
}

mpfr_polynomial mpfr_polynomial::operator+(const mpfr_polynomial& other) const {
    mpfr_polynomial tmp = *this;
    if (tmp.m_data.size() < other.m_data.size()) {
        tmp.set_max_degree(other.get_max_degree());
    }
    for (size_t i = 0; i < other.m_data.size(); ++i) {
        tmp.m_data[i] += other.m_data[i];
    }
    return tmp;
}

mpfr_polynomial mpfr_polynomial::operator+(const mpfr_class& other) const {
    mpfr_polynomial tmp = *this;
    tmp.m_data[0] += other;
    return tmp;
}

mpfr_polynomial& mpfr_polynomial::operator+=(const mpfr_polynomial& other) {
    if (this->m_data.size() < other.m_data.size()) {
        this->set_max_degree(other.get_max_degree());
    }
    for (size_t i = 0; i < other.m_data.size(); ++i) {
        this->m_data[i] += other.m_data[i];
    }
    return *this;
}

mpfr_polynomial& mpfr_polynomial::operator+=(const mpfr_class& other) {
    this->m_data[0] += other;
    return *this;
}

mpfr_polynomial mpfr_polynomial::operator+() const {
    return mpfr_polynomial(*this);
}

mpfr_polynomial mpfr_polynomial::operator-(const mpfr_polynomial& other) const {
    mpfr_polynomial tmp = *this;
    if (tmp.m_data.size() < other.m_data.size()) {
        tmp.set_max_degree(other.get_max_degree());
    }
    for (size_t i = 0; i < other.m_data.size(); ++i) {
        tmp.m_data[0] -= other.m_data[i];
    }
    return tmp;
}

mpfr_polynomial mpfr_polynomial::operator-(const mpfr_class& other) const {
    mpfr_polynomial tmp = *this;
    tmp.m_data[0] -= other;
    return tmp;
}

mpfr_polynomial& mpfr_polynomial::operator-=(const mpfr_polynomial& other) {
    if (this->m_data.size() < other.m_data.size()) {
        this->set_max_degree(other.get_max_degree());
    }
    for (size_t i = 0; i < other.m_data.size(); ++i) {
        this->m_data[0] -= other.m_data[i];
    }
    return *this;
}

mpfr_polynomial& mpfr_polynomial::operator-=(const mpfr_class& other) {
    this->m_data[0] -= other;
    return *this;
}

mpfr_polynomial mpfr_polynomial::operator-() const {
    mpfr_polynomial tmp = *this;
    for (size_t i = 0; i < tmp.m_data.size(); ++i) {
        tmp.m_data[i].set_neg();
    }
    return tmp;
}

mpfr_polynomial mpfr_polynomial::operator*(const mpfr_polynomial& other) const {
    mpfr_class zero;
    zero.set_zero(true);
    mpfr_polynomial tmp(this->get_max_degree() + other.get_max_degree(), zero);
    for (size_t i = 0; i < this->get_max_degree() + 1; ++i) {
        for (size_t j = 0; j < other.get_max_degree() + 1; ++j) {
            tmp.m_data[i + j] += this->m_data[i] * other.m_data[j];
        }
    }
    return tmp;
}

mpfr_polynomial mpfr_polynomial::operator*(const mpfr_class& other) const {
    mpfr_polynomial tmp = *this;
    for (size_t i = 0; i < tmp.m_data.size(); ++i) {
        tmp.m_data[i] *= other;
    }
    return tmp;
}

mpfr_polynomial& mpfr_polynomial::operator*=(const mpfr_polynomial& other) {
    mpfr_class zero;
    zero.set_zero(true);
    mpfr_polynomial tmp(this->get_max_degree() + other.get_max_degree(), zero);
    for (size_t i = 0; i < this->get_max_degree() + 1; ++i) {
        for (size_t j = 0; j < other.get_max_degree() + 1; ++j) {
            tmp.m_data[i + j] += this->m_data[i] * other.m_data[j];
        }
    }
    this->operator=(tmp);
    return *this;
}

mpfr_polynomial& mpfr_polynomial::operator*=(const mpfr_class& other) {
    for (size_t i = 0; i < this->m_data.size(); ++i) {
        this->m_data[i] *= other;
    }
    return *this;
}

mpfr_polynomial mpfr_polynomial::operator/(const mpfr_class& other) const {
    mpfr_polynomial tmp = *this;
    for (size_t i = 0; i < tmp.m_data.size(); ++i) {
        tmp.m_data[i] /= other;
    }
    return tmp;
}

mpfr_polynomial& mpfr_polynomial::operator/=(const mpfr_class& other) {
    for (size_t i = 0; i < this->m_data.size(); ++i) {
        this->m_data[i] /= other;
    }
    return *this;
}

mpfr_class& mpfr_polynomial::operator[](const size_t offset) {
    return this->m_data[offset];
}

const mpfr_class& mpfr_polynomial::operator[](const size_t offset) const {
    return this->m_data[offset];
}

std::ostream& operator<<(std::ostream& left, const mpfr_polynomial& right) {
    for (size_t i = 0; i < right.m_data.size(); ++i) {
        mpfr_class tmp_value = right.m_data[right.m_data.size() - i - 1];
        left << tmp_value << "*x^" << right.m_data.size() - i - 1;
    }
    return left;
}

// horner -> synthetic division
mpfr_class mpfr_polynomial::evaluate_at(const mpfr_class& point) const {
    mpfr_class tmp = this->m_data[this->m_data.size() - 1];
    for (size_t i = 1; i < this->m_data.size(); ++i) {
        tmp = tmp * point + this->m_data[this->m_data.size() - i - 1];
    }
    return tmp;
}

mpfr_polynomial mpfr_polynomial::synthetic_division_without_remainder(const mpfr_class& point, const bool check_remainder) const {
    if (check_remainder && this->evaluate_at(point) != 0) {
        return mpfr_polynomial();
    }
    size_t degree = this->get_degree();
    if (degree == 0) {
        return mpfr_polynomial();
    }
    mpfr_polynomial tmp(degree - 1);
    for (size_t i = 0; i < tmp.m_data.size(); ++i) {
        size_t offset = tmp.m_data.size() - i - 1;
        tmp.m_data[offset] = this->m_data[offset + 1];
        if (i > 0) {
            tmp.m_data[offset] += point * tmp.m_data[offset + 1];
        }
    }
    return tmp;
}

mpfr_polynomial mpfr_polynomial::derivative() const {
    size_t degree = this->get_degree();
    if (degree == 0) {
        return mpfr_polynomial();
    }
    mpfr_polynomial tmp(degree - 1);
    for (size_t i = 0; i < tmp.m_data.size(); ++i) {
        tmp.m_data[i] = (i + 1) * this->m_data[i + 1];
    }
    return tmp;
}

mpfr_polynomial mpfr_polynomial::antiderivative(const mpfr_class& constant) const {
    size_t degree = this->get_degree();
    mpfr_polynomial tmp(degree + 1);
    tmp.m_data[0] = constant;
    for (size_t i = 1; i < tmp.m_data.size(); ++i) {
        tmp.m_data[i] = this->m_data[i - 1] / i;
    }
    return tmp;
}

mpfr_class mpfr_polynomial::integral(const mpfr_class& left, const mpfr_class& right) const {
    mpfr_polynomial antiderivative = this->antiderivative();
    mpfr_class right_value = antiderivative.evaluate_at(right);
    mpfr_class left_value = antiderivative.evaluate_at(left);
    return right_value - left_value;
}

void mpfr_polynomial::set_zero() {
    this->set_max_degree(0);
    this->m_data[0].set_zero(true);
}

void mpfr_polynomial::set_neg() {
    for (size_t i = 0; i < this->m_data.size(); ++i) {
        this->m_data[i].set_neg();
    }
}

size_t mpfr_polynomial::get_degree() const {
    size_t degree = 0;
    for (size_t i = 0; i < this->m_data.size(); ++i) {
        if (this->m_data[i] != 0) {
            degree = i;
        }
    }
    return degree;
}

size_t mpfr_polynomial::get_max_degree() const {
    return this->m_data.size() - 1;
}

void mpfr_polynomial::set_max_degree(const size_t degree) {
    size_t new_size = degree + 1;
    if (this->m_data.size() < new_size) {
        size_t delta = new_size - this->m_data.size();
        mpfr_class initial_value;
        for (size_t i = 0; i < delta; ++i) {
            this->m_data.push_back(initial_value);
        }
    } else if (this->m_data.size() > new_size) {
        this->m_data.erase(this->m_data.begin() + new_size, this->m_data.end());
    }
}
