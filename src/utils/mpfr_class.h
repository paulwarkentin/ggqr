//
//  mpfr_class.h
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

#ifndef __MPFR_CLASS_H__
#define __MPFR_CLASS_H__

#include <stdint.h>
#include <mpfr.h>
#include <string>

class mpfr_class {

private:

    mpfr_t m_raw;

public:

    mpfr_class();
    mpfr_class(const mpfr_class& other);
    mpfr_class(const mpfr_ptr other);
    mpfr_class(const int other, const mpfr_prec_t prec = mpfr_class::get_default_prec(), const mpfr_rnd_t rnd = mpfr_class::get_default_rnd());
    mpfr_class(const long int other, const mpfr_prec_t prec = mpfr_class::get_default_prec(), const mpfr_rnd_t rnd = mpfr_class::get_default_rnd());
    mpfr_class(const long long int other, const mpfr_prec_t prec = mpfr_class::get_default_prec(), const mpfr_rnd_t rnd = mpfr_class::get_default_rnd());
    mpfr_class(const unsigned int other, const mpfr_prec_t prec = mpfr_class::get_default_prec(), const mpfr_rnd_t rnd = mpfr_class::get_default_rnd());
    mpfr_class(const unsigned long int other, const mpfr_prec_t prec = mpfr_class::get_default_prec(), const mpfr_rnd_t rnd = mpfr_class::get_default_rnd());
    mpfr_class(const unsigned long long int other, const mpfr_prec_t prec = mpfr_class::get_default_prec(), const mpfr_rnd_t rnd = mpfr_class::get_default_rnd());
    mpfr_class(const float other, const mpfr_prec_t prec = mpfr_class::get_default_prec(), const mpfr_rnd_t rnd = mpfr_class::get_default_rnd());
    mpfr_class(const double other, const mpfr_prec_t prec = mpfr_class::get_default_prec(), const mpfr_rnd_t rnd = mpfr_class::get_default_rnd());
    mpfr_class(const long double other, const mpfr_prec_t prec = mpfr_class::get_default_prec(), const mpfr_rnd_t rnd = mpfr_class::get_default_rnd());
    mpfr_class(const char *other, const mpfr_prec_t prec = mpfr_class::get_default_prec(), const int base = 10, const mpfr_rnd_t rnd = mpfr_class::get_default_rnd());
    mpfr_class(const std::string& other, const mpfr_prec_t prec = mpfr_class::get_default_prec(), const int base = 10, const mpfr_rnd_t rnd = mpfr_class::get_default_rnd());
    ~mpfr_class();

    mpfr_class& operator=(const mpfr_class& other);
    mpfr_class& operator=(const mpfr_ptr other);
    mpfr_class& operator=(const int other);
    mpfr_class& operator=(const long int other);
    mpfr_class& operator=(const long long int other);
    mpfr_class& operator=(const unsigned int other);
    mpfr_class& operator=(const unsigned long int other);
    mpfr_class& operator=(const unsigned long long int other);
    mpfr_class& operator=(const float other);
    mpfr_class& operator=(const double other);
    mpfr_class& operator=(const long double other);
    mpfr_class& operator=(const char *other);
    mpfr_class& operator=(const std::string& other);

    mpfr_class operator+(const mpfr_class& other) const;
    mpfr_class operator+(const mpfr_ptr other) const;
    mpfr_class operator+(const int other) const;
    mpfr_class operator+(const long int other) const;
    mpfr_class operator+(const long long int other) const;
    mpfr_class operator+(const unsigned int other) const;
    mpfr_class operator+(const unsigned long int other) const;
    mpfr_class operator+(const unsigned long long int other) const;
    mpfr_class operator+(const float other) const;
    mpfr_class operator+(const double other) const;
    mpfr_class operator+(const long double other) const;

    friend mpfr_class operator+(const mpfr_ptr left, const mpfr_class& right);
    friend mpfr_class operator+(const int left, const mpfr_class& right);
    friend mpfr_class operator+(const long int left, const mpfr_class& right);
    friend mpfr_class operator+(const long long int left, const mpfr_class& right);
    friend mpfr_class operator+(const unsigned int left, const mpfr_class& right);
    friend mpfr_class operator+(const unsigned long int left, const mpfr_class& right);
    friend mpfr_class operator+(const unsigned long long int left, const mpfr_class& right);
    friend mpfr_class operator+(const float left, const mpfr_class& right);
    friend mpfr_class operator+(const double left, const mpfr_class& right);
    friend mpfr_class operator+(const long double left, const mpfr_class& right);

