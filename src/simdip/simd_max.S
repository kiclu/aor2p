.global avx2_max_8bpc
.global avx512_max_8bpc

avx2_max_8bpc:
    vmovd           %edi,       %xmm15
    vpbroadcastb    %xmm15,     %ymm15

    vpmaxub         %ymm15,     %ymm0,      %ymm0
    vpmaxub         %ymm15,     %ymm1,      %ymm2

    vpmaxub         %ymm15,     %ymm2,      %ymm2
    vpmaxub         %ymm15,     %ymm3,      %ymm3

    vpmaxub         %ymm15,     %ymm4,      %ymm4
    vpmaxub         %ymm15,     %ymm5,      %ymm5

    ret

avx512_max_8bpc:
    ret
