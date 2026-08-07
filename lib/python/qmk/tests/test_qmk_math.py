import qmk.math

from nose2.tools import params


@params(('2^6', 4), ('2**6', 64), ('1 + 2*3**(4^5) / (6 + -7)', -5.0))
def test_compute(expr, expected):
    result = qmk.math.compute(expr)
    assert result == expected
