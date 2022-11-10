#include <algorithm>
#include <ap_int.h>


#ifndef BASIC_ARITH_UTILS
#define BASIC_ARITH_UTILS

// explicitly pipelined add and sub
#ifndef W_THR_DEFAULT
#define W_THR_DEFAULT 160
#endif

// types
template <int W>
struct ap_uint_pair {
	ap_uint<W> uint0;
	ap_uint<W> uint1;
};
template <int W>
struct ap_uint_16 {
	ap_uint<W> uint0;
	ap_uint<W> uint1;
	ap_uint<W> uint2;
	ap_uint<W> uint3;
	ap_uint<W> uint4;
	ap_uint<W> uint5;
	ap_uint<W> uint6;
	ap_uint<W> uint7;
	ap_uint<W> uint8;
	ap_uint<W> uint9;
	ap_uint<W> uint10;
	ap_uint<W> uint11;
	ap_uint<W> uint12;
	ap_uint<W> uint13;
	ap_uint<W> uint14;
	ap_uint<W> uint15;
};
template <int W>
struct ap_uint_32 {
	ap_uint<W> uint0;
	ap_uint<W> uint1;
	ap_uint<W> uint2;
	ap_uint<W> uint3;
	ap_uint<W> uint4;
	ap_uint<W> uint5;
	ap_uint<W> uint6;
	ap_uint<W> uint7;
	ap_uint<W> uint8;
	ap_uint<W> uint9;
	ap_uint<W> uint10;
	ap_uint<W> uint11;
	ap_uint<W> uint12;
	ap_uint<W> uint13;
	ap_uint<W> uint14;
	ap_uint<W> uint15;
	ap_uint<W> uint16;
	ap_uint<W> uint17;
	ap_uint<W> uint18;
	ap_uint<W> uint19;
	ap_uint<W> uint20;
	ap_uint<W> uint21;
	ap_uint<W> uint22;
	ap_uint<W> uint23;
	ap_uint<W> uint24;
	ap_uint<W> uint25;
	ap_uint<W> uint26;
	ap_uint<W> uint27;
	ap_uint<W> uint28;
	ap_uint<W> uint29;
	ap_uint<W> uint30;
	ap_uint<W> uint31;
};
template <int W>
struct complex_element {
    ap_uint<W> re;
    ap_uint<W> im;
};

template <int W>
struct affine_point {
    ap_uint<W> x;
    ap_uint<W> y;
};

template <int W>
struct projective_point {
    ap_uint<W> x;
    ap_uint<W> y;
    ap_uint<W> z;
};

template <int W>
struct complex_projective_point {
    complex_element<W> x;
    complex_element<W> y;
    complex_element<W> z;
};

// explicit pipelining
template <int P=1, int W>
ap_uint<W> pipe_this(ap_uint<W> x) {
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1
#pragma HLS LATENCY min=P max=P
    return x;
}

// explicitly pipelined mult
template<int P=2, int W0, int W1>
ap_uint<W0 + W1> mult_piped(ap_uint<W0> x, ap_uint<W1> y) {
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1
#pragma HLS LATENCY min=P max=P
    return x * y;
}

// explicit concatenation
template <int W0, int W1, bool S0, bool S1>
ap_uint<W0 + W1> concat(ap_int_base<W0, S0> x, ap_int_base<W1, S1> y) {
#pragma HLS INLINE
    return (ap_uint<W0 + W1>)(x, y);
}

template <int W0, int W1, bool S0, bool S1>
ap_uint<W0 + W1> concat(ap_int_base<W0, S0> x, ap_range_ref<W1, S1> y) {
#pragma HLS INLINE
    return (ap_uint<W0 + W1>)(x, y);
}

template <int W0, int W1, bool S0, bool S1>
ap_uint<W0 + W1> concat(ap_range_ref<W0, S0> x, ap_int_base<W1, S1> y) {
#pragma HLS INLINE
    return (ap_uint<W0 + W1>)(x, y);
}

