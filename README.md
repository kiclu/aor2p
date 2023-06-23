# AOR2p
## 1. Description

## 2. Functions / command line arguments
Usage: `./aor2p input-file [options]`
### 2.1. Basic arithmetic operations
**2.1.1.  Arithmetic add**\
`px[r,g,b] <= px[r,g,b] + c`\
\
`-a=<const>` / `--add=<const>`
___
**2.1.2.  Arithmetic sub**\
`px[r,g,b] <= px[r,g,b] - c`\
\
`-s=<const>` / `--sub=<const>`
___
**2.1.3.  Arithmetic inverse sub**\
`px[r,g,b] <= c - px[r,g,b]`\
\
`-is=<const>` / `--isub=<const>`
___
**2.1.4.  Arithmetic mul**\
`px[r,g,b] <= px[r,g,b] * c`\
\
`-m=<const>` / `--mul=<const>`
___
**2.1.5.  Arithmetic div**\
`px[r,g,b] <= px[r,g,b] / c`\
\
`-d=<const>` / `--div=<const>`
___
**2.1.7.  Arithmetic inverse div**\
`px[r,g,b] <= c / px[r,g,b]`\
\
`-id=<const>` / `--idiv=<const>`
___
### 2.2. Arithmetic operations with saturation
**2.2.1. Add with saturation**\
`px[r,g,b] <= px[r,g,b] + c > PX_MAX ? PX_MAX : px[r,g,b] + c`\
\
`-as=<const>` / `--add-saturate=<const>`
___
**2.2.2. Sub with saturation**\
`px[r,g,b] <= px[r,g,b] - c < 0 ? 0 : px[r,g,b] - c`\
\
`-ss=<const>` / `--sub-saturate=<const>`
___
**2.2.3. Inverse sub with saturation**\
`px[r,g,b] <= c - px[r,g,b] < 0 ? 0 : c - px[r,g,b]`\
\
`-iss=<const>` / `--isub-saturate=<const>`
___
### 2.3. Misc arithmetic operations
**2.3.1.  Pow**\
`px[r,g,b] <= px[r,g,b]**c`\
\
`-p=<const>` / `--pow=<const>`
___
**2.3.2.  Log**\
`px[r,g,b] <= log2(px[r,g,b])`\
\
`-l` / `--log`
___
**2.3.3.  Abs**\
`px[r,g,b] <= abs(px[r,g,b])`\
\
`--abs`
___
**2.3.4.  Min**\
`px[r,g,b] <= min(px[r,g,b], c)`\
\
`--min=<const>`
___
**2.3.5.  Max**\
`px[r,g,b] <= max(px[r,g,b], c)`\
\
`--max=<const>`
___
### 2.4. Image processing
**2.4.1.  Negative**\
`px[r,g,b] <= PX_MAX - px[r,g,b]`\
\
`-n` / `--neg`
___
**2.4.2.  Greyscale**\
`px[r,g,b] <= 0.299 * px[r] + 0.587 * px[g] + 0.114 * px[b]`\
\
`-gs` / `--greyscale`
___
### 2.5. Kernel filtering
//
___
### 2.6. File operations
`-o=<file>`
___
### 2.7. Optimization level
`--no-pipeline`\
`--no-simd`\
`-s0` - no optimizations\
`-s2` - SIMD, no pipeline\
`-s3` - SIMD & pipeline, default
## 3. Performance
Time taken for a single operation on 1280x838 sample image, averaged over 10 tests.

| op      | t avg simd[ns] | t avg nosimd[ns] | relative |
| ------- | -------------- | ---------------- | -------- |
| add     | 208,966        | 9,048,538        |  43.30x  |
| sub     | 234,554        | 9,139,344        |  38.96x  |
| subi    | 167,414        | 7,725,080        |  46.14x  |
| mul     | 242,342        | 8,503,376        |  35.09x  |
| div     | 527,300        | 15,933,050       |  30.22x  |
| divi    | 560,900        | 13,873,760       |  24.73x  |
| adds    | 198,910        | 8,159,120        |  41.02x  |
| subs    | 187,672        | 8,236,660        |  43.89x  |
| subis   | 177,922        | 6,982,600        |  39.25x  |
| pow     | 244,310        | 59,400,760       | 243.14x  |
| log     | 467,486        | 27,075,790       |  57.92x  |
| abs     | 199,296        | 7,703,620        |  38.65x  |
| min     | 204,034        | 6,366,710        |  31.20x  |
| max     | 181,212        | 6,475,020        |  35.73x  |
| neg     | 192,072        | 7,619,170        |  39.67x  |
| gs      | 465,720        | 8,371,089        |  17.97x  |
| kern3x3 | 7,548,670      | 28,859,810       |   3.82x  |
| kern5x5 | 14,156,100     | 71,436,110       |   5.05x  |
___
Belgrade, June 2023.