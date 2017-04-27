//
//  mpfr_class.cpp
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

#include "mpfr_class.h"

#include <iostream>

mpfr_class::mpfr_class() {
    mpfr_init2(this->m_raw, mpfr_class::get_default_prec());
    mpfr_set_nan(this->m_raw);
}

mpfr_class::mpfr_class(const mpfr_class& other) {
    mpfr_init2(this->m_raw, mpfr_get_prec(other.m_raw));
    mpfr_set(this->m_raw, other.m_raw, mpfr_class::get_default_rnd());
}

mpfr_class::mpfr_class(const mpfr_ptr other) {
    mpfr_init2(this->m_raw, mpfr_get_prec(other));
    mpfr_set(this->m_raw, other, mpfr_class::get_default_rnd());
}

mpfr_class::mpfr_class(const int other, const mpfr_prec_t prec, const mpfr_rnd_t rnd) {
    mpfr_init2(this->m_raw, prec);
    mpfr_set_si(this->m_raw, other, rnd);
}

mpfr_class::mpfr_class(const long int other, const mpfr_prec_t prec, const mpfr_rnd_t rnd) {
    mpfr_init2(this->m_raw, prec);
    mpfr_set_si(this->m_raw, other, rnd);
}

mpfr_class::mpfr_class(const long long int other, const mpfr_prec_t prec, const mpfr_rnd_t rnd) {
    mpfr_init2(this->m_raw, prec);
    mpfr_set_sj(this->m_raw, other, rnd);
}

mpfr_class::mpfr_class(const unsigned int other, const mpfr_prec_t prec, const mpfr_rnd_t rnd) {
    mpfr_init2(this->m_raw, prec);
    mpfr_set_ui(this->m_raw, other, rnd);
}

mpfr_class::mpfr_class(const unsigned long int other, const mpfr_prec_t prec, const mpfr_rnd_t rnd) {
    mpfr_init2(this->m_raw, prec);
    mpfr_set_ui(this->m_raw, other, rnd);
}

mpfr_class::mpfr_class(const unsigned long long int other, const mpfr_prec_t prec, const mpfr_rnd_t rnd) {
    mpfr_init2(this->m_raw, prec);
    mpfr_set_uj(this->m_raw, other, rnd);
}

mpfr_class::mpfr_class(const float other, const mpfr_prec_t prec, const mpfr_rnd_t rnd) {
    mpfr_init2(this->m_raw, prec);
    mpfr_set_flt(this->m_raw, other, rnd);
}

mpfr_class::mpfr_class(const double other, const mpfr_prec_t prec, const mpfr_rnd_t rnd) {
    mpfr_init2(this->m_raw, prec);
    mpfr_set_d(this->m_raw, other, rnd);
}

mpfr_class::mpfr_class(const long double other, const mpfr_prec_t prec, const mpfr_rnd_t rnd) {
    mpfr_init2(this->m_raw, prec);
    mpfr_set_ld(this->m_raw, other, rnd);
}

mpfr_class::mpfr_class(const char *other, const mpfr_prec_t prec, const int base, const mpfr_rnd_t rnd) {
    mpfr_init2(this->m_raw, prec);
    std::string tmp_other = other;
    this->set_str(tmp_other, base, rnd);
}

mpfr_class::mpfr_class(const std::string& other, const mpfr_prec_t prec, const int base, const mpfr_rnd_t rnd) {
    mpfr_init2(this->m_raw, prec);
    this->set_str(other, base, rnd);
}

mpfr_class::~mpfr_class() {
    this->clear();
}

mpfr_class& mpfr_class::operator=(const mpfr_class& other) {
    if (&other != this) {
        mpfr_set_prec(this->m_raw, mpfr_get_prec(other.m_raw));
        mpfr_set(this->m_raw, other.m_raw, mpfr_class::get_default_rnd());
    }
    return *this;
}

mpfr_class& mpfr_class::operator=(const mpfr_ptr other) {
    mpfr_set_prec(this->m_raw, mpfr_get_prec(other));
    mpfr_set(this->m_raw, other, mpfr_class::get_default_rnd());
    return *this;
}

mpfr_class& mpfr_class::operator=(const int other) {
    mpfr_init2(this->m_raw, mpfr_class::get_default_prec());
    mpfr_set_si(this->m_raw, other, mpfr_class::get_default_rnd());
    return *this;
}

mpfr_class& mpfr_class::operator=(const long int other) {
    mpfr_init2(this->m_raw, mpfr_class::get_default_prec());
    mpfr_set_si(this->m_raw, other, mpfr_class::get_default_rnd());
    return *this;
}

mpfr_class& mpfr_class::operator=(const long long int other) {
    mpfr_init2(this->m_raw, mpfr_class::get_default_prec());
    mpfr_set_sj(this->m_raw, other, mpfr_class::get_default_rnd());
    return *this;
}

mpfr_class& mpfr_class::operator=(const unsigned int other) {
    mpfr_init2(this->m_raw, mpfr_class::get_default_prec());
    mpfr_set_ui(this->m_raw, other, mpfr_class::get_default_rnd());
    return *this;
}

mpfr_class& mpfr_class::operator=(const unsigned long int other) {
    mpfr_init2(this->m_raw, mpfr_class::get_default_prec());
    mpfr_set_ui(this->m_raw, other, mpfr_class::get_default_rnd());
    return *this;
}

mpfr_class& mpfr_class::operator=(const unsigned long long int other) {
    mpfr_init2(this->m_raw, mpfr_class::get_default_prec());
    mpfr_set_uj(this->m_raw, other, mpfr_class::get_default_rnd());
    return *this;
}

mpfr_class& mpfr_class::operator=(const float other) {
    mpfr_init2(this->m_raw, mpfr_class::get_default_prec());
    mpfr_set_flt(this->m_raw, other, mpfr_class::get_default_rnd());
    return *this;
}

mpfr_class& mpfr_class::operator=(const double other) {
    mpfr_init2(this->m_raw, mpfr_class::get_default_prec());
    mpfr_set_d(this->m_raw, other, mpfr_class::get_default_rnd());
    return *this;
}

mpfr_class& mpfr_class::operator=(const long double other) {
    mpfr_init2(this->m_raw, mpfr_class::get_default_prec());
    mpfr_set_ld(this->m_raw, other, mpfr_class::get_default_rnd());
    return *this;
}

