.global avx2_adds_8bpc
.global avx512_adds_8bpc

avx2_adds_8bpc:
    vmovd           %rdi,       %xmm15
    vpbroadcastb    %xmm15,     %ymm15

    vpaddusb        %ymm15,     %ymm0,      %ymm0
    vpaddusb        %ymm15,     %ymm1,      %ymm1
    vpaddusb        %ymm15,     %ymm2,      %ymm2
    vpaddusb        %ymm15,     %ymm3,      %ymm3
    vpaddusb        %ymm15,     %ymm4,      %ymm4
    vpaddusb        %ymm15,     %ymm5,      %ymm5

    ret

avx512_adds_8bpc:
    ret
