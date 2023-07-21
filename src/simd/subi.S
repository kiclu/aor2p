.global avx2_subi_8bpc
.global avx512_subi_8bpc

avx2_subi_8bpc:
    vmovd           %rdi,       %xmm15
    vpbroadcastb    %xmm15,     %ymm15

    vpsubb          %ymm0,      %ymm15,     %ymm0
    vpsubb          %ymm1,      %ymm15,     %ymm1
    vpsubb          %ymm2,      %ymm15,     %ymm2
    vpsubb          %ymm3,      %ymm15,     %ymm3
    vpsubb          %ymm4,      %ymm15,     %ymm4
    vpsubb          %ymm5,      %ymm15,     %ymm5

    ret

avx512_subi_8bpc:
    ret
