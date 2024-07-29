import numpy as np
import sys


FLOAT_MAX = sys.float_info.max
MINUS_FLOAT_MAX = - FLOAT_MAX


binary_flag = {'c': 1, 'p': -1, 1: 1, -1: -1, '1': 1, '-1': -1}


def _preprocess_flags(flags):
    return np.array([binary_flag[f] for f in flags], dtype=np.float64)


def _maybe_format_data(data):
    dtype = np.float64
    if isinstance(data, (int, float)):
        return np.array([data], dtype=dtype)
    elif isinstance(data, (list, tuple)):
        return np.array(data, dtype=dtype)
    elif isinstance(data, np.ndarray):
        return data.astype(dtype=dtype)
    raise ValueError(f"Data type {type(data)} unsupported, must be in: list, tuple, np.array.")


def maybe_format_data_and_broadcast(*all_data):
    dtype = np.float64
    data_numpy = tuple(np.ravel(_maybe_format_data(d)) for d in all_data)
    return [np.ascontiguousarray(a, dtype=dtype) for a in np.broadcast_arrays(*data_numpy)]
