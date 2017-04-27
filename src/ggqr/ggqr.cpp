//
//  ggqr.cpp
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

#include "ggqr.h"

#include <iostream>
#include <iomanip>

#include "ggqr_lagrange.h"
#include "ggqr_lu.h"
#include "../utils/mpfr_polynomial.h"

ggqr::ggqr() {
    mpfr_class::set_default_prec(512);
    this->m_singularity = ggqr_logarithm;
    this->m_exponent = 0;
    this->m_error_tolerance = "1e-20";
    this->m_max_damping = 5;
    this->m_n_nodes = 10;
    this->m_eval_func = NULL;
    this->m_left_limit = 0;
    this->m_right_limit = 1;
}

ggqr::~ggqr() {
}

void ggqr::set_precision(const mpfr_prec_t precision) {
    mpfr_class::set_default_prec(precision);
}

void ggqr::set_singularity(const singularity_type singularity) {
    this->m_singularity = singularity;
}

void ggqr::set_singularity_exponent(const mpfr_class& exponent) {
    this->m_exponent = exponent;
}

void ggqr::set_error_tolerance(const mpfr_class& error_tolerance) {
    this->m_error_tolerance = error_tolerance;
}

void ggqr::set_max_damping(const size_t max_damping) {
    this->m_max_damping = max_damping;
}

void ggqr::set_n_nodes(const size_t n_nodes) {
    this->m_n_nodes = n_nodes;
}

void ggqr::set_evaluation_function(mpfr_class (*eval_func)(const mpfr_class&)) {
    this->m_eval_func = eval_func;
}

void ggqr::set_left_limit(const mpfr_class& left_limit) {
    this->m_left_limit = left_limit;
}

void ggqr::set_right_limit(const mpfr_class& right_limit) {
    this->m_right_limit = right_limit;
}

mpfr_class ggqr::singularity_value(const mpfr_class& value) {
    switch (this->m_singularity) {
        case ggqr_exponentiation: { // => x^e
            return (value ^ this->m_exponent);
        } break;
        case ggqr_logarithm: { // => log(x)
            return value.log_value();
        } break;
        default: {
            printf("ggqr[%s:%d]: Undefined singularity function.\n", __FILE__, __LINE__);
            abort();
        }
    }
}

mpfr_class ggqr::singularity_value_inverse(const mpfr_class& value) {
    switch (this->m_singularity) {
        case ggqr_exponentiation: { // => x^(1/e)
            mpfr_class exponent = 1 / this->m_exponent;
            return (value ^ exponent);
        } break;
        case ggqr_logarithm: { // => exp(x)
            return value.exp_value();
        } break;
        default: {
            printf("ggqr[%s:%d]: Undefined singularity function.\n", __FILE__, __LINE__);
            abort();
        }
    }
}

mpfr_class ggqr::singularity_value_derivation(const mpfr_class& value) {
    switch (this->m_singularity) {
        case ggqr_exponentiation: { // => e * x^(e-1)
            return (this->m_exponent * (value ^ (this->m_exponent - 1)));
        } break;
        case ggqr_logarithm: { // => 1/x
            return (1 / value);
        } break;
        default: {
            printf("ggqr[%s:%d]: Undefined singularity function.\n", __FILE__, __LINE__);
            abort();
        }
    }
}

mpfr_class ggqr::basis_value(const mpfr_class& value, const size_t k) {
    if (k % 2 == 0) { // => x^(k/2)
        return (value ^ (k / 2));
    }
    // => x^((k-1)/2) * psi(x)
    return ((value ^ ((k - 1) / 2)) * this->singularity_value(value));
}

