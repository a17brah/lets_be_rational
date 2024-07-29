#ifndef PY_LETS_BE_RATIONAL_EXPORT_H
#define PY_LETS_BE_RATIONAL_EXPORT_H

#include "lets_be_rational.h"
#include <nanobind/nanobind.h>
#include <nanobind/stl/vector.h>
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>

namespace nb = nanobind;

void impliedVolatility(
        nb::ndarray<double, nb::shape<-1>> output,
        const nb::ndarray<double, nb::shape<-1>> &price,
        const nb::ndarray<double, nb::shape<-1>> &F,
        const nb::ndarray<double, nb::shape<-1>> &K,
        const nb::ndarray<double, nb::shape<-1>> &T,
        const nb::ndarray<double, nb::shape<-1>> &q /* q=±1 */);

#endif //PY_LETS_BE_RATIONAL_EXPORT_H
