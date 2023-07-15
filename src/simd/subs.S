.global avx2_subs_8bpc
.global avx512_subs_8bpc

avx2_subs_8bpc:
    vmovd           %edi,       %xmm15
    vpbroadcastb    %xmm15,     %ymm15

    vpsubusb        %ymm15,     %ymm0,      %ymm0
    vpsubusb        %ymm15,     %ymm1,      %ymm1

    vpsubusb        %ymm15,     %ymm2,      %ymm2
    vpsubusb        %ymm15,     %ymm3,      %ymm3

    vpsubusb        %ymm15,     %ymm4,      %ymm4
    vpsubusb        %ymm15,     %ymm5,      %ymm5

    ret

avx512_subs_8bpc:
    ret
