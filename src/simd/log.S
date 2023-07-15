.global avx2_log_8bpc
.global avx512_log_8bpc

avx2_log_8bpc:
    mov             $0x7f,  %eax
    vmovd           %eax,   %xmm0
    vpbroadcastb    %xmm0,  %xmm0

    vpmovzxbd       %xmm1,      %ymm1
    vcvtdq2ps       %ymm1,      %ymm1
    #vpsrld          $0x17,      %ymm1,      %ymm1
    #vpsubq          %ymm0,      %ymm1,      %ymm1

    vpmovzxbd       %xmm2,      %ymm2
    vcvtdq2ps       %ymm2,      %ymm2
    #vpsrld          $0x17,      %ymm2,      %ymm2
    #vpsubq          %ymm0,      %ymm2,      %ymm2

    movq            0x10(%rdi), %xmm3
    vpmovzxbd       %xmm3,      %ymm3
    vcvtdq2ps       %ymm3,      %ymm3
    #vpsrld          $0x17,      %ymm3,      %ymm3
    #vpsubq          %ymm0,      %ymm3,      %ymm3

    movq            0x18(%rdi), %xmm4
    vpmovzxbd       %xmm4,      %ymm4
    vcvtdq2ps       %ymm4,      %ymm4
    #vpsrld          $0x17,      %ymm4,      %ymm4
    #vpsubq          %ymm0,      %ymm4,      %ymm4

    vpackusdw       %ymm3,      %ymm1,      %ymm1
    vpermq          $0xD8,      %ymm1,      %ymm1

    vpackusdw       %ymm4,      %ymm2,      %ymm2
    vpermq          $0xD8,      %ymm2,      %ymm2

    vpackuswb       %ymm2,      %ymm1,      %ymm1

    vmovdqa         %ymm1,      (%rdi)
  

    movq            0x00(%rsi), %xmm1
    vpmovzxbd       %xmm1,      %ymm1
    vcvtdq2ps       %ymm1,      %ymm1
    #vpsrld          $0x17,      %ymm1,      %ymm1
    #vpsubq          %ymm0,      %ymm1,      %ymm1

    movq            0x08(%rsi), %xmm2
    vpmovzxbd       %xmm2,      %ymm2
    vcvtdq2ps       %ymm2,      %ymm2
    #vpsrld          $0x17,      %ymm2,      %ymm2
    #vpsubq          %ymm0,      %ymm2,      %ymm2

    movq            0x10(%rsi), %xmm3
    vpmovzxbd       %xmm3,      %ymm3
    vcvtdq2ps       %ymm3,      %ymm3
    #vpsrld          $0x17,      %ymm3,      %ymm3
    #vpsubq          %ymm0,      %ymm3,      %ymm3

    movq            0x18(%rsi), %xmm4
    vpmovzxbd       %xmm4,      %ymm4
    vcvtdq2ps       %ymm4,      %ymm4
    #vpsrld          $0x17,      %ymm4,      %ymm4
    #vpsubq          %ymm0,      %ymm4,      %ymm4

    vpackusdw       %ymm3,      %ymm1,      %ymm1
    vpermq          $0xD8,      %ymm1,      %ymm1

    vpackusdw       %ymm4,      %ymm2,      %ymm2
    vpermq          $0xD8,      %ymm2,      %ymm2

    vpackuswb       %ymm2,      %ymm1,      %ymm1

    vmovdqa         %ymm1,      (%rsi)
  

    movq            0x00(%rdx), %xmm1
    vpmovzxbd       %xmm1,      %ymm1
    vcvtdq2ps       %ymm1,      %ymm1
    #vpsrld          $0x17,      %ymm1,      %ymm1
    #vpsubq          %ymm0,      %ymm1,      %ymm1

    movq            0x08(%rdx), %xmm2
    vpmovzxbd       %xmm2,      %ymm2
    vcvtdq2ps       %ymm2,      %ymm2
    #vpsrld          $0x17,      %ymm2,      %ymm2
    #vpsubq          %ymm0,      %ymm2,      %ymm2

    movq            0x10(%rdx), %xmm3
    vpmovzxbd       %xmm3,      %ymm3
    vcvtdq2ps       %ymm3,      %ymm3
    #vpsrld          $0x17,      %ymm3,      %ymm3
    #vpsubq          %ymm0,      %ymm3,      %ymm3

    movq            0x18(%rdx), %xmm4
    vpmovzxbd       %xmm4,      %ymm4
    vcvtdq2ps       %ymm4,      %ymm4
    #vpsrld          $0x17,      %ymm4,      %ymm4
    #vpsubq          %ymm0,      %ymm4,      %ymm4

    vpackusdw       %ymm3,      %ymm1,      %ymm1
    vpermq          $0xD8,      %ymm1,      %ymm1

    vpackusdw       %ymm4,      %ymm2,      %ymm2
    vpermq          $0xD8,      %ymm2,      %ymm2

    vpackuswb       %ymm2,      %ymm1,      %ymm1

    vmovdqa         %ymm1,      (%rdx) 

    ret
