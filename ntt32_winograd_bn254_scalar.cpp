#include "ntt32_winograd_bn254_scalar.hpp"

void ntt32_winograd_bn254_scalar(
    const ap_uint<254> x0, 
    const ap_uint<254> x1, 
    const ap_uint<254> x2, 
    const ap_uint<254> x3, 
    const ap_uint<254> x4, 
    const ap_uint<254> x5, 
    const ap_uint<254> x6, 
    const ap_uint<254> x7, 
    const ap_uint<254> x8, 
    const ap_uint<254> x9, 
    const ap_uint<254> x10, 
    const ap_uint<254> x11, 
    const ap_uint<254> x12, 
    const ap_uint<254> x13, 
    const ap_uint<254> x14, 
    const ap_uint<254> x15, 
    const ap_uint<254> x16, 
    const ap_uint<254> x17, 
    const ap_uint<254> x18, 
    const ap_uint<254> x19, 
    const ap_uint<254> x20, 
    const ap_uint<254> x21, 
    const ap_uint<254> x22, 
    const ap_uint<254> x23, 
    const ap_uint<254> x24, 
    const ap_uint<254> x25, 
    const ap_uint<254> x26, 
    const ap_uint<254> x27, 
    const ap_uint<254> x28, 
    const ap_uint<254> x29, 
    const ap_uint<254> x30, 
    const ap_uint<254> x31, 
    ap_uint<254>* y0, 
    ap_uint<254>* y1, 
    ap_uint<254>* y2, 
    ap_uint<254>* y3, 
    ap_uint<254>* y4, 
    ap_uint<254>* y5, 
    ap_uint<254>* y6, 
    ap_uint<254>* y7, 
    ap_uint<254>* y8, 
    ap_uint<254>* y9, 
    ap_uint<254>* y10, 
    ap_uint<254>* y11, 
    ap_uint<254>* y12, 
    ap_uint<254>* y13, 
    ap_uint<254>* y14, 
    ap_uint<254>* y15, 
    ap_uint<254>* y16, 
    ap_uint<254>* y17, 
    ap_uint<254>* y18, 
    ap_uint<254>* y19, 
    ap_uint<254>* y20, 
    ap_uint<254>* y21, 
    ap_uint<254>* y22, 
    ap_uint<254>* y23, 
    ap_uint<254>* y24, 
    ap_uint<254>* y25, 
    ap_uint<254>* y26, 
    ap_uint<254>* y27, 
    ap_uint<254>* y28, 
    ap_uint<254>* y29, 
    ap_uint<254>* y30, 
    ap_uint<254>* y31
    )
    {
        ntt32_winograd(
            x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31,
            y0, y1, y2, y3, y4, y5, y6, y7, y8, y9, y10, y11, y12, y13, y14, y15, y16, y17, y18, y19, y20, y21, y22, y23, y24, y25, y26, y27, y28, y29, y30, y31
            );
        return;
    }