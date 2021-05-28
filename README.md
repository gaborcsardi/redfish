
# Demonstrate a crash with R ALTREP

Either an ALTREP bug, or possibly I am doing something wrong.

## How to reproduce

This happens with every R version with ALTREP support, from 3.5.0 to
4.2.0 (current R-devel).

1. Install the refish package. (`load_all()` tends not to crash.)

2. Run `redfish:::fail()` from the command line:

```
❯ R-3.5 -q --vanilla -e 'redfish:::fail()'
> redfish:::fail()
[1]
 *** caught segfault ***
address 0x7fc400000001, cause 'memory not mapped'

Traceback:
 1: print.default(i)
 2: print(i)
 3: FUN(X[[i]], ...)
 4: lapply(make(let5), function(i) {    print(i)})
 5: redfish:::fail()
An irrecoverable exception occurred. R is aborting now ...
zsh: segmentation fault  R-3.5 -q --vanilla -e 'redfish:::fail()'
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