mpfr_class ggqr::basis_value_derivation(const mpfr_class& value, const size_t k) {
    if (k % 2 == 0) {
        if (k == 0) {
            return 0;
        } else { // => (k/2) * x^(k/2-1)
            return ((k / 2) * (value ^ ((k / 2) - 1)));
        }
    }
    if (k == 1) { // => psi'(x)
        return this->singularity_value_derivation(value);
    }
    switch (this->m_singularity) {
        case ggqr_exponentiation: { // => (e + (k-1)/2) * x^(e + (k-3)/2)
            mpfr_class tmp = this->m_exponent + ((k - 3) / 2);
            return ((this->m_exponent + ((k - 1) / 2)) * (value ^ tmp));
        } break;
        case ggqr_logarithm: { // => x^((k-3)/2) * ((k-1)/2 * log(x) + 1)
            mpfr_class tmp = ((k - 1) / 2) * value.log_value() + 1;
            return (tmp * (value ^ ((k - 3) / 2)));
        } break;
        default: {
            printf("ggqr[%s:%d]: Undefined singularity function.\n", __FILE__, __LINE__);
            abort();
        }
    }
}

mpfr_class ggqr::basis_value_antiderivation(const mpfr_class& value, const size_t k) {
    if (k % 2 == 0) { // => 1/((k+2)/2) * x^((k+2)/2)
        size_t tmp = (k + 2) / 2;
        return ((value ^ tmp) / tmp);
    }
    switch (this->m_singularity) {
        case ggqr_exponentiation: { // => (2/(2*e+k+1)) * x^((2*e+k+1)/2)
            mpfr_class tmp = (2 * this->m_exponent + k + 1) / 2;
            return ((value ^ tmp) / tmp);
        } break;
        case ggqr_logarithm: { // => (2*x^((k+1)/2) * ((k+1)*log(x)-2)) / ((k+1)*(k+1))
            mpfr_class tmp = (k + 1) * (k + 1);
            return ((2 * (value ^ ((k + 1) / 2)) * (((k + 1) * value.log_value()) - 2)) / tmp);
        } break;
        default: {
            printf("ggqr[%s:%d]: Undefined singularity function.\n", __FILE__, __LINE__);
            abort();
        }
    }
}

mpfr_class ggqr::basis_value_integration(const size_t k) {
    return (this->basis_value_antiderivation(this->m_right_limit, k) -
            this->basis_value_antiderivation(this->m_left_limit + this->m_delta, k));
}

mpfr_vector ggqr::function_f_value(const mpfr_vector& nodes_weights) {
    if (nodes_weights.size() % 2 == 1) {
        printf("ggqr[%s:%d]: The size of the vector must be even.\n", __FILE__, __LINE__);
        abort();
    }
    mpfr_vector::size_t n = nodes_weights.size() / 2;
    mpfr_vector result(nodes_weights.size(), 0);
    for (mpfr_vector::size_t i = 0; i < nodes_weights.size(); ++i) {
        for (mpfr_vector::size_t j = 0; j < n; ++j) {
            result[i] += nodes_weights[n + j] * this->basis_value(nodes_weights[j], i);
        }
        result[i] -= this->basis_value_integration(i);
    }
    return result;
}

mpfr_matrix ggqr::function_f_value_derivation(const mpfr_vector& nodes_weights) {
    if (nodes_weights.size() % 2 == 1) {
        printf("ggqr[%s:%d]: The size of the vector must be even.\n", __FILE__, __LINE__);
        abort();
    }
    mpfr_vector::size_t n = nodes_weights.size() / 2;
    mpfr_matrix result(nodes_weights.size(), nodes_weights.size(), 0);
    for (mpfr_vector::size_t i = 0; i < nodes_weights.size(); ++i) {
        for (mpfr_vector::size_t j = 0; j < n; ++j) {
            result[i][j] = nodes_weights[n + j] * this->basis_value_derivation(nodes_weights[j], i);
        }
        for (mpfr_vector::size_t j = n; j < nodes_weights.size(); ++j) {
            result[i][j] = this->basis_value(nodes_weights[j - n], i);
        }
    }
    return result;
}

mpfr_class ggqr::starting_point() { // psi^-1( (Psi(b)-Psi(a+d)) / (b-(a+d)) )
    mpfr_class limit_delta = this->m_right_limit - (this->m_left_limit + this->m_delta);
    mpfr_class value = this->basis_value_integration(1) / limit_delta;
    return this->singularity_value_inverse(value);
}

