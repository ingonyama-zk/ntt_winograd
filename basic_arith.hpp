#include "basic_arith_utils.hpp"


#ifndef BASIC_ARITH
#define BASIC_ARITH

// add + modulo
template<int W>
ap_uint<W> basic_add_mod(const ap_uint<W> pmod, const ap_uint<W> in_a, const ap_uint<W> in_b) {
#pragma HLS FUNCTION_INSTANTIATE variable=pmod
#pragma HLS PIPELINE II=1
    ap_uint<W+1> rr_m0 = add_piped_inline(in_a, in_b);
    ap_uint<W+1> rr_m1 = sub_piped_inline(rr_m0, pmod);
    return rr_m1[W] ? rr_m0(W-1, 0) : rr_m1(W-1, 0);
}

// sub + modulo
template<int W>
ap_uint<W> basic_sub_mod(const ap_uint<W> pmod, const ap_uint<W> in_a, const ap_uint<W> in_b) {
#pragma HLS FUNCTION_INSTANTIATE variable=pmod
#pragma HLS PIPELINE II=1
    ap_uint<W+1> rr_m0 = sub_piped_inline(in_a, in_b);
    ap_uint<W+1> rr_m1 = add_piped_inline(rr_m0, pmod);
    return rr_m0[W] ? rr_m1(W-1, 0) : rr_m0(W-1, 0);
}

// log ladder modulo
template<int W0, int W>
ap_uint<W> basic_mod(const ap_uint<W> pmod, const ap_uint<W0> in) {
#pragma HLS FUNCTION_INSTANTIATE variable=pmod
#pragma HLS PIPELINE II=1
    const int w = W0 - W;
    const ap_uint<w> zeros = 0;
    if(w <= 0) return in;
    ap_uint<W0+1> int_pre = in;
    ap_uint<W0+1> int_pst;
    for (int i=0; i<w; i++) {
        int_pst = sub_piped_inline(int_pre, concat(pmod, zeros(w-1-i, 0)));
        int_pre = int_pst[W0-i] ? int_pre(W0-1-i, 0) : int_pst(W0-1-i, 0);
    }
    int_pst = sub_piped_inline(int_pre, pmod);
    int_pre = int_pst[W] ? int_pre(W-1, 0) : int_pst(W-1, 0);
    return int_pre(W-1, 0);
}

// times 3 + modulo
template<int W>
ap_uint<W> basic_x3_mod(const ap_uint<W> pmod, const ap_uint<W> in) {
#pragma HLS FUNCTION_INSTANTIATE variable=pmod
#pragma HLS PIPELINE II=1
    ap_uint<W+2> rr = add_piped_inline(concat(in, ap_uint<1>(0)), in);
    return basic_mod(pmod, rr);
}

// times 9 + modulo
template<int W>
ap_uint<W> basic_x9_mod(const ap_uint<W> pmod, const ap_uint<W> in) {
#pragma HLS FUNCTION_INSTANTIATE variable=pmod
#pragma HLS PIPELINE II=1
    ap_uint<W+4> rr = add_piped_inline(concat(in, ap_uint<3>(0)), in);
    return basic_mod(pmod, rr);
}

// complex add + modulo
template<int W>
complex_element<W> basic_cadd_mod(const ap_uint<W> pmod, const complex_element<W> in_a, const complex_element<W> in_b) {
#pragma HLS FUNCTION_INSTANTIATE variable=pmod
#pragma HLS PIPELINE II=1
    complex_element<W> ret;
    ret.re = basic_add_mod(pmod, in_a.re, in_b.re);
    ret.im = basic_add_mod(pmod, in_a.im, in_b.im);
    return ret;
}

// complex sub + modulo
template<int W>
complex_element<W> basic_csub_mod(const ap_uint<W> pmod, const complex_element<W> in_a, const complex_element<W> in_b) {
#pragma HLS FUNCTION_INSTANTIATE variable=pmod
#pragma HLS PIPELINE II=1
    complex_element<W> ret;
    ret.re = basic_sub_mod(pmod, in_a.re, in_b.re);
    ret.im = basic_sub_mod(pmod, in_a.im, in_b.im);
    return ret;
}

// complex times 3 + modulo
template<int W>
complex_element<W> basic_cx3_mod(const ap_uint<W> pmod, const complex_element<W> in) {
#pragma HLS FUNCTION_INSTANTIATE variable=pmod
#pragma HLS PIPELINE II=1
    complex_element<W> ret;
    ret.re = basic_x3_mod(pmod, in.re);
    ret.im = basic_x3_mod(pmod, in.im);
    return ret;
}

#endif