mpfr_class& mpfr_class::operator=(const char *other) {
    std::string tmp_other = other;
    this->set_str(tmp_other, 10, mpfr_class::get_default_rnd());
    return *this;
}

mpfr_class& mpfr_class::operator=(const std::string& other) {
    this->set_str(other, 10, mpfr_class::get_default_rnd());
    return *this;
}

mpfr_class mpfr_class::operator+(const mpfr_class& other) const {
    mpfr_class tmp = *this;
    mpfr_add(tmp.m_raw, tmp.m_raw, other.m_raw, mpfr_class::get_default_rnd());
    return tmp;
}

mpfr_class mpfr_class::operator+(const mpfr_ptr other) const {
    mpfr_class tmp_other(other);
    return this->operator+(tmp_other);
}

mpfr_class mpfr_class::operator+(const int other) const {
    mpfr_class tmp_other(other);
    return this->operator+(tmp_other);
}

mpfr_class mpfr_class::operator+(const long int other) const {
    mpfr_class tmp_other(other);
    return this->operator+(tmp_other);
}

mpfr_class mpfr_class::operator+(const long long int other) const {
    mpfr_class tmp_other(other);
    return this->operator+(tmp_other);
}

mpfr_class mpfr_class::operator+(const unsigned int other) const {
    mpfr_class tmp_other(other);
    return this->operator+(tmp_other);
}

mpfr_class mpfr_class::operator+(const unsigned long int other) const {
    mpfr_class tmp_other(other);
    return this->operator+(tmp_other);
}

mpfr_class mpfr_class::operator+(const unsigned long long int other) const {
    mpfr_class tmp_other(other);
    return this->operator+(tmp_other);
}

mpfr_class mpfr_class::operator+(const float other) const {
    mpfr_class tmp_other(other);
    return this->operator+(tmp_other);
}

mpfr_class mpfr_class::operator+(const double other) const {
    mpfr_class tmp_other(other);
    return this->operator+(tmp_other);
}

mpfr_class mpfr_class::operator+(const long double other) const {
    mpfr_class tmp_other(other);
    return this->operator+(tmp_other);
}

mpfr_class operator+(const mpfr_ptr left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator+(right);
}

mpfr_class operator+(const int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator+(right);
}

mpfr_class operator+(const long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator+(right);
}

mpfr_class operator+(const long long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator+(right);
}

mpfr_class operator+(const unsigned int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator+(right);
}

mpfr_class operator+(const unsigned long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator+(right);
}

mpfr_class operator+(const unsigned long long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator+(right);
}

mpfr_class operator+(const float left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator+(right);
}

mpfr_class operator+(const double left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator+(right);
}

mpfr_class operator+(const long double left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator+(right);
}

mpfr_class& mpfr_class::operator+=(const mpfr_class& other) {
    mpfr_add(this->m_raw, this->m_raw, other.m_raw, mpfr_class::get_default_rnd());
    return *this;
}

mpfr_class& mpfr_class::operator+=(const mpfr_ptr other) {
    mpfr_class tmp_other(other);
    return this->operator+=(tmp_other);
}

mpfr_class& mpfr_class::operator+=(const int other) {
    mpfr_class tmp_other(other);
    return this->operator+=(tmp_other);
}

mpfr_class& mpfr_class::operator+=(const long int other) {
    mpfr_class tmp_other(other);
    return this->operator+=(tmp_other);
}

mpfr_class& mpfr_class::operator+=(const long long int other) {
    mpfr_class tmp_other(other);
    return this->operator+=(tmp_other);
}

mpfr_class& mpfr_class::operator+=(const unsigned int other) {
    mpfr_class tmp_other(other);
    return this->operator+=(tmp_other);
}

mpfr_class& mpfr_class::operator+=(const unsigned long int other) {
    mpfr_class tmp_other(other);
    return this->operator+=(tmp_other);
}

mpfr_class& mpfr_class::operator+=(const unsigned long long int other) {
    mpfr_class tmp_other(other);
    return this->operator+=(tmp_other);
}

mpfr_class& mpfr_class::operator+=(const float other) {
    mpfr_class tmp_other(other);
    return this->operator+=(tmp_other);
}

mpfr_class& mpfr_class::operator+=(const double other) {
    mpfr_class tmp_other(other);
    return this->operator+=(tmp_other);
}

mpfr_class& mpfr_class::operator+=(const long double other) {
    mpfr_class tmp_other(other);
    return this->operator+=(tmp_other);
}

mpfr_class mpfr_class::operator+() const {
    return mpfr_class(*this);
}

mpfr_class mpfr_class::operator++(int) {
    mpfr_class tmp = *this;
    this->operator+=((unsigned int)1);
    return tmp;
}

mpfr_class& mpfr_class::operator++() {
    return this->operator+=((unsigned int)1);
}

mpfr_class mpfr_class::operator-(const mpfr_class& other) const {
    mpfr_class tmp = *this;
    mpfr_sub(tmp.m_raw, tmp.m_raw, other.m_raw, mpfr_class::get_default_rnd());
    return tmp;
}

mpfr_class mpfr_class::operator-(const mpfr_ptr other) const {
    mpfr_class tmp_other(other);
    return this->operator-(tmp_other);
}

mpfr_class mpfr_class::operator-(const int other) const {
    mpfr_class tmp_other(other);
    return this->operator-(tmp_other);
}

mpfr_class mpfr_class::operator-(const long int other) const {
    mpfr_class tmp_other(other);
    return this->operator-(tmp_other);
}

mpfr_class mpfr_class::operator-(const long long int other) const {
    mpfr_class tmp_other(other);
    return this->operator-(tmp_other);
}

mpfr_class mpfr_class::operator-(const unsigned int other) const {
    mpfr_class tmp_other(other);
    return this->operator-(tmp_other);
}

mpfr_class mpfr_class::operator-(const unsigned long int other) const {
    mpfr_class tmp_other(other);
    return this->operator-(tmp_other);
}

mpfr_class mpfr_class::operator-(const unsigned long long int other) const {
    mpfr_class tmp_other(other);
    return this->operator-(tmp_other);
}

mpfr_class mpfr_class::operator-(const float other) const {
    mpfr_class tmp_other(other);
    return this->operator-(tmp_other);
}

