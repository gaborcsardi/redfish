
#' @useDynLib redfish, .registration=TRUE
NULL

make <- function(seq) {
  .Call(make_fish, seq)
}

.onLoad <- function(libname, pkgname) {
  .GlobalEnv$callback <- callback
}

callback <- function() {
  loadNamespace("Matrix")
}

fail <- function() {
  let5 <- letters[1:5]
  lapply(make(let5), function(i) {
    print(i)
  })
}