    mpfr_class& operator+=(const mpfr_class& other);
    mpfr_class& operator+=(const mpfr_ptr other);
    mpfr_class& operator+=(const int other);
    mpfr_class& operator+=(const long int other);
    mpfr_class& operator+=(const long long int other);
    mpfr_class& operator+=(const unsigned int other);
    mpfr_class& operator+=(const unsigned long int other);
    mpfr_class& operator+=(const unsigned long long int other);
    mpfr_class& operator+=(const float other);
    mpfr_class& operator+=(const double other);
    mpfr_class& operator+=(const long double other);

    mpfr_class operator+() const;

    mpfr_class operator++(int);
    mpfr_class& operator++();

    mpfr_class operator-(const mpfr_class& other) const;
    mpfr_class operator-(const mpfr_ptr other) const;
    mpfr_class operator-(const int other) const;
    mpfr_class operator-(const long int other) const;
    mpfr_class operator-(const long long int other) const;
    mpfr_class operator-(const unsigned int other) const;
    mpfr_class operator-(const unsigned long int other) const;
    mpfr_class operator-(const unsigned long long int other) const;
    mpfr_class operator-(const float other) const;
    mpfr_class operator-(const double other) const;
    mpfr_class operator-(const long double other) const;

    friend mpfr_class operator-(const mpfr_ptr left, const mpfr_class& right);
    friend mpfr_class operator-(const int left, const mpfr_class& right);
    friend mpfr_class operator-(const long int left, const mpfr_class& right);
    friend mpfr_class operator-(const long long int left, const mpfr_class& right);
    friend mpfr_class operator-(const unsigned int left, const mpfr_class& right);
    friend mpfr_class operator-(const unsigned long int left, const mpfr_class& right);
    friend mpfr_class operator-(const unsigned long long int left, const mpfr_class& right);
    friend mpfr_class operator-(const float left, const mpfr_class& right);
    friend mpfr_class operator-(const double left, const mpfr_class& right);
    friend mpfr_class operator-(const long double left, const mpfr_class& right);

    mpfr_class& operator-=(const mpfr_class& other);
    mpfr_class& operator-=(const mpfr_ptr other);
    mpfr_class& operator-=(const int other);
    mpfr_class& operator-=(const long int other);
    mpfr_class& operator-=(const long long int other);
    mpfr_class& operator-=(const unsigned int other);
    mpfr_class& operator-=(const unsigned long int other);
    mpfr_class& operator-=(const unsigned long long int other);
    mpfr_class& operator-=(const float other);
    mpfr_class& operator-=(const double other);
    mpfr_class& operator-=(const long double other);

    mpfr_class operator-() const;

    mpfr_class operator--(int);
    mpfr_class& operator--();

    mpfr_class operator*(const mpfr_class& other) const;
    mpfr_class operator*(const mpfr_ptr other) const;
    mpfr_class operator*(const int other) const;
    mpfr_class operator*(const long int other) const;
    mpfr_class operator*(const long long int other) const;
    mpfr_class operator*(const unsigned int other) const;
    mpfr_class operator*(const unsigned long int other) const;
    mpfr_class operator*(const unsigned long long int other) const;
    mpfr_class operator*(const float other) const;
    mpfr_class operator*(const double other) const;
    mpfr_class operator*(const long double other) const;

    friend mpfr_class operator*(const mpfr_ptr left, const mpfr_class& right);
    friend mpfr_class operator*(const int left, const mpfr_class& right);
    friend mpfr_class operator*(const long int left, const mpfr_class& right);
    friend mpfr_class operator*(const long long int left, const mpfr_class& right);
    friend mpfr_class operator*(const unsigned int left, const mpfr_class& right);
    friend mpfr_class operator*(const unsigned long int left, const mpfr_class& right);
    friend mpfr_class operator*(const unsigned long long int left, const mpfr_class& right);
    friend mpfr_class operator*(const float left, const mpfr_class& right);
    friend mpfr_class operator*(const double left, const mpfr_class& right);
    friend mpfr_class operator*(const long double left, const mpfr_class& right);

    mpfr_class& operator*=(const mpfr_class& other);
    mpfr_class& operator*=(const mpfr_ptr other);
    mpfr_class& operator*=(const int other);
    mpfr_class& operator*=(const long int other);
    mpfr_class& operator*=(const long long int other);
    mpfr_class& operator*=(const unsigned int other);
    mpfr_class& operator*=(const unsigned long int other);
    mpfr_class& operator*=(const unsigned long long int other);
    mpfr_class& operator*=(const float other);
    mpfr_class& operator*=(const double other);
    mpfr_class& operator*=(const long double other);

