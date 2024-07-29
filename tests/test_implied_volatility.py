import pytest
from lets_be_rational.implied_volatility import implied_volatility
import numpy as np
import sys

MINUS_FLOAT = -sys.float_info.max


def test_implied_volatility():
    dtype = np.float64
    F = np.array([100.0, 120.0, 100.0, 100], dtype=dtype)
    K = np.array([100.0, 100.0, 90.0, 80.0], dtype=dtype)
    t = np.array([1.0, 1.0, 1.0, 1.0], dtype=dtype)
    P = np.array([7.966, 2.14729, 1.0, 80.0], dtype=dtype)
    q = np.array([1, -1, 1, -1])  # call, put
    expected = np.array([0.2, 0.2, np.nan, np.nan], dtype=dtype)
    output = implied_volatility(P, F, K, t, q)
    np.testing.assert_allclose(expected, output, atol=1e-4)