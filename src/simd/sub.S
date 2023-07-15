.global avx2_sub_8bpc
.global avx512_sub_8bpc

avx2_sub_8bpc:
    vmovd           %edi,       %xmm15
    vpbroadcastb    %xmm15,     %ymm15

    vpsubb          %ymm15,     %ymm0,      %ymm0
    vpsubb          %ymm15,     %ymm1,      %ymm1

    vpsubb          %ymm15,     %ymm2,      %ymm2
    vpsubb          %ymm15,     %ymm3,      %ymm3

    vpsubb          %ymm15,     %ymm4,      %ymm4
    vpsubb          %ymm15,     %ymm5,      %ymm5

    ret

avx512_sub_8bpc:
    ret
