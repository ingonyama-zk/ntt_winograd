

test_ntt32_winograd_bn254_scalar:
	mkdir -p work
	g++ -o work/test_ntt32_winograd_bn254_scalar \
		-I$(XILINX_HLS)/include/ \
		-I$(BOOST)/ \
		fixed_size_arith_bn254_scalar.cpp \
		bn254_scalar_ab_blocks_81_version_0_hls.cpp \
		bn254_scalar_p_lsb_blocks_14_version_0_hls.cpp \
		bn254_scalar_m_msb_blocks_27_version_0_hls.cpp \
		ntt32_winograd_bn254_scalar.cpp \
		test_ntt32_winograd_bn254_scalar.cpp 
	work/test_ntt32_winograd_bn254_scalar

clean:
	rm -rf work


