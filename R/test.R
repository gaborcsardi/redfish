
#' @useDynLib redfish, .registration=TRUE
NULL

make <- function(seq) {
  foo <- "bar"
  .Call(make_fish, seq_along(seq), environment())
}

.onLoad <- function(libname, pkgname) {
  .Call(fish_init, asNamespace("redfish"))
}

callback <- function(env) {
  cli::cli_verbatim("So far so good")
}

fail <- function() {
  let5 <- letters[1:5]
  lapply(make(let5), function(i) {
    print(i)
  })
}

simple_callback <- function() {
  foo <- "bar"
  .Call(fish_update, environment())
}
