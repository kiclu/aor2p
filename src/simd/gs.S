.global avx2_gs_8bpc
.global avx512_gs_8bpc

avx2_gs_8bpc:
    vpxor           %ymm14,     %ymm14,     %ymm14

    mov             $0x3e991687,%rdi
    vmovd           %rdi,       %xmm15
    vbroadcastss    %xmm15,     %ymm15

    vpermq          $0xD8,      %ymm0,      %ymm6
    vpshufd         $0xD8,      %ymm6,      %ymm6

    vpermq          $0x01,      %ymm6,      %ymm7
    vpermq          $0x02,      %ymm6,      %ymm8
    vpermq          $0x03,      %ymm6,      %ymm9

    vpmovzxbd       %xmm6,      %ymm6
    vpmovzxbd       %xmm7,      %ymm7
    vpmovzxbd       %xmm8,      %ymm8
    vpmovzxbd       %xmm9,      %ymm9

    vcvtdq2ps       %ymm6,      %ymm6
    vcvtdq2ps       %ymm7,      %ymm7
    vcvtdq2ps       %ymm8,      %ymm8
    vcvtdq2ps       %ymm9,      %ymm9

    vmulps          %ymm15,     %ymm6,      %ymm6
    vmulps          %ymm15,     %ymm7,      %ymm7
    vmulps          %ymm15,     %ymm8,      %ymm8
    vmulps          %ymm15,     %ymm9,      %ymm9

    mov             $0x3f1645a2,%rdi
    vmovd           %rdi,       %xmm15
    vbroadcastss    %xmm15,     %ymm15

    vpermq          $0xD8,      %ymm2,      %ymm10
    vpshufd         $0xD8,      %ymm10,     %ymm10

    vpermq          $0x01,      %ymm10,     %ymm11
    vpermq          $0x02,      %ymm10,     %ymm12
    vpermq          $0x03,      %ymm10,     %ymm13

    vpmovzxbd       %xmm10,     %ymm10
    vpmovzxbd       %xmm11,     %ymm11
    vpmovzxbd       %xmm12,     %ymm12
    vpmovzxbd       %xmm13,     %ymm13

    vcvtdq2ps       %ymm10,     %ymm10
    vcvtdq2ps       %ymm11,     %ymm11
    vcvtdq2ps       %ymm12,     %ymm12
    vcvtdq2ps       %ymm13,     %ymm13

    vfmadd231ps     %ymm15,     %ymm10,     %ymm6
    vfmadd231ps     %ymm15,     %ymm11,     %ymm7
    vfmadd231ps     %ymm15,     %ymm12,     %ymm8
    vfmadd231ps     %ymm15,     %ymm13,     %ymm9

    mov             $0x3de978d5,%rdi
    vmovd           %rdi,       %xmm15
    vbroadcastss    %xmm15,     %ymm15

    vpermq          $0xD8,      %ymm4,      %ymm10
    vpshufd         $0xD8,      %ymm10,     %ymm10

    vpermq          $0x01,      %ymm10,     %ymm11
    vpermq          $0x02,      %ymm10,     %ymm12
    vpermq          $0x03,      %ymm10,     %ymm13

    vpmovzxbd       %xmm10,     %ymm10
    vpmovzxbd       %xmm11,     %ymm11
    vpmovzxbd       %xmm12,     %ymm12
    vpmovzxbd       %xmm13,     %ymm13

    vcvtdq2ps       %ymm10,     %ymm10
    vcvtdq2ps       %ymm11,     %ymm11
    vcvtdq2ps       %ymm12,     %ymm12
    vcvtdq2ps       %ymm13,     %ymm13

    vfmadd231ps     %ymm15,     %ymm10,     %ymm6
    vfmadd231ps     %ymm15,     %ymm11,     %ymm7
    vfmadd231ps     %ymm15,     %ymm12,     %ymm8
    vfmadd231ps     %ymm15,     %ymm13,     %ymm9

    vcvtps2dq       %ymm6,      %ymm6
    vcvtps2dq       %ymm7,      %ymm7
    vcvtps2dq       %ymm8,      %ymm8
    vcvtps2dq       %ymm9,      %ymm9

    vpackusdw       %ymm7,      %ymm6,      %ymm6
    vpackusdw       %ymm9,      %ymm8,      %ymm7
    vpackuswb       %ymm7,      %ymm6,      %ymm0

    vpaddb          %ymm14,     %ymm0,      %ymm2
    vpaddb          %ymm14,     %ymm0,      %ymm4


    mov             $0x3e991687,%rdi
    vmovd           %rdi,       %xmm15
    vbroadcastss    %xmm15,     %ymm15

    vpermq          $0xD8,      %ymm1,      %ymm6
    vpshufd         $0xD8,      %ymm6,      %ymm6

    vpermq          $0x01,      %ymm6,      %ymm7
    vpermq          $0x02,      %ymm6,      %ymm8
    vpermq          $0x03,      %ymm6,      %ymm9

    vpmovzxbd       %xmm6,      %ymm6
    vpmovzxbd       %xmm7,      %ymm7
    vpmovzxbd       %xmm8,      %ymm8
    vpmovzxbd       %xmm9,      %ymm9

    vcvtdq2ps       %ymm6,      %ymm6
    vcvtdq2ps       %ymm7,      %ymm7
    vcvtdq2ps       %ymm8,      %ymm8
    vcvtdq2ps       %ymm9,      %ymm9

    vmulps          %ymm15,     %ymm6,      %ymm6
    vmulps          %ymm15,     %ymm7,      %ymm7
    vmulps          %ymm15,     %ymm8,      %ymm8
    vmulps          %ymm15,     %ymm9,      %ymm9

    mov             $0x3f1645a2,%rdi
    vmovd           %rdi,       %xmm15
    vbroadcastss    %xmm15,     %ymm15

    vpermq          $0xD8,      %ymm3,      %ymm10
    vpshufd         $0xD8,      %ymm10,     %ymm10

    vpermq          $0x01,      %ymm10,     %ymm11
    vpermq          $0x02,      %ymm10,     %ymm12
    vpermq          $0x03,      %ymm10,     %ymm13

    vpmovzxbd       %xmm10,     %ymm10
    vpmovzxbd       %xmm11,     %ymm11
    vpmovzxbd       %xmm12,     %ymm12
    vpmovzxbd       %xmm13,     %ymm13

    vcvtdq2ps       %ymm10,     %ymm10
    vcvtdq2ps       %ymm11,     %ymm11
    vcvtdq2ps       %ymm12,     %ymm12
    vcvtdq2ps       %ymm13,     %ymm13

    vfmadd231ps     %ymm15,     %ymm10,     %ymm6
    vfmadd231ps     %ymm15,     %ymm11,     %ymm7
    vfmadd231ps     %ymm15,     %ymm12,     %ymm8
    vfmadd231ps     %ymm15,     %ymm13,     %ymm9

    mov             $0x3de978d5,%rdi
    vmovd           %rdi,       %xmm15
    vbroadcastss    %xmm15,     %ymm15

    vpermq          $0xD8,      %ymm5,      %ymm10
    vpshufd         $0xD8,      %ymm10,     %ymm10

    vpermq          $0x01,      %ymm10,     %ymm11
    vpermq          $0x02,      %ymm10,     %ymm12
    vpermq          $0x03,      %ymm10,     %ymm13

    vpmovzxbd       %xmm10,     %ymm10
    vpmovzxbd       %xmm11,     %ymm11
    vpmovzxbd       %xmm12,     %ymm12
    vpmovzxbd       %xmm13,     %ymm13

    vcvtdq2ps       %ymm10,     %ymm10
    vcvtdq2ps       %ymm11,     %ymm11
    vcvtdq2ps       %ymm12,     %ymm12
    vcvtdq2ps       %ymm13,     %ymm13

    vfmadd231ps     %ymm15,     %ymm10,     %ymm6
    vfmadd231ps     %ymm15,     %ymm11,     %ymm7
    vfmadd231ps     %ymm15,     %ymm12,     %ymm8
    vfmadd231ps     %ymm15,     %ymm13,     %ymm9

    vcvtps2dq       %ymm6,      %ymm6
    vcvtps2dq       %ymm7,      %ymm7
    vcvtps2dq       %ymm8,      %ymm8
    vcvtps2dq       %ymm9,      %ymm9

    vpackusdw       %ymm7,      %ymm6,      %ymm6
    vpackusdw       %ymm9,      %ymm8,      %ymm7
    vpackuswb       %ymm7,      %ymm6,      %ymm1

    vpaddb          %ymm14,     %ymm1,      %ymm3
    vpaddb          %ymm14,     %ymm1,      %ymm5

    ret

avx512_gs_8bpc:
    ret