mpfr_class mpfr_class::operator-(const double other) const {
    mpfr_class tmp_other(other);
    return this->operator-(tmp_other);
}

mpfr_class mpfr_class::operator-(const long double other) const {
    mpfr_class tmp_other(other);
    return this->operator-(tmp_other);
}

mpfr_class operator-(const mpfr_ptr left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator-(right);
}

mpfr_class operator-(const int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator-(right);
}

mpfr_class operator-(const long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator-(right);
}

mpfr_class operator-(const long long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator-(right);
}

mpfr_class operator-(const unsigned int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator-(right);
}

mpfr_class operator-(const unsigned long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator-(right);
}

mpfr_class operator-(const unsigned long long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator-(right);
}

mpfr_class operator-(const float left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator-(right);
}

mpfr_class operator-(const double left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator-(right);
}

mpfr_class operator-(const long double left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator-(right);
}

mpfr_class& mpfr_class::operator-=(const mpfr_class& other) {
    mpfr_sub(this->m_raw, this->m_raw, other.m_raw, mpfr_class::get_default_rnd());
    return *this;
}

mpfr_class& mpfr_class::operator-=(const mpfr_ptr other) {
    mpfr_class tmp_other(other);
    return this->operator-=(tmp_other);
}

mpfr_class& mpfr_class::operator-=(const int other) {
    mpfr_class tmp_other(other);
    return this->operator-=(tmp_other);
}

mpfr_class& mpfr_class::operator-=(const long int other) {
    mpfr_class tmp_other(other);
    return this->operator-=(tmp_other);
}

mpfr_class& mpfr_class::operator-=(const long long int other) {
    mpfr_class tmp_other(other);
    return this->operator-=(tmp_other);
}

mpfr_class& mpfr_class::operator-=(const unsigned int other) {
    mpfr_class tmp_other(other);
    return this->operator-=(tmp_other);
}

mpfr_class& mpfr_class::operator-=(const unsigned long int other) {
    mpfr_class tmp_other(other);
    return this->operator-=(tmp_other);
}

mpfr_class& mpfr_class::operator-=(const unsigned long long int other) {
    mpfr_class tmp_other(other);
    return this->operator-=(tmp_other);
}

mpfr_class& mpfr_class::operator-=(const float other) {
    mpfr_class tmp_other(other);
    return this->operator-=(tmp_other);
}

mpfr_class& mpfr_class::operator-=(const double other) {
    mpfr_class tmp_other(other);
    return this->operator-=(tmp_other);
}

mpfr_class& mpfr_class::operator-=(const long double other) {
    mpfr_class tmp_other(other);
    return this->operator-=(tmp_other);
}

mpfr_class mpfr_class::operator-() const {
    mpfr_class tmp = *this;
    tmp.set_neg();
    return tmp;
}

mpfr_class mpfr_class::operator--(int) {
    mpfr_class tmp = *this;
    this->operator-=((unsigned int)1);
    return tmp;
}

mpfr_class& mpfr_class::operator--() {
    return this->operator-=((unsigned int)1);
}

mpfr_class mpfr_class::operator*(const mpfr_class& other) const {
    mpfr_class tmp = *this;
    mpfr_mul(tmp.m_raw, tmp.m_raw, other.m_raw, mpfr_class::get_default_rnd());
    return tmp;
}

mpfr_class mpfr_class::operator*(const mpfr_ptr other) const {
    mpfr_class tmp_other(other);
    return this->operator*(tmp_other);
}

mpfr_class mpfr_class::operator*(const int other) const {
    mpfr_class tmp_other(other);
    return this->operator*(tmp_other);
}

mpfr_class mpfr_class::operator*(const long int other) const {
    mpfr_class tmp_other(other);
    return this->operator*(tmp_other);
}

mpfr_class mpfr_class::operator*(const long long int other) const {
    mpfr_class tmp_other(other);
    return this->operator*(tmp_other);
}

mpfr_class mpfr_class::operator*(const unsigned int other) const {
    mpfr_class tmp_other(other);
    return this->operator*(tmp_other);
}

mpfr_class mpfr_class::operator*(const unsigned long int other) const {
    mpfr_class tmp_other(other);
    return this->operator*(tmp_other);
}

mpfr_class mpfr_class::operator*(const unsigned long long int other) const {
    mpfr_class tmp_other(other);
    return this->operator*(tmp_other);
}

mpfr_class mpfr_class::operator*(const float other) const {
    mpfr_class tmp_other(other);
    return this->operator*(tmp_other);
}

mpfr_class mpfr_class::operator*(const double other) const {
    mpfr_class tmp_other(other);
    return this->operator*(tmp_other);
}

mpfr_class mpfr_class::operator*(const long double other) const {
    mpfr_class tmp_other(other);
    return this->operator*(tmp_other);
}

mpfr_class operator*(const mpfr_ptr left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator*(right);
}

mpfr_class operator*(const int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator*(right);
}

mpfr_class operator*(const long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator*(right);
}

mpfr_class operator*(const long long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator*(right);
}

mpfr_class operator*(const unsigned int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator*(right);
}

mpfr_class operator*(const unsigned long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator*(right);
}

mpfr_class operator*(const unsigned long long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator*(right);
}

mpfr_class operator*(const float left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator*(right);
}

mpfr_class operator*(const double left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator*(right);
}

mpfr_class operator*(const long double left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator*(right);
}

mpfr_class& mpfr_class::operator*=(const mpfr_class& other) {
    mpfr_mul(this->m_raw, this->m_raw, other.m_raw, mpfr_class::get_default_rnd());
    return *this;
}

mpfr_class& mpfr_class::operator*=(const mpfr_ptr other) {
    mpfr_class tmp_other(other);
    return this->operator*=(tmp_other);
}

mpfr_class& mpfr_class::operator*=(const int other) {
    mpfr_class tmp_other(other);
    return this->operator*=(tmp_other);
}

mpfr_class& mpfr_class::operator*=(const long int other) {
    mpfr_class tmp_other(other);
    return this->operator*=(tmp_other);
}

mpfr_class& mpfr_class::operator*=(const long long int other) {
    mpfr_class tmp_other(other);
    return this->operator*=(tmp_other);
}

