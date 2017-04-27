# GGQR (Generalized Gaussian Quadrature Rules)

This project was created in the context of my bachelor thesis in Mathematics. The results were
calculated with the [GNU MP Bignum Library](https://gmplib.org).

## Abstract

In this console application, we consider the problem of a Gaussian quadrature rule on [a,b] for
integrands with a singularity in the endpoint a. This rule consists of quadrature points in the
given interval and associated weights that are strictly positive.

## Getting Started

### Prerequisites

GGQR only uses the external library [GNU MPFR Library](http://www.mpfr.org) which is based on the
[GNU MP Bignum Library](https://gmplib.org).
Please install these two libraries in order to compile GGQR successfully.

### Compiling

The project contains the makefile, I was able to compile the project with. Please adapt the paths
to GMP and MPFR in the makefile to your installation locations.

## Built With

- [GNU MP Bignum Library](https://gmplib.org)
- [GNU MPFR Library](http://www.mpfr.org)

## To Do

- Add comments to the project
- Increase performance on `mpfr_class`
- Extend `mpfr_vector`, `mpfr_matrix`, `mpfr_polynomial`

## Contributing

When contributing to this repository, please first discuss the change you wish to make via
[email](mailto:paul@warkentin.email), or any other method with the owners of this repository
before making a change.

Please note we have a code of conduct, please follow it in all your interactions with the project.

## Authors

- Paul A. Warkentin - [Email](mailto:paul@warkentin.email) - [GitHub](https://github.com/paulwarkentin)

## License

This project is licensed under the MIT License - see the
[LICENSE](LICENSE) file for details.