    mpfr_class operator/(const mpfr_class& other) const;
    mpfr_class operator/(const mpfr_ptr other) const;
    mpfr_class operator/(const int other) const;
    mpfr_class operator/(const long int other) const;
    mpfr_class operator/(const long long int other) const;
    mpfr_class operator/(const unsigned int other) const;
    mpfr_class operator/(const unsigned long int other) const;
    mpfr_class operator/(const unsigned long long int other) const;
    mpfr_class operator/(const float other) const;
    mpfr_class operator/(const double other) const;
    mpfr_class operator/(const long double other) const;

    friend mpfr_class operator/(const mpfr_ptr left, const mpfr_class& right);
    friend mpfr_class operator/(const int left, const mpfr_class& right);
    friend mpfr_class operator/(const long int left, const mpfr_class& right);
    friend mpfr_class operator/(const long long int left, const mpfr_class& right);
    friend mpfr_class operator/(const unsigned int left, const mpfr_class& right);
    friend mpfr_class operator/(const unsigned long int left, const mpfr_class& right);
    friend mpfr_class operator/(const unsigned long long int left, const mpfr_class& right);
    friend mpfr_class operator/(const float left, const mpfr_class& right);
    friend mpfr_class operator/(const double left, const mpfr_class& right);
    friend mpfr_class operator/(const long double left, const mpfr_class& right);

    mpfr_class& operator/=(const mpfr_class& other);
    mpfr_class& operator/=(const mpfr_ptr other);
    mpfr_class& operator/=(const int other);
    mpfr_class& operator/=(const long int other);
    mpfr_class& operator/=(const long long int other);
    mpfr_class& operator/=(const unsigned int other);
    mpfr_class& operator/=(const unsigned long int other);
    mpfr_class& operator/=(const unsigned long long int other);
    mpfr_class& operator/=(const float other);
    mpfr_class& operator/=(const double other);
    mpfr_class& operator/=(const long double other);

    mpfr_class operator^(const mpfr_class& other) const;
    mpfr_class operator^(const mpfr_ptr other) const;
    mpfr_class operator^(const int other) const;
    mpfr_class operator^(const long int other) const;
    mpfr_class operator^(const long long int other) const;
    mpfr_class operator^(const unsigned int other) const;
    mpfr_class operator^(const unsigned long int other) const;
    mpfr_class operator^(const unsigned long long int other) const;
    mpfr_class operator^(const float other) const;
    mpfr_class operator^(const double other) const;
    mpfr_class operator^(const long double other) const;

    friend mpfr_class operator^(const mpfr_ptr left, const mpfr_class& right);
    friend mpfr_class operator^(const int left, const mpfr_class& right);
    friend mpfr_class operator^(const long int left, const mpfr_class& right);
    friend mpfr_class operator^(const long long int left, const mpfr_class& right);
    friend mpfr_class operator^(const unsigned int left, const mpfr_class& right);
    friend mpfr_class operator^(const unsigned long int left, const mpfr_class& right);
    friend mpfr_class operator^(const unsigned long long int left, const mpfr_class& right);
    friend mpfr_class operator^(const float left, const mpfr_class& right);
    friend mpfr_class operator^(const double left, const mpfr_class& right);
    friend mpfr_class operator^(const long double left, const mpfr_class& right);

    mpfr_class& operator^=(const mpfr_class& other);
    mpfr_class& operator^=(const mpfr_ptr other);
    mpfr_class& operator^=(const int other);
    mpfr_class& operator^=(const long int other);
    mpfr_class& operator^=(const long long int other);
    mpfr_class& operator^=(const unsigned int other);
    mpfr_class& operator^=(const unsigned long int other);
    mpfr_class& operator^=(const unsigned long long int other);
    mpfr_class& operator^=(const float other);
    mpfr_class& operator^=(const double other);
    mpfr_class& operator^=(const long double other);

    bool operator==(const mpfr_class& other) const;
    bool operator==(const mpfr_ptr other) const;
    bool operator==(const int other) const;
    bool operator==(const long int other) const;
    bool operator==(const long long int other) const;
    bool operator==(const unsigned int other) const;
    bool operator==(const unsigned long int other) const;
    bool operator==(const unsigned long long int other) const;
    bool operator==(const float other) const;
    bool operator==(const double other) const;
    bool operator==(const long double other) const;