template <int W0, int W1, bool S0, bool S1>
ap_uint<W0 + W1> concat(ap_range_ref<W0, S0> x, ap_range_ref<W1, S1> y) {
#pragma HLS INLINE
    return (ap_uint<W0 + W1>)(x, y);
}

template<int W_THR=W_THR_DEFAULT, int W0, int W1>
ap_uint<std::max({W0, W1}) + 1> add_piped_inline(const ap_uint<W0> x, const ap_uint<W1> y) {
#pragma HLS INLINE
    const int W_max = std::max({W0, W1});
    ap_uint<W_max + 1> ret;
    if (W_max < W_THR) {
        ret = x + y;
#pragma HLS BIND_OP variable=ret op=add impl=fabric latency=-1
    } else if (W_max < 2*W_THR) {
        ret = x + y;
#pragma HLS BIND_OP variable=ret op=add impl=fabric latency=1
    } else if (W_max < 3*W_THR) {
        ret = x + y;
#pragma HLS BIND_OP variable=ret op=add impl=fabric latency=2
    } else if (W_max < 4*W_THR) {
        ret = x + y;
#pragma HLS BIND_OP variable=ret op=add impl=fabric latency=3
    } else {
        ret = x + y;
#pragma HLS BIND_OP variable=ret op=add impl=fabric latency=4
    }
    return ret;
}

template<int W_THR=W_THR_DEFAULT, int W0, int W1, int W2>
ap_uint<std::max({W0, W1, W2}) + 2> add_piped_inline(const ap_uint<W0> x, const ap_uint<W1> y, const ap_uint<W2> z) {
#pragma HLS INLINE
    const int W_max = std::max({W0, W1, W2});
    ap_uint<W_max + 2> ret;
    if (W_max < W_THR) {
        ret = x + y + z;
#pragma HLS BIND_OP variable=ret op=add impl=fabric latency=-1
    } else if (W_max < 2*W_THR) {
        ret = x + y + z;
#pragma HLS BIND_OP variable=ret op=add impl=fabric latency=1
    } else if (W_max < 3*W_THR) {
        ret = x + y + z;
#pragma HLS BIND_OP variable=ret op=add impl=fabric latency=2
    } else if (W_max < 4*W_THR) {
        ret = x + y + z;
#pragma HLS BIND_OP variable=ret op=add impl=fabric latency=3
    } else {
        ret = x + y + z;
#pragma HLS BIND_OP variable=ret op=add impl=fabric latency=4
    }
    return ret;
}

template<int W_THR=W_THR_DEFAULT, int W0, int W1>
ap_uint<std::max({W0, W1}) + 1> sub_piped_inline(const ap_uint<W0> x, const ap_uint<W1> y) {
#pragma HLS INLINE
    const int W_max = std::max({W0, W1});
    ap_uint<W_max + 1> ret;
    if (W_max < W_THR) {
        ret = x - y;
#pragma HLS BIND_OP variable=ret op=sub impl=fabric latency=-1
    } else if (W_max < 2*W_THR) {
        ret = x - y;
#pragma HLS BIND_OP variable=ret op=sub impl=fabric latency=1
    } else if (W_max < 3*W_THR) {
        ret = x - y;
#pragma HLS BIND_OP variable=ret op=sub impl=fabric latency=2
    } else if (W_max < 4*W_THR) {
        ret = x - y;
#pragma HLS BIND_OP variable=ret op=sub impl=fabric latency=3
    } else {
        ret = x - y;
#pragma HLS BIND_OP variable=ret op=sub impl=fabric latency=4
    }
    return ret;
}

