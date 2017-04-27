//
//  ggqr.h
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

#ifndef __GGQR_H__
#define __GGQR_H__

#include "../utils/mpfr_class.h"
#include "../utils/mpfr_vector.h"
#include "../utils/mpfr_matrix.h"

class ggqr {

public:

    typedef enum singularity_type {
        ggqr_undefined = 0,
        ggqr_exponentiation = 1,
        ggqr_logarithm = 2
    } singularity_type;

    typedef unsigned long size_t;

private:

    singularity_type m_singularity;
    mpfr_class m_exponent;

    mpfr_class m_error_tolerance;
    size_t m_max_damping;

    size_t m_n_nodes;
    mpfr_class (*m_eval_func)(const mpfr_class&);

    mpfr_class m_left_limit;
    mpfr_class m_right_limit;

    mpfr_vector m_out_nodes;
    mpfr_vector m_out_weights;
    mpfr_class m_delta;

public:

    ggqr();
    ~ggqr();

    void set_precision(const mpfr_prec_t precision);
    void set_singularity(const singularity_type singularity);
    void set_singularity_exponent(const mpfr_class& exponent);
    void set_error_tolerance(const mpfr_class& error_tolerance);
    void set_max_damping(const size_t max_damping);
    void set_n_nodes(const size_t n_nodes);
    void set_evaluation_function(mpfr_class (*eval_func)(const mpfr_class&));
    void set_left_limit(const mpfr_class& left_limit);
    void set_right_limit(const mpfr_class& right_limit);

    mpfr_class singularity_value(const mpfr_class& value);
    mpfr_class singularity_value_inverse(const mpfr_class& value);
    mpfr_class singularity_value_derivation(const mpfr_class& value);

    mpfr_class basis_value(const mpfr_class& value, const size_t k);
    mpfr_class basis_value_derivation(const mpfr_class& value, const size_t k);
    mpfr_class basis_value_antiderivation(const mpfr_class& value, const size_t k);
    mpfr_class basis_value_integration(const size_t k);

    mpfr_vector function_f_value(const mpfr_vector& nodes_weights);
    mpfr_matrix function_f_value_derivation(const mpfr_vector& nodes_weights);

    mpfr_class starting_point();
    mpfr_vector starting_points(const mpfr_vector& previous_nodes);
    mpfr_vector starting_weights(const mpfr_vector& nodes);
    mpfr_vector starting_values(const size_t n_nodes);

    void execute();

private:

    void do_calculation_level_delta();
    mpfr_vector do_calculation_level_main(size_t& out_n_steps, size_t& out_n_dampings);
    mpfr_vector do_calculation_level_newton(const mpfr_vector& start_x, size_t& out_n_steps, size_t& out_n_dampings);

    void output_head() const;
    void output_step(const size_t step, const mpfr_class& delta, const mpfr_class& error, const size_t n_steps, const size_t n_dampings) const;
    void output_nodes_weights() const;
    void output_evaluation() const;

}; // class ggqr

#endif // __GGQR_H__
