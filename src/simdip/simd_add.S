.global avx2_add_8bpc
.global avx512_add_8bpc

avx2_add_8bpc:
    vmovd           %ecx,       %xmm0
    vpbroadcastb    %xmm0,      %ymm0

    vmovdqa         0x00(%rdi), %ymm1
    vpaddb          %ymm0,      %ymm1,      %ymm1
    vmovdqa         %ymm1,      0x00(%rdi)

    vmovdqa         0x00(%rsi), %ymm1
    vpaddb          %ymm0,      %ymm1,      %ymm1
    vmovdqa         %ymm1,      0x00(%rsi)

    vmovdqa         0x00(%rdx), %ymm1
    vpaddb          %ymm0,      %ymm1,      %ymm1
    vmovdqa         %ymm1,      0x00(%rdx)

    vmovdqa         0x20(%rdi), %ymm1
    vpaddb          %ymm0,      %ymm1,      %ymm1
    vmovdqa         %ymm1,      0x20(%rdi)

    vmovdqa         0x20(%rsi), %ymm1
    vpaddb          %ymm0,      %ymm1,      %ymm1
    vmovdqa         %ymm1,      0x20(%rsi)

    vmovdqa         0x20(%rdx), %ymm1
    vpaddb          %ymm0,      %ymm1,      %ymm1
    vmovdqa         %ymm1,      0x20(%rdx)

    ret

avx512_add_8bpc:
    vpbroadcastb    %ecx,       %zmm0

    vmovdqa32       (%rdi),     %zmm1
    vpaddb          %zmm0,      %zmm1,      %zmm1
    vmovdqa32       %zmm1,      (%rdi)

    vmovdqa32       (%rsi),     %zmm1
    vpaddb          %zmm0,      %zmm1,      %zmm1
    vmovdqa32       %zmm1,      (%rsi)

    vmovdqa32       (%rdx),     %zmm1
    vpaddb          %zmm0,      %zmm1,      %zmm1
    vmovdqa32       %zmm1,      (%rdx)

    ret