mpfr_class& mpfr_class::operator*=(const unsigned int other) {
    mpfr_class tmp_other(other);
    return this->operator*=(tmp_other);
}

mpfr_class& mpfr_class::operator*=(const unsigned long int other) {
    mpfr_class tmp_other(other);
    return this->operator*=(tmp_other);
}

mpfr_class& mpfr_class::operator*=(const unsigned long long int other) {
    mpfr_class tmp_other(other);
    return this->operator*=(tmp_other);
}

mpfr_class& mpfr_class::operator*=(const float other) {
    mpfr_class tmp_other(other);
    return this->operator*=(tmp_other);
}

mpfr_class& mpfr_class::operator*=(const double other) {
    mpfr_class tmp_other(other);
    return this->operator*=(tmp_other);
}

mpfr_class& mpfr_class::operator*=(const long double other) {
    mpfr_class tmp_other(other);
    return this->operator*=(tmp_other);
}

mpfr_class mpfr_class::operator/(const mpfr_class& other) const {
    mpfr_class tmp = *this;
    mpfr_div(tmp.m_raw, tmp.m_raw, other.m_raw, mpfr_class::get_default_rnd());
    return tmp;
}

mpfr_class mpfr_class::operator/(const mpfr_ptr other) const {
    mpfr_class tmp_other(other);
    return this->operator/(tmp_other);
}

mpfr_class mpfr_class::operator/(const int other) const {
    mpfr_class tmp_other(other);
    return this->operator/(tmp_other);
}

mpfr_class mpfr_class::operator/(const long int other) const {
    mpfr_class tmp_other(other);
    return this->operator/(tmp_other);
}

mpfr_class mpfr_class::operator/(const long long int other) const {
    mpfr_class tmp_other(other);
    return this->operator/(tmp_other);
}

mpfr_class mpfr_class::operator/(const unsigned int other) const {
    mpfr_class tmp_other(other);
    return this->operator/(tmp_other);
}

mpfr_class mpfr_class::operator/(const unsigned long int other) const {
    mpfr_class tmp_other(other);
    return this->operator/(tmp_other);
}

mpfr_class mpfr_class::operator/(const unsigned long long int other) const {
    mpfr_class tmp_other(other);
    return this->operator/(tmp_other);
}

mpfr_class mpfr_class::operator/(const float other) const {
    mpfr_class tmp_other(other);
    return this->operator/(tmp_other);
}

mpfr_class mpfr_class::operator/(const double other) const {
    mpfr_class tmp_other(other);
    return this->operator/(tmp_other);
}

mpfr_class mpfr_class::operator/(const long double other) const {
    mpfr_class tmp_other(other);
    return this->operator/(tmp_other);
}

mpfr_class operator/(const mpfr_ptr left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator/(right);
}

mpfr_class operator/(const int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator/(right);
}

mpfr_class operator/(const long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator/(right);
}

mpfr_class operator/(const long long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator/(right);
}

mpfr_class operator/(const unsigned int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator/(right);
}

mpfr_class operator/(const unsigned long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator/(right);
}

mpfr_class operator/(const unsigned long long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator/(right);
}

mpfr_class operator/(const float left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator/(right);
}

mpfr_class operator/(const double left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator/(right);
}

mpfr_class operator/(const long double left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator/(right);
}

mpfr_class& mpfr_class::operator/=(const mpfr_class& other) {
    mpfr_div(this->m_raw, this->m_raw, other.m_raw, mpfr_class::get_default_rnd());
    return *this;
}

mpfr_class& mpfr_class::operator/=(const mpfr_ptr other) {
    mpfr_class tmp_other(other);
    return this->operator/=(tmp_other);
}

mpfr_class& mpfr_class::operator/=(const int other) {
    mpfr_class tmp_other(other);
    return this->operator/=(tmp_other);
}

mpfr_class& mpfr_class::operator/=(const long int other) {
    mpfr_class tmp_other(other);
    return this->operator/=(tmp_other);
}

mpfr_class& mpfr_class::operator/=(const long long int other) {
    mpfr_class tmp_other(other);
    return this->operator/=(tmp_other);
}

mpfr_class& mpfr_class::operator/=(const unsigned int other) {
    mpfr_class tmp_other(other);
    return this->operator/=(tmp_other);
}

mpfr_class& mpfr_class::operator/=(const unsigned long int other) {
    mpfr_class tmp_other(other);
    return this->operator/=(tmp_other);
}

mpfr_class& mpfr_class::operator/=(const unsigned long long int other) {
    mpfr_class tmp_other(other);
    return this->operator/=(tmp_other);
}

mpfr_class& mpfr_class::operator/=(const float other) {
    mpfr_class tmp_other(other);
    return this->operator/=(tmp_other);
}

mpfr_class& mpfr_class::operator/=(const double other) {
    mpfr_class tmp_other(other);
    return this->operator/=(tmp_other);
}

mpfr_class& mpfr_class::operator/=(const long double other) {
    mpfr_class tmp_other(other);
    return this->operator/=(tmp_other);
}

mpfr_class mpfr_class::operator^(const mpfr_class& other) const {
    mpfr_class tmp = *this;
    mpfr_pow(tmp.m_raw, tmp.m_raw, other.m_raw, mpfr_class::get_default_rnd());
    return tmp;
}

mpfr_class mpfr_class::operator^(const mpfr_ptr other) const {
    mpfr_class tmp_other(other);
    return this->operator^(tmp_other);
}

mpfr_class mpfr_class::operator^(const int other) const {
    mpfr_class tmp_other(other);
    return this->operator^(tmp_other);
}

mpfr_class mpfr_class::operator^(const long int other) const {
    mpfr_class tmp_other(other);
    return this->operator^(tmp_other);
}

mpfr_class mpfr_class::operator^(const long long int other) const {
    mpfr_class tmp_other(other);
    return this->operator^(tmp_other);
}

mpfr_class mpfr_class::operator^(const unsigned int other) const {
    mpfr_class tmp_other(other);
    return this->operator^(tmp_other);
}

mpfr_class mpfr_class::operator^(const unsigned long int other) const {
    mpfr_class tmp_other(other);
    return this->operator^(tmp_other);
}

