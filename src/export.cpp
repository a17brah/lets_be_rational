#include "lets_be_rational.h"
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>

namespace nb = nanobind;

//check corner cases
void impliedVolatility(
        nb::ndarray<double, nb::shape<-1>> output,
        const nb::ndarray<double, nb::shape<-1>> &price,
        const nb::ndarray<double, nb::shape<-1>> &F,
        const nb::ndarray<double, nb::shape<-1>> &K,
        const nb::ndarray<double, nb::shape<-1>> &T,
        const nb::ndarray<double, nb::shape<-1>> &q /* q=±1 */) {
    //check same size;
    size_t n = price.size();
    if (n != K.size() || n != q.size() || n != output.size() || n != T.size() || n != F.size()) {
        throw std::runtime_error("Error: All input arrays must have the same size.");
    }

    for (std::size_t i = 0; i < n; ++i) {
        double res = implied_volatility_from_a_transformed_rational_guess(price(i), F(i), K(i), T(i), q(i));
        output(i) = res;
    }
};

NB_MODULE(lets_be_rational_core, m) {
    m.def("implied_volatility_core", &impliedVolatility,
          R"pbdoc(
              Calculate implied volatility.

              Args:
                  output (numpy.ndarray): Output array to store the results.
                  price (numpy.ndarray): Input array of prices.
                  F (float): forward.
                  K (numpy.ndarray): Input array of strikes.
                  t (float): Time parameter.
                  q (numpy.ndarray): Input array of q values.

              Returns:
                  None
          )pbdoc");
}