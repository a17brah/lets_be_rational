#include "export.h"
#include <iostream>

namespace nb = nanobind;
constexpr double DOUBLE_MAX = 1.7976931348623157e+308;

//check corner cases
void impliedVolatility(
        nb::ndarray<double, nb::shape<nb::any>> output,
        const nb::ndarray<double, nb::shape<nb::any>> &price,
        const nb::ndarray<double, nb::shape<nb::any>> &F,
        const nb::ndarray<double, nb::shape<nb::any>> &K,
        const nb::ndarray<double, nb::shape<nb::any>> &T,
        const nb::ndarray<double, nb::shape<nb::any>> &q /* q=±1 */) {
    //check same size;
    size_t n = price.size();
    if (n != K.size() || n != q.size() || n != output.size() || n != T.size() || n != F.size())
    {
        throw std::runtime_error("Error: All input arrays must have the same size.");
    }

    #pragma omp parallel for
    for (int64_t i = 0; i < n; ++i) {
        double res = implied_volatility_from_a_transformed_rational_guess(price(i), F(i), K(i), T(i), q(i));
        if (std::fabs(res) == DOUBLE_MAX) {
            res = 0;
        }
        output(i) = res;
    }
};

NB_MODULE(_lets_be_rational_core, m_) {
    nb::module_ m = nb::module_::import_("py_lets_be_rational");

    m.def("implied_volatility", &impliedVolatility,
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