#include "basic_arith.hpp"


const ap_uint<254> PMOD = ap_uint<254>("0x30644e72e131a029b85045b68181585d2833e84879b9709143e1f593f0000001");
const ap_uint<508> P2MOD = ap_uint<508>("0x925c4b8763cbf9c599a6f7c0348d21c85f73bb0d379d3df2c77527b47b62fe7a6ce1975e821ddb0ffe9a62c68c9bb7fc7f26223dcb3400008c3eb27e0000001");

ap_uint<508> bn254_scalar_ab_multiplier(ap_uint<254> in_a, ap_uint<254> in_b);
ap_uint<509> bn254_scalar_m_multiplier(ap_uint<254> in);
ap_uint<509> bn254_scalar_p_multiplier(ap_uint<255> in);

ap_uint<508> mult(ap_uint<254> in_a, ap_uint<254> in_b);
ap_uint<254> red(ap_uint<508> in);
