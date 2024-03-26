import pytest
from py_lets_be_rational import implied_volatility
import numpy as np


def test_implied_volatility():
    dtype = np.float64
    S = np.array([100.0, 120.0], dtype=dtype)
    K = np.array([100.0, 100.0], dtype=dtype)
    t = np.array([1.0, 1.0], dtype=dtype)
    P = np.array([7.966, 2.147], dtype=dtype)
    q = np.array([1, -1]) #call, put
    output = np.zeros_like(S)
    expected = np.array([0.2, 0.2], dtype=dtype)
    implied_volatility(output, P, S, K, t, q)
    np.testing.assert_allclose(expected, output, atol=1e-4)


