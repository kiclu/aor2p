.global avx2_min_8bpc
.global avx512_min_8bpc

avx2_min_8bpc:
    vmovd           %edi,       %xmm15
    vpbroadcastb    %xmm15,     %ymm15

    vpminub         %ymm15,     %ymm0,      %ymm0
    vpminub         %ymm15,     %ymm1,      %ymm2

    vpminub         %ymm15,     %ymm2,      %ymm2
    vpminub         %ymm15,     %ymm3,      %ymm3

    vpminub         %ymm15,     %ymm4,      %ymm4
    vpminub         %ymm15,     %ymm5,      %ymm5

    ret

avx512_min_8bpc:
    ret
