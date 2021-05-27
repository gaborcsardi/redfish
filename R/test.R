
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
  cli::cli_text("So far so good: {foo}", .envir = env)
}

fail <- function() {
  let5 <- letters[1:5]
  lapply(make(let5), function(i) {
    download.file(let5[i], tempfile())
  })
}

simple_callback <- function() {
  foo <- "bar"
  .Call(fish_update, environment())
}
