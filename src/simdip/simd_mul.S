.global avx2_mul_8bpc
.global avx512_mul_8bpc

avx2_mul_8bpc:
    vmovd           %edi,       %xmm15
    vpbroadcastw    %xmm15,     %ymm15
    
# RED CHANNEL
    vpermq          $0x08,      %ymm0,      %ymm6
    vpermq          $0x0D,      %ymm0,      %ymm7

    vpmovzxbw       %xmm6,      %ymm6
    vpmovzxbw       %xmm7,      %ymm7
    
    vpmullw         %ymm15,     %ymm6,      %ymm6
    vpmullw         %ymm15,     %ymm7,      %ymm7
    vpackuswb       %ymm7,      %ymm6,      %ymm0

    vpermq          $0x08,      %ymm1,      %ymm6
    vpermq          $0x0D,      %ymm1,      %ymm7

    vpmovzxbw       %xmm6,      %ymm6
    vpmovzxbw       %xmm7,      %ymm7
    
    vpmullw         %ymm15,     %ymm6,      %ymm6
    vpmullw         %ymm15,     %ymm7,      %ymm7
    vpackuswb       %ymm7,      %ymm6,      %ymm1


# BLUE CHANNEL
    vpermq          $0x08,      %ymm2,      %ymm6
    vpermq          $0x0D,      %ymm2,      %ymm7

    vpmovzxbw       %xmm6,      %ymm6
    vpmovzxbw       %xmm7,      %ymm7
    
    vpmullw         %ymm15,     %ymm6,      %ymm6
    vpmullw         %ymm15,     %ymm7,      %ymm7
    vpackuswb       %ymm7,      %ymm6,      %ymm2

    vpermq          $0x08,      %ymm3,      %ymm6
    vpermq          $0x0D,      %ymm3,      %ymm7

    vpmovzxbw       %xmm6,      %ymm6
    vpmovzxbw       %xmm7,      %ymm7
    
    vpmullw         %ymm15,     %ymm6,      %ymm6
    vpmullw         %ymm15,     %ymm7,      %ymm7
    vpackuswb       %ymm7,      %ymm6,      %ymm3


# GREEN CHANNEL
    vpermq          $0x08,      %ymm4,      %ymm6
    vpermq          $0x0D,      %ymm4,      %ymm7

    vpmovzxbw       %xmm6,      %ymm6
    vpmovzxbw       %xmm7,      %ymm7
    
    vpmullw         %ymm15,     %ymm6,      %ymm6
    vpmullw         %ymm15,     %ymm7,      %ymm7
    vpackuswb       %ymm7,      %ymm6,      %ymm4

    vpermq          $0x08,      %ymm5,      %ymm6
    vpermq          $0x0D,      %ymm5,      %ymm7

    vpmovzxbw       %xmm6,      %ymm6
    vpmovzxbw       %xmm7,      %ymm7
    
    vpmullw         %ymm15,     %ymm6,      %ymm6
    vpmullw         %ymm15,     %ymm7,      %ymm7
    vpackuswb       %ymm7,      %ymm6,      %ymm5
   
    ret

avx512_mul_8bpc:
    ret
