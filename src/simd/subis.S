.global avx2_subis_8bpc
.global avx512_subis_8bpc

avx2_subis_8bpc:
    vmovd           %rdi,       %xmm15
    vpbroadcastb    %xmm15,     %ymm15

    vpsubusb        %ymm0,      %ymm15,     %ymm0
    vpsubusb        %ymm1,      %ymm15,     %ymm1
    vpsubusb        %ymm2,      %ymm15,     %ymm2
    vpsubusb        %ymm3,      %ymm15,     %ymm3
    vpsubusb        %ymm4,      %ymm15,     %ymm4
    vpsubusb        %ymm5,      %ymm15,     %ymm5

    ret

avx512_subis_8bpc:
    ret
