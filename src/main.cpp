//
//  main.cpp
//  Generalized Gaussian Quadrature
//
//  Created by Paul Warkentin on 07.09.16.
//  Copyright © 2016 Paul Warkentin. All rights reserved.
//

#include <stdint.h>
#include <mpfr.h>
#include <string>
#include <iostream>

#include "ggqr/ggqr.h"

mpfr_class func_f(const mpfr_class& point) {
    return point.sin_value();
}

int main(int argc, const char * argv[]) {
    ggqr quadrature_rules;
    quadrature_rules.set_precision(512);
    quadrature_rules.set_singularity(ggqr::ggqr_logarithm); // ggqr_logarithm | ggqr_exponentiation
    quadrature_rules.set_singularity_exponent(0);
    quadrature_rules.set_error_tolerance("1e-20");
    quadrature_rules.set_max_damping(5);
    quadrature_rules.set_n_nodes(10);
    quadrature_rules.set_evaluation_function(func_f);
    quadrature_rules.set_left_limit(0);
    quadrature_rules.set_right_limit(1);
    quadrature_rules.execute();
    return 0;
}
