import numpy as np
from .lets_be_rational_core import implied_volatility_core
from .utils.data_format import maybe_format_data_and_broadcast, MINUS_FLOAT_MAX, FLOAT_MAX


def implied_volatility(price, F, K, t, flags) -> np.ndarray:
    price, F, K, t, flags = maybe_format_data_and_broadcast(price, F, K, t, flags)
    sigma = np.zeros_like(price)
    implied_volatility_core(sigma, price, F, K, t, flags)
    sigma[sigma <= MINUS_FLOAT_MAX] = np.nan
    sigma[sigma >= FLOAT_MAX] = np.nan
    return sigma
