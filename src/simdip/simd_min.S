.global simd_min_8bpc

simd_min_8bpc:
    vmovd           %ecx,   %xmm0
    vpbroadcastb    %xmm0,  %ymm0

    vmovdqa         (%rdi), %ymm1
    vpminub         %ymm0,  %ymm1,  %ymm1
    vmovdqa         %ymm1,  (%rdi)

    vmovdqa         (%rsi), %ymm1
    vpminub         %ymm0,  %ymm1,  %ymm1
    vmovdqa         %ymm1,  (%rsi)

    vmovdqa         (%rdx), %ymm1
    vpminub         %ymm0,  %ymm1,  %ymm1
    vmovdqa         %ymm1,  (%rdx)

    ret
