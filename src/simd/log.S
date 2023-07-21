.global avx2_log_8bpc
.global avx512_log_8bpc

avx2_log_8bpc:
    mov             $0x7F,      %rdi
    vmovd           %rdi,       %xmm15
    vpbroadcastd    %xmm15,     %ymm15

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

    vpsrld          $0x17,      %ymm6,      %ymm6
    vpsrld          $0x17,      %ymm7,      %ymm7
    vpsrld          $0x17,      %ymm8,      %ymm8
    vpsrld          $0x17,      %ymm9,      %ymm9

    vpsubd          %ymm15,     %ymm6,      %ymm6
    vpsubd          %ymm15,     %ymm7,      %ymm7
    vpsubd          %ymm15,     %ymm8,      %ymm8
    vpsubd          %ymm15,     %ymm9,      %ymm9

    vpackusdw       %ymm7,      %ymm6,      %ymm6
    vpackusdw       %ymm9,      %ymm8,      %ymm7
    vpackuswb       %ymm7,      %ymm6,      %ymm0


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

    vpsrld          $0x17,      %ymm6,      %ymm6
    vpsrld          $0x17,      %ymm7,      %ymm7
    vpsrld          $0x17,      %ymm8,      %ymm8
    vpsrld          $0x17,      %ymm9,      %ymm9

    vpsubd          %ymm15,     %ymm6,      %ymm6
    vpsubd          %ymm15,     %ymm7,      %ymm7
    vpsubd          %ymm15,     %ymm8,      %ymm8
    vpsubd          %ymm15,     %ymm9,      %ymm9

    vpackusdw       %ymm7,      %ymm6,      %ymm6
    vpackusdw       %ymm9,      %ymm8,      %ymm7
    vpackuswb       %ymm7,      %ymm6,      %ymm1


    vpermq          $0xD8,      %ymm2,      %ymm6
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

    vpsrld          $0x17,      %ymm6,      %ymm6
    vpsrld          $0x17,      %ymm7,      %ymm7
    vpsrld          $0x17,      %ymm8,      %ymm8
    vpsrld          $0x17,      %ymm9,      %ymm9

    vpsubd          %ymm15,     %ymm6,      %ymm6
    vpsubd          %ymm15,     %ymm7,      %ymm7
    vpsubd          %ymm15,     %ymm8,      %ymm8
    vpsubd          %ymm15,     %ymm9,      %ymm9

    vpackusdw       %ymm7,      %ymm6,      %ymm6
    vpackusdw       %ymm9,      %ymm8,      %ymm7
    vpackuswb       %ymm7,      %ymm6,      %ymm2


    vpermq          $0xD8,      %ymm3,      %ymm6
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

    vpsrld          $0x17,      %ymm6,      %ymm6
    vpsrld          $0x17,      %ymm7,      %ymm7
    vpsrld          $0x17,      %ymm8,      %ymm8
    vpsrld          $0x17,      %ymm9,      %ymm9

    vpsubd          %ymm15,     %ymm6,      %ymm6
    vpsubd          %ymm15,     %ymm7,      %ymm7
    vpsubd          %ymm15,     %ymm8,      %ymm8
    vpsubd          %ymm15,     %ymm9,      %ymm9

    vpackusdw       %ymm7,      %ymm6,      %ymm6
    vpackusdw       %ymm9,      %ymm8,      %ymm7
    vpackuswb       %ymm7,      %ymm6,      %ymm3


    vpermq          $0xD8,      %ymm4,      %ymm6
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

    vpsrld          $0x17,      %ymm6,      %ymm6
    vpsrld          $0x17,      %ymm7,      %ymm7
    vpsrld          $0x17,      %ymm8,      %ymm8
    vpsrld          $0x17,      %ymm9,      %ymm9

    vpsubd          %ymm15,     %ymm6,      %ymm6
    vpsubd          %ymm15,     %ymm7,      %ymm7
    vpsubd          %ymm15,     %ymm8,      %ymm8
    vpsubd          %ymm15,     %ymm9,      %ymm9

    vpackusdw       %ymm7,      %ymm6,      %ymm6
    vpackusdw       %ymm9,      %ymm8,      %ymm7
    vpackuswb       %ymm7,      %ymm6,      %ymm4


    vpermq          $0xD8,      %ymm5,      %ymm6
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

    vpsrld          $0x17,      %ymm6,      %ymm6
    vpsrld          $0x17,      %ymm7,      %ymm7
    vpsrld          $0x17,      %ymm8,      %ymm8
    vpsrld          $0x17,      %ymm9,      %ymm9

    vpsubd          %ymm15,     %ymm6,      %ymm6
    vpsubd          %ymm15,     %ymm7,      %ymm7
    vpsubd          %ymm15,     %ymm8,      %ymm8
    vpsubd          %ymm15,     %ymm9,      %ymm9

    vpackusdw       %ymm7,      %ymm6,      %ymm6
    vpackusdw       %ymm9,      %ymm8,      %ymm7
    vpackuswb       %ymm7,      %ymm6,      %ymm5

    ret

avx512_log_8bpc:
    ret