    friend bool operator==(const mpfr_ptr left, const mpfr_class& right);
    friend bool operator==(const int left, const mpfr_class& right);
    friend bool operator==(const long int left, const mpfr_class& right);
    friend bool operator==(const long long int left, const mpfr_class& right);
    friend bool operator==(const unsigned int left, const mpfr_class& right);
    friend bool operator==(const unsigned long int left, const mpfr_class& right);
    friend bool operator==(const unsigned long long int left, const mpfr_class& right);
    friend bool operator==(const float left, const mpfr_class& right);
    friend bool operator==(const double left, const mpfr_class& right);
    friend bool operator==(const long double left, const mpfr_class& right);

    bool operator!=(const mpfr_class& other) const;
    bool operator!=(const mpfr_ptr other) const;
    bool operator!=(const int other) const;
    bool operator!=(const long int other) const;
    bool operator!=(const long long int other) const;
    bool operator!=(const unsigned int other) const;
    bool operator!=(const unsigned long int other) const;
    bool operator!=(const unsigned long long int other) const;
    bool operator!=(const float other) const;
    bool operator!=(const double other) const;
    bool operator!=(const long double other) const;

    friend bool operator!=(const mpfr_ptr left, const mpfr_class& right);
    friend bool operator!=(const int left, const mpfr_class& right);
    friend bool operator!=(const long int left, const mpfr_class& right);
    friend bool operator!=(const long long int left, const mpfr_class& right);
    friend bool operator!=(const unsigned int left, const mpfr_class& right);
    friend bool operator!=(const unsigned long int left, const mpfr_class& right);
    friend bool operator!=(const unsigned long long int left, const mpfr_class& right);
    friend bool operator!=(const float left, const mpfr_class& right);
    friend bool operator!=(const double left, const mpfr_class& right);
    friend bool operator!=(const long double left, const mpfr_class& right);

    bool operator<(const mpfr_class& other) const;
    bool operator<(const mpfr_ptr other) const;
    bool operator<(const int other) const;
    bool operator<(const long int other) const;
    bool operator<(const long long int other) const;
    bool operator<(const unsigned int other) const;
    bool operator<(const unsigned long int other) const;
    bool operator<(const unsigned long long int other) const;
    bool operator<(const float other) const;
    bool operator<(const double other) const;
    bool operator<(const long double other) const;

    friend bool operator<(const mpfr_ptr left, const mpfr_class& right);
    friend bool operator<(const int left, const mpfr_class& right);
    friend bool operator<(const long int left, const mpfr_class& right);
    friend bool operator<(const long long int left, const mpfr_class& right);
    friend bool operator<(const unsigned int left, const mpfr_class& right);
    friend bool operator<(const unsigned long int left, const mpfr_class& right);
    friend bool operator<(const unsigned long long int left, const mpfr_class& right);
    friend bool operator<(const float left, const mpfr_class& right);
    friend bool operator<(const double left, const mpfr_class& right);
    friend bool operator<(const long double left, const mpfr_class& right);

    bool operator<=(const mpfr_class& other) const;
    bool operator<=(const mpfr_ptr other) const;
    bool operator<=(const int other) const;
    bool operator<=(const long int other) const;
    bool operator<=(const long long int other) const;
    bool operator<=(const unsigned int other) const;
    bool operator<=(const unsigned long int other) const;
    bool operator<=(const unsigned long long int other) const;
    bool operator<=(const float other) const;
    bool operator<=(const double other) const;
    bool operator<=(const long double other) const;

    friend bool operator<=(const mpfr_ptr left, const mpfr_class& right);
    friend bool operator<=(const int left, const mpfr_class& right);
    friend bool operator<=(const long int left, const mpfr_class& right);
    friend bool operator<=(const long long int left, const mpfr_class& right);
    friend bool operator<=(const unsigned int left, const mpfr_class& right);
    friend bool operator<=(const unsigned long int left, const mpfr_class& right);
    friend bool operator<=(const unsigned long long int left, const mpfr_class& right);
    friend bool operator<=(const float left, const mpfr_class& right);
    friend bool operator<=(const double left, const mpfr_class& right);
    friend bool operator<=(const long double left, const mpfr_class& right);

    bool operator>(const mpfr_class& other) const;
    bool operator>(const mpfr_ptr other) const;
    bool operator>(const int other) const;
    bool operator>(const long int other) const;
    bool operator>(const long long int other) const;
    bool operator>(const unsigned int other) const;
    bool operator>(const unsigned long int other) const;
    bool operator>(const unsigned long long int other) const;
    bool operator>(const float other) const;
    bool operator>(const double other) const;
    bool operator>(const long double other) const;

