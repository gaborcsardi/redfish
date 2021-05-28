
# Demonstrate a crash with R ALTREP

Either an ALTREP bug, or possibly I am doing something wrong.

## How to reproduce

This happens with every R version with ALTREP support, from 3.5.0 to
4.2.0 (current R-devel). This is macOS Mojave, if that matters.

1. Install the redfish package. (`load_all()` tends not to crash.)

2. Run `redfish:::fail()` from the command line:

```
❯ R-4.2 -q --vanilla -e 'sessionInfo(); redfish:::fail()'
> sessionInfo(); redfish:::fail()
R Under development (unstable) (2021-05-04 r80261)
Platform: x86_64-apple-darwin17.0 (64-bit)
Running under: macOS Mojave 10.14.6

Matrix products: default
BLAS:   /Library/Frameworks/R.framework/Versions/4.2/Resources/lib/libRblas.dylib
LAPACK: /Library/Frameworks/R.framework/Versions/4.2/Resources/lib/libRlapack.dylib

locale:
[1] en_US.UTF-8/en_US.UTF-8/en_US.UTF-8/C/en_US.UTF-8/en_US.UTF-8

attached base packages:
[1] stats     graphics  grDevices utils     datasets  methods   base

loaded via a namespace (and not attached):
[1] compiler_4.2.0
[1]
 *** caught segfault ***
address 0x7fed00000001, cause 'memory not mapped'

Traceback:
 1: print.default(i)
 2: print(i)
 3: FUN(X[[i]], ...)
 4: lapply(make(let5), function(i) {    print(i)})
 5: redfish:::fail()
An irrecoverable exception occurred. R is aborting now ...
zsh: segmentation fault  R-4.2 -q --vanilla -e 'sessionInfo(); redfish:::fail()'
```

Sometimes there is no crash, but the first element of the indexed vector
is corrupted:

```
❯ R-4.2 -q --vanilla -e 'redfish:::fail()'
> redfish:::fail()
[1] TRUE
[1] 1
[1] 1
[1] 1
[1] 1
[[1]]
[1] TRUE

[[2]]
[1] 1

[[3]]
[1] 1

[[4]]
[1] 1

[[5]]
[1] 1
```

