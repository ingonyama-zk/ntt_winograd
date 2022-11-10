#include "basic_arith.hpp"
#include FIXED_SIZE_ARITH_HPP


// mult + modulo
template<int W>
ap_uint<W> mult_red(const ap_uint<W> in_a, const ap_uint<W> in_b) {
    ap_uint<2*W> ab = mult(in_a, in_b);
    return red(ab);
}

// add of 2 mults + modulo
template<int W>
ap_uint<W> mult_add_red(const ap_uint<W> in0_a, const ap_uint<W> in0_b, const ap_uint<W> in1_a, const ap_uint<W> in1_b) {
    ap_uint<2*W> ab0 = mult(in0_a, in0_b);
    ap_uint<2*W> ab1 = mult(in1_a, in1_b);
    ap_uint<2*W> ab = basic_add_mod(P2MOD, ab0, ab1);
    return red(ab);
}

// sub of 2 mults + modulo
template<int W>
ap_uint<W> mult_sub_red(const ap_uint<W> in0_a, const ap_uint<W> in0_b, const ap_uint<W> in1_a, const ap_uint<W> in1_b) {
    ap_uint<2*W> ab0 = mult(in0_a, in0_b);
    ap_uint<2*W> ab1 = mult(in1_a, in1_b);
    ap_uint<2*W> ab = basic_sub_mod(P2MOD, ab0, ab1);
    return red(ab);
}

// complex mult
template<int W>
complex_element<2*W> cmult(const complex_element<W> in_a, const complex_element<W> in_b) {
    ap_uint<W> as = basic_add_mod(PMOD, in_a.re, in_a.im);
    ap_uint<W> bs = basic_add_mod(PMOD, in_b.re, in_b.im);
    ap_uint<2*W> asbs = mult(as, bs);
    ap_uint<2*W> arbr = mult(in_a.re, in_b.re);
    ap_uint<2*W> aibi = mult(in_a.im, in_b.im);
    ap_uint<2*W> r2i2 = basic_add_mod(P2MOD, arbr, aibi);
    ap_uint<2*W> abr = basic_sub_mod(P2MOD, arbr, aibi);
    ap_uint<2*W> abi = basic_sub_mod(P2MOD, asbs, r2i2);
    return {abr, abi};
}

// complex mult + modulo
template<int W>
complex_element<W> cmult_red(const complex_element<W> in_a, const complex_element<W> in_b) {
    ap_uint<W> as = basic_add_mod(PMOD, in_a.re, in_a.im);
    ap_uint<W> bs = basic_add_mod(PMOD, in_b.re, in_b.im);
    ap_uint<2*W> asbs = mult(as, bs);
    ap_uint<2*W> arbr = mult(in_a.re, in_b.re);
    ap_uint<2*W> aibi = mult(in_a.im, in_b.im);
    ap_uint<2*W> r2i2 = basic_add_mod(P2MOD, arbr, aibi);
    ap_uint<2*W> abr = basic_sub_mod(P2MOD, arbr, aibi);
    ap_uint<2*W> abi = basic_sub_mod(P2MOD, asbs, r2i2);
    return {red(abr), red(abi)};
}

// add of 2 cmults + modulo
template<int W>
complex_element<W> cmult_add_red(const complex_element<W> in0_a, const complex_element<W> in0_b, const complex_element<W> in1_a, const complex_element<W> in1_b) {
    complex_element<2*W> ab0 = cmult(in0_a, in0_b);
    complex_element<2*W> ab1 = cmult(in1_a, in1_b);
    complex_element<2*W> ab = basic_cadd_mod(P2MOD, ab0, ab1);
    return {red(ab.re), red(ab.im)};
}

// sub of 2 cmults + modulo
template<int W>
complex_element<W> cmult_sub_red(const complex_element<W> in0_a, const complex_element<W> in0_b, const complex_element<W> in1_a, const complex_element<W> in1_b) {
    complex_element<2*W> ab0 = cmult(in0_a, in0_b);
    complex_element<2*W> ab1 = cmult(in1_a, in1_b);
    complex_element<2*W> ab = basic_csub_mod(P2MOD, ab0, ab1);
    return {red(ab.re), red(ab.im)};
}
