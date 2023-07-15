.global avx2_pow_8bpc
.global avx512_pow_8bpc

avx2_pow_8bpc:
    push            %rdi

    vpermq          $0x08,      %ymm0,      %ymm10
    vpmovzxbw       %xmm10,     %ymm10
    vpermq          $0x0D,      %ymm0,      %ymm11
    vpmovzxbw       %xmm11,     %ymm11
    vpermq          $0x08,      %ymm1,      %ymm12
    vpmovzxbw       %xmm12,     %ymm12
    vpermq          $0x0D,      %ymm1,      %ymm13
    vpmovzxbw       %xmm13,     %ymm13
    vpermq          $0x08,      %ymm2,      %ymm14
    vpmovzxbw       %xmm14,     %ymm14
    vpermq          $0x0D,      %ymm2,      %ymm15
    vpmovzxbw       %xmm15,     %ymm15

    mov             $0x01,      %rsi
    vmovd           %rsi,       %xmm0
    vpbroadcastw    %xmm0,      %ymm0

    vpxor           %ymm9,      %ymm9,      %ymm9

    vpaddw          %ymm9,      %ymm0,      %ymm1
    vpaddw          %ymm9,      %ymm0,      %ymm2
    vpaddw          %ymm9,      %ymm0,      %ymm6
    vpaddw          %ymm9,      %ymm0,      %ymm7
    vpaddw          %ymm9,      %ymm0,      %ymm8

    cmp             $0x00,      %rdi
    jle             loop_0_end

loop_0_start:

    mov             %rdi,       %rsi
    and             $0x01,      %rsi
    jz              skip_mul_0

    vpmullw         %ymm0,      %ymm10,     %ymm0
    vpmullw         %ymm6,      %ymm11,     %ymm6
    vpmullw         %ymm1,      %ymm12,     %ymm1
    vpmullw         %ymm7,      %ymm13,     %ymm7
    vpmullw         %ymm2,      %ymm14,     %ymm2
    vpmullw         %ymm8,      %ymm15,     %ymm8

skip_mul_0:

    vpmullw         %ymm10,     %ymm10,     %ymm10
    vpmullw         %ymm11,     %ymm11,     %ymm11
    vpmullw         %ymm12,     %ymm12,     %ymm12
    vpmullw         %ymm13,     %ymm13,     %ymm13
    vpmullw         %ymm14,     %ymm14,     %ymm14
    vpmullw         %ymm15,     %ymm15,     %ymm15
    
    shr             $0x01,      %rdi
    cmp             $0x00,      %rdi
    jne             loop_0_start

loop_0_end:

    vpackuswb       %ymm6,      %ymm0,      %ymm0
    vpackuswb       %ymm7,      %ymm1,      %ymm1
    vpackuswb       %ymm8,      %ymm2,      %ymm2

    pop             %rdi

    vpermq          $0x08,      %ymm3,      %ymm10
    vpmovzxbw       %xmm10,     %ymm10
    vpermq          $0x0D,      %ymm3,      %ymm11
    vpmovzxbw       %xmm11,     %ymm11
    vpermq          $0x08,      %ymm4,      %ymm12
    vpmovzxbw       %xmm12,     %ymm12
    vpermq          $0x0D,      %ymm4,      %ymm13
    vpmovzxbw       %xmm13,     %ymm13
    vpermq          $0x08,      %ymm5,      %ymm14
    vpmovzxbw       %xmm14,     %ymm14
    vpermq          $0x0D,      %ymm5,      %ymm15
    vpmovzxbw       %xmm15,     %ymm15

    mov             $0x01,      %rsi
    vmovd           %rsi,       %xmm3
    vpbroadcastw    %xmm3,      %ymm3

    vpaddw          %ymm9,      %ymm3,      %ymm4
    vpaddw          %ymm9,      %ymm3,      %ymm5
    vpaddw          %ymm9,      %ymm3,      %ymm6
    vpaddw          %ymm9,      %ymm3,      %ymm7
    vpaddw          %ymm9,      %ymm3,      %ymm8

    cmp             $0x00,      %rdi
    jle             loop_1_end

loop_1_start:

    mov             %rdi,       %rsi
    and             $0x01,      %rsi
    jz              skip_mul_1

    vpmullw         %ymm3,      %ymm10,     %ymm3
    vpmullw         %ymm6,      %ymm11,     %ymm6
    vpmullw         %ymm4,      %ymm12,     %ymm4
    vpmullw         %ymm7,      %ymm13,     %ymm7
    vpmullw         %ymm5,      %ymm14,     %ymm5
    vpmullw         %ymm8,      %ymm15,     %ymm8

skip_mul_1:

    vpmullw         %ymm10,     %ymm10,     %ymm10
    vpmullw         %ymm11,     %ymm11,     %ymm11
    vpmullw         %ymm12,     %ymm12,     %ymm12
    vpmullw         %ymm13,     %ymm13,     %ymm13
    vpmullw         %ymm14,     %ymm14,     %ymm14
    vpmullw         %ymm15,     %ymm15,     %ymm15
    
    shr             $0x01,      %rdi
    cmp             $0x00,      %rdi
    jne             loop_1_start

loop_1_end:

    vpackuswb       %ymm6,      %ymm3,      %ymm3
    vpackuswb       %ymm7,      %ymm4,      %ymm4
    vpackuswb       %ymm8,      %ymm5,      %ymm5

    ret
