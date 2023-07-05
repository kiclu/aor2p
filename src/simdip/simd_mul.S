.global simd_mul_8bpc

simd_mul_8bpc:
    # set broadcast constant c to YMM0
    vmovd           %ecx,       %xmm0
    vpbroadcastw    %xmm0,      %ymm0

    # red channel
    movdqu          0x00(%rdi), %xmm1
    pmovzxbw        %xmm1,      %xmm1

    movdqu          0x10(%rdi), %xmm2
    pmovzxbw        %xmm2,      %xmm2

    vinserti128     $0x01,      %xmm2,      %ymm1,      %ymm1
    vpmullw         %ymm0,      %ymm1,      %ymm1

    movdqu          0x08(%rdi), %xmm2
    pmovzxbw        %xmm2,      %xmm2

    movdqu          0x18(%rdi), %xmm3
    pmovzxbw        %xmm3,      %xmm3

    vinserti128     $0x01,      %xmm3,      %ymm2,      %ymm2
    vpmullw         %ymm0,      %ymm2,      %ymm2

    vpackuswb       %ymm2,      %ymm1,      %ymm1
    vmovdqa         %ymm1,      0x00(%rdi)

    movdqu          0x20(%rdi), %xmm4
    pmovzxbw        %xmm4,      %xmm4

    movdqu          0x30(%rdi), %xmm5
    pmovzxbw        %xmm5,      %xmm5

    vinserti128     $0x01,      %xmm5,      %ymm4,      %ymm4
    vpmullw         %ymm0,      %ymm4,      %ymm4

    movdqu          0x28(%rdi), %xmm5
    pmovzxbw        %xmm5,      %xmm5

    movdqu          0x38(%rdi), %xmm6
    pmovzxbw        %xmm6,      %xmm6

    vinserti128     $0x01,      %xmm6,      %ymm5,      %ymm5
    vpmullw         %ymm0,      %ymm5,      %ymm5

    vpackuswb       %ymm5,      %ymm4,      %ymm4
    vmovdqa         %ymm4,      0x20(%rdi)


    # green channel
    movdqu          0x00(%rsi), %xmm1
    pmovzxbw        %xmm1,      %xmm1

    movdqu          0x10(%rsi), %xmm2
    pmovzxbw        %xmm2,      %xmm2

    vinserti128     $0x01,      %xmm2,      %ymm1,      %ymm1
    vpmullw         %ymm0,      %ymm1,      %ymm1

    movdqu          0x08(%rsi), %xmm2
    pmovzxbw        %xmm2,      %xmm2

    movdqu          0x18(%rsi), %xmm3
    pmovzxbw        %xmm3,      %xmm3

    vinserti128     $0x01,      %xmm3,      %ymm2,      %ymm2
    vpmullw         %ymm0,      %ymm2,      %ymm2

    vpackuswb       %ymm2,      %ymm1,      %ymm1
    vmovdqa         %ymm1,      0x00(%rsi)

    movdqu          0x20(%rsi), %xmm4
    pmovzxbw        %xmm4,      %xmm4

    movdqu          0x30(%rsi), %xmm5
    pmovzxbw        %xmm5,      %xmm5

    vinserti128     $0x01,      %xmm5,      %ymm4,      %ymm4
    vpmullw         %ymm0,      %ymm4,      %ymm4

    movdqu          0x28(%rsi), %xmm5
    pmovzxbw        %xmm5,      %xmm5

    movdqu          0x38(%rsi), %xmm6
    pmovzxbw        %xmm6,      %xmm6

    vinserti128     $0x01,      %xmm6,      %ymm5,      %ymm5
    vpmullw         %ymm0,      %ymm5,      %ymm5

    vpackuswb       %ymm5,      %ymm4,      %ymm4
    vmovdqa         %ymm4,      0x20(%rsi)


   # blue channel
    movdqu          0x00(%rdx), %xmm1
    pmovzxbw        %xmm1,      %xmm1

    movdqu          0x10(%rdx), %xmm2
    pmovzxbw        %xmm2,      %xmm2

    vinserti128     $0x01,      %xmm2,      %ymm1,      %ymm1
    vpmullw         %ymm0,      %ymm1,      %ymm1

    movdqu          0x08(%rdx), %xmm2
    pmovzxbw        %xmm2,      %xmm2

    movdqu          0x18(%rdx), %xmm3
    pmovzxbw        %xmm3,      %xmm3

    vinserti128     $0x01,      %xmm3,      %ymm2,      %ymm2
    vpmullw         %ymm0,      %ymm2,      %ymm2

    vpackuswb       %ymm2,      %ymm1,      %ymm1
    vmovdqa         %ymm1,      0x00(%rdx)

    movdqu          0x20(%rdx), %xmm4
    pmovzxbw        %xmm4,      %xmm4

    movdqu          0x30(%rdx), %xmm5
    pmovzxbw        %xmm5,      %xmm5

    vinserti128     $0x01,      %xmm5,      %ymm4,      %ymm4
    vpmullw         %ymm0,      %ymm4,      %ymm4

    movdqu          0x28(%rdx), %xmm5
    pmovzxbw        %xmm5,      %xmm5

    movdqu          0x38(%rdx), %xmm6
    pmovzxbw        %xmm6,      %xmm6

    vinserti128     $0x01,      %xmm6,      %ymm5,      %ymm5
    vpmullw         %ymm0,      %ymm5,      %ymm5

    vpackuswb       %ymm5,      %ymm4,      %ymm4
    vmovdqa         %ymm4,      0x20(%rdx)


    ret
