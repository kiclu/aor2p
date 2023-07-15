.global avx2_divi_8bpc
.global avx512_divi_8bpc

avx2_divi_8bpc:
    vmovd           %rdi,       %xmm15
    vpbroadcastd    %xmm15,     %ymm15
    vcvtdq2ps       %ymm15,     %ymm15

    vpermq          $0xD8,      %ymm0,      %ymm6
    vpshufd         $0xD8,      %ymm6,      %ymm6

    vpermq          $0x01,      %ymm6,      %ymm7
    vpermq          $0x02,      %ymm6,      %ymm8
    vpermq          $0x03,      %ymm6,      %ymm9

    vpermq          $0xD8,      %ymm1,      %ymm10
    vpshufd         $0xD8,      %ymm10,     %ymm10

    vpermq          $0x01,      %ymm10,     %ymm11
    vpermq          $0x02,      %ymm10,     %ymm12
    vpermq          $0x03,      %ymm10,     %ymm13

    vpmovzxbd       %xmm6,      %ymm6 
    vpmovzxbd       %xmm7,      %ymm7 
    vpmovzxbd       %xmm8,      %ymm8 
    vpmovzxbd       %xmm9,      %ymm9 
    vpmovzxbd       %xmm10,     %ymm10
    vpmovzxbd       %xmm11,     %ymm11
    vpmovzxbd       %xmm12,     %ymm12
    vpmovzxbd       %xmm13,     %ymm13

    vcvtdq2ps       %ymm6,      %ymm6
    vcvtdq2ps       %ymm7,      %ymm7
    vcvtdq2ps       %ymm8,      %ymm8
    vcvtdq2ps       %ymm9,      %ymm9
    vcvtdq2ps       %ymm10,     %ymm10
    vcvtdq2ps       %ymm11,     %ymm11
    vcvtdq2ps       %ymm12,     %ymm12
    vcvtdq2ps       %ymm13,     %ymm13

    vrcpps          %ymm6,      %ymm6 
    vrcpps          %ymm7,      %ymm7 
    vrcpps          %ymm8,      %ymm8 
    vrcpps          %ymm9,      %ymm9 
    vrcpps          %ymm10,     %ymm10
    vrcpps          %ymm11,     %ymm11
    vrcpps          %ymm12,     %ymm12
    vrcpps          %ymm13,     %ymm13

    vmulps          %ymm15,     %ymm6,      %ymm6
    vmulps          %ymm15,     %ymm7,      %ymm7
    vmulps          %ymm15,     %ymm8,      %ymm8
    vmulps          %ymm15,     %ymm9,      %ymm9
    vmulps          %ymm15,     %ymm10,     %ymm10
    vmulps          %ymm15,     %ymm11,     %ymm11
    vmulps          %ymm15,     %ymm12,     %ymm12
    vmulps          %ymm15,     %ymm13,     %ymm13

    vcvtps2dq       %ymm6,      %ymm6
    vcvtps2dq       %ymm7,      %ymm7
    vcvtps2dq       %ymm8,      %ymm8
    vcvtps2dq       %ymm9,      %ymm9
    vcvtps2dq       %ymm10,     %ymm10
    vcvtps2dq       %ymm11,     %ymm11
    vcvtps2dq       %ymm12,     %ymm12
    vcvtps2dq       %ymm13,     %ymm13

    vpackusdw       %ymm7,      %ymm6,      %ymm6
    vpackusdw       %ymm9,      %ymm8,      %ymm7
    vpackusdw       %ymm11,     %ymm10,     %ymm8
    vpackusdw       %ymm13,     %ymm12,     %ymm9

    vpackuswb       %ymm7,      %ymm6,      %ymm0
    vpackuswb       %ymm9,      %ymm8,      %ymm1


    vpermq          $0xD8,      %ymm2,      %ymm6
    vpshufd         $0xD8,      %ymm6,      %ymm6

    vpermq          $0x01,      %ymm6,      %ymm7
    vpermq          $0x02,      %ymm6,      %ymm8
    vpermq          $0x03,      %ymm6,      %ymm9

    vpermq          $0xD8,      %ymm3,      %ymm10
    vpshufd         $0xD8,      %ymm10,     %ymm10

    vpermq          $0x01,      %ymm10,     %ymm11
    vpermq          $0x02,      %ymm10,     %ymm12
    vpermq          $0x03,      %ymm10,     %ymm13

    vpmovzxbd       %xmm6,      %ymm6 
    vpmovzxbd       %xmm7,      %ymm7 
    vpmovzxbd       %xmm8,      %ymm8 
    vpmovzxbd       %xmm9,      %ymm9 
    vpmovzxbd       %xmm10,     %ymm10
    vpmovzxbd       %xmm11,     %ymm11
    vpmovzxbd       %xmm12,     %ymm12
    vpmovzxbd       %xmm13,     %ymm13

    vcvtdq2ps       %ymm6,      %ymm6
    vcvtdq2ps       %ymm7,      %ymm7
    vcvtdq2ps       %ymm8,      %ymm8
    vcvtdq2ps       %ymm9,      %ymm9
    vcvtdq2ps       %ymm10,     %ymm10
    vcvtdq2ps       %ymm11,     %ymm11
    vcvtdq2ps       %ymm12,     %ymm12
    vcvtdq2ps       %ymm13,     %ymm13

    vrcpps          %ymm6,      %ymm6 
    vrcpps          %ymm7,      %ymm7 
    vrcpps          %ymm8,      %ymm8 
    vrcpps          %ymm9,      %ymm9 
    vrcpps          %ymm10,     %ymm10
    vrcpps          %ymm11,     %ymm11
    vrcpps          %ymm12,     %ymm12
    vrcpps          %ymm13,     %ymm13

    vmulps          %ymm15,     %ymm6,      %ymm6
    vmulps          %ymm15,     %ymm7,      %ymm7
    vmulps          %ymm15,     %ymm8,      %ymm8
    vmulps          %ymm15,     %ymm9,      %ymm9
    vmulps          %ymm15,     %ymm10,     %ymm10
    vmulps          %ymm15,     %ymm11,     %ymm11
    vmulps          %ymm15,     %ymm12,     %ymm12
    vmulps          %ymm15,     %ymm13,     %ymm13

    vcvtps2dq       %ymm6,      %ymm6
    vcvtps2dq       %ymm7,      %ymm7
    vcvtps2dq       %ymm8,      %ymm8
    vcvtps2dq       %ymm9,      %ymm9
    vcvtps2dq       %ymm10,     %ymm10
    vcvtps2dq       %ymm11,     %ymm11
    vcvtps2dq       %ymm12,     %ymm12
    vcvtps2dq       %ymm13,     %ymm13

    vpackusdw       %ymm7,      %ymm6,      %ymm6
    vpackusdw       %ymm9,      %ymm8,      %ymm7
    vpackusdw       %ymm11,     %ymm10,     %ymm8
    vpackusdw       %ymm13,     %ymm12,     %ymm9

    vpackuswb       %ymm7,      %ymm6,      %ymm2
    vpackuswb       %ymm9,      %ymm8,      %ymm3


    vpermq          $0xD8,      %ymm4,      %ymm6
    vpshufd         $0xD8,      %ymm6,      %ymm6

    vpermq          $0x01,      %ymm6,      %ymm7
    vpermq          $0x02,      %ymm6,      %ymm8
    vpermq          $0x03,      %ymm6,      %ymm9

    vpermq          $0xD8,      %ymm5,      %ymm10
    vpshufd         $0xD8,      %ymm10,     %ymm10

    vpermq          $0x01,      %ymm10,     %ymm11
    vpermq          $0x02,      %ymm10,     %ymm12
    vpermq          $0x03,      %ymm10,     %ymm13

    vpmovzxbd       %xmm6,      %ymm6 
    vpmovzxbd       %xmm7,      %ymm7 
    vpmovzxbd       %xmm8,      %ymm8 
    vpmovzxbd       %xmm9,      %ymm9 
    vpmovzxbd       %xmm10,     %ymm10
    vpmovzxbd       %xmm11,     %ymm11
    vpmovzxbd       %xmm12,     %ymm12
    vpmovzxbd       %xmm13,     %ymm13

    vcvtdq2ps       %ymm6,      %ymm6
    vcvtdq2ps       %ymm7,      %ymm7
    vcvtdq2ps       %ymm8,      %ymm8
    vcvtdq2ps       %ymm9,      %ymm9
    vcvtdq2ps       %ymm10,     %ymm10
    vcvtdq2ps       %ymm11,     %ymm11
    vcvtdq2ps       %ymm12,     %ymm12
    vcvtdq2ps       %ymm13,     %ymm13

    vrcpps          %ymm6,      %ymm6 
    vrcpps          %ymm7,      %ymm7 
    vrcpps          %ymm8,      %ymm8 
    vrcpps          %ymm9,      %ymm9 
    vrcpps          %ymm10,     %ymm10
    vrcpps          %ymm11,     %ymm11
    vrcpps          %ymm12,     %ymm12
    vrcpps          %ymm13,     %ymm13

    vmulps          %ymm15,     %ymm6,      %ymm6
    vmulps          %ymm15,     %ymm7,      %ymm7
    vmulps          %ymm15,     %ymm8,      %ymm8
    vmulps          %ymm15,     %ymm9,      %ymm9
    vmulps          %ymm15,     %ymm10,     %ymm10
    vmulps          %ymm15,     %ymm11,     %ymm11
    vmulps          %ymm15,     %ymm12,     %ymm12
    vmulps          %ymm15,     %ymm13,     %ymm13

    vcvtps2dq       %ymm6,      %ymm6
    vcvtps2dq       %ymm7,      %ymm7
    vcvtps2dq       %ymm8,      %ymm8
    vcvtps2dq       %ymm9,      %ymm9
    vcvtps2dq       %ymm10,     %ymm10
    vcvtps2dq       %ymm11,     %ymm11
    vcvtps2dq       %ymm12,     %ymm12
    vcvtps2dq       %ymm13,     %ymm13

    vpackusdw       %ymm7,      %ymm6,      %ymm6
    vpackusdw       %ymm9,      %ymm8,      %ymm7
    vpackusdw       %ymm11,     %ymm10,     %ymm8
    vpackusdw       %ymm13,     %ymm12,     %ymm9

    vpackuswb       %ymm7,      %ymm6,      %ymm4
    vpackuswb       %ymm9,      %ymm8,      %ymm5

    ret
    
avx512_divi_8bpc:
    ret
