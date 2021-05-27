
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
  cli::cli_alert_success("So far so good")
}

fail <- function() {
  let5 <- letters[1:2]
  lapply(make(let5), function(i) {
    typeof(i)
  })
}

simple_callback <- function() {
  foo <- "bar"
  .Call(fish_update, environment())
}
