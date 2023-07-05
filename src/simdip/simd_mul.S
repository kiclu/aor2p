.global avx2_mul_8bpc
.global avx512_mul_8bpc

avx2_mul_8bpc:
    vmovd           %edi,       %xmm15
    vpbroadcastw    %xmm15,     %ymm15
    
# RED CHANNEL
    vpermq          $0x08,      %ymm0,      %ymm6
    vpermq          $0x0D,      %ymm0,      %ymm7
    vpermq          $0x08,      %ymm1,      %ymm8
    vpermq          $0x0D,      %ymm1,      %ymm9

    vpmovzxbw       %xmm6,      %ymm6
    vpmovzxbw       %xmm7,      %ymm7
    vpmovzxbw       %xmm8,      %ymm8
    vpmovzxbw       %xmm9,      %ymm9

    vpmullw         %ymm15,     %ymm6,      %ymm6
    vpmullw         %ymm15,     %ymm7,      %ymm7
    vpmullw         %ymm15,     %ymm8,      %ymm8
    vpmullw         %ymm15,     %ymm9,      %ymm9

    vpackuswb       %ymm7,      %ymm6,      %ymm0
    vpackuswb       %ymm9,      %ymm8,      %ymm1


# BLUE CHANNEL
    vpermq          $0x08,      %ymm2,      %ymm10
    vpermq          $0x0D,      %ymm2,      %ymm11
    vpermq          $0x08,      %ymm3,      %ymm12
    vpermq          $0x0D,      %ymm3,      %ymm13

    vpmovzxbw       %xmm10,     %ymm10
    vpmovzxbw       %xmm11,     %ymm11
    vpmovzxbw       %xmm12,     %ymm12
    vpmovzxbw       %xmm13,     %ymm13

    vpmullw         %ymm15,     %ymm10,     %ymm10
    vpmullw         %ymm15,     %ymm11,     %ymm11
    vpmullw         %ymm15,     %ymm12,     %ymm12
    vpmullw         %ymm15,     %ymm13,     %ymm13

    vpackuswb       %ymm11,     %ymm10,     %ymm2
    vpackuswb       %ymm13,     %ymm12,     %ymm3


# GREEN CHANNEL
    vpermq          $0x08,      %ymm4,      %ymm6
    vpermq          $0x0D,      %ymm4,      %ymm7
    vpermq          $0x08,      %ymm5,      %ymm8
    vpermq          $0x0D,      %ymm5,      %ymm9

    vpmovzxbw       %xmm6,      %ymm6
    vpmovzxbw       %xmm7,      %ymm7
    vpmovzxbw       %xmm8,      %ymm8
    vpmovzxbw       %xmm9,      %ymm9

    vpmullw         %ymm15,     %ymm6,      %ymm6
    vpmullw         %ymm15,     %ymm7,      %ymm7
    vpmullw         %ymm15,     %ymm8,      %ymm8
    vpmullw         %ymm15,     %ymm9,      %ymm9

    vpackuswb       %ymm7,      %ymm6,      %ymm4
    vpackuswb       %ymm9,      %ymm8,      %ymm5

  
    ret

avx512_mul_8bpc:
    ret