mpfr_class mpfr_class::operator^(const unsigned long long int other) const {
    mpfr_class tmp_other(other);
    return this->operator^(tmp_other);
}

mpfr_class mpfr_class::operator^(const float other) const {
    mpfr_class tmp_other(other);
    return this->operator^(tmp_other);
}

mpfr_class mpfr_class::operator^(const double other) const {
    mpfr_class tmp_other(other);
    return this->operator^(tmp_other);
}

mpfr_class mpfr_class::operator^(const long double other) const {
    mpfr_class tmp_other(other);
    return this->operator^(tmp_other);
}

mpfr_class operator^(const mpfr_ptr left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator^(right);
}

mpfr_class operator^(const int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator^(right);
}

mpfr_class operator^(const long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator^(right);
}

mpfr_class operator^(const long long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator^(right);
}

mpfr_class operator^(const unsigned int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator^(right);
}

mpfr_class operator^(const unsigned long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator^(right);
}

mpfr_class operator^(const unsigned long long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator^(right);
}

mpfr_class operator^(const float left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator^(right);
}

mpfr_class operator^(const double left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator^(right);
}

mpfr_class operator^(const long double left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator^(right);
}

mpfr_class& mpfr_class::operator^=(const mpfr_class& other) {
    mpfr_pow(this->m_raw, this->m_raw, other.m_raw, mpfr_class::get_default_rnd());
    return *this;
}

mpfr_class& mpfr_class::operator^=(const mpfr_ptr other) {
    mpfr_class tmp_other(other);
    return this->operator^=(tmp_other);
}

mpfr_class& mpfr_class::operator^=(const int other) {
    mpfr_class tmp_other(other);
    return this->operator^=(tmp_other);
}

mpfr_class& mpfr_class::operator^=(const long int other) {
    mpfr_class tmp_other(other);
    return this->operator^=(tmp_other);
}

mpfr_class& mpfr_class::operator^=(const long long int other) {
    mpfr_class tmp_other(other);
    return this->operator^=(tmp_other);
}

mpfr_class& mpfr_class::operator^=(const unsigned int other) {
    mpfr_class tmp_other(other);
    return this->operator^=(tmp_other);
}

mpfr_class& mpfr_class::operator^=(const unsigned long int other) {
    mpfr_class tmp_other(other);
    return this->operator^=(tmp_other);
}

mpfr_class& mpfr_class::operator^=(const unsigned long long int other) {
    mpfr_class tmp_other(other);
    return this->operator^=(tmp_other);
}

mpfr_class& mpfr_class::operator^=(const float other) {
    mpfr_class tmp_other(other);
    return this->operator^=(tmp_other);
}

mpfr_class& mpfr_class::operator^=(const double other) {
    mpfr_class tmp_other(other);
    return this->operator^=(tmp_other);
}

mpfr_class& mpfr_class::operator^=(const long double other) {
    mpfr_class tmp_other(other);
    return this->operator^=(tmp_other);
}

bool mpfr_class::operator==(const mpfr_class& other) const {
    return (mpfr_cmp(this->m_raw, other.m_raw) == 0);
}

bool mpfr_class::operator==(const mpfr_ptr other) const {
    mpfr_class tmp_other(other);
    return this->operator==(tmp_other);
}

bool mpfr_class::operator==(const int other) const {
    mpfr_class tmp_other(other);
    return this->operator==(tmp_other);
}

bool mpfr_class::operator==(const long int other) const {
    mpfr_class tmp_other(other);
    return this->operator==(tmp_other);
}

bool mpfr_class::operator==(const long long int other) const {
    mpfr_class tmp_other(other);
    return this->operator==(tmp_other);
}

bool mpfr_class::operator==(const unsigned int other) const {
    mpfr_class tmp_other(other);
    return this->operator==(tmp_other);
}

bool mpfr_class::operator==(const unsigned long int other) const {
    mpfr_class tmp_other(other);
    return this->operator==(tmp_other);
}

bool mpfr_class::operator==(const unsigned long long int other) const {
    mpfr_class tmp_other(other);
    return this->operator==(tmp_other);
}

bool mpfr_class::operator==(const float other) const {
    mpfr_class tmp_other(other);
    return this->operator==(tmp_other);
}

bool mpfr_class::operator==(const double other) const {
    mpfr_class tmp_other(other);
    return this->operator==(tmp_other);
}

bool mpfr_class::operator==(const long double other) const {
    mpfr_class tmp_other(other);
    return this->operator==(tmp_other);
}

bool operator==(const mpfr_ptr left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator==(right);
}

bool operator==(const int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator==(right);
}

bool operator==(const long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator==(right);
}

bool operator==(const long long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator==(right);
}

bool operator==(const unsigned int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator==(right);
}

bool operator==(const unsigned long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator==(right);
}

bool operator==(const unsigned long long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator==(right);
}

bool operator==(const float left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator==(right);
}

bool operator==(const double left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator==(right);
}

bool operator==(const long double left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator==(right);
}

bool mpfr_class::operator!=(const mpfr_class& other) const {
    return (mpfr_cmp(this->m_raw, other.m_raw) != 0);
}

bool mpfr_class::operator!=(const mpfr_ptr other) const {
    mpfr_class tmp_other(other);
    return this->operator!=(tmp_other);
}

bool mpfr_class::operator!=(const int other) const {
    mpfr_class tmp_other(other);
    return this->operator!=(tmp_other);
}

bool mpfr_class::operator!=(const long int other) const {
    mpfr_class tmp_other(other);
    return this->operator!=(tmp_other);
}

bool mpfr_class::operator!=(const long long int other) const {
    mpfr_class tmp_other(other);
    return this->operator!=(tmp_other);
}

bool mpfr_class::operator!=(const unsigned int other) const {
    mpfr_class tmp_other(other);
    return this->operator!=(tmp_other);
}

bool mpfr_class::operator!=(const unsigned long int other) const {
    mpfr_class tmp_other(other);
    return this->operator!=(tmp_other);
}

bool mpfr_class::operator!=(const unsigned long long int other) const {
    mpfr_class tmp_other(other);
    return this->operator!=(tmp_other);
}

bool mpfr_class::operator!=(const float other) const {
    mpfr_class tmp_other(other);
    return this->operator!=(tmp_other);
}

