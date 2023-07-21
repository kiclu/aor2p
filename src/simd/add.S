.global avx2_add_8bpc
.global avx512_add_8bpc

avx2_add_8bpc:
    vmovd           %rdi,       %xmm15
    vpbroadcastb    %xmm15,     %ymm15

    vpaddb          %ymm15,     %ymm0,      %ymm0
    vpaddb          %ymm15,     %ymm1,      %ymm1
    vpaddb          %ymm15,     %ymm2,      %ymm2
    vpaddb          %ymm15,     %ymm3,      %ymm3
    vpaddb          %ymm15,     %ymm4,      %ymm4
    vpaddb          %ymm15,     %ymm5,      %ymm5

    ret

avx512_add_8bpc:
    vpbroadcastb    %edi,       %zmm31

    vpaddb          %zmm31,     %zmm0,      %zmm0
    vpaddb          %zmm31,     %zmm1,      %zmm1
    vpaddb          %zmm31,     %zmm2,      %zmm2

    ret
