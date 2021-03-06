
#include <R_ext/Rdynload.h>
#include <Rversion.h>
#include <Rinternals.h>
#include <R_ext/Altrep.h>

R_altrep_class_t red_fish_t;

SEXP make_fish(SEXP seq) {
  SEXP val = R_new_altrep(red_fish_t, seq, R_NilValue);
  return val;
}

R_xlen_t red_fish_Length(SEXP x) {
  SEXP data1 = R_altrep_data1(x);
  return XLENGTH(data1);
}

SEXP red_fish_Duplicate(SEXP x, Rboolean deep) {
  SEXP data1 = R_altrep_data1(x);
  return make_fish(duplicate(data1));
}

Rboolean red_fish_Inspect(SEXP x,
                          int pre,
                          int deep,
                          int pvec,
                          void (*inspect_subtree)(SEXP, int, int, int)) {
  
  Rprintf(" red_fish %s\n", type2char(TYPEOF(x)));
  return FALSE;
}

void* red_fish_Dataptr(SEXP x, Rboolean writeable) {
  SEXP data1 = R_altrep_data1(x);
  if (writeable) {
    return DATAPTR(data1);
  } else {
    return (void*) DATAPTR_RO(data1);
  }
}

const void* red_fish_Dataptr_or_null(SEXP x) {
  SEXP data1 = R_altrep_data1(x);
  return DATAPTR_OR_NULL(data1);
}

SEXP fish_update() {
  SEXP call = PROTECT(Rf_lang1(Rf_install("callback")));
  SEXP res = PROTECT(Rf_eval(call, R_GlobalEnv));
  UNPROTECT(2);
  return res;
}

int red_fish_Elt(SEXP x, R_xlen_t i) {
  fish_update();
  return 1;
}

static void init_altrep(DllInfo *dll) {
  R_altrep_class_t cls = R_make_altinteger_class("red_fish_t", "redfish", dll);
  red_fish_t = cls;

  R_set_altrep_Duplicate_method(red_fish_t, red_fish_Duplicate);
  R_set_altrep_Inspect_method(red_fish_t, red_fish_Inspect);
  R_set_altrep_Length_method(red_fish_t, red_fish_Length);

  // override ALTVEC methods
  R_set_altvec_Dataptr_method(red_fish_t, red_fish_Dataptr);
  R_set_altvec_Dataptr_or_null_method(red_fish_t, red_fish_Dataptr_or_null);

  // override ALTINTEGER methods
  R_set_altinteger_Elt_method(red_fish_t, red_fish_Elt);
  // R_set_altinteger_Get_region_method(red_fish_t, red_fish_Get_region);
  // R_set_altinteger_Sum_method(red_fish_t, red_fish_Sum);
  // R_set_altinteger_Max_method(red_fish_t, red_fish_Max);
  // R_set_altinteger_Min_method(red_fish_t, red_fish_Min);
  // R_set_altinteger_No_NA_method(red_fish_t, red_fish_No_NA);
  // R_set_altinteger_Is_sorted_method(red_fish_t, red_fish_Is_sorted);  
}

static const R_CallMethodDef callMethods[]  = {
  { "make_fish",   (DL_FUNC) make_fish,   1 },
  { NULL, NULL, 0 }
};


void R_init_redfish(DllInfo *dll) {
  init_altrep(dll);
  R_registerRoutines(dll, NULL, callMethods, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
  R_forceSymbols(dll, TRUE);
}