bool mpfr_class::operator!=(const double other) const {
    mpfr_class tmp_other(other);
    return this->operator!=(tmp_other);
}

bool mpfr_class::operator!=(const long double other) const {
    mpfr_class tmp_other(other);
    return this->operator!=(tmp_other);
}

bool operator!=(const mpfr_ptr left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator!=(right);
}

bool operator!=(const int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator!=(right);
}

bool operator!=(const long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator!=(right);
}

bool operator!=(const long long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator!=(right);
}

bool operator!=(const unsigned int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator!=(right);
}

bool operator!=(const unsigned long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator!=(right);
}

bool operator!=(const unsigned long long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator!=(right);
}

bool operator!=(const float left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator!=(right);
}

bool operator!=(const double left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator!=(right);
}

bool operator!=(const long double left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator!=(right);
}

bool mpfr_class::operator<(const mpfr_class& other) const {
    return (mpfr_cmp(this->m_raw, other.m_raw) < 0);
}

bool mpfr_class::operator<(const mpfr_ptr other) const {
    mpfr_class tmp_other(other);
    return this->operator<(tmp_other);
}

bool mpfr_class::operator<(const int other) const {
    mpfr_class tmp_other(other);
    return this->operator<(tmp_other);
}

bool mpfr_class::operator<(const long int other) const {
    mpfr_class tmp_other(other);
    return this->operator<(tmp_other);
}

bool mpfr_class::operator<(const long long int other) const {
    mpfr_class tmp_other(other);
    return this->operator<(tmp_other);
}

bool mpfr_class::operator<(const unsigned int other) const {
    mpfr_class tmp_other(other);
    return this->operator<(tmp_other);
}

bool mpfr_class::operator<(const unsigned long int other) const {
    mpfr_class tmp_other(other);
    return this->operator<(tmp_other);
}

bool mpfr_class::operator<(const unsigned long long int other) const {
    mpfr_class tmp_other(other);
    return this->operator<(tmp_other);
}

bool mpfr_class::operator<(const float other) const {
    mpfr_class tmp_other(other);
    return this->operator<(tmp_other);
}

bool mpfr_class::operator<(const double other) const {
    mpfr_class tmp_other(other);
    return this->operator<(tmp_other);
}

bool mpfr_class::operator<(const long double other) const {
    mpfr_class tmp_other(other);
    return this->operator<(tmp_other);
}

bool operator<(const mpfr_ptr left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator<(right);
}

bool operator<(const int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator<(right);
}

bool operator<(const long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator<(right);
}

bool operator<(const long long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator<(right);
}

bool operator<(const unsigned int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator<(right);
}

bool operator<(const unsigned long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator<(right);
}

bool operator<(const unsigned long long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator<(right);
}

bool operator<(const float left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator<(right);
}

bool operator<(const double left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator<(right);
}

bool operator<(const long double left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator<(right);
}

bool mpfr_class::operator<=(const mpfr_class& other) const {
    return (mpfr_cmp(this->m_raw, other.m_raw) <= 0);
}

bool mpfr_class::operator<=(const mpfr_ptr other) const {
    mpfr_class tmp_other(other);
    return this->operator<=(tmp_other);
}

bool mpfr_class::operator<=(const int other) const {
    mpfr_class tmp_other(other);
    return this->operator<=(tmp_other);
}

bool mpfr_class::operator<=(const long int other) const {
    mpfr_class tmp_other(other);
    return this->operator<=(tmp_other);
}

bool mpfr_class::operator<=(const long long int other) const {
    mpfr_class tmp_other(other);
    return this->operator<=(tmp_other);
}

bool mpfr_class::operator<=(const unsigned int other) const {
    mpfr_class tmp_other(other);
    return this->operator<=(tmp_other);
}

bool mpfr_class::operator<=(const unsigned long int other) const {
    mpfr_class tmp_other(other);
    return this->operator<=(tmp_other);
}

bool mpfr_class::operator<=(const unsigned long long int other) const {
    mpfr_class tmp_other(other);
    return this->operator<=(tmp_other);
}

bool mpfr_class::operator<=(const float other) const {
    mpfr_class tmp_other(other);
    return this->operator<=(tmp_other);
}

bool mpfr_class::operator<=(const double other) const {
    mpfr_class tmp_other(other);
    return this->operator<=(tmp_other);
}

bool mpfr_class::operator<=(const long double other) const {
    mpfr_class tmp_other(other);
    return this->operator<=(tmp_other);
}

bool operator<=(const mpfr_ptr left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator<=(right);
}

bool operator<=(const int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator<=(right);
}

bool operator<=(const long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator<=(right);
}

bool operator<=(const long long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator<=(right);
}

bool operator<=(const unsigned int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator<=(right);
}

bool operator<=(const unsigned long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator<=(right);
}

bool operator<=(const unsigned long long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator<=(right);
}

bool operator<=(const float left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator<=(right);
}

bool operator<=(const double left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator<=(right);
}

bool operator<=(const long double left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator<=(right);
}

bool mpfr_class::operator>(const mpfr_class& other) const {
    return (mpfr_cmp(this->m_raw, other.m_raw) > 0);
}

bool mpfr_class::operator>(const mpfr_ptr other) const {
    mpfr_class tmp_other(other);
    return this->operator>(tmp_other);
}

bool mpfr_class::operator>(const int other) const {
    mpfr_class tmp_other(other);
    return this->operator>(tmp_other);
}

bool mpfr_class::operator>(const long int other) const {
    mpfr_class tmp_other(other);
    return this->operator>(tmp_other);
}

bool mpfr_class::operator>(const long long int other) const {
    mpfr_class tmp_other(other);
    return this->operator>(tmp_other);
}

bool mpfr_class::operator>(const unsigned int other) const {
    mpfr_class tmp_other(other);
    return this->operator>(tmp_other);
}

bool mpfr_class::operator>(const unsigned long int other) const {
    mpfr_class tmp_other(other);
    return this->operator>(tmp_other);
}

bool mpfr_class::operator>(const unsigned long long int other) const {
    mpfr_class tmp_other(other);
    return this->operator>(tmp_other);
}

bool mpfr_class::operator>(const float other) const {
    mpfr_class tmp_other(other);
    return this->operator>(tmp_other);
}

