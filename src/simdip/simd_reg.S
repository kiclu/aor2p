.global avx2_reg_load_8bpc
.global avx2_reg_store_8bpc
.global avx512_reg_load_8bpc
.global avx512_reg_store_8bpc

avx2_reg_load_8bpc:
    vmovdqa     0x00(%rdi), %ymm0
    vmovdqa     0x20(%rdi), %ymm1

    vmovdqa     0x00(%rsi), %ymm2
    vmovdqa     0x20(%rsi), %ymm3

    vmovdqa     0x00(%rdx), %ymm4
    vmovdqa     0x20(%rdx), %ymm5
    
    ret

avx2_reg_store_8bpc:
    vmovdqa     %ymm0,  0x00(%rdi)
    vmovdqa     %ymm1,  0x20(%rdi)

    vmovdqa     %ymm2,  0x00(%rsi)
    vmovdqa     %ymm3,  0x20(%rsi)

    vmovdqa     %ymm4,  0x00(%rdx)
    vmovdqa     %ymm5,  0x20(%rdx)

    ret

avx512_reg_load_8bpc:
    ret

avx512_reg_store_8bpc:
    ret
