#include "fixed_size_arith_bn254_scalar.hpp"


ap_uint<508> mult(ap_uint<254> in_a, ap_uint<254> in_b) {
    return bn254_scalar_ab_multiplier(in_a, in_b);
}

ap_uint<254> red(ap_uint<508> in) {
    ap_uint<509> l1 = bn254_scalar_m_multiplier(in(508-1, 254));
    ap_uint<509> l1s = bn254_scalar_p_multiplier(l1(509-1, 254));
    ap_uint<254+4> rr = add_piped_inline(ap_uint<254+4>(in(254+4-1, 0)), ap_uint<254+4>(~l1s(254+4-1, 0)), ap_uint<1>(1));
    return basic_mod(PMOD, rr);
}