mpfr_vector ggqr::starting_points(const mpfr_vector& previous_nodes) {
    mpfr_vector::size_t size = previous_nodes.size();
    mpfr_vector nodes(size + 1);
    nodes[0] = (this->m_left_limit + this->m_delta + previous_nodes[0]) / 2;
    for (mpfr_vector::size_t i = 1; i < size; ++i) {
        nodes[i] = (previous_nodes[i - 1] + previous_nodes[i]) / 2;
    }
    nodes[size] = (previous_nodes[size - 1] + this->m_right_limit) / 2;
    return nodes;
}

mpfr_vector ggqr::starting_weights(const mpfr_vector& nodes) {
    mpfr_vector::size_t size = nodes.size();
    mpfr_class left_limit = this->m_left_limit + this->m_delta;
    if (size == 1) {
        mpfr_vector weight(1);
        weight[0] = this->m_right_limit - left_limit;
        return weight;
    }
    ggqr_lagrange lagrange(nodes);
    lagrange.calculate();
    mpfr_vector weights(size);
    for (mpfr_vector::size_t i = 0; i < size; ++i) {
        mpfr_polynomial basis_polynomial = lagrange.get_basis_polynomial(i);
        weights[i] = basis_polynomial.integral(left_limit, this->m_right_limit);
    }
    return weights;
}

mpfr_vector ggqr::starting_values(const size_t n_nodes) {
    mpfr_vector nodes(1, this->starting_point());
    for (mpfr_vector::size_t i = 1; i < n_nodes; ++i) {
        nodes = this->starting_points(nodes);
    }
    mpfr_vector weights = this->starting_weights(nodes);
    mpfr_vector nodes_weights(2 * n_nodes);
    for (mpfr_vector::size_t i = 0; i < n_nodes; ++i) {
        nodes_weights[i] = nodes[i];
        nodes_weights[n_nodes + i] = weights[i];
    }
    return nodes_weights;
}

void ggqr::execute() {
    this->do_calculation_level_delta();
    this->output_nodes_weights();
    this->output_evaluation();
}

void ggqr::do_calculation_level_delta() {
    size_t n_steps;
    size_t n_dampings;
    mpfr_vector previous_x, x;
    this->m_delta = (this->m_right_limit - this->m_left_limit) / 1000;
    this->output_head();
    for (size_t i = 0;; ++i) {
        x = this->do_calculation_level_main(n_steps, n_dampings);
        if (i > 0) {
            mpfr_vector dx = x - previous_x;
            mpfr_class error = dx.euclidean_norm();
            this->output_step(i + 1, this->m_delta, error, n_steps, n_dampings);
            if (error < this->m_error_tolerance) {
                break;
            }
        } else {
            this->output_step(i + 1, this->m_delta, mpfr_class(), n_steps, n_dampings);
        }
        previous_x = x;
        this->m_delta /= 1e+6;
    }
    this->m_out_nodes = mpfr_vector(this->m_n_nodes);
    this->m_out_weights = mpfr_vector(this->m_n_nodes);
    for (mpfr_vector::size_t i = 0; i < this->m_n_nodes; ++i) {
        this->m_out_nodes[i] = x[i];
        this->m_out_weights[i] = x[this->m_n_nodes + i];
    }
}

mpfr_vector ggqr::do_calculation_level_main(size_t& out_n_steps, size_t& out_n_dampings) {
    mpfr_vector start_x = this->starting_values(1);
    mpfr_vector x;
    size_t n_newton_steps = 0;
    size_t n_newton_dampings = 0;
    out_n_steps = 0;
    out_n_dampings = 0;
    for (size_t i = 0; i < this->m_n_nodes; ++i) {
        x = this->do_calculation_level_newton(start_x, n_newton_steps, n_newton_dampings);
        out_n_steps += n_newton_steps;
        out_n_dampings += n_newton_dampings;
        if (i == this->m_n_nodes - 1) {
            break;
        }
        mpfr_vector nodes(i + 1);
        for (mpfr_vector::size_t i = 0; i < nodes.size(); ++i) {
            nodes[i] = x[i];
        }
        start_x = this->starting_points(nodes);
        mpfr_vector weights = this->starting_weights(start_x);
        start_x.append(weights);
    }
    return x;
}