    friend bool operator>(const mpfr_ptr left, const mpfr_class& right);
    friend bool operator>(const int left, const mpfr_class& right);
    friend bool operator>(const long int left, const mpfr_class& right);
    friend bool operator>(const long long int left, const mpfr_class& right);
    friend bool operator>(const unsigned int left, const mpfr_class& right);
    friend bool operator>(const unsigned long int left, const mpfr_class& right);
    friend bool operator>(const unsigned long long int left, const mpfr_class& right);
    friend bool operator>(const float left, const mpfr_class& right);
    friend bool operator>(const double left, const mpfr_class& right);
    friend bool operator>(const long double left, const mpfr_class& right);

    bool operator>=(const mpfr_class& other) const;
    bool operator>=(const mpfr_ptr other) const;
    bool operator>=(const int other) const;
    bool operator>=(const long int other) const;
    bool operator>=(const long long int other) const;
    bool operator>=(const unsigned int other) const;
    bool operator>=(const unsigned long int other) const;
    bool operator>=(const unsigned long long int other) const;
    bool operator>=(const float other) const;
    bool operator>=(const double other) const;
    bool operator>=(const long double other) const;

    friend bool operator>=(const mpfr_ptr left, const mpfr_class& right);
    friend bool operator>=(const int left, const mpfr_class& right);
    friend bool operator>=(const long int left, const mpfr_class& right);
    friend bool operator>=(const long long int left, const mpfr_class& right);
    friend bool operator>=(const unsigned int left, const mpfr_class& right);
    friend bool operator>=(const unsigned long int left, const mpfr_class& right);
    friend bool operator>=(const unsigned long long int left, const mpfr_class& right);
    friend bool operator>=(const float left, const mpfr_class& right);
    friend bool operator>=(const double left, const mpfr_class& right);
    friend bool operator>=(const long double left, const mpfr_class& right);

    mpfr_class pow_value(const mpfr_class& exponent) const;
    void to_pow(const mpfr_class& exponent);

    int int_value() const;
    long int long_value() const;
    long long int llong_value() const;
    int uint_value() const;
    long int ulong_value() const;
    long long int ullong_value() const;
    float float_value() const;
    double double_value() const;
    long double ldouble_value() const;

#if __has_feature(cxx_explicit_conversions)
    explicit operator int() const { return this->int_value(); }
    explicit operator long int() const { return this->long_value(); }
    explicit operator long long int() const { return this->llong_value(); }
    explicit operator unsigned int() const { return this->uint_value(); }
    explicit operator unsigned long int() const { return this->ulong_value(); }
    explicit operator unsigned long long int() const { return this->ullong_value(); }
    explicit operator float() const { return this->float_value(); }
    explicit operator double() const { return this->double_value(); }
    explicit operator long double() const { return this->ldouble_value(); }
#endif

    friend std::ostream& operator<<(std::ostream& left, const mpfr_class& right);
    friend std::istream& operator>>(std::istream& left, mpfr_class& right);

    std::string get_str() const;
    std::string get_str_with_format(std::string format) const;
    void set_str(const std::string& other, const int base, const mpfr_rnd_t rnd);

    mpfr_class abs_value() const;
    void to_abs();

    mpfr_class sqrt_value() const;
    void to_sqrt();

    mpfr_class log_value() const;
    void to_log();

    mpfr_class log2_value() const;
    void to_log2();

    mpfr_class log10_value() const;
    void to_log10();

    mpfr_class exp_value() const;
    void to_exp();

    mpfr_class exp2_value() const;
    void to_exp2();

    mpfr_class exp10_value() const;
    void to_exp10();

    mpfr_class cos_value() const;
    void to_cos();

    mpfr_class sin_value() const;
    void to_sin();

    mpfr_class tan_value() const;
    void to_tan();

    mpfr_prec_t get_prec() const;
    void set_prec(mpfr_prec_t prec);

    bool is_nan() const;
    bool is_inf() const;
    bool is_number() const;
    bool is_zero() const;
    bool is_regular() const;

    void set_nan();
    void set_inf(int sign);
    void set_zero(int sign);
    void set_neg();

    int get_sign() const;
    void set_sign(int sign);

    void clear();

public:

    static mpfr_rnd_t get_default_rnd();
    static void set_default_rnd(mpfr_rnd_t rnd);

    static mpfr_prec_t get_default_prec();
    static void set_default_prec(mpfr_prec_t prec);

    static mpfr_class const_log2();
    static mpfr_class const_pi();
    static mpfr_class const_euler();
    static mpfr_class const_catalan();

}; // class mpfr_class

#endif // __MPFR_CLASS_H__