template<int W_THR=W_THR_DEFAULT, int W0, int W1, int W2>
ap_uint<std::max({W0, W1, W2}) + 2> sub_piped_inline(const ap_uint<W0> x, const ap_uint<W1> y, const ap_uint<W2> z) {
#pragma HLS INLINE
    const int W_max = std::max({W0, W1, W2});
    ap_uint<W_max + 2> ret;
    if (W_max < W_THR) {
        ret = x - y - z;
#pragma HLS BIND_OP variable=ret op=sub impl=fabric latency=-1
    } else if (W_max < 2*W_THR) {
        ret = x - y - z;
#pragma HLS BIND_OP variable=ret op=sub impl=fabric latency=1
    } else if (W_max < 3*W_THR) {
        ret = x - y - z;
#pragma HLS BIND_OP variable=ret op=sub impl=fabric latency=2
    } else if (W_max < 4*W_THR) {
        ret = x - y - z;
#pragma HLS BIND_OP variable=ret op=sub impl=fabric latency=3
    } else {
        ret = x - y - z;
#pragma HLS BIND_OP variable=ret op=sub impl=fabric latency=4
    }
    return ret;
}

template<int W_THR=W_THR_DEFAULT, int W0, int W1>
ap_uint<std::max({W0, W1}) + 1> add_piped(const ap_uint<W0> x, const ap_uint<W1> y) {
#pragma HLS INLINE off
    return add_piped_inline<W_THR>(x, y);
}

template<int W_THR=W_THR_DEFAULT, int W0, int W1>
ap_uint<std::max({W0, W1}) + 1> sub_piped(const ap_uint<W0> x, const ap_uint<W1> y) {
#pragma HLS INLINE off
    return sub_piped_inline<W_THR>(x, y);
}

template<int W_THR=W_THR_DEFAULT, int W0, int W1, bool S0, bool S1>
ap_uint<std::max({W0, W1}) + 1> add_piped_inline(const ap_range_ref<W0, S0> x, const ap_range_ref<W1, S1> y) {
#pragma HLS INLINE
    return add_piped_inline<W_THR>(ap_uint<W0>(x), ap_uint<W1>(y));
}

template<int W_THR=W_THR_DEFAULT, int W0, int W1, bool S0, bool S1>
ap_uint<std::max({W0, W1}) + 1> add_piped_inline(const ap_int_base<W0, S0> x, const ap_int_base<W1, S1> y) {
#pragma HLS INLINE
    return add_piped_inline<W_THR>(ap_uint<W0>(x), ap_uint<W1>(y));
}

template<int W_THR=W_THR_DEFAULT, int W0, int W1, int W2, bool S0, bool S1, bool S2>
ap_uint<std::max({W0, W1, W2}) + 2> add_piped_inline(const ap_range_ref<W0, S0> x, const ap_range_ref<W1, S1> y, const ap_range_ref<W2, S2> z) {
#pragma HLS INLINE
    return add_piped_inline<W_THR>(ap_uint<W0>(x), ap_uint<W1>(y), ap_uint<W2>(z));
}

template<int W_THR=W_THR_DEFAULT, int W0, int W1, int W2, bool S0, bool S1, bool S2>
ap_uint<std::max({W0, W1, W2}) + 2> add_piped_inline(const ap_int_base<W0, S0> x, const ap_int_base<W1, S1> y, const ap_int_base<W2, S2> z) {
#pragma HLS INLINE
    return add_piped_inline<W_THR>(ap_uint<W0>(x), ap_uint<W1>(y), ap_uint<W2>(z));
}

template<int W_THR=W_THR_DEFAULT, int W0, int W1, int W2, bool S0, bool S1, bool S2>
ap_uint<std::max({W0, W1, W2}) + 2> sub_piped_inline(const ap_range_ref<W0, S0> x, const ap_range_ref<W1, S1> y, const ap_range_ref<W2, S2> z) {
#pragma HLS INLINE
    return sub_piped_inline<W_THR>(ap_uint<W0>(x), ap_uint<W1>(y), ap_uint<W2>(z));
}

template<int W_THR=W_THR_DEFAULT, int W0, int W1, int W2, bool S0, bool S1, bool S2>
ap_uint<std::max({W0, W1, W2}) + 2> sub_piped_inline(const ap_int_base<W0, S0> x, const ap_int_base<W1, S1> y, const ap_int_base<W2, S2> z) {
#pragma HLS INLINE
    return sub_piped_inline<W_THR>(ap_uint<W0>(x), ap_uint<W1>(y), ap_uint<W2>(z));
}

#endif