mpfr_vector ggqr::do_calculation_level_newton(const mpfr_vector& start_x, size_t& out_n_steps, size_t& out_n_dampings) {
    mpfr_vector x = start_x;
    mpfr_class damping = 1;
    bool use_damping = false;
    out_n_steps = 0;
    out_n_dampings = 0;
    for (size_t i = 0, j = 1;; ++i, ++j) {
        mpfr_vector func_f = this->function_f_value(x);
        mpfr_matrix jac_f = this->function_f_value_derivation(x);
        ggqr_lu lu_decomposition(jac_f);
        lu_decomposition.decompose();
        mpfr_vector dx = lu_decomposition.solve(func_f);
        if (dx.contains_nan()) {
            damping *= 2;
            x = start_x;
            ++i, j = 0;
            if (!use_damping) {
                use_damping = true;
            }
            continue;
        }
        if (use_damping && j < this->m_max_damping) {
            ++out_n_dampings;
            dx /= damping;
        }
        x -= dx;
        if (j > 1) {
            mpfr_class error = dx.euclidean_norm();
            if (error < this->m_error_tolerance) {
                out_n_steps = j - 1;
                break;
            }
        }
    }
    return x;
}

void ggqr::output_head() const {
    std::cout << "Calculate a quadrature rule with "
              << this->m_n_nodes
              << " points in ["
              << this->m_left_limit.get_str_with_format("%.2Rf")
              << ", "
              << this->m_right_limit.get_str_with_format("%.2Rf")
              << "]:"
              << std::endl;
    std::cout << "                   Delta             Error    No.Steps    No.Dampings"
              << std::endl;
    std::cout << "    -----------------------------------------------------------------"
              << std::endl;
}

void ggqr::output_step(const size_t step, const mpfr_class& delta, const mpfr_class& error, const size_t n_steps, const size_t n_dampings) const {
    if (error.is_nan()) {
        std::cout << "    "
                  << std::setw(4) << step
                  << "    "
                  << delta.get_str_with_format("%+12.4RE")
                  << "                --       "
                  << std::setw(5) << n_steps
                  << "          "
                  << std::setw(5) << n_dampings
                  << std::endl;
    } else {
        std::cout << "    "
                  << std::setw(4) << step
                  << "    "
                  << delta.get_str_with_format("%+12.4RE")
                  << "    "
                  << error.get_str_with_format("%14.6RE")
                  << "       "
                  << std::setw(5) << n_steps
                  << "          "
                  << std::setw(5) << n_dampings
                  << std::endl;
    }
}

void ggqr::output_nodes_weights() const {
    std::cout << "Nodes and weights:" << std::endl;
    for (mpfr_vector::size_t i = 0; i < this->m_n_nodes; ++i) {
        std::cout << "    x["
                  << std::setw(2) << i + 1
                  << "] = "
                  << this->m_out_nodes[i].get_str_with_format("%+.20Rf")
                  << "    w["
                  << std::setw(2) << i + 1
                  << "] = "
                  << this->m_out_weights[i].get_str_with_format("%+.20Rf")
                  << std::endl;
    }
}

void ggqr::output_evaluation() const {
    if (this->m_eval_func == NULL) {
        return;
    }
    mpfr_class eval = 0;
    for (mpfr_vector::size_t i = 0; i < this->m_n_nodes; ++i) {
        eval += this->m_out_weights[i] * (*this->m_eval_func)(this->m_out_nodes[i]);
    }
    std::cout << "Evaluation of the integrand:"
              << std::endl
              << "    Q[f] = "
              << eval.get_str_with_format("%+.20Rf")
              << std::endl;
}
