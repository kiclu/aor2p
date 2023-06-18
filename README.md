# AOR2p
## 1. Description

## 2. Functions / command line arguments
### 2.1. Basic arithmetic operations
**2.1.1.  Arithmetic add**\
`px[r,g,b] <= px[r,g,b] + c`\
\
`-a=const.` / `--add=const.`
___
**2.1.2.  Arithmetic sub**\
`px[r,g,b] <= px[r,g,b] - c`\
\
`-s=const.` / `--sub=const.`
___
**2.1.3.  Arithmetic inverse sub**\
`px[r,g,b] <= c - px[r,g,b]`\
\
`-is=const.` / `-isub=const.`
___
**2.1.4.  Arithmetic mul**\
`px[r,g,b] <= px[r,g,b] * c`\
\
`-m=const.` / `--mul=const.`
___
**2.1.5.  Arithmetic div**\
`px[r,g,b] <= px[r,g,b] / c`\
\
`-d=const.` / `--div=const.`
___
**2.1.7.  Arithmetic inverse div**\
`px[r,g,b] <= c / px[r,g,b]`\
\
`-id=const.` / `--idiv=const.`
___
### 2.2. Arithmetic operations with saturation
**2.2.1. Add with saturation**\
`px[r,g,b] <= px[r,g,b] + c > PX_MAX ? PX_MAX : px[r,g,b] + c`\
\
`-as=const.` / `--add-saturate=const.`
___
**2.2.2. Sub with saturation**\
`px[r,g,b] <= px[r,g,b] - c < 0 ? 0 : px[r,g,b] - c`\
\
`-ss=const.` / `--sub-saturate=const.`
___
**2.2.3. Inverse sub with saturation**\
`px[r,g,b] <= c - px[r,g,b] < 0 ? 0 : c - px[r,g,b]`\
\
`-iss=const.` / `--isub-saturate=const.`
___
### 2.3. Misc arithmetic operations
**2.3.1.  Pow**\
`px[r,g,b] <= px[r,g,b]**c`\
\
`-p=const.` / `--pow=const.`
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
`--min=const.`
___
**2.3.5.  Max**\
`px[r,g,b] <= max(px[r,g,b], c)`\
\
`--max=const.`
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
### 2.6. File operations
`-o=output_file`
### 2.7. Optimization level
`--no-pipeline`\
`--no-simd`\
`-s0` - no optimizations\
`-s2` - SIMD, no pipeline\
`-s3` - SIMD & pipeline, default
## 3. TODO
- [ ] implement kern
- [ ] implement min/max
- [ ] implement mul
- [ ] implement subis
