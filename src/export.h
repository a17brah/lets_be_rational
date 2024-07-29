#ifndef PY_LETS_BE_RATIONAL_EXPORT_H
#define PY_LETS_BE_RATIONAL_EXPORT_H

#include "lets_be_rational.h"
#include <nanobind/nanobind.h>
#include <nanobind/stl/vector.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>

namespace nb = nanobind;

void impliedVolatility(
        nb::ndarray<double, nb::shape<nb::any>> output,
        const nb::ndarray<double, nb::shape<nb::any>> &price,
        const nb::ndarray<double, nb::shape<nb::any>> &F,
        const nb::ndarray<double, nb::shape<nb::any>> &K,
        const nb::ndarray<double, nb::shape<nb::any>> &T,
        const nb::ndarray<double, nb::shape<nb::any>> &q /* q=±1 */);

#endif //PY_LETS_BE_RATIONAL_EXPORT_H