bool mpfr_class::operator>(const double other) const {
    mpfr_class tmp_other(other);
    return this->operator>(tmp_other);
}

bool mpfr_class::operator>(const long double other) const {
    mpfr_class tmp_other(other);
    return this->operator>(tmp_other);
}

bool operator>(const mpfr_ptr left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator>(right);
}

bool operator>(const int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator>(right);
}

bool operator>(const long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator>(right);
}

bool operator>(const long long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator>(right);
}

bool operator>(const unsigned int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator>(right);
}

bool operator>(const unsigned long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator>(right);
}

bool operator>(const unsigned long long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator>(right);
}

bool operator>(const float left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator>(right);
}

bool operator>(const double left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator>(right);
}

bool operator>(const long double left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator>(right);
}

bool mpfr_class::operator>=(const mpfr_class& other) const {
    return (mpfr_cmp(this->m_raw, other.m_raw) >= 0);
}

bool mpfr_class::operator>=(const mpfr_ptr other) const {
    mpfr_class tmp_other(other);
    return this->operator>=(tmp_other);
}

bool mpfr_class::operator>=(const int other) const {
    mpfr_class tmp_other(other);
    return this->operator>=(tmp_other);
}

bool mpfr_class::operator>=(const long int other) const {
    mpfr_class tmp_other(other);
    return this->operator>=(tmp_other);
}

bool mpfr_class::operator>=(const long long int other) const {
    mpfr_class tmp_other(other);
    return this->operator>=(tmp_other);
}

bool mpfr_class::operator>=(const unsigned int other) const {
    mpfr_class tmp_other(other);
    return this->operator>=(tmp_other);
}

bool mpfr_class::operator>=(const unsigned long int other) const {
    mpfr_class tmp_other(other);
    return this->operator>=(tmp_other);
}

bool mpfr_class::operator>=(const unsigned long long int other) const {
    mpfr_class tmp_other(other);
    return this->operator>=(tmp_other);
}

bool mpfr_class::operator>=(const float other) const {
    mpfr_class tmp_other(other);
    return this->operator>=(tmp_other);
}

bool mpfr_class::operator>=(const double other) const {
    mpfr_class tmp_other(other);
    return this->operator>=(tmp_other);
}

bool mpfr_class::operator>=(const long double other) const {
    mpfr_class tmp_other(other);
    return this->operator>=(tmp_other);
}

bool operator>=(const mpfr_ptr left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator>=(right);
}

bool operator>=(const int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator>=(right);
}

bool operator>=(const long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator>=(right);
}

bool operator>=(const long long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator>=(right);
}

bool operator>=(const unsigned int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator>=(right);
}

bool operator>=(const unsigned long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator>=(right);
}

bool operator>=(const unsigned long long int left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator>=(right);
}

bool operator>=(const float left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator>=(right);
}

bool operator>=(const double left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator>=(right);
}

bool operator>=(const long double left, const mpfr_class& right) {
    mpfr_class tmp_left(left);
    return tmp_left.operator>=(right);
}

mpfr_class mpfr_class::pow_value(const mpfr_class& exponent) const {
    mpfr_class tmp;
    mpfr_pow(tmp.m_raw, this->m_raw, exponent.m_raw, mpfr_class::get_default_rnd());
    return tmp;
}

void mpfr_class::to_pow(const mpfr_class& exponent) {
    mpfr_pow(this->m_raw, this->m_raw, exponent.m_raw, mpfr_class::get_default_rnd());
}

int mpfr_class::int_value() const {
    return mpfr_get_si(this->m_raw, mpfr_class::get_default_rnd());
}

long int mpfr_class::long_value() const {
    return mpfr_get_si(this->m_raw, mpfr_class::get_default_rnd());
}

long long int mpfr_class::llong_value() const {
    return mpfr_get_sj(this->m_raw, mpfr_class::get_default_rnd());
}

int mpfr_class::uint_value() const {
    return mpfr_get_ui(this->m_raw, mpfr_class::get_default_rnd());
}

long int mpfr_class::ulong_value() const {
    return mpfr_get_ui(this->m_raw, mpfr_class::get_default_rnd());
}

long long int mpfr_class::ullong_value() const {
    return mpfr_get_uj(this->m_raw, mpfr_class::get_default_rnd());
}

float mpfr_class::float_value() const {
    return mpfr_get_flt(this->m_raw, mpfr_class::get_default_rnd());
}

double mpfr_class::double_value() const {
    return mpfr_get_d(this->m_raw, mpfr_class::get_default_rnd());
}

long double mpfr_class::ldouble_value() const {
    return mpfr_get_ld(this->m_raw, mpfr_class::get_default_rnd());
}

std::ostream& operator<<(std::ostream& left, const mpfr_class& right) {
    left << right.get_str();
    return left;
}

std::istream& operator>>(std::istream& left, mpfr_class& right) {
    std::string tmp_string;
    left >> tmp_string;
    right.set_str(tmp_string, 10, mpfr_class::get_default_rnd());
    return left;
}

std::string mpfr_class::get_str() const {
    char buffer[256];
    mpfr_sprintf(buffer, "%+RG", this->m_raw);
    return std::string(buffer);
}

std::string mpfr_class::get_str_with_format(std::string format) const {
    char buffer[256];
    mpfr_sprintf(buffer, format.c_str(), this->m_raw);
    return std::string(buffer);
}

void mpfr_class::set_str(const std::string& other, const int base, const mpfr_rnd_t rnd) {
    mpfr_t tmp;
    mpfr_init2(tmp, mpfr_get_prec(this->m_raw));
    int status = mpfr_set_str(tmp, other.c_str(), base, rnd);
    if (status == 0) {
        mpfr_set(this->m_raw, tmp, rnd);
    } else {
        mpfr_set_nan(this->m_raw);
    }
    mpfr_clear(tmp);
}

mpfr_class mpfr_class::sqrt_value() const {
    mpfr_class tmp;
    mpfr_sqrt(tmp.m_raw, this->m_raw, mpfr_class::get_default_rnd());
    return tmp;
}

void mpfr_class::to_sqrt() {
    mpfr_sqrt(this->m_raw, this->m_raw, mpfr_class::get_default_rnd());
}

