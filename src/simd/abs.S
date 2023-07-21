.global avx2_abs_8bpc
.global avx512_abs_8bpc

avx2_abs_8bpc:
    vpabsb          %ymm0,      %ymm0
    vpabsb          %ymm1,      %ymm1
    vpabsb          %ymm2,      %ymm2
    vpabsb          %ymm3,      %ymm3
    vpabsb          %ymm4,      %ymm4
    vpabsb          %ymm5,      %ymm5

    ret

avx512_abs_8bpc:
    ret
