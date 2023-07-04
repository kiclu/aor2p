.global avx2_sub_8bpc

avx2_sub_8bpc:
    vmovd           %ecx,       %xmm0
    vpbroadcastb    %xmm0,      %ymm0

    vmovdqa         0x00(%rdi), %ymm1
    vpsubb          %ymm0,      %ymm1,      %ymm1
    vmovdqa         %ymm1,      0x00(%rdi)

    vmovdqa         0x00(%rsi), %ymm1
    vpsubb          %ymm0,      %ymm1,      %ymm1
    vmovdqa         %ymm1,      0x00(%rsi)

    vmovdqa         0x00(%rdx), %ymm1
    vpsubb          %ymm0,      %ymm1,      %ymm1
    vmovdqa         %ymm1,      0x00(%rdx)

    vmovdqa         0x20(%rdi), %ymm1
    vpsubb          %ymm0,      %ymm1,      %ymm1
    vmovdqa         %ymm1,      0x20(%rdi)

    vmovdqa         0x20(%rsi), %ymm1
    vpsubb          %ymm0,      %ymm1,      %ymm1
    vmovdqa         %ymm1,      0x20(%rsi)

    vmovdqa         0x20(%rdx), %ymm1
    vpsubb          %ymm0,      %ymm1,      %ymm1
    vmovdqa         %ymm1,      0x20(%rdx)

    ret