mpfr_class mpfr_class::abs_value() const {
    mpfr_class tmp;
    mpfr_abs(tmp.m_raw, this->m_raw, mpfr_class::get_default_rnd());
    return tmp;
}

void mpfr_class::to_abs() {
    mpfr_abs(this->m_raw, this->m_raw, mpfr_class::get_default_rnd());
}

mpfr_class mpfr_class::log_value() const {
    mpfr_class tmp;
    mpfr_log(tmp.m_raw, this->m_raw, mpfr_class::get_default_rnd());
    return tmp;
}

void mpfr_class::to_log() {
    mpfr_log(this->m_raw, this->m_raw, mpfr_class::get_default_rnd());
}

mpfr_class mpfr_class::log2_value() const {
    mpfr_class tmp;
    mpfr_log2(tmp.m_raw, this->m_raw, mpfr_class::get_default_rnd());
    return tmp;
}

void mpfr_class::to_log2() {
    mpfr_log2(this->m_raw, this->m_raw, mpfr_class::get_default_rnd());
}

mpfr_class mpfr_class::log10_value() const {
    mpfr_class tmp;
    mpfr_log10(tmp.m_raw, this->m_raw, mpfr_class::get_default_rnd());
    return tmp;
}

void mpfr_class::to_log10() {
    mpfr_log10(this->m_raw, this->m_raw, mpfr_class::get_default_rnd());
}

mpfr_class mpfr_class::exp_value() const {
    mpfr_class tmp;
    mpfr_exp(tmp.m_raw, this->m_raw, mpfr_class::get_default_rnd());
    return tmp;
}

void mpfr_class::to_exp() {
    mpfr_exp(this->m_raw, this->m_raw, mpfr_class::get_default_rnd());
}

mpfr_class mpfr_class::exp2_value() const {
    mpfr_class tmp;
    mpfr_exp2(tmp.m_raw, this->m_raw, mpfr_class::get_default_rnd());
    return tmp;
}

void mpfr_class::to_exp2() {
    mpfr_exp2(this->m_raw, this->m_raw, mpfr_class::get_default_rnd());
}

mpfr_class mpfr_class::exp10_value() const {
    mpfr_class tmp;
    mpfr_exp10(tmp.m_raw, this->m_raw, mpfr_class::get_default_rnd());
    return tmp;
}

void mpfr_class::to_exp10() {
    mpfr_exp10(this->m_raw, this->m_raw, mpfr_class::get_default_rnd());
}

mpfr_class mpfr_class::cos_value() const {
    mpfr_class tmp;
    mpfr_cos(tmp.m_raw, this->m_raw, mpfr_class::get_default_rnd());
    return tmp;
}

void mpfr_class::to_cos() {
    mpfr_cos(this->m_raw, this->m_raw, mpfr_class::get_default_rnd());
}

mpfr_class mpfr_class::sin_value() const {
    mpfr_class tmp;
    mpfr_sin(tmp.m_raw, this->m_raw, mpfr_class::get_default_rnd());
    return tmp;
}

void mpfr_class::to_sin() {
    mpfr_sin(this->m_raw, this->m_raw, mpfr_class::get_default_rnd());
}

mpfr_class mpfr_class::tan_value() const {
    mpfr_class tmp;
    mpfr_tan(tmp.m_raw, this->m_raw, mpfr_class::get_default_rnd());
    return tmp;
}

void mpfr_class::to_tan() {
    mpfr_tan(this->m_raw, this->m_raw, mpfr_class::get_default_rnd());
}

mpfr_prec_t mpfr_class::get_prec() const {
    return mpfr_get_prec(this->m_raw);
}

void mpfr_class::set_prec(mpfr_prec_t prec) {
    return mpfr_set_prec(this->m_raw, prec);
}

bool mpfr_class::is_nan() const {
    return mpfr_nan_p(this->m_raw) != 0;
}

bool mpfr_class::is_inf() const {
    return mpfr_inf_p(this->m_raw) != 0;
}

bool mpfr_class::is_number() const {
    return mpfr_number_p(this->m_raw) != 0;
}

bool mpfr_class::is_zero() const {
    return mpfr_zero_p(this->m_raw) != 0;
}

bool mpfr_class::is_regular() const {
    return mpfr_regular_p(this->m_raw) != 0;
}

void mpfr_class::set_nan() {
    mpfr_set_nan(this->m_raw);
}

void mpfr_class::set_inf(int sign) {
    mpfr_set_inf(this->m_raw, sign);
}

void mpfr_class::set_zero(int sign) {
    mpfr_set_zero(this->m_raw, sign);
}

void mpfr_class::set_neg() {
    mpfr_neg(this->m_raw, this->m_raw, mpfr_class::get_default_rnd());
}

int mpfr_class::get_sign() const {
    return mpfr_sgn(this->m_raw);
}

void mpfr_class::set_sign(int sign) {
    mpfr_setsign(this->m_raw, this->m_raw, sign, mpfr_class::get_default_rnd());
}

void mpfr_class::clear() {
    mpfr_clear(this->m_raw);
}

mpfr_rnd_t mpfr_class::get_default_rnd() {
    return mpfr_get_default_rounding_mode();
}

void mpfr_class::set_default_rnd(mpfr_rnd_t rnd) {
    mpfr_set_default_rounding_mode(rnd);
}

mpfr_prec_t mpfr_class::get_default_prec() {
    return mpfr_get_default_prec();
}

void mpfr_class::set_default_prec(mpfr_prec_t prec) {
    mpfr_set_default_prec(prec);
}

mpfr_class mpfr_class::const_log2() {
    mpfr_class tmp;
    mpfr_const_log2(tmp.m_raw, mpfr_class::get_default_rnd());
    return tmp;
}

mpfr_class mpfr_class::const_pi() {
    mpfr_class tmp;
    mpfr_const_pi(tmp.m_raw, mpfr_class::get_default_rnd());
    return tmp;
}

mpfr_class mpfr_class::const_euler() {
    mpfr_class tmp;
    mpfr_const_euler(tmp.m_raw, mpfr_class::get_default_rnd());
    return tmp;
}

mpfr_class mpfr_class::const_catalan() {
    mpfr_class tmp(0);
    mpfr_const_catalan(tmp.m_raw, mpfr_class::get_default_rnd());
    return tmp;
}